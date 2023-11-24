#include "COIList.h"

void COIList::preload() {
    oiMaxIndex = readInt(file, offset);

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
                        break;
                    case 17478:
                        ois[x]->oiFileOffset = offset;
                        break;
                }
                
                offset = fptr;
            }
        }
    }
}
