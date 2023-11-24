#ifndef CANIM_HEADER_H
#define CANIM_HEADER_H

#include "CAnim.h"

class CAnim;

class CAnimHeader {
public:
    CAnimHeader(std::vector<uint8_t>* f, size_t of) { file = f; offset = of;};
    ~CAnimHeader() {};
    
    void load();
private:
    std::vector<uint8_t>* file;
    size_t offset;
    
    int tableApprox[16][4] = {{3, 1, 2, 0}, {2, 0, 0, 0}, {1, 0, 0, 0}, {0, 1, 2, 0}, {0, 0, 0, 0}, {0, 1, 2, 0}, {0, 1, 2, 0}, {1, 2, 0, 0}, {0, 1, 2, 0}, {1, 2, 0, 0}, {0, 1, 2, 0}, {0, 1, 2, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    
    std::vector<std::unique_ptr<CAnim>> ahAnims;
    std::vector<bool> ahAnimExists;
    uint32_t ahAnimMax;
    
};
#endif
