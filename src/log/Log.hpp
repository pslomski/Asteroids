#pragma once

#include <SDL_log.h>

#define LOG_INF(fmt...) SDL_LogInfo(0, fmt)
#define LOG_ERR(fmt...) SDL_LogError(0, fmt)
