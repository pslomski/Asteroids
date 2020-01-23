#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <exception>
#include <stdexcept>
#include <string>
#include <sstream>
#include "SDL.h"

class EGenericError:public std::exception{
public:
	EGenericError(const char * const &what):exception(what){}
};

class ECannotCreateFont:public std::exception{
public:
	ECannotCreateFont(const char * const &what):exception(what){}
};

class SDLException : public std::runtime_error
{
private:
	std::string GetMessage(const std::string& _Message)
	{
		std::stringstream msg;
		msg << _Message << "SDL_Error: " << SDL_GetError();
		return msg.str();
	}

public:
	SDLException(const std::string& _Message) :
		std::runtime_error(GetMessage(_Message)) {};
};


#endif  // _EXCEPTION_H_