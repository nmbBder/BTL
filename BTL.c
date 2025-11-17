#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

/* Hàm tạo node mới */
Node* createNode(int x) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (!p) {
        printf("Loi cap phat bo nho!\n");
        exit(1);
    }
    p->data = x;
    p->prev = p->next = NULL;
    return p;
}

/* Khởi tạo danh sách rỗng */
void initList(List* l) {
    l->head = l->tail = NULL;
}

/* Thêm vào cuối danh sách */
void append(List* l, int x) {
    Node* p = createNode(x);
    if (l->head == NULL) {
        l->head = l->tail = p;
    } else {
        l->tail->next = p;
        p->prev = l->tail;
        l->tail = p;
    }
}

/* In danh sách từ đầu tới cuối */
void printList(List l) {
    Node* p = l.head;
    if (!p) {
        printf("Danh sach rong.\n");
        return;
    }
    printf("Danh sach: ");
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/* In danh sách từ cuối tới đầu */
void printListReverse(List l) {
    Node* p = l.tail;
    if (!p) {
        printf("Danh sach rong.\n");
        return;
    }
    printf("Danh sach (nguoc): ");
    while (p) {
        printf("%d ", p->data);
        p = p->prev;
    }
    printf("\n");
}

/* Xóa 1 node cụ thể (giả sử node p thuộc danh sach l) */
void deleteNode(List* l, Node* p) {
    if (!p || !l->head) return;

    if (p == l->head && p == l->tail) { // duy nhất
        l->head = l->tail = NULL;
    } else if (p == l->head) {
        l->head = p->next;
        l->head->prev = NULL;
    } else if (p == l->tail) {
        l->tail = p->prev;
        l->tail->next = NULL;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    free(p);
}

/* Giải phóng toàn bộ danh sách */
void freeList(List* l) {
    Node* p = l->head;
    while (p) {
        Node* q = p->next;
        free(p);
        p = q;
    }
    l->head = l->tail = NULL;
}

/* Kiểm tra số hoàn hảo */
int isPerfect(int n) {
    if (n <= 1) return 0;
    int sum = 1; // 1 luôn là ước
    int r = (int)sqrt(n);
    for (int i = 2; i <= r; ++i) {
        if (n % i == 0) {
            sum += i;
            int other = n / i;
            if (other != i) sum += other;
        }
    }
    return sum == n;
}

/* Đếm số hoàn hảo trong danh sách */
int countPerfectNumbers(List l) {
    int cnt = 0;
    Node* p = l.head;
    while (p) {
        if (isPerfect(p->data)) cnt++;
        p = p->next;
    }
    return cnt;
}

/* Tìm min và max -- trả về 0 nếu rỗng, 1 nếu có kết quả (min và max via con trỏ) */
int findMinMax(List l, int* min, int* max) {
    if (!l.head) return 0;
    Node* p = l.head;
    *min = *max = p->data;
    p = p->next;
    while (p) {
        if (p->data < *min) *min = p->data;
        if (p->data > *max) *max = p->data;
        p = p->next;
    }
    return 1;
}

/* Xóa tất cả phần tử âm */
void deleteNegative(List* l) {
    Node* p = l->head;
    while (p) {
        Node* q = p->next;
        if (p->data < 0) deleteNode(l, p);
        p = q;
    }
}

/* Tính tổng các phần tử */
long long sumList(List l) {
    long long s = 0;
    Node* p = l.head;
    while (p) {
        s += p->data;
        p = p->next;
    }
    return s;
}

/* Thay thế X bằng Y (tất cả các node có data == X) */
int replaceXwithY(List* l, int X, int Y) {
    int cnt = 0;
    Node* p = l->head;
    while (p) {
        if (p->data == X) {
            p->data = Y;
            cnt++;
        }
        p = p->next;
    }
    return cnt;
}

/* Sắp xếp danh sách tăng dần bằng cách đổi dữ liệu (bubble sort) */
void sortListAscending(List* l) {
    if (!l->head) return;
    int swapped;
    do {
        swapped = 0;
        Node* p = l->head;
        while (p && p->next) {
            if (p->data > p->next->data) {
                int tmp = p->data;
                p->data = p->next->data;
                p->next->data = tmp;
                swapped = 1;
            }
            p = p->next;
        }
    } while (swapped);
}

/* Hàm nhập danh sách: nhập từng token, nếu gặp '#' thì dừng */
void inputList(List* l) {
    char token[128];
    printf("Nhap cac so (nhap # de ket thuc):\n");
    while (1) {
        if (scanf("%127s", token) != 1) break;
        if (strcmp(token, "#") == 0) break;
        // kiểm tra token có phải là số hợp lệ (có thể âm)
        int sign = 1;
        int i = 0;
        if (token[0] == '+' || token[0] == '-') {
            if (token[0] == '-') sign = -1;
            i = 1;
            if (token[1] == '\0') {
                printf("Nhap khong hop le, bo qua: %s\n", token);
                continue;
            }
        }
        int valid = 0;
        for (int j = i; token[j]; ++j) {
            if (!isdigit((unsigned char)token[j])) { valid = 0; break; }
            valid = 1;
        }
        if (!valid) {
            printf("Nhap khong hop le, bo qua: %s\n", token);
            continue;
        }
        int val = atoi(token);
        append(l, val);
    }
    // Clear newline remain
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Menu chính */
void menu() {
    List l;
    initList(&l);
    int choice;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Nhap danh sach (nhap den khi gap #)\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Hien thi danh sach nguoc\n");
        printf("4. Dem so luong so hoan hao\n");
        printf("5. Tim min / max\n");
        printf("6. Xoa cac phan tu am\n");
        printf("7. Tinh tong cac phan tu\n");
        printf("8. Thay the X thanh Y\n");
        printf("9. Sap xep tang dan\n");
        printf("0. Thoat\n");
        printf("================\n");
        printf("Lua chon cua ban: ");
        if (scanf("%d", &choice) != 1) {
            printf("Nhap khong hop le. Ket thuc.\n");
            break;
        }
        // clear newline
        int c; while ((c = getchar()) != '\n' && c != EOF);

        if (choice == 1) {
            freeList(&l); // nếu đã có dữ liệu trước đó thì xóa đi
            initList(&l);
            inputList(&l);
        } else if (choice == 2) {
            printList(l);
        } else if (choice == 3) {
            printListReverse(l);
        } else if (choice == 4) {
            int cnt = countPerfectNumbers(l);
            printf("So luong so hoan hao: %d\n", cnt);
        } else if (choice == 5) {
            int mn, mx;
            if (findMinMax(l, &mn, &mx)) {
                printf("Min = %d, Max = %d\n", mn, mx);
            } else {
                printf("Danh sach rong.\n");
            }
        } else if (choice == 6) {
            deleteNegative(&l);
            printf("Da xoa cac phan tu am (neu co).\n");
        } else if (choice == 7) {
            long long s = sumList(l);
            printf("Tong cac phan tu = %lld\n", s);
        } else if (choice == 8) {
            int X, Y;
            printf("Nhap X va Y (cach nhau boi dau cach): ");
            if (scanf("%d %d", &X, &Y) == 2) {
                int cnt = replaceXwithY(&l, X, Y);
                printf("Da thay the %d lan.\n", cnt);
            } else {
                printf("Nhap khong hop le.\n");
            }
            while ((c = getchar()) != '\n' && c != EOF);
        } else if (choice == 9) {
            sortListAscending(&l);
            printf("Da sap xep tang dan.\n");
        } else if (choice == 0) {
            printf("Ket thuc chuong trinh.\n");
        } else {
            printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);

    freeList(&l);
}

int main() {
    menu();
    return 0;
}
