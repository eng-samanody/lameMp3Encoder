#pragma once
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
/*"WINDOWS"*/
#include <windows.h>
#elif __linux__
/* "LINUX" */
#else
#   error "Unknown compiler"
#endif

class Logger{
    public :
		enum class tEnuColors {
			RESET, //7
			RED, //4
			GREEN, //2
		};
    public :
		
        static void setColor(tEnuColors color);
		
        static void log() {
            std::cout << std::endl;
        }
		template < typename T, typename... Types>
		static void log( T msg, Types... msgs) {
			std::cout << msg;
			log(msgs...);			
		}
		template < typename TC, typename T, typename... Types>
		static void logColored(TC color, T msg, Types... msgs) {
			setColor(static_cast<tEnuColors>(color));
			log(msg, msgs...);	
			setColor(tEnuColors::RESET);
		}
		
};