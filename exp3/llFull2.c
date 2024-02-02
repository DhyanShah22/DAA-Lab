#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int digit) {
    Node* newNode = malloc(sizeof(Node));
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

    while (num1 !=NULL  || num2 != NULL ||  carry != 0) {
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
    Node* result = NULL;
    Node* tail = NULL;
    int borrow = 0;

    while (num1 != NULL || num2 != NULL) {
        int diff = (num1 ? num1->data : 0) - (num2 ? num2->data : 0) - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        if (result == NULL) {
            result = createNode(diff);
            tail = result;
        } else {
            tail->next = createNode(diff);
            tail = tail->next;
        }

        if (num1) num1 = num1->next;
        if (num2) num2 = num2->next;
    }

    return result;
}

Node* multiply(Node* num1, Node* num2) {
    Node* result = createNode(0);
    int multiplier = 1;

    while (num2 != NULL) {
        Node* partialProduct = NULL;
        Node* partialProductTail = NULL;
        int carry = 0;

        for (int i = 0; i < multiplier - 1; ++i) {
            insertDigit(&partialProduct, 0);
            if (partialProductTail == NULL) {
                partialProductTail = partialProduct;
            }
        }

        while (num1 != NULL) {
            int product = num1->data * num2->data + carry;
            carry = product / 10;
            product %= 10;

            if (partialProduct == NULL) {
                partialProduct = createNode(product);
                partialProductTail = partialProduct;
            } else {
                partialProductTail->next = createNode(product);
                partialProductTail = partialProductTail->next;
            }

            num1 = num1->next;
        }

        if (carry > 0) {
            partialProductTail->next = createNode(carry);
        }

        result = add(result, partialProduct);
        freeList(partialProduct);

        num1 = num1;
        num2 = num2->next;
        ++multiplier;
    }

    return result;
}

Node* power(Node* base, unsigned int exponent) {
    Node* result = createNode(1);
    while (exponent > 0) {
        if (exponent & 1) {
            result = multiply(result, base);
        }
        base = multiply(base, base);
        exponent >>= 1;
    }
    return result;
}

int main() {
    printf("Name: Khushi Shah\n");
    printf("Roll No: 22BCP258\n");

    Node* num1 = NULL;
    Node* num2 = NULL;

    int digit;

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

    int choice;
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    Node* result;
    switch (choice) {
        case 1:
            result = add(num1, num2);
            printf("Addition Result: ");
            printNumber(result);
            break;
        case 2:
            result = subtract(num1, num2);
            printf("Subtraction Result: ");
            printNumber(result);
            break;
        case 3:
            result = multiply(num1, num2);
            printf("Multiplication Result: ");
            printNumber(result);
            break;
        case 4: {
            unsigned int exponent;
            printf("Enter the exponent (a positive integer): ");
            scanf("%u", &exponent);
            result = power(num1, exponent);
            printf("Exponentiation Result: ");
            printNumber(result);
            break;
        }
        default:
            printf("Invalid choice\n");
    }

    freeList(result);
    freeList(num1);
    freeList(num2);

    return 0;
}