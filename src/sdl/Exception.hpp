#pragma once

#include <exception>
#include <sstream>
#include <stdexcept>
#include <string>

#include <SDL.h>

class EGenericError:public std::runtime_error
{
public:
    EGenericError(const char * const &what):
        std::runtime_error(what)
    {}
};

class ECannotCreateFont:public EGenericError
{
public:
    ECannotCreateFont(const char * const &what):
        EGenericError(what)
    {}
};

class SDLException : public std::runtime_error
{
public:
    SDLException(const std::string& _Message) :
        std::runtime_error(GetMessage(_Message))
    {};

private:
    std::string GetMessage(const std::string& message)
    {
        std::stringstream msg;
        msg << message << "SDL_Error: " << SDL_GetError();
        return msg.str();
    }
};
