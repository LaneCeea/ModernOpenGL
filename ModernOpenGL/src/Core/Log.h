#ifndef CORE_LOG_H_
#define CORE_LOG_H_

#ifdef GLDEBUG
#define ERRORLOG(...)   Log(LogType::ERR,       __VA_ARGS__)
#define WARNINGLOG(...) Log(LogType::WARNING,   __VA_ARGS__)
#define INFOLOG(...)    Log(LogType::INFO,      __VA_ARGS__)

#else // ^^^ GLDEBUG ^^^ // vvv !GLDEBUG vvv
#define ERRORLOG(...)   (void)(__VA_ARGS__)
#define WARNINGLOG(...) (void)(__VA_ARGS__)
#define INFOLOG(...)    (void)(__VA_ARGS__)

#endif // GLDEBUG

enum class LogType {
    NONE = 0, ERR, WARNING, INFO,
};

void Log(LogType type, const char* format, ...);

#endif // !CORE_LOG_H_