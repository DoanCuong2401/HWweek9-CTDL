#include <stdio.h>
#include <stdlib.h>

// Định nghĩa một cấu trúc cho mỗi node (mỗi file)
typedef struct Node {
    char fileName[100];        // Tên file
    long long fileSize;        // Kích thước file (tính bằng bytes)
    long long timestamp;       // Thời gian tạo file (tính bằng timestamp)
    struct Node* next;         // Con trỏ đến node tiếp theo
} Node;

// Khởi tạo danh sách rỗng
Node* head = NULL;

// Hàm sao chép chuỗi
void StringCopy(char* begin, const char* start, size_t destSize) {
    // Kiểm tra nếu đích hoặc nguồn là NULL
    if (begin == NULL || start == NULL) {
        return;
    }
    
    // Sao chép từng ký tự từ nguồn sang đích, đảm bảo không vượt quá kích thước
    size_t i;
    for (i = 0; i < destSize - 1 && start[i] != '\0'; i++) {
        begin[i] = start[i];
    }
    
    // Đảm bảo chuỗi đích luôn kết thúc bằng '\0'
    begin[i] = '\0';
}

// Hàm tạo một node mới
Node* createNode(char* fileName, long long fileSize, long long timestamp) {
    Node* newNode = (Node*)malloc(sizeof(Node));    // cấp phát bộ nhớ cho 1 node mới
    StringCopy(newNode->fileName, fileName, sizeof(newNode->fileName));  // sao chép tên file vào fileName của node mới
    newNode->fileSize = fileSize;   // gán kích thước file cho fileSize
    newNode->timestamp = timestamp; // gán thời gian tạo file cho timestamp
    newNode->next = NULL;
    return newNode;
}

// Hàm chèn file theo thứ tự thời gian
void insertFile(char* fileName, long long fileSize, long long timestamp) {
    Node* newNode = createNode(fileName, fileSize, timestamp);  // Tạo node mới
    if (head == NULL || head->timestamp > timestamp) {  // Nếu danh sách rỗng hoặc node mới có timestamp nhỏ hơn node đầu tiên
        newNode->next = head;   // Chèn node mới vào đầu danh sách
        head = newNode;
    } else {
        Node* current = head;   // Tìm vị trí phù hợp để chèn
        while (current->next != NULL && current->next->timestamp < timestamp) { // Chèn vào thời gian phù hợp
            current = current->next;
        }
        // Chèn vào cuối danh sách
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Hàm tính tổng kích thước file trong danh sách
long long calculateTotalSize() {
    long long totalSize = 0;   // Khởi tạo tổng kích thước ban đầu bằng 0
    Node* current = head;      // Đặt con trỏ current trỏ đến node đầu tiên trong danh sách
    // Duyệt qua từng node trong danh sách
    while (current != NULL) {
        totalSize += current->fileSize; // Cộng kích thước file của node hiện tại vào totalSize
        current = current->next;       // Di chuyển con trỏ `current` đến node tiếp theo
    }

    return totalSize;          // Trả về tổng kích thước của tất cả các file
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

    // Hiển thị danh sách file sau khi sao lưu
    printf("\nDanh sach file sau khi sao luu:\n");
    printFiles();

    // Hiển thị tổng kích thước sau khi sao lưu
    printf("\nTong kich thuoc sau khi sao luu: %lld bytes\n", calculateTotalSize());

    return 0;
}
