//
// Created by JunhaoWang on 4/3/16.
//

#include <stdio.h>
#include <stdlib.h>

#define N 30

struct node {
    int number;
    struct node *next;
    struct node *prev;
};

void generateIntegerList(struct node **L);
void printIntegerList(struct node *L);

int main(int argc, char **argv) {

    printf("长整型数加减程序-王俊皓-2014101027\n\n");

    struct node *num1;
    generateIntegerList(&num1);
    printIntegerList(num1);

    printf("\n----------END----------\n");

    return 0;
}

void generateIntegerList(struct node **L)
{
    // head node
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->next = p;
    p->prev = p;
    p->number = 0;
    *L = p;

    // input str
    char inputStr[N] = "";
    printf("请输入整数: ");
    scanf("%s", inputStr);

    // sign determination
    int s_flag;
    if (inputStr[0] == '-')
        s_flag = -1;
    else
        s_flag = 1;

    // for-in inputStr
    int numbers[4] = {0};
    int rank = 0; // rank of numbers
    for (int i = 0; i < N; ++i) {
        char ch = inputStr[i];
        // meet SIGN
        if (ch == '+' || ch == '-')
            continue;
        // meet number / ','
        if (ch >= '0' && ch <= '9') {
            int num = (int)ch;
            if (rank < 4) {
                numbers[rank] = num;
                rank++;
            }
        } else if (ch == ',' || ch == '\0') {
            // save numbers to a new node
            p->next = (struct node *)malloc(sizeof(struct node));
            p->number = 0;
            for (int k = rank - 1, j = 0; k >= 0; k++, j++) {
                switch (j) {
                    case 0:
                        p->number += numbers[k]; break;
                    case 1:
                        p->number += numbers[k] * 10; break;
                    case 2:
                        p->number += numbers[k] * 100; break;
                    case 3:
                        p->number += numbers[k] * 1000; break;
                    default:
                        break;
                }
            }
            p->next->next = *L;
            p->next->prev = p;
            (*L)->prev = p->next;
            (*L)->number += 1 * s_flag;
            p = p->next;
            rank = 0;
            numbers[0] = numbers[1] = numbers[2] = numbers[3] = 0;
        }
        // meet END
        if (ch == '\0')
            break;
    }
}

void printIntegerList(struct node *L)
{
    printf("整数为: ");
    struct node *p = L->next;
    for (int i = 0; i < abs(L->number); i++) {
        if (i == 0 || i == abs(L->number) - 1) {
            // first or last number
            printf("%d", p->number);
        } else {
            printf("%04d", p->number);
        }
        if (i < abs(L->number) - 1)
            printf(",");
        p = p->next;
    }
    printf("\n");
}

