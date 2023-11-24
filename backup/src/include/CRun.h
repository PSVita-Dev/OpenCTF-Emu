#ifndef CRUN_H
#define CRUN_H

#include "utils.h"
#include <memory>
#include "COIList.h"
#include "CImageBank.h"

class CImageBank;
class COIList;

class CRun {
public:
    CRun(std::string path);
    
    void parse();
    void readChunks();
    void loadAppHeader();
    void loadFrameHandles(size_t i);
    void loadGlobalStrings();
    
    std::vector<uint8_t> getFile() { return file; };
private:
    std::vector<uint8_t> file;
    bool bUnicode = false;
    bool load = false;
    size_t offset = 0;
    size_t frameMaxHandle;
    std::vector<uint16_t> frameHandleToIndex;
    
    uint32_t nGlobalStringsInit;
    std::vector<std::string> globalStringsInit;
    
    uint16_t chID;
    uint16_t chFlags;
    uint32_t chSize;
    
    uint16_t width;
    uint16_t height;
    uint32_t nbFrames;
    uint32_t maxFrameIndex = 0;
    std::vector<size_t> frameOffsets;
    std::string appName;
    std::unique_ptr<COIList> OIList;
    std::unique_ptr<CImageBank> imageBank;
};
#endif
