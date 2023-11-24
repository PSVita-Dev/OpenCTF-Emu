#include "COIList.h"

void COIList::resetToLoad() {
    for (int i = 0; i < oiMaxHandle; i++) {
        oiToLoad[i] = false;
    }
}

std::unique_ptr<COI>& COIList::getOIFromHandle(uint16_t s) {
    // std::shared_ptr<COI> res;
    
    return ois[oiHandleToIndex[s]];
}

void COIList::load() {
    for (int i = 0; i < oiMaxHandle; i++) {
        if (oiToLoad[i] != false) {
            if (oiLoaded[i] == false || !(oiLoaded[i] == false || (ois[oiHandleToIndex[i]]->oiLoadFlags & 32) == 0)) {
                ois[oiHandleToIndex[i]]->load();
                oiLoaded[i] = true;
            }
        } else if (oiLoaded[i] != false) {
            // ois[oiHandleToIndex[i]]->unLoad();
            oiLoaded[i] = false;
        }
    }
    resetToLoad();
}


void COIList::setToLoad(int i) {
    oiToLoad[i] = true;
}

void COIList::preload() {
    oiMaxIndex = readInt(file, offset);
    
    std::cout << oiMaxIndex << " Objects " << offset << std::endl;
    
    ois.resize(oiMaxIndex);

    // for(int i = 0; i < oiMaxIndex; i++)
        // ois[i] = std::make_unique<COI>(&file);
    

    for(int x = 0; x < oiMaxIndex; x++) {
        while (chID != CHUNK_LAST) {
            chID = readShort(file, offset);
            chFlags = readShort(file, offset);
            chSize = readInt(file, offset);
            
            if(chSize != 0) {
                size_t fptr = offset + chSize;
                switch(chID) {
                    case 17476:
                        ois[x] = std::make_unique<COI>(&file, offset);
                        ois[x]->loadHeader();
                        if (ois[x]->oiHandle >= oiMaxHandle) {
                            oiMaxHandle = (ois[x]->oiHandle + 1);
                            break;
                        }
                        break;
                    case 17477:
                        ois[x]->oiName = readString(file, offset);
                        // std::cout << ois[x]->oiName << std::endl;
                        break;
                    case 17478:
                        ois[x]->oiFileOffset = offset;
                        break;
                }
                
                offset = fptr;
            }
        }
        //ugly hack :skull:
        chID = 0;
    }
    oiHandleToIndex.resize(oiMaxHandle);
    oiToLoad.resize(oiMaxHandle);
    oiLoaded.resize(oiMaxHandle);
    
    for (int i2 = 0; i2 < oiMaxIndex; i2++) {
        oiHandleToIndex[ois[i2]->oiHandle] = i2;
    }

    for (int i3 = 0; i3 < oiMaxHandle; i3++) {
        oiToLoad[i3] = false;
        oiLoaded[i3] = false;
    }
}
