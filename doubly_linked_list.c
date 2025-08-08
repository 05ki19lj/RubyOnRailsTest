#include <stdio.h>
#include <stdlib.h>

// 節點結構
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 建立新節點
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// 在頭部插入
void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head != NULL) {
        newNode->next = *head;
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// 在尾部插入
void insertAtTail(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// 刪除節點
void deleteNode(Node** head, int key) {
    Node* temp = *head;
    while (temp != NULL) {
        if (temp->data == key) {
            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                *head = temp->next; // 刪的是頭節點
            if (temp->next != NULL)
                temp->next->prev = temp->prev;
            free(temp);
            return;
        }
        temp = temp->next;
    }
}

// 正向遍歷
void traverseForward(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// 反向遍歷
void traverseBackward(Node* head) {
    Node* temp = head;
    if (temp == NULL) return;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->prev;
    }
    printf("NULL\n");
}

// 測試主程式
int main() {
    Node* head = NULL;

    insertAtHead(&head, 3);
    insertAtHead(&head, 2);
    insertAtHead(&head, 1);
    insertAtTail(&head, 4);

    printf("正向遍歷: ");
    traverseForward(head);

    printf("反向遍歷: ");
    traverseBackward(head);

    deleteNode(&head, 2);
    printf("刪除 2 後正向遍歷: ");
    traverseForward(head);

    return 0;
}