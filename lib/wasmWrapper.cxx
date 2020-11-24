#include <vector>
#include <sstream>
#include <emscripten/emscripten.h>
#include "HTF.h"

extern "C"{
    HFEnc* encoderPtr = nullptr;
    char* retBuf = nullptr;

    void EMSCRIPTEN_KEEPALIVE nEncoder(double *probs,
                                       size_t bufSize,
                                       int *syms,
                                       size_t symc);

    char *getCode(size_t i);
    void EMSCRIPTEN_KEEPALIVE recEnc();
    void EMSCRIPTEN_KEEPALIVE recBuf();
    void EMSCRIPTEN_KEEPALIVE buildEnc();
}

void EMSCRIPTEN_KEEPALIVE nEncoder(double* probs, 
                                      size_t bufSize, 
                                      int* syms, 
                                      size_t symc){
    encoderPtr = new HFEnc(std::vector<double>(probs, probs + bufSize),
                           std::vector<int>(syms, syms + symc));
}

void EMSCRIPTEN_KEEPALIVE buildEnc(){
    encoderPtr->build();
}

char* getCode(size_t i){
    auto vec = (*encoderPtr)();
    std::stringstream sbuf;
    for(auto str: vec){
        sbuf<<str<<' ';
    }
    std::string tmp = sbuf.str();
    char* buf = new char[tmp.size()];
    strcpy(buf, tmp.c_str());
    return buf;
}

void EMSCRIPTEN_KEEPALIVE recEnc(){
    delete encoderPtr;
}

void EMSCRIPTEN_KEEPALIVE recBuf(){
    delete[] retBuf;
}