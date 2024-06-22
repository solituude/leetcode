/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number}
 */
var numberOfSubarrays = function(nums, k) {
    let result = 0, minLeftInd = -1, maxRightInd = nums.length, rightPart, leftPart;
    const oddIndArray = [];
    for (let i = 0; i < nums.length; i++) {
        if (nums[i] % 2 !== 0) {
            oddIndArray.push(i);
        }
    }

    for (let i = k - 1; i < oddIndArray.length; i++) {
        let leftPointerWindow = i - k + 1, rightPointerWindow = i;
        leftPart = oddIndArray[leftPointerWindow] - minLeftInd - 1;
        minLeftInd = oddIndArray[leftPointerWindow];
        if (i !== oddIndArray.length - 1) {
            rightPart = oddIndArray[rightPointerWindow + 1] - oddIndArray[rightPointerWindow] - 1;
        } else {
            rightPart = maxRightInd - oddIndArray[rightPointerWindow] - 1;
        }
        result += 1 + leftPart + rightPart + (leftPart * rightPart);
    }
    return result;
};