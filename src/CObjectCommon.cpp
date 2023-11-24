#include "CObjectCommon.h" 

void CObjectCommon::load(COI* oi) {
    size_t filePointer = offset;
    ocQualifiers.resize(8);
    offset += 4;
    uint16_t readAShort = readShort(*file, offset);
    uint16_t readAShort2 = readShort(*file, offset);
    offset += 2;
    uint16_t readAShort3 = readShort(*file, offset);
    uint16_t readAShort4 = readShort(*file, offset);
    offset += 2;
    
    ocOEFlags = readInt(*file, offset);
    for (int i = 0; i < 8; i++) {
        ocQualifiers[i] = readShort(*file, offset);
    }
    uint16_t readAShort5 = readShort(*file, offset);
    uint16_t readAShort6 = readShort(*file, offset);
    uint16_t readAShort7 = readShort(*file, offset);
    
    ocFlags2 = readShort(*file, offset);
    ocOEPrefs = readShort(*file, offset);
    ocIdentifier = readInt(*file, offset);
    ocBackColor = readColor(*file, offset);
    int readAInt = readInt(*file, offset);
    int readAInt2 = readInt(*file, offset);
    ocOEFlags &= -4097;
    
    if (readAShort != 0) {
        // cFile.seek(((long) readAShort) + filePointer);
        // this.ocMovements = new CMoveDefList();
        // this.ocMovements.load(cFile);
    }
    if (readAShort6 != 0) {
        // cFile.seek(((long) readAShort6) + filePointer);
        // this.ocValues = new CDefValues();
        // this.ocValues.load(cFile);
    }
    if (readAShort7 != 0) {
        // cFile.seek(((long) readAShort7) + filePointer);
        // this.ocStrings = new CDefStrings();
        // this.ocStrings.load(cFile);
    }
    if (readAShort2 != 0) {
        offset = readAShort2 + filePointer;
        ocAnimations = std::make_unique<CAnimHeader>(file, offset);
        ocAnimations->load();
    }
    if (readAShort3 != 0) {
        // cFile.seek(((long) readAShort3) + filePointer);
        // this.ocObject = new CDefCounter();
        // this.ocObject.load(cFile);
    }
    if (readAShort5 != 0) {
        /*cFile.seek(((long) readAShort5) + filePointer);
        int readAInt3 = cFile.readAInt();
        cFile.skipBytes(4);
        this.ocVersion = cFile.readAInt();
        this.ocID = cFile.readAInt();
        this.ocPrivate = cFile.readAInt();
        int i2 = readAInt3 - 20;
        if (i2 != 0) {
            this.ocExtension = new byte[i2];
            cFile.read(this.ocExtension);
        }*/
    }
    if (readAInt != 0) {
        // cFile.seek(((long) readAInt) + filePointer);
        // this.ocFadeIn = new CTransitionData();
        // this.ocFadeIn.load(cFile);
    }
    if (readAInt2 != 0) {
        // cFile.seek(((long) readAInt2) + filePointer);
        // this.ocFadeOut = new CTransitionData();
        // this.ocFadeOut.load(cFile);
    }
}
