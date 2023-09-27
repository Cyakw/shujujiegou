#include <stdio.h>
#include <stdlib.h>

struct Node {
    int xishu; // 系数
    int zhishu; // 指数
    struct Node* next;
};

struct Node* creat(int x, int z) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->xishu = x;
    newNode->zhishu = z;
    newNode->next = NULL;
    return newNode;
}

void insert(struct Node** xiang, int x, int z) {
    struct Node* newNode = creat(x, z);
    if (*xiang == NULL || z > (*xiang)->zhishu) {
        newNode->next = *xiang;
        *xiang = newNode;
    } else {
        struct Node* current = *xiang;
        struct Node* prev = NULL;
        while (current && z < current->zhishu) {
            prev = current;
            current = current->next;
        }
        if (current && z == current->zhishu) {
            current->xishu += x;
            free(newNode);
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
}

struct Node* add(struct Node* xiang1, struct Node* xiang2) {
    struct Node* result = NULL;
    while (xiang1 || xiang2) {
        int x1 = (xiang1 != NULL) ? xiang1->xishu : 0;
        int x2 = (xiang2 != NULL) ? xiang2->xishu : 0;
        int z1 = (xiang1 != NULL) ? xiang1->zhishu : -1;
        int z2 = (xiang2 != NULL) ? xiang2->zhishu : -1;

        if (z1 == z2) {
            insert(&result, x1 + x2, z1);
            xiang1 = xiang1->next;
            xiang2 = xiang2->next;
        } else if (z1 > z2) {
            insert(&result, x1, z1);
            xiang1 = xiang1->next;
        } else {
            insert(&result, x2, z2);
            xiang2 = xiang2->next;
        }
    }
    return result;
}

void display(struct Node* xiang) {
    struct Node* current = xiang;
    while (current != NULL) {
        printf("%dx^%d", current->xishu, current->zhishu);
        current = current->next;
        if (current != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

void freexiang(struct Node* xiang) {
    struct Node* current = xiang;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* xiang1 = NULL;
    struct Node* xiang2 = NULL;

    printf("输入多项式1，以-1 -1作为结束标志：\n");
    int x, z;
    while (1) {
        scanf("%d %d", &x, &z);
        if (x == -1 && z == -1) {
            break;
        }
        insert(&xiang1, x, z);
    }

    printf("输入多项式2，以-1 -1作为结束标志：\n");
    while (1) {
        scanf("%d %d", &x, &z);
        if (x == -1 && z == -1) {
            break;
        }
        insert(&xiang2, x, z);
    }

    printf("多项式1：");
    display(xiang1);

    printf("多项式2：");
    display(xiang2);

    struct Node* result = add(xiang1, xiang2);
    printf("相加后的多项式：");
    display(result);

    freexiang(xiang1);
    freexiang(xiang2);
    freexiang(result);

    return 0;
}
