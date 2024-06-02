/**
 * @param {character[]} s
 * @return {void} Do not return anything, modify s in-place instead.
 */
var reverseString = function(s) {
    for (let i = 0; i < Math.floor(s.length / 2); i++) {
        s[i] = String.fromCharCode(
            (s[i].charCodeAt(0) ^ s[s.length - i - 1].charCodeAt(0))
        );
        s[s.length - i - 1] = String.fromCharCode(
            (s[i].charCodeAt(0) ^ s[s.length - i - 1].charCodeAt(0))
        );
        s[i] = String.fromCharCode(
            (s[i].charCodeAt(0) ^ s[s.length - i - 1].charCodeAt(0))
        );
    }
};
s = ["H","a","n","n","a","h"]
reverseString(s)
console.log(s);