#ifndef COILIST_H
#define COILIST_H

#include "COI.h"
#include <memory>

class COI;

class COIList {
public:
    COIList(std::vector<uint8_t> f, size_t of) { file = f; offset = of;};
    ~COIList() {};
    
    void load();
    void preload();
    void resetToLoad();
    void setToLoad(int i);
    // static COIList *get_Singleton() { return singleton;};
    std::unique_ptr<COI>& getOIFromHandle(uint16_t s);
private:
    std::vector<uint8_t> file;
    uint16_t chID;
    uint16_t chFlags;
    uint32_t chSize;
    size_t offset;
    
    uint32_t oiMaxIndex;
    uint16_t oiMaxHandle;
    std::vector<std::unique_ptr<COI>> ois;
    std::vector<bool> oiToLoad;
    std::vector<bool> oiLoaded;
    std::vector<int> oiHandleToIndex;
    // static COIList* singleton;
};
#endif
