/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} p
 * @param {TreeNode} q
 * @return {boolean}
 */
var isSameTree = function(p, q) {
    let queueP = [p];
    let queueQ = [q];
    let isSame = true;
    while (isSame && queueP.length !== 0 && queueQ.length !== 0) {
        let currP = queueP.shift();
        let currQ = queueQ.shift();
        let countAdd = 0;
        if (currP !== null && currQ !== null && currP.val !== currQ.val) {
            isSame = false;
        } else {
            if (currP !== null) {
                queueP.push(currP.left);
                queueP.push(currP.right);
                countAdd++;
            }
            if (currQ !== null) {
                queueQ.push(currQ.left);
                queueQ.push(currQ.right);
                countAdd++;
            }
        }
        if (countAdd % 2 !== 0) isSame = false;
    }
    return isSame;
};