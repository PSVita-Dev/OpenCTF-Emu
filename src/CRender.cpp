#include "CRender.h"
#include <iostream>

#define RATIO 720 / 720 //temp

CRender::CRender(uint16_t width, uint16_t height) {
    curWidth = width;
    curHeight = height;
    
    if (!glfwInit())
        std::cerr << "Failed to init GLFW." << std::endl;
    
    // glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwSetErrorCallback(errorcb);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
    window = glfwCreateWindow(width, height, "NanoVG", NULL, NULL);
    
    glfwMakeContextCurrent(window);
    
    vg = nvgCreateGLES3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    if (vg == NULL) {
        std::cerr << "Error init nvg" << std::endl;
    }

}

void CRender::beginFrame() {

    nvgBeginFrame(vg, curWidth, curHeight, 1);
    nvgBeginPath(vg);
    
    // nvgFillColor(vg, nvgRGBA(255, 192, 0, 255));

    // nvgEndFrame(vg);
}

void CRender::drawImage(int x, int y, std::unique_ptr<CImage>& image) {
    if(image->width > curWidth || image->height > curHeight) {
        resizeWindow(image->width, image->height);
    }
    
    nvgRect(vg, x, y, image->width, image->height);
    
    NVGpaint i = nvgImagePattern(vg, x, y, image->width, image->height,  0.0f/180.0f*NVG_PI, image->data, 1);
    nvgFillPaint(vg, i);
    nvgFill(vg);
}

void CRender::resizeWindow(int w, int h) {
    glfwSetWindowSize(window, w, h);
    glViewport(0, 0, w, h);
    
    curWidth = w;
    curHeight = h;
}

int CRender::loadImage(int w, int h, unsigned char* image) {
    return nvgCreateImageRGBA(vg, w, h, 0, image);
}

void CRender::endFrame() {
    nvgEndFrame(vg);
    glfwSwapBuffers(window);
}
