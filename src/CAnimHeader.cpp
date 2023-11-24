#include "CAnimHeader.h"


void CAnimHeader::load() {
    size_t filePointer = offset;
    offset += 2;
    ahAnimMax = readShort(*file, offset);
    std::vector<uint16_t> sArr(ahAnimMax);
    for (int i = 0; i < ahAnimMax; i++) {
        sArr[i] = readShort(*file, offset);
    }
    ahAnims.resize(ahAnimMax);
    ahAnimExists.resize(ahAnimMax);
    for (int i2 = 0; i2 < ahAnimMax; i2++) {
        ahAnims[i2] = nullptr;
        ahAnimExists[i2] = 0;
        if (sArr[i2] != 0) {
            ahAnims[i2] = std::make_unique<CAnim>(file, offset);
            offset = sArr[i2] + filePointer;
            ahAnims[i2]->load();
            ahAnimExists[i2] = 1;
        }
    }
    for (int i3 = 0; i3 < ahAnimMax; i3++) {
        if (ahAnimExists[i3] == 0) {
            bool z = false;
            if (i3 < 12) {
                int i4 = 0;
                while (true) {
                    if (i4 >= 4) {
                        break;
                    } else if (ahAnimExists[tableApprox[i3][i4]] != 0) {
                        // ahAnims[i3] = ahAnims[tableApprox[i3][i4]];
                        z = true;
                        break;
                    } else {
                        i4++;
                    }
                }
            }
            if (!z) {
                int i5 = 0;
                while (true) {
                    if (i5 >= ahAnimMax) {
                        break;
                    } else if (ahAnimExists[i5] != 0) {
                        // ahAnims[i3] = ahAnims[i5];
                        break;
                    } else {
                        i5++;
                    }
                }
            }
        } else {
            ahAnims[i3]->approximate(i3);
        }
    }
}
