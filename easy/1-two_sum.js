/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
var twoSum = function(nums, target) {
    let hashSet = new Map();
    hashSet.set(nums[0], 0);
    for (let i = 1; i < nums.length; i++) {
        if (hashSet.has(target - nums[i])) {
            return [hashSet.get(target - nums[i]), i];
        } else {
            hashSet.set(nums[i], i);
        }
    }
};

console.log(twoSum([2,7,11,15], 9));
console.log(twoSum([3,2,4], 6));
console.log(twoSum([3,3], 6));