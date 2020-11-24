function getHFC(probs, syms = [0, 1]){
    const retLen = probs.length;
    const symsLen = syms.length;
    const pArray = new Float64Array(retLen);
    const sArray = new Int32Array(symsLen);
    probs.forEach((prob, i) => pArray[i] = prob);
    syms.forEach((sym, i) => sArray[i] = sym);
    const pBuf = Module._malloc(pArray.length * pArray.BYTES_PER_ELEMENT);
    const sBuf = Module._malloc(sArray.length * sArray.BYTES_PER_ELEMENT);
    Module.HEAPF64.set(pArray, pBuf / pArray.BYTES_PER_ELEMENT);
    Module.HEAP32.set(sArray, sBuf / sArray.BYTES_PER_ELEMENT);
    Module.ccall("nEncoder", null, 
                ["number", "number", "number", "number"], 
                [pBuf, retLen, sBuf, symsLen]);
    const ret = UTF8ToString(Module._getCode()).split(' ');
    ret.pop();
    Module._recEnc();
    Module._free(pBuf);
    Module._free(sBuf);
    return ret;
}