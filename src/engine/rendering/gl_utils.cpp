#include "gl_utils.h"


#include "GL/glew.h"
#include <iostream>


void GLClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum errorCode = glGetError()) {
        std::cerr << "OpenGL error with code: '"
                  << errorCode
                  << "' in function call: "
                  << function << std::endl
                  << "File: "
                  << file << ":" << line
                  << std::endl;
        return false;
    }
    return true;
}