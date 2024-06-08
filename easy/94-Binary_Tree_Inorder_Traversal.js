/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} root
 * @return {number[]}
 */
var inorderTraversal = function(root) {
    if (root !== null) {
        const inorderArray = [], stack = [];
        const dfs = (node) => {
            if (node === null) {
                stack.length !== 0 && inorderArray.push(stack.pop());
                return;
            } else if (node.left === null && node.right === null) {
                inorderArray.push(node.val);
                stack.length !== 0 && inorderArray.push(stack.pop());
                return;
            }
            stack.push(node.val);
            dfs(node.left);
            dfs(node.right);
        }
        dfs(root);
        return inorderArray;
    }
    return [];
};