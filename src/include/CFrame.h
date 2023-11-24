#ifndef CFRAME_H
#define CFRAME_H

#include "CRun.h"
#include "CLayer.h"
#include "CLOList.h"

class CLOList;

class CFrame {
public:
    CFrame(std::vector<uint8_t>* f, size_t of) { file = f; offset = of;};
    ~CFrame() {};
    
    bool loadFullFrame(int i, std::vector<size_t> offsets, std::unique_ptr<COIList>& oiList);
    void loadLayers();
    void loadObjects(std::unique_ptr<COIList>& oiList);
    // void setOIList(COIList& list) { oiList = list; };
    
    std::unique_ptr<CLOList> cloList;
private:
    std::vector<uint8_t>* file;
    uint16_t chID;
    uint16_t chFlags;
    uint32_t chSize;
    size_t offset;
    
    std::vector<std::unique_ptr<CLayer>> layers;
    
    
    std::string frameName;
};
#endif
