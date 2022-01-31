#ifndef TRASHENGINE_GL_UTILS_H
#define TRASHENGINE_GL_UTILS_H


#include <GL/glew.h>


#define ASSERT(call) if (!(call)) exit(-1)
#define GLCALL(call) GLClearErrors(); \
                     call;            \
                     ASSERT(GLLogCall(#call, __FILE__, __LINE__))
void GLClearErrors();
bool GLLogCall(const char* function, const char* file, int line);




#endif //TRASHENGINE_GL_UTILS_H
