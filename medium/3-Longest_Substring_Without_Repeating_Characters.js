/**
 * @param {string} s
 * @return {number}
 */
var lengthOfLongestSubstring = function(s) {
    let start = 0, end = 0, maxLen = 0;
    let map = new Map();
    while (end !== s.length && !map.has(s[end])) {
        map.set(s[end], end);
        end++;
    }
    maxLen = end > maxLen ? end : maxLen;
    while (end < s.length) {
        if (map.has(s[end])) {
            let newStart = map.get(s[end]) + 1;
            for (let i = start; i < newStart; i++) {
                map.delete(s[i]);
            }
            start = newStart;
            map.set(s[end], end);
            end++;
        } else {
            map.set(s[end], end);
            end++;
            maxLen = (end - start) > maxLen ? (end - start) : maxLen;
        }
    }
    return maxLen;
};

console.log(lengthOfLongestSubstring("abcabcbb")); // 3
console.log(lengthOfLongestSubstring("bbbbb")); // 1
console.log(lengthOfLongestSubstring("pwwkew")); // 3
console.log(lengthOfLongestSubstring("tmmzuxt")); // 5
