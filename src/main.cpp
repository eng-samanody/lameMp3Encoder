#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include "lame/lame.h"
#include <pthread.h>
#include <thread>
#include "Logger.h"

std::vector<std::string>* queue;
unsigned int ItemsCompleted = 0;

bool encodeToMp3(const std::string& inputWavFilePath) {
    bool retVal = false;
    const unsigned int PCM_SIZE = 144000, MP3_SIZE = 144000;
    short int pcm_buffer[PCM_SIZE * 2];
    unsigned char mp3_buffer[MP3_SIZE];
    lame_t lameGlobalFlags = lame_init();
    lame_set_in_samplerate(lameGlobalFlags, 44100);//Input files support is limited to 16 bit stereo WAV files, sample rate 44100
    lame_set_VBR(lameGlobalFlags, vbr_default); /* Types of VBR.  default = vbr_off = CBR */
    lame_set_VBR_q(lameGlobalFlags, 5);/* VBR quality level.  0=highest  9=lowest  */
    id3tag_init(lameGlobalFlags);
	std::cout<<"Encoding " << inputWavFilePath << " to MP3 Using LAME version " << get_lame_short_version() << std::endl;
    if (!(lame_init_params(lameGlobalFlags) < 0)) {
        std::string outputMp3FilePath(inputWavFilePath);
        outputMp3FilePath.replace((end(outputMp3FilePath) - 3), end(outputMp3FilePath), "mp3");
        std::ifstream wavInStream;
        std::ofstream mp3OutStream;
        try {
            wavInStream.open(inputWavFilePath, std::ios_base::binary);
            mp3OutStream.open(outputMp3FilePath, std::ios_base::binary);
        }
        catch (std::ifstream::failure &e) {
            std::cout << "Exception opening in/out streams" << e.what() << '\n';
            return false;
        }

        while (wavInStream.good()) {
            int wrtCount = 0;
            try{
                wavInStream.read(reinterpret_cast<char*>(pcm_buffer), sizeof(pcm_buffer));
            }
            catch (const std::exception& e){
                std::cout << "Exception wav.read : " << e.what() << '\n';
            }
            int rCount = wavInStream.gcount() / (2 * sizeof(short)); //Input files support is limited to 16 bit stereo WAV files, sample rate 44100
            if (rCount == 0) {
                wrtCount = lame_encode_flush(lameGlobalFlags, mp3_buffer, MP3_SIZE);
            } else {
                wrtCount = lame_encode_buffer_interleaved(lameGlobalFlags, pcm_buffer, rCount, mp3_buffer, MP3_SIZE);
            }
            mp3OutStream.write(reinterpret_cast<char*>(mp3_buffer), wrtCount);
        }

        wavInStream.close();
        mp3OutStream.close();
        lame_close(lameGlobalFlags);
        retVal = true;
    }

    return retVal;
}

std::vector<std::string> getWavFiles(std::string & inputDir)
{
    std::vector <std::string> foundWavFiles;
    auto GetFileSize = [](const std::string & filename) {
        struct stat statusBuffer;
        //int rc = stat(filename.c_str(), &statusBuffer);
        return (stat(filename.c_str(), &statusBuffer)) == 0 ? statusBuffer.st_size : -1;
    };

    auto * directory = opendir(inputDir.c_str());
    struct dirent * entry;
    entry = readdir(directory);
    while (entry != nullptr)
    {
        std::string filePath((entry->d_name));
        auto pos = filePath.rfind(".wav");
        auto inFilePath = inputDir + "/" + entry->d_name;
        if ((pos != std::string::npos) && (pos == filePath.length() - 4)) {
            
            if (GetFileSize(inFilePath) > 0) {
                foundWavFiles.push_back(inFilePath);
                static int i = 0;
               Logger::logColored(Logger::tEnuColors::GREEN,">> Found file " , i++ , " : " , inFilePath );
            } else {
                Logger::logColored(Logger::tEnuColors::RED, ">> Ignored : " , inFilePath );
            }
        } else {
            Logger::logColored(Logger::tEnuColors::RED, ">> Ignored : ", inFilePath);
        }
        entry = readdir(directory);
    }
	closedir(directory);
    return foundWavFiles;
}

void* ThreadFunction(void *arg){
	pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
    while (1) {
        pthread_mutex_lock(&queue_mutex);
        if (queue->empty()) {
            pthread_mutex_unlock(&queue_mutex);
            break;
        }
        std::string cur(queue->back());
        queue->pop_back();
        pthread_mutex_unlock(&queue_mutex);
        if (encodeToMp3(cur)){
            ItemsCompleted++;
		}
    }
    return nullptr;
}

void createThreadPool (std::vector<std::string> files){
	const int MAX_Threads = std::thread::hardware_concurrency();
	int filesCount = files.size();
	const int POSSIBLE_ThreadsCount = std::min(filesCount, MAX_Threads);
	std::vector <pthread_t> vectorOfThreads;
	std::cout<<"CPU Threading Capacity : " << MAX_Threads << std::endl;
	std::cout<<"Number of Files : " << filesCount << std::endl;
	std::cout<<"Number of Possible Threads : " << POSSIBLE_ThreadsCount << std::endl;
	vectorOfThreads.resize(POSSIBLE_ThreadsCount);
	queue = &files;
	for (auto &thread: vectorOfThreads) {
		auto result = pthread_create(&thread, nullptr, ThreadFunction, nullptr);
		switch (result) {
		case 0:
			break;
		case EAGAIN:
            throw std::runtime_error("**failed to create thread due to Insufficient resources**");
			break;
        case EPERM:
            throw std::runtime_error("**failed to create thread due to Insufficitent permissions**");
            break;
		case EINVAL:
            throw std::runtime_error("**failed to create thread due to Invalid settings**");
			break;
		default:
            throw std::runtime_error("**!!!UNKNOWN ERROR!!!**");
            break;
		}

	}
	
	for (auto thread: vectorOfThreads) {
        pthread_join(thread, nullptr);
    }
    Logger::logColored(Logger::tEnuColors::GREEN, "Successfully processed: " , ItemsCompleted , "/" , filesCount , " items" );
}

int main(int argc, char* argv[])
{

	if (argc == 2) {
		std::string inputDirPath(argv[1]);
		std::vector<std::string> wavFiles = getWavFiles(inputDirPath);
		if(wavFiles.size()){
            try {
                createThreadPool(wavFiles);
            } catch (const std::exception & e) {
                Logger::logColored( Logger::tEnuColors::RED, "**ERR** THREAD CREATE FAILED : " , e.what() );
            }
		} else {
            Logger::logColored( Logger::tEnuColors::RED, "**ERR** NO .WAV FILES FOUND" );
		}
	} else {
        Logger::logColored( Logger::tEnuColors::RED, "**ERR** USAGE ERROR > Please try : " , argv[0] , " <in/out directory>" );
	}
}