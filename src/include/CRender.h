#ifndef CRENDER_H
#define CRENDER_H

// #define GLFW_INCLUDE_ES2
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include "nanovg.h"
// #define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"
// #include "nanovg_gl.c"
// #include "nanovg_gl_utils.h"

#include "CImage.h"

#include <memory>
#include <cstdio>

class CImage;

class CRender {
public:
    CRender(uint16_t width, uint16_t height);
    ~CRender() { nvgDeleteGLES2(vg); };
    
    void beginFrame();
    void endFrame();
    void drawImage(int x, int y, std::unique_ptr<CImage>& image);
    int loadImage(int w, int h, unsigned char* image);
    void resizeWindow(int w, int h);
private:
    NVGcontext* vg = NULL;
    GLFWwindow* window;
    
    int curWidth;
    int curHeight;
};

inline void errorcb(int error, const char* desc)
{
	printf("GLFW error %d: %s\n", error, desc);
}
#endif
