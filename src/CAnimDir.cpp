#include "CAnimDir.h"

void CAnimDir::load() {
    adMinSpeed = readByte(*file, offset);
    adMaxSpeed = readByte(*file, offset);
    adRepeat = readShort(*file, offset);
    adRepeatFrame = readShort(*file, offset);
    adNumberOfFrame = readShort(*file, offset);
    adFrames.resize(adNumberOfFrame);
    for (int i = 0; i < adNumberOfFrame; i++) {
        adFrames[i] = readShort(*file, offset);
    }
}
