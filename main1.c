#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa một cấu trúc cho mỗi node (mỗi file)
typedef struct Node {
    char fileName[100];        // Tên file
    long long fileSize;        // Kích thước file (tính bằng bytes)
    long long timestamp;       // Thời gian tạo file (tính bằng timestamp)
    struct Node* next;         // Con trỏ đến node tiếp theo
} Node;

// Khởi tạo danh sách rỗng
Node* head = NULL;

// Hàm tạo một node mới
Node* createNode(char* fileName, long long fileSize, long long timestamp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->fileName, fileName);
    newNode->fileSize = fileSize;
    newNode->timestamp = timestamp;
    newNode->next = NULL;
    return newNode;
}

// Hàm chèn file theo thứ tự thời gian
void insertFile(char* fileName, long long fileSize, long long timestamp) {
    Node* newNode = createNode(fileName, fileSize, timestamp);
    if (head == NULL || head->timestamp > timestamp) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != NULL && current->next->timestamp < timestamp) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Hàm tính tổng kích thước file trong danh sách
long long calculateTotalSize() {
    long long totalSize = 0;
    Node* current = head;
    while (current != NULL) {
        totalSize += current->fileSize;
        current = current->next;
    }
    return totalSize;
}

// Hàm tìm và xóa node có kích thước nhỏ nhất
void deleteSmallestFile() {
    if (head == NULL) return;

    Node *current = head, *smallest = head, *prev = NULL, *prevSmallest = NULL;

    while (current != NULL) {
        if (current->fileSize < smallest->fileSize) {
            smallest = current;
            prevSmallest = prev;
        }
        prev = current;
        current = current->next;
    }

    // Nếu smallest là head
    if (smallest == head) {
        head = head->next;
    } else {
        prevSmallest->next = smallest->next;
    }
    free(smallest);
}

// Hàm xóa các file nhỏ nhất cho đến khi tổng kích thước <= 32GB
void backupToUSB() {
    long long USB_SIZE = 34359738368LL;  // 32GB in bytes
    while (calculateTotalSize() > USB_SIZE) {
        deleteSmallestFile();
    }
}

// Hàm in danh sách các file
void printFiles() {
    Node* current = head;
    printf("Danh sach cac file:\n");
    while (current != NULL) {
        printf("File: %s, Size: %lld bytes, Timestamp: %lld\n", current->fileName, current->fileSize, current->timestamp);
        current = current->next;
    }
}

int main() {
    // Thêm một vài file vào danh sách (thư mục ban đầu)
    insertFile("file1.txt", 500000, 1609459200);   // File 1: 500KB, 01-01-2021
    insertFile("file2.txt", 1200000, 1609545600);  // File 2: 1.2MB, 02-01-2021
    insertFile("file3.txt", 2000000, 1609632000);  // File 3: 2MB, 03-01-2021
    insertFile("file4.txt", 30000000, 1609718400); // File 4: 30MB, 04-01-2021

    // In danh sách file ban đầu
    printf("Danh sach file ban dau:\n");
    printFiles();

    // Copy một file từ thư mục khác sang thư mục này
    printf("\nCopy file 'newfile.txt' (15MB, 05-01-2021) vao thu muc...\n");
    insertFile("newfile.txt", 15000000, 1609804800); // File mới: 15MB, 05-01-2021

    // Hiển thị danh sách file sau khi thêm
    printFiles();

    // Hiển thị tổng kích thước các file
    printf("\nTong kich thuoc cac file: %lld bytes\n", calculateTotalSize());

    // Sao lưu vào USB, nếu vượt quá 32GB thì xóa các file có kích thước nhỏ nhất
    printf("\nTien hanh sao luu vao USB...\n");
    backupToUSB();

    // Hiển thị danh sách file sau khi sao lưu
    printf("\nDanh sach file sau khi sao luu:\n");
    printFiles();

    // Hiển thị tổng kích thước sau khi sao lưu
    printf("\nTong kich thuoc sau khi sao luu: %lld bytes\n", calculateTotalSize());

    return 0;
}
