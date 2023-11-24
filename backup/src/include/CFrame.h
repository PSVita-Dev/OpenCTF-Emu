#ifndef CFRAME_H
#define CFRAME_H

#include "CRun.h"

class CFrame {
public:
    CFrame(CRun& app) { file = app.getFile(); };
    ~CFrame() {};
    
    bool loadFullFrame(int i, std::vector<size_t> offsets);
private:
    std::vector<uint8_t> file;
    uint16_t chID;
    uint16_t chFlags;
    uint32_t chSize;
    size_t offset;
    
    std::string frameName;
};
#endif
