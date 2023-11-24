#ifndef COI_H
#define COI_H

#include "CRun.h"
#include "CObjectCommon.h"
#include <memory>

class CObjectCommon;

class COI {
public:
    COI(std::vector<uint8_t>* f, size_t of) { file = f; offset = of;};
    ~COI() {};
    
    void loadHeader();
    void load();
    
    std::string oiName;
    size_t oiFileOffset;
    uint16_t oiHandle;
    uint32_t oiLoadFlags = 0;
    uint16_t oiType;
private:
    std::vector<uint8_t>* file;
    uint16_t chID;
    uint16_t chFlags;
    uint32_t chSize;
    size_t offset;

    std::unique_ptr<CObjectCommon> oiOC;
    
    uint16_t oiFlags;
    uint32_t oiInkEffect;
    uint32_t oiInkEffectParam;
};

#endif
