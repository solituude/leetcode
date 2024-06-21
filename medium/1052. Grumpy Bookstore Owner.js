/**
 * @param {number[]} customers
 * @param {number[]} grumpy
 * @param {number} minutes
 * @return {number}
 */
var maxSatisfied = function(customers, grumpy, minutes) {
    let minSatisfied = 0, maxPrefixSatisfied = 0, currentPrefix = 0;
    const n = customers.length;

    if (minutes >= n) {
        return customers.reduce((sum, a) => sum + a, 0);
    }

    for (let i = 0; i < n; i++) {
        if (grumpy[i] === 0) {
            minSatisfied += customers[i];
        } else if (i < minutes) {
            maxPrefixSatisfied += customers[i];
            currentPrefix += customers[i];
        }
    }

    for (let i = minutes; i < n; i++) {
        if (grumpy[i] === 1) {
            currentPrefix += customers[i];
        }
        if (grumpy[i - minutes] === 1) {
            currentPrefix -= customers[i - minutes];
        }
        maxPrefixSatisfied = Math.max(maxPrefixSatisfied, currentPrefix);
    }
    return minSatisfied + maxPrefixSatisfied;
};

console.log(maxSatisfied([1,0,1,2,1,1,7,5], [0,1,0,1,0,1,0,1], 3));
console.log(maxSatisfied([1], [0], 1));