#include "CLOList.h"
#include "utils.h"
#include "COI.h"

void CLOList::load(std::unique_ptr<COIList>& oiList) {
    maxIndex = readInt(*file, offset);
    list.resize(maxIndex);
    int i = 0;
    for (int i2 = 0; i2 < maxIndex; i2++) {
        list[i2] = std::make_unique<CLO>();
        list[i2]->loHandle = readShort(*file, offset);
        list[i2]->loOiHandle = readShort(*file, offset);
        list[i2]->loX = readInt(*file, offset);
        list[i2]->loY = readInt(*file, offset);
        
        list[i2]->loParentType = readShort(*file, offset);
        list[i2]->loOiParentHandle = readShort(*file, offset);
        list[i2]->loLayer = readShort(*file, offset);
        
        offset += 2;
        
        if (list[i2]->loHandle + 1 > i) {
            i = list[i2]->loHandle + 1;
        }
        std::unique_ptr<COI>& oIFromHandle = oiList->getOIFromHandle(list[i2]->loOiHandle);
        list[i2]->loType = oIFromHandle->oiType;
    }
    
    handleToIndex.resize(i);
    for (int i3 = 0; i3 < maxIndex; i3++) {
        handleToIndex[list[i3]->loHandle] = i3;
    }
}

std::unique_ptr<CLO>& CLOList::first_LevObj() {
    loFranIndex = 0;
    return next_LevObj();
}

std::unique_ptr<CLO>& CLOList::getLOFromIndex(int i) {
    return list[i];
}

bool CLOList::checkNext() {
    if(loFranIndex < maxIndex) { return true; } else { return false; }
}

std::unique_ptr<CLO>& CLOList::next_LevObj() {
    if (loFranIndex < maxIndex) {
        do {
            int i = loFranIndex;
            loFranIndex++;;
            std::unique_ptr<CLO>& clo = list[i];
            if (clo->loType >= 2) {
                return clo;
            }
        } while (loFranIndex < maxIndex);
    }
    // return nullptr;
}
