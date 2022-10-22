#include "Core/GLSystem.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Core/Log.h"

namespace GLSystem {

#ifdef GLDEBUG

static void APIENTRY _ErrorCallBack(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam) {

    const char* source_str;
    switch (source) {
    case GL_DEBUG_SOURCE_API:               source_str = "API";                 break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:     source_str = "Window System";       break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:   source_str = "Shader Compiler";     break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:       source_str = "Third Party";         break;
    case GL_DEBUG_SOURCE_APPLICATION:       source_str = "Application";         break;
    case GL_DEBUG_SOURCE_OTHER:             source_str = "Other";               break;
    default:                                source_str = "";                    break;
    }

    const char* type_str;
    switch (type) {
    case GL_DEBUG_TYPE_ERROR:               type_str = "Error";                 break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "Deprecated Behaviour";  break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_str = "Undefined Behaviour";   break; 
    case GL_DEBUG_TYPE_PORTABILITY:         type_str = "Portability";           break;
    case GL_DEBUG_TYPE_PERFORMANCE:         type_str = "Performance";           break;
    case GL_DEBUG_TYPE_MARKER:              type_str = "Marker";                break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          type_str = "Push Group";            break;
    case GL_DEBUG_TYPE_POP_GROUP:           type_str = "Pop Group";             break;
    case GL_DEBUG_TYPE_OTHER:               type_str = "Other";                 break;
    default:                                type_str = "";                      break;
    }
    
    LogType logtype = LogType::NONE;
    const char* severity_str;
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:            severity_str = "high";          logtype = LogType::ERR;     break;
    case GL_DEBUG_SEVERITY_MEDIUM:          severity_str = "medium";        logtype = LogType::ERR;     break;
    case GL_DEBUG_SEVERITY_LOW:             severity_str = "low";           logtype = LogType::WARNING; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:    severity_str = "notification";  logtype = LogType::INFO;    break;
    default:                                severity_str = "";              logtype = LogType::NONE;    break;
    }
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;
    Log(logtype,
        "[OpenGL Log](%u)\n"
        "Source: %s\n"
        "Type: %s\n"
        "Severity: %s\n"
        "- %s\n\n",
        id, source_str, type_str, severity_str, message);

}
#endif // GLDEBUG

bool initGLFW() {
    if (!glfwInit()) {
        ERRORLOG("Failed to initialize glfw!\n");
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef GLDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    INFOLOG("GLFW library binrary - %s\n\n",glfwGetVersionString());
#endif // GLDEBUG

    return true;
}

bool initGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ERRORLOG("Failed to initialize glad!\n");
        return false;
    }

#ifdef GLDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(_ErrorCallBack, nullptr);

    const unsigned char* version    = glGetString(GL_VERSION);
    const unsigned char* vendor     = glGetString(GL_VENDOR);
    const unsigned char* renderer   = glGetString(GL_RENDERER);
    INFOLOG(
        "OpenGL   - %s\n"
        "Vendor   - %s\n"
        "Renderer - %s\n\n",
        version, vendor, renderer);
#endif // GLDEBUG

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    return true;
}

void exit() {
    glfwTerminate();
}

} // namespace GLSystem