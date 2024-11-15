#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100

typedef struct Node {
    char word[100]; // Từ
    struct Node* next; // Con trỏ đến node tiếp theo
} Node;

// Hàm khởi tạo node mới
Node* createNode(char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->next = NULL;
    return newNode;
}

// Hàm thêm một node vào cuối danh sách liên kết
void appendNode(Node** head, char* word) {
    Node* newNode = createNode(word);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Hàm đếm số lần xuất hiện của một từ trong danh sách
int countWord(Node* head, char* word) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->word, word) == 0) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}

// Hàm tìm từ xuất hiện nhiều nhất
void findMostFrequentWord(Node* head) {
    Node* temp = head;
    char mostFrequentWord[100];
    int maxCount = 0;

    while (temp != NULL) {
        int count = countWord(head, temp->word);
        if (count > maxCount) {
            maxCount = count;
            strcpy(mostFrequentWord, temp->word);
        }
        temp = temp->next;
    }

    printf("Tu xuat hien nhieu nhat: %s\n", mostFrequentWord);
}

// Hàm loại bỏ từ láy trong danh sách
void removeRedundantWords(Node* head) {
    Node* temp = head;
    while (temp != NULL && temp->next != NULL) {
        if (strcmp(temp->word, temp->next->word) == 0) {
            Node* redundantNode = temp->next;
            temp->next = temp->next->next;
            free(redundantNode);
        } else {
            temp = temp->next;
        }
    }
}

// Hàm đếm số từ vựng trong câu
int countVocabulary(Node* head) {
    Node* temp = head;
    char uniqueWords[MAX_WORDS][100];
    int uniqueCount = 0;

    while (temp != NULL) {
        int isUnique = 1;
        for (int i = 0; i < uniqueCount; i++) {
            if (strcmp(temp->word, uniqueWords[i]) == 0) {
                isUnique = 0;
                break;
            }
        }
        if (isUnique) {
            strcpy(uniqueWords[uniqueCount], temp->word);
            uniqueCount++;
        }
        temp = temp->next;
    }

    return uniqueCount;
}

// Hàm viết lại câu từ danh sách liên kết (sau khi loại bỏ từ láy)
void rewriteSentence(Node* head) {
    Node* temp = head;
    printf("Cau moi: ");
    while (temp != NULL) {
        printf("%s ", temp->word);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;

    // Thêm các từ vào danh sách liên kết
    appendNode(&head, "xanh");
    appendNode(&head, "xanh");
    appendNode(&head, "do");
    appendNode(&head, "vang");
    appendNode(&head, "vang");

    // Xử lý từ láy
    removeRedundantWords(head);

    // Tìm từ xuất hiện nhiều nhất
    findMostFrequentWord(head);

    // Đếm số từ vựng
    int vocabularyCount = countVocabulary(head);
    printf("So tu vung trong cau: %d\n", vocabularyCount);

    // Viết lại câu sau khi loại bỏ từ láy
    rewriteSentence(head);

    return 0;
}
