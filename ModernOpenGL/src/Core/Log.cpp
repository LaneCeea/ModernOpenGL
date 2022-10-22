#include "Core/Log.h"

#include <cstdarg>
#include <cstdio>
#include <cstdint>

#include <Windows.h>

void Log(LogType type, const char* format, ...) {
    static HANDLE s_Console = GetStdHandle(STD_OUTPUT_HANDLE);
    static constexpr std::uint16_t red      = FOREGROUND_RED;
    static constexpr std::uint16_t yellow   = FOREGROUND_RED | FOREGROUND_GREEN;
    static constexpr std::uint16_t white    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    std::uint16_t text_color = 0;
    switch (type) {
    case LogType::ERR:      text_color = red;       break;
    case LogType::WARNING:  text_color = yellow;    break;
    case LogType::INFO:     text_color = white;     break;
    }
    SetConsoleTextAttribute(s_Console, text_color);

    std::va_list args;
    va_start(args, format);
    std::vprintf(format, args);
    va_end(args);
    SetConsoleTextAttribute(s_Console, white);
}