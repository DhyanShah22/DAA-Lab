#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Node* addNode(struct Node* head, int data) {
    if (head == NULL) {
        head = createNode(data);
        return head;
    }
    struct Node* temp = createNode(data);
    temp->next = head;
    head = temp;
    return head;
}

struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* forw = NULL;
    while (current != NULL) {
        forw = current->next;
        current->next = prev;
        prev = current;
        current = forw;
    }
    return prev;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

struct Node* addNodeAtEnd(struct Node* head, int data) {
    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = createNode(data);
    return head;
}

struct Node* addLists(struct Node* first, struct Node* second) {
    first = reverseList(first);
    second = reverseList(second);
    struct Node* resultHead = NULL;
    int carry = 0;
    while (first != NULL || second != NULL) {
        int sum = carry;
        if (first != NULL) {
            sum += first->data;
            first = first->next;
        }
        if (second != NULL) {
            sum += second->data;
            second = second->next;
        }
        carry = sum / 10;
        resultHead = addNode(resultHead, sum % 10);
    }
    if (carry > 0) {
        resultHead = addNode(resultHead, carry);
    }
    return resultHead;
}

int length(struct Node* head) {
    int len = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        len++;
        temp = temp->next;
    }
    return len;
}

struct Node* multiplyList(struct Node* first, struct Node* second) {
    first = reverseList(first);
    second = reverseList(second);
    int sLen = length(second);
    int pow = 0;
    struct Node* ans = NULL;
    while (second != NULL) {
        struct Node* temp = NULL;
        int carry = 0;
        struct Node* tempFirst = first;
        while (tempFirst != NULL) {
            int sum = carry + (tempFirst->data * second->data);
            carry = sum / 10;
            temp = addNode(temp, sum % 10);
            tempFirst = tempFirst->next;
        }
        if (carry > 0) {
            temp = addNode(temp, carry);
        }
        for (int i = 0; i < pow; i++) {
            temp = addNodeAtEnd(temp, 0);
        }
        ans = addLists(ans, temp);
        second = second->next;
        pow++;
    }
    return ans;
}

int main() {
    struct Node* first = NULL;
    struct Node* second = NULL;
    int m, n, value;
    printf("Enter the first number: ");
    scanf("%d", &m);
    while (m != 0) {
        value = m % 10;
        first = addNode(first, value);
        m /= 10;
    }
    printf("Enter the second number: ");
    scanf("%d", &n);
    while (n != 0) {
        value = n % 10;
        second = addNode(second, value);
        n /= 10;
    }
    printf("First number: ");
    printList(first);
    printf("Second number: ");
    printList(second);
    struct Node* result = multiplyList(first, second);
    printf("Result: ");
    printList(result);
    return 0;
}