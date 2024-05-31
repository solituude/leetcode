/**
 * @param {string[]} bank
 * @return {number}
 */
var numberOfBeams = function(bank) {
    let ans = 0, count = 0;
    for (let i = 0; i < bank.length; i++) {
        let countSecondRow = 0;
        for (let j = 0; j < bank[i].length; j++) {
            countSecondRow += bank[i][j] === '0' ? 0 : 1;
        }
        ans += count * countSecondRow;
        if (countSecondRow !== 0) {
            count = countSecondRow;
        }
    }
    return ans;
};


console.log(numberOfBeams(["011001","000000","010100","001000"]));
console.log(numberOfBeams(["000","111","000"]));