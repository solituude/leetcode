// Definition for singly-linked list.
function ListNode(val, next) {
    this.val = (val === undefined ? 0 : val)
    this.next = (next === undefined ? null : next)
}

/**
 * @param {ListNode} l1
 * @param {ListNode} l2
 * @return {ListNode}
 */
var addTwoNumbers = function (l1, l2) {
    let extra = 0;
    let head = new ListNode((l1.val + l2.val + extra) % 10);
    if (l1.val + l2.val + extra > 9) {
        extra = 1;
    } else {
        extra = 0;
    }
    let curr = head;
    l1 = l1.next;
    l2 = l2.next;

    while (l1 !== null && l2 !== null) {
        curr.next = new ListNode((l1.val + l2.val + extra) % 10);
        if (l1.val + l2.val + extra > 9) {
            extra = 1;
        } else {
            extra = 0;
        }
        curr = curr.next;
        l1 = l1.next;
        l2 = l2.next;
    }

    while (l1 !== null) {
        curr.next = new ListNode((l1.val + extra) % 10);
        if (l1.val + extra > 9) {
            extra = 1;
        } else {
            extra = 0;
        }
        curr = curr.next;
        l1 = l1.next;
    }

    while (l2 !== null) {
        curr.next = new ListNode((l2.val + extra) % 10);
        if (l2.val + extra > 9) {
            extra = 1;
        } else {
            extra = 0;
        }
        curr = curr.next;
        l2 = l2.next;
    }
    if (extra !== 0) {
        curr.next = new ListNode(1);
    }
    return head;
};

let a1 = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1], a2 = [5, 6, 4],
    l1, l2;

function arrToList(arr) {
    if (arr.length === 0) {
        return null;
    }
    let head = new ListNode(arr[0]);
    let currNode = head;
    for (let i = 1; i < arr.length; i++) {
        currNode.next = new ListNode(arr[i]);
        currNode = currNode.next;
    }
    return head;
}

l1 = arrToList(a1);
l2 = arrToList(a2);
let r = addTwoNumbers(l1, l2);
console.log(r);