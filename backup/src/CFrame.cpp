#include "CFrame.h"


bool CFrame::loadFullFrame(int i, std::vector<size_t> offsets) {
    
    offset = offsets[i];
    
    while (chID != CHUNK_LAST) {
        chID = readShort(file, offset);
        chFlags = readShort(file, offset);
        chSize = readInt(file, offset);
        
        if(chSize != 0) {
            size_t fptr = offset + chSize;
            switch(chID) {
                case 13109:
                    frameName = readString(file, offset);
                    std::cout << "Name: " << frameName << std::endl;
                    break;
                default:
                    // std::cerr << "Unknown chunk " << chID << " " << chSize <<  std::endl;
                    break;
            }
            
            offset = fptr;
        }
    }
    chID = 0;
    return true;
}
