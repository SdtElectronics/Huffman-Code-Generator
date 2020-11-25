const sym = document.getElementById("symsIn"),
      prb = document.getElementById("probIn"),
      gen = document.getElementById("gen"),
      dsp = document.getElementById("out"),
      cls = document.getElementById("cls"),
      otp = document.getElementById("outRowTmpl");

function supportWasm(){
    try {
        if (typeof WebAssembly === "object"
            && typeof WebAssembly.instantiate === "function") {
            const module = new WebAssembly.Module(Uint8Array.of(0x0, 0x61, 0x73, 0x6d, 0x01, 0x00, 0x00, 0x00));
            if (module instanceof WebAssembly.Module)
                return new WebAssembly.Instance(module) instanceof WebAssembly.Instance;
        }
    } catch (e) {
    }
    return false;
};

gen.onclick = ()=>{
    dsp.innerHTML = "";
    const probs = prb.textContent.split(",").map(prob => parseFloat(prob));
    const syms = sym.textContent.split(",").map(sym => parseInt(sym));
    if (prb.textContent == "") {
		alert("Please enter probabilities!");
		return;
	}
    if (sym.textContent == "") {
		alert("Please enter symbols!");
		return;
    }
    if(probs.some(e => isNaN(e)) || syms.some(e => isNaN(e))){
        alert("Please enter valid numbers!");
		return;
    }
    getHFC(probs, syms).forEach((code, i) => {
        const otr = otp.content.getElementById("outRow");
        otr.textContent = `${probs[i]}: ${code}`;
        const clone = document.importNode(otp.content, true);
        dsp.appendChild(clone);
    });
    dsp.style.display = "block";
    cls.style.display = "block";
}

cls.onclick = ()=>{
    dsp.innerHTML = "";
    prb.textContent = "";
    sym.textContent = "";
    dsp.style.display = "none";
    cls.style.display = "none";
}

window.onload = ()=>{
    if(!supportWasm()){
        alert("Your browser does not support WebAssembly.")
    }

}
