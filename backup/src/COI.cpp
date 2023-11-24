#include "COI.h"
 
void COI::loadHeader() {
    oiHandle = readShort(*file, offset);
    oiType = readShort(*file, offset);
    oiFlags = readShort(*file, offset);
    offset+=2;
    oiInkEffect = readInt(*file, offset);
    oiInkEffectParam = readInt(*file, offset);
}
