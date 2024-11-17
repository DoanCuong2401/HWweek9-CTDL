#include <stdio.h>
#include <stdlib.h>

#define MAX_WORDS 100

typedef struct Node {
    char word[100]; // Từ
    struct Node* next; // Con trỏ đến node tiếp theo
} Node;

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

// Hàm khởi tạo node mới
Node* createNode(char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    StringCopy(newNode->word, word, sizeof(newNode->word));  
    newNode->next = NULL;
    return newNode;
}


// Hàm thêm một node vào cuối danh sách liên kết
void insertNode(Node** head, char* word) {
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
        int i = 0;
        // So sánh từng ký tự của chuỗi word và temp->word
        while (word[i] != '\0' && temp->word[i] != '\0') {
            if (word[i] != temp->word[i]) {
                break; // Nếu có sự khác biệt, thoát khỏi vòng lặp
            }
            i++;
        }

        // Kiểm tra nếu chuỗi word và temp->word giống nhau (kết thúc cùng lúc)
        if (word[i] == '\0' && temp->word[i] == '\0') {
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
            StringCopy(mostFrequentWord, temp->word, sizeof(mostFrequentWord));
        }
        temp = temp->next;
    }

    printf("Tu xuat hien nhieu nhat: %s\n", mostFrequentWord);
}

// Hàm loại bỏ từ láy trong danh sách
void removeWords(Node* head) {
    Node* temp = head;

    while (temp != NULL && temp->next != NULL) {
        int i = 0;
        // So sánh từng ký tự của temp->word và temp->next->word
        while (temp->word[i] != '\0' && temp->next->word[i] != '\0') {
            if (temp->word[i] != temp->next->word[i]) {
                break;  // Nếu có sự khác biệt, thoát khỏi vòng lặp
            }
            i++;
        }

        // Kiểm tra nếu hai chuỗi giống nhau
        if (temp->word[i] == '\0' && temp->next->word[i] == '\0') {
            // Nếu giống nhau, xóa nút tiếp theo (redundantNode)
            Node* redundantNode = temp->next;
            temp->next = temp->next->next;
            free(redundantNode);
        } else {
            // Nếu không giống nhau, di chuyển tới nút kế tiếp
            temp = temp->next;
        }
    }
}


// Hàm đếm số từ vựng trong câu
int countVocabulary(Node* head) {
    Node* temp = head;
    char Words[MAX_WORDS][100];
    int Count = 0;

    while (temp != NULL) {
        int a = 1;
        // Kiểm tra xem từ hiện tại đã có trong danh sách Words chưa
        for (int i = 0; i < Count; i++) {
            int j = 0;
            // So sánh từng ký tự giữa temp->word và Words[i]
            while (temp->word[j] != '\0' && Words[i][j] != '\0') {
                if (temp->word[j] != Words[i][j]) {
                    break;  // Nếu có sự khác biệt, thoát khỏi vòng lặp
                }
                j++;
            }

            // Kiểm tra nếu cả hai chuỗi kết thúc cùng lúc
            if (temp->word[j] == '\0' && Words[i][j] == '\0') {
                a = 0;  // Nếu giống nhau, đánh dấu là không duy nhất
                break;
            }
        }

        // Nếu từ là duy nhất, thêm vào mảng Words
        if (a) {
            StringCopy(Words[Count], temp->word, sizeof(Words[Count]));
            Count++;
        }
        temp = temp->next;
    }

    return Count;
}


// Hàm viết lại câu từ danh sách liên kết (sau khi loại bỏ từ láy)
void writeSentence(Node* head) {
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
    insertNode(&head, "xanh");
    insertNode(&head, "xanh");
    insertNode(&head, "do");
    insertNode(&head, "vang");
    insertNode(&head, "vang");

    // Xử lý từ láy
    removeWords(head);

    // Tìm từ xuất hiện nhiều nhất
    findMostFrequentWord(head);

    // Đếm số từ vựng
    int vocabularyCount = countVocabulary(head);
    printf("So tu vung trong cau: %d\n", vocabularyCount);

    // Viết lại câu sau khi loại bỏ từ láy
    writeSentence(head);

    return 0;
}
