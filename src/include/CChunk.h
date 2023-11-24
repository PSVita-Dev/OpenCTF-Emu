#if 0
class CChunk {
public:
    static short CHUNK_LAST = 32639;
    short chFlags = 0;
    short chID = 0;
    int chSize = 0;

    short readHeader(CFile cFile) {
        chID = cFile.readAShort();
        chFlags = cFile.readAShort();
        chSize = cFile.readAInt();
        return chID;
    }

    void skipChunk(CFile cFile) {
        cFile.skipBytes(this.chSize);
    }
}
#endif
