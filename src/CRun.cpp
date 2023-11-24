#include "CRun.h" 
#include "CFrame.h"

CRun::CRun(std::string path) {
    file = LoadFile(path);
}

// short CRun::readHeader() {
    

void CRun::parse() {
    std::vector<uint8_t> b = readBytes(file, offset, 4);
    
    if (b[0] == 80 && b[1] == 65 && b[2] == 77 && b[3] == 85) {
        std::cout << "Found PAMU header" << std::endl;
        bUnicode = true;
        load = true;
    }
    if (b[0] == 80 && b[1] == 65 && b[2] == 77 && b[3] == 69) {
        std::cout << "Found PAME header" << std::endl;
        bUnicode = false;
        load = true;
    }
    
    if(!load)
        return;
    
    if(readBytes(file, offset, 2)[0] != 0x02)
        return;
    
    offset += 10; //skip
    
    readChunks();
    
    frame = std::make_unique<CFrame>(&file, offset);
    
    for(int i = 0; i < frameOffsets.size(); i++)
        frame->loadFullFrame(i, frameOffsets, OIList);
    
    // frame->setOIList(&OIList);
    
    frame->loadObjects(OIList);
}

void CRun::createFrameObjects() {
    int i = 0;
    std::unique_ptr<CLO>& first_LevObj = frame->cloList->first_LevObj();
    while (frame->cloList->checkNext()) {
        
        std::unique_ptr<COI>& oIFromHandle = OIList->getOIFromHandle(first_LevObj->loOiHandle);
            // CObjectCommon cObjectCommon = (CObjectCommon) oIFromHandle.oiOC;
        short s = oIFromHandle->oiType;
        short s2 = 8;
        if (first_LevObj->loParentType == 0) {
            if (s == 3) {
                s2 = (short) 12;
            }
            /*if ((cObjectCommon.ocFlags2 & 8) == 0) {
                if (s != 4) {
                    s2 = (short) (s2 | 2);
                }
            }*/
            // if ((!z || s < 32 || (cObjectCommon.ocOEFlags & 8) != 0) && (cObjectCommon.ocOEFlags & 131072) == 0) {
                f_CreateObject(first_LevObj->loHandle, first_LevObj->loOiHandle);
            // }
        }
        i++;
        std::unique_ptr<CLO>& first_LevObj = frame->cloList->next_LevObj();
    }
    rhGameFlags = rhGameFlags & -513;
}

void CRun::f_CreateObject(uint16_t loHandle, uint16_t loOiHandle) {
    
}

void CRun::loadFrameHandles(size_t i) {
    frameMaxHandle = (i / 2);
    frameHandleToIndex.resize(frameMaxHandle);
    for (int i2 = 0; i2 < frameMaxHandle; i2++) {
        frameHandleToIndex[i2] = readShort(file, offset);
    }
}

void CRun::loadGlobalStrings() {
    nGlobalStringsInit = readInt(file, offset);
    globalStringsInit.resize(nGlobalStringsInit);
    for (int i = 0; i < nGlobalStringsInit; i++) {
        globalStringsInit[i] = readString(file, offset);
        std::cout << globalStringsInit[i] << std::endl;
    }
}

void CRun::loadAppHeader() {
    offset += 4;
    
    offset += 4; //skip flags

    std::cout << "Mode: " << readShort(file, offset) << std::endl;
    
    readShort(file, offset);
    
    width = readShort(file, offset);
    
    height = readShort(file, offset);
    
    std::cout << "Width: " << width << std::endl;
    
    std::cout << "Height: " << height << std::endl;
    
    offset += 8; //skip init lives
    
    offset += 4*2; //skip ctrl types
    
    offset += (4*8)*2; //skip key input
    
    readColor(file, offset);
    
    nbFrames = readInt(file, offset);
    std::cout << "Frames: " << nbFrames << std::endl;
    
    renderer = std::make_unique<CRender>(width, height);
}

void CRun::readChunks() {
    
    
    
    while (chID != CHUNK_LAST) {
        chID = readShort(file, offset);
        chFlags = readShort(file, offset);
        chSize = readInt(file, offset);
        
        if(chSize != 0) {
            size_t fptr = offset + chSize;
            switch(chID) {
                case 8739:
                    std::cout << "Got CHUNK_APPHEADER" << std::endl;
                    loadAppHeader();
                    frameOffsets.resize(nbFrames);
                    break;
                case 8740:
                    appName = readString(file, offset);
                    std::cout << "Name: " << appName << std::endl;
                    break;
                case 8745:
                case 8767:
                    OIList = std::make_unique<COIList>(file, offset);
                    OIList->preload();
                    break;
                case 13107:
                    frameOffsets[maxFrameIndex] = offset;
                    // std::cout << "Found frame " << offset << std::endl;
                    while (chID != CHUNK_LAST) {
                        chID = readShort(file, offset);
                        chFlags = readShort(file, offset);
                        chSize = readInt(file, offset);
                        if (chSize != 0) {
                            offset = (offset + chSize);
                        }
                    }
                    maxFrameIndex++;
                    chID = 0;
                    break;
                case 8747:
                    loadFrameHandles(chSize);
                    break;
                case 8755:
                    loadGlobalStrings();
                    break;
                case 26214:
                    imageBank = std::make_unique<CImageBank>(&file, offset);
                    imageBank->preload(renderer);
                    break;
                default:
                    std::cerr << "Unknown chunk " << chID << " " << chSize <<  std::endl;
                    break;
            }
            
            offset = fptr;
        }
    }
}

void CRun::run() {
    // createFrameObjects();
    int i = 0;
    while(1) {
        renderer->beginFrame();
        
        renderer->drawImage(0, 0, imageBank->getImg(i++));
        
        usleep(50000);
        
        renderer->endFrame();
    };
}
