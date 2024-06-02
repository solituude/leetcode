/**
 * @param {number[]} nums
 * @return {number}
 */
var lengthOfLIS = function(nums) {
    const bestArray = [{currInd: 0, lenSeq: 1}];
    let globalMaxLen = 1;

    for (let i = 0; i < nums.length; i++) {
        let maxLen = 0;
        let j = bestArray.length - 1;
        let currNum = nums[i];

        while (j >= 0) {
            if (bestArray[j].lenSeq > maxLen && nums[bestArray[j].currInd] < currNum) {
                maxLen = bestArray[j].lenSeq;
            }
            j--;
        }
        if (globalMaxLen < maxLen + 1)
            globalMaxLen = maxLen + 1;
        bestArray.push({currInd: i, lenSeq: maxLen + 1});
    }
    return globalMaxLen;
};

console.log(lengthOfLIS([10,9,2,5,3,7,101,18]));
console.log(lengthOfLIS([0,1,0,3,2,3]));
console.log(lengthOfLIS([7,7,7,7,7,7,7]));
