#include "COI.h"
 
void COI::loadHeader() {
    oiHandle = readShort(*file, offset);
    oiType = readShort(*file, offset);
    oiFlags = readShort(*file, offset);
    offset+=2;
    oiInkEffect = readInt(*file, offset);
    oiInkEffectParam = readInt(*file, offset);
}

void COI::load() {
    offset = oiFileOffset;
    switch (oiType) {
        case 0:
            // oiOC = new COCQBackdrop();
            std::cerr << "COCQBackdrop" << std::endl;
            break;
        case 1:
            std::cerr << "COCBackground" << std::endl;
            // oiOC = new COCBackground();
            break;
        default:
            // std::cerr << "COCBackground" << std::endl;
            oiOC = std::make_unique<CObjectCommon>(file, offset);
            oiOC->load(this);
            break;
    }
    
}
