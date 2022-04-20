function factorial(num) {
    if(num<=1) return num;
    else return num*factorial(num-1);
}

self.addEventListener("message", function(e) {
    var data = e.data;
    var returnValue = factorial(data.value);

    this.postMessage(returnValue);
}, false);