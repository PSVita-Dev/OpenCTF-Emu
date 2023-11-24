#ifndef COBJECT_COMMON_H
#define COBJECT_COMMON_H

#include "COI.h"
#include "CAnimHeader.h"

class CAnimHeader;
class COI;

class CObjectCommon {
public:
    CObjectCommon(std::vector<uint8_t>* f, size_t of) { file = f; offset = of;};
    ~CObjectCommon() {};
    
    void load(COI* oi);
private:
    std::vector<uint8_t>* file;
    size_t offset;
    
    std::vector<uint16_t> ocQualifiers;
    std::unique_ptr<CAnimHeader> ocAnimations;
    
    uint32_t ocOEFlags;
    uint16_t ocFlags2;
    uint16_t ocOEPrefs;
    uint32_t ocIdentifier;
    uint32_t ocBackColor;
    uint32_t ocVersion;
    uint32_t ocID;
    uint32_t ocPrivate;
};
#endif
