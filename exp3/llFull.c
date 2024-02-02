#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = digit;
    newNode->next = NULL;
    return newNode;
}

void insertDigit(Node** head, int digit) {
    Node* newNode = createNode(digit);
    newNode->next = *head;
    *head = newNode;
}

void printNumber(Node* head) {
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

Node* add(Node* num1, Node* num2) {
    Node* result = NULL;
    Node* tail = NULL;
    int carry = 0;

    while (num1 != NULL  || num2 != NULL  || carry != 0) {
        int sum = carry + (num1 ? num1->data : 0) + (num2 ? num2->data : 0);

        carry = sum / 10;
        sum = sum % 10;

        if (result == NULL) {
            result = createNode(sum);
            tail = result;
        } else {
            tail->next = createNode(sum);
            tail = tail->next;
        }

        if (num1) num1 = num1->next;
        if (num2) num2 = num2->next;
    }

    return result;
}

Node* subtract(Node* num1, Node* num2) {
    return createNode(0);
}

Node* multiply(Node* num1, Node* num2) {
    return createNode(0);
}

Node* power(Node* base, unsigned int exponent) {
    return createNode(0);
}

int main() {
    printf("Name: Dhyan Shah\n");
    printf("Roll No: 22BCP269\n");

    Node* num1 = NULL;
    Node* num2 = NULL;

    int digit;
    int choice;

    printf("Enter the first number digit by digit (enter -1 to finish):\n");
    while (1) {
        scanf("%d", &digit);
        if (digit == -1) {
            break;
        }
        insertDigit(&num1, digit);
    }

    printf("Enter the second number digit by digit (enter -1 to finish):\n");
    while (1) {
        scanf("%d", &digit);
        if (digit == -1) {
            break;
        }
        insertDigit(&num2, digit);
    }

    printf("\nSelect operation:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Exponentiation\n");

    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            Node* resultAdd = add(num1, num2);
            printf("Addition Result: ");
            printNumber(resultAdd);
            freeList(resultAdd);
            break;
        }
        case 2: {
            Node* resultSubtract = subtract(num1, num2);
            printf("Subtraction Result: ");
            printNumber(resultSubtract);
            freeList(resultSubtract);
            break;
        }
        case 3: {
            Node* resultMultiply = multiply(num1, num2);
            printf("Multiplication Result: ");
            printNumber(resultMultiply);
            freeList(resultMultiply);
            break;
        }
        case 4: {
            unsigned int exponent;
            printf("Enter the exponent (a positive integer): ");
            scanf("%u", &exponent);
            Node* resultPower = power(num1, exponent);
            printf("Exponentiation Result: ");
            printNumber(resultPower);
            freeList(resultPower);
            break;
        }
        default:
            printf("Invalid choice\n");
    }

    freeList(num1);
    freeList(num2);

    return 0;
}