/**
 * @param {number} n
 * @return {number}
 */
var climbStairs = function(n) {
    const dp = [];
    for (let i = 0; i <= Math.min(n, 2); i++) {
        dp.push(i);
    }
    for (let i = 3; i <= n; i++) {
        dp.push(dp[i - 1] + dp[i - 2]);
    }
    return dp[n];
};

console.log(climbStairs(1));
console.log(climbStairs(3));
console.log(climbStairs(4));