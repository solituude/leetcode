/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} head
 * @return {ListNode}
 */
var removeNodes = function(head) {
    const deque = [];
    let currNode = head;
    deque.push(currNode);
    currNode = currNode.next;
    while (currNode !== null) {
        if (deque[deque.length - 1].val < currNode.val) {
            while (deque.length !== 0 && deque[deque.length - 1] !== null && deque[deque.length - 1].val < currNode.val) {
                deque.pop();
            }
        }
        deque.push(currNode);
        currNode = currNode.next;
    }
    let lastPushed = deque.pop();
    lastPushed.next = null;
    while (deque.length !== 0) {
        const currNode = deque.pop();
        currNode.next = lastPushed;
        lastPushed = currNode;
    }
    return lastPushed;
};