#ifndef CIMAGEBANK_H
#define CIMAGEBANK_H

#include "CRun.h"
#include <memory>

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
    
    void preload();
    
    std::vector<uint8_t> AndroidMode4ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha);
    std::vector<uint8_t> AndroidMode3ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha);
    std::vector<uint8_t> AndroidMode0ToRGBA(std::vector<uint8_t> imageData, int width, int height, bool alpha);
private:
    std::vector<uint8_t>* file;
    uint16_t chID;
    uint16_t chFlags;
    uint32_t chSize;
    size_t offset;
    std::vector<std::unique_ptr<BankSlot>> images;
};

#endif
