#ifndef COILIST_H
#define COILIST_H

#include "COI.h"
#include <memory>

class COI;

class COIList {
public:
    COIList(std::vector<uint8_t> f, size_t of) { file = f; offset = of; };
    ~COIList() {};
    
    void preload();
private:
    std::vector<uint8_t> file;
    uint16_t chID;
    uint16_t chFlags;
    uint32_t chSize;
    size_t offset;
    
    uint32_t oiMaxIndex;
    uint16_t oiMaxHandle;
    std::vector<std::unique_ptr<COI>> ois;
};
#endif
