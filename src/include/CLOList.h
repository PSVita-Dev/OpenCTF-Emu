#ifndef CLOLIST_H
#define CLOLIST_H

#include <vector>
#include <memory>

#include "CLO.h"

class CLO;
class COIList;
class COI;

class CLOList {
public:
    CLOList(std::vector<uint8_t>* f, size_t of) { file = f; offset = of;};
    ~CLOList() {};
    
    void load(std::unique_ptr<COIList>& oiList);
    std::unique_ptr<CLO>& next_LevObj();
    std::unique_ptr<CLO>& first_LevObj();
    std::unique_ptr<CLO>& getLOFromIndex(int i);
    bool checkNext();
    
    uint32_t maxIndex;
private:
    std::vector<uint8_t>* file;
    size_t offset;
    
    int loFranIndex;
    
    
    std::vector<std::unique_ptr<CLO>> list;
    std::vector<int> handleToIndex;
};
#endif
