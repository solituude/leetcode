function TreeNode(val, left, right) {
    this.val = (val === undefined ? 0 : val)
    this.left = (left === undefined ? null : left)
    this.right = (right === undefined ? null : right)
}

/**
 * @param {TreeNode} root
 * @param {number} start
 * @return {number}
 */
var amountOfTime = function (root, start) {
    if (root.left === null && root.right === null) return 0;
    let graph = {};
    let visited = new Set();
    let queue = [];
    let countMinutes = 1;
    const dfs = (node) => {
        if (node !== null) {
            if (!graph[node.val]) graph[node.val] = [];

            if (node.left !== null) {
                if (!graph[node.left.val]) graph[node.left.val] = [];

                graph[node.val].push(node.left.val);
                graph[node.left.val].push(node.val);
                dfs(node.left);
            }
            if (node.right !== null) {
                if (!graph[node.right.val]) graph[node.right.val] = [];

                graph[node.val].push(node.right.val);
                graph[node.right.val].push(node.val);
                dfs(node.right);
            }
        }
    }
    dfs(root);

    visited.add(start);
    queue = graph[start];
    for (let i = 0; i < queue.length; i++) {
        visited.add(queue[i]);
    }
    while (queue.length !== 0) {
        let currNode = queue.shift();
        let isAdded = false;
        for (let i = 0; i < graph[currNode].length; i++) {
            if (!visited.has(graph[currNode][i])){
                isAdded = true;
                visited.add(graph[currNode][i]);
                queue.push(graph[currNode][i]);
            }
        }
        if (isAdded) countMinutes++;
    }
    return countMinutes;
};


function insertLevelOrder(arr, root, i) {
    if (i < arr.length) {
        let temp = null;
        if (arr[i] !== null) {
            temp = new TreeNode(arr[i]);
            root = temp;

            root.left = insertLevelOrder(arr, root.left, 2 * i + 1);
            root.right = insertLevelOrder(arr, root.right, 2 * i + 2);
        }
        return root;
    }
    return null;
}


// let arr = [1, 5, 3, null, 4, 10, 6, 9, 2];
// let i = 0;
// while (i < arr.length) {
//     if (arr[i] === null) {
//         if (i * 2 + 1 < arr.length) arr.splice(i * 2 + 1, 0, null);
//         if (i * 2 + 1 < arr.length) arr.splice(i * 2 + 2, 0, null);
//     }
//     i++;
// }
// let root = insertLevelOrder(arr, null, 0);
// console.log(amountOfTime(root, 3));


arr = [1,2,null,3,null,4,null,5]
i = 0;
while (i < arr.length) {
    if (arr[i] === null) {
        if (i * 2 + 1 < arr.length) arr.splice(i * 2 + 1, 0, null);
        if (i * 2 + 1 < arr.length) arr.splice(i * 2 + 2, 0, null);
    }
    i++;
}
root = insertLevelOrder(arr, null, 0);
console.log(amountOfTime(root, 3))