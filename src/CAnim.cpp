#include "CAnim.h"

void CAnim::load() {
    size_t filePointer = offset;
    std::vector<uint16_t> sArr(32);
    for (int i = 0; i < 32; i++) {
        sArr[i] = readShort(*file, offset);
    }
    anDirs.resize(32);
    anTrigo.resize(32);
    anAntiTrigo.resize(32);
    for (int i2 = 0; i2 < 32; i2++) {
        anDirs[i2] = nullptr;
        anTrigo[i2] = 0;
        anAntiTrigo[i2] = 0;
        if (sArr[i2] != 0) {
            anDirs[i2] = std::make_unique<CAnimDir>(file, offset);
            offset = sArr[i2] + filePointer;
            anDirs[i2]->load();
        }
    }
}
