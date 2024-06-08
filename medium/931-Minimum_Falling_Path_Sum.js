/**
 * @param {number[][]} matrix
 * @return {number}
 */
var minFallingPathSum = function(matrix) {
    let n = matrix.length;
    if (n === 1) return matrix[0][0];
    let ans = Infinity;
    let dp = [];
    dp.push([]);
    for (let i = 0; i < n; i++) {
        dp[0].push(matrix[0][i]);
    }

    for (let i = 1; i < n; i++) {
        dp.push([]);
        for (let j = 0; j < n; j++) {
            if (j === 0) {
                dp[i].push(matrix[i][j] + Math.min(dp[i - 1][j], dp[i - 1][j + 1]));
            } else if (j === n - 1) {
                dp[i].push(matrix[i][j] + Math.min(dp[i - 1][j - 1], dp[i - 1][j]));
            } else {
                dp[i].push(matrix[i][j] + Math.min(dp[i - 1][j - 1], dp[i - 1][j], dp[i - 1][j + 1]));
            }

            if (i === n - 1) {
                ans = ans > dp[i][j] ? dp[i][j] : ans;
            }
        }
    }

    return ans;
};

console.log(minFallingPathSum([[2,1,3],[6,5,4],[7,8,9]]));
console.log(minFallingPathSum([[-19,57],[-40,-5]]));
