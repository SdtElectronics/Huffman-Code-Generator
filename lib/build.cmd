emcc .\wasmWrapper.cxx .\HTF.cxx -s WASM=1 -std=c++17 -o hello.html -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' -s EXPORTED_FUNCTIONS="['_nEncoder', '_retCode', '_recEnc', '_recBuf']"
