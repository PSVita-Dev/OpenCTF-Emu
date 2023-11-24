#ifndef CANIM_DIR_H
#define CANIM_DIR_H

#include "utils.h"

#include <memory>

class CAnimDir {
public:
    CAnimDir(std::vector<uint8_t>* f, size_t of) { file = f; offset = of;};
    ~CAnimDir() {};
    
    void load();
private:
    std::vector<uint8_t>* file;
    size_t offset;
    
    std::vector<uint16_t> adFrames;
    uint8_t adMaxSpeed;
    uint8_t adMinSpeed;
    uint16_t adNumberOfFrame;
    uint16_t adRepeat;
    uint16_t adRepeatFrame;
};
#endif
