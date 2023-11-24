#include "CFrame.h"


bool CFrame::loadFullFrame(int i, std::vector<size_t> offsets, std::unique_ptr<COIList>& oiList) {
    
    offset = offsets[i];
    
    while (chID != CHUNK_LAST) {
        chID = readShort(*file, offset);
        chFlags = readShort(*file, offset);
        chSize = readInt(*file, offset);
        
        if(chSize != 0) {
            size_t fptr = offset + chSize;
            switch(chID) {
                case 13109:
                    frameName = readString(*file, offset);
                    std::cout << "Name: " << frameName << std::endl;
                    break;
                case 13121:
                    loadLayers();
                    break;
                case 13112:
                    // oiList->load();
                    cloList = std::make_unique<CLOList>(file, offset);
                    cloList->load(oiList);
                    break;
                default:
                    // std::cerr << "Unknown chunk " << chID << " " << chSize <<  std::endl;
                    break;
            }
            
            offset = fptr;
        }
    }
    chID = 0;
    // OIList->load();
    return true;
}

void CFrame::loadLayers() {
    uint32_t nLayers = readInt(*file, offset);
    
    layers.resize(nLayers);
    
    for(int i = 0; i < nLayers; i++) {
        layers[i] = std::make_unique<CLayer>();
        
        layers[i]->dwOptions = readInt(*file, offset);
        layers[i]->xCoef = readFloat(*file, offset);
        layers[i]->yCoef = readFloat(*file, offset);
        layers[i]->nBkdLOs = readInt(*file, offset);
        layers[i]->nFirstLOIndex = readInt(*file, offset);
        layers[i]->name = readString(*file, offset);
    }
}

void CFrame::loadObjects(std::unique_ptr<COIList>& oiList) {
    for (int i4 = 0; i4 < cloList->maxIndex; i4++) {
        oiList->setToLoad(cloList->getLOFromIndex(i4)->loOiHandle);
    }
    oiList->load();
}
