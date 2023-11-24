#ifndef CANIM_H
#define CANIM_H

#include "CAnimDir.h"

class CAnimDir;

class CAnim {
public:
    CAnim(std::vector<uint8_t>* f, size_t of) { file = f; offset = of;};
    ~CAnim() {};
    
    void load();
    void approximate(int i) { };
private:
    std::vector<uint8_t>* file;
    size_t offset;
    
    char tableAnimTwoSpeeds[16] = {0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    
    std::vector<std::unique_ptr<CAnimDir>> anDirs;
    std::vector<bool> anAntiTrigo;
    std::vector<bool> anTrigo;
};
#endif
