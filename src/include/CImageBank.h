#ifndef CIMAGEBANK_H
#define CIMAGEBANK_H

#include "CRun.h"
#include "CImage.h"
#include "CRender.h"
#include <memory>

class CRender;

class BankSlot {
public:
    size_t dataOffset = -1;
    uint16_t handle;
    unsigned char *data;
    int useCount;
};

class CImageBank {
public:
    CImageBank(std::vector<uint8_t>* f, size_t of) { file = f; offset = of;};
    ~CImageBank() {};
    
    void preload(std::unique_ptr<CRender>& renderer);
    
    std::unique_ptr<CImage>& getImg(int i);
    
    std::vector<uint8_t> AndroidMode4ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha);
    std::vector<uint8_t> AndroidMode3ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha);
    std::vector<uint8_t> AndroidMode0ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha);
    std::vector<uint8_t> AndroidMode1ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha);
    
    std::vector<uint32_t> handles;
private:
    std::vector<uint8_t>* file;
    uint16_t chID;
    uint16_t chFlags;
    uint32_t chSize;
    size_t offset;
    
    uint16_t numBmp;
    
    std::vector<std::unique_ptr<CImage>> images;
};

#endif
