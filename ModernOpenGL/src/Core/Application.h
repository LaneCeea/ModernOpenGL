#ifndef CORE_APPLICATION_H_
#define CORE_APPLICATION_H_

#include <memory>

#include "Core/Window.h"

class Application {
public:
    static Application& get() {
        static Application s_Instance;
        return s_Instance;
    }

    void run();

    inline Window& getWindow() {
        return *m_Window;
    }

    Application(const Application&)             = delete;
    Application& operator=(const Application&)  = delete;

private:
    Application();
    ~Application();

private:
    std::unique_ptr<Window> m_Window;
    float m_LastFrameTime = 0.0f;
};

#endif // !CORE_APPLICATION_H_