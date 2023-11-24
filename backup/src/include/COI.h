#ifndef COI_H
#define COI_H

#include "CRun.h"
#include <memory>

class COI {
public:
    COI(std::vector<uint8_t>* f, size_t of) { file = f; offset = of;};
    ~COI() {};
    
    void loadHeader();
    
    std::string oiName;
    size_t oiFileOffset;
    uint16_t oiHandle;
private:
    std::vector<uint8_t>* file;
    uint16_t chID;
    uint16_t chFlags;
    uint32_t chSize;
    size_t offset;

    
    uint16_t oiType;
    uint16_t oiFlags;
    uint32_t oiInkEffect;
    uint32_t oiInkEffectParam;
};

#endif
