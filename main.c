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
void operateIntegerList(struct node *L1, struct node *L2, struct node **L3);

int main(int argc, char **argv) {

    printf("长整型数加减程序-王俊皓-2014101027\n\n");

    // num1
    struct node *num1;
    generateIntegerList(&num1);
    printIntegerList(num1);

    // num2
    struct node *num2;
    generateIntegerList(&num2);
    printIntegerList(num2);
    printf("\n");

    // result
    struct node *num3;
    operateIntegerList(num1, num2, &num3);
    printf("<输出结果>\n");
    printIntegerList(num3);

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
            int num = ch - '0';
            if (rank < 4) {
                numbers[rank] = num;
                rank++;
            }
        } else if (ch == ',' || ch == '\0') {
            // save numbers to a new node
            p->next = (struct node *)malloc(sizeof(struct node));
            p->next->number = 0;
            for (int k = rank - 1, j = 0; k >= 0; k--, j++) {
                switch (j) {
                    case 0:
                        p->next->number += numbers[k]; break;
                    case 1:
                        p->next->number += numbers[k] * 10; break;
                    case 2:
                        p->next->number += numbers[k] * 100; break;
                    case 3:
                        p->next->number += numbers[k] * 1000; break;
                    default:
                        break;
                }
            }
            p->next->next = (*L)->next;
            p->next->prev = (p != *L) ? p : (*L)->prev;
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

    //sign
    if (L->number < 0)
        printf("-");

    // number
    int zero = 0;
    for (int i = 0; i < abs(L->number); i++) {
        if (i == 0) {
            // first

            // first & last
            if (i == abs(L->number) - 1) {
                printf("%d", p->number);
                break;
            }

            if (p->number == 0) {
                zero = 1;
            } else {
                printf("%d", p->number);
            }
        } else if (i == abs(L->number) - 1) {
            // last
            if (zero == 0) {
                printf("%04d", p->number);
            } else {
                printf("%d", p->number);
            }
        } else {
            // else
            if (p->number == 0 && zero == 1) {
                // continue 0 no output
            } else if (p->number > 0 && zero == 1) {
                // meet non-0
                printf("%d", p->number);
                zero = 0;
            } else {
                printf("%04d", p->number);
            }
        }

        if (i < abs(L->number) - 1 && zero == 0)
            printf(",");

        p = p->next;
    }
    printf("\n");
}

void operateIntegerList(struct node *L1, struct node *L2, struct node **L3)
{
    struct node *p1 = L1->prev;
    struct node *p2 = L2->prev;

    struct node *p3 = (struct node *)malloc(sizeof(struct node));
    p3->number = 0;
    p3->next = p3;
    p3->prev = p3;
    *L3 = p3;

    // number of nodes
    int n1 = abs(L1->number);
    int n2 = abs(L2->number);

    // sign
    int s1 = (L1->number > 0) ? 1 : -1;
    int s2 = (L2->number > 0) ? 1 : -1;
    int max = (n1 > n2) ? n1 : n2;

    // type
    int type = (s1 == s2) ? 0 : 1;   // 0 means same signs, 1 means not

    // for-in
    if (type == 0) {
        // type 0
        int carry = 0; // carry number
        for (int i = 0; i < max; i++) {
            // addNum1
            int addNum1 = 0;
            if (i < n1) {
                addNum1 = s1 * p1->number;
                p1 = p1->prev;
            }
            // addNum2
            int addNum2 = 0;
            if (i < n2) {
                addNum2 = s2 * p2->number;
                p2 = p2->prev;
            }
            // result
            int result = addNum1 + addNum2 + carry;
            carry = result / 10000; // carry must be positive
            result = result % 10000;

            // new a node for L3
            p3->prev = (struct node *)malloc(sizeof(struct node));
            p3->prev->number = result;
            p3->prev->next = (p3 != *L3) ? p3 : (*L3)->next;
            p3->prev->prev = (*L3)->prev;
            (*L3)->next = p3->prev;
            (*L3)->number++;
            p3 = p3->prev;

            // new the last node for L3
            if (i == max - 1 && carry != 0) {
                p3->prev = (struct node *)malloc(sizeof(struct node));
                p3->prev->number = carry;
                p3->prev->next = (p3 != *L3) ? p3 : (*L3)->next;
                p3->prev->prev = (*L3)->prev;
                (*L3)->next = p3->prev;
                (*L3)->number++;
                p3 = p3->prev;
            }
        }
    } else {
        // type 1

        // sign & bigger decision
        int sign = 1;
        int bigger = 1;   // p1 default is bigger   0 means p2 is bigger
        if (n1 > n2) {
            sign = s1;
            bigger = 1;
        } else if (n1 < n2) {
            sign = s2;
            bigger = 0;
        } else {
            if (L1->next->number > L2->next->number) {
                sign = s1;
                bigger = 1;
            } else if (L1->next->number < L2->next->number) {
                sign = s2;
                bigger = 0;
            } else {
                sign = 1;
                bigger = 1;
            }
        }

        int borrow = 0; // borrow number
        for (int i = 0; i < max; i++) {
            // minusNum1
            int minusNum1 = 0;
            if (i < n1) {
                minusNum1 = p1->number;
                p1 = p1->prev;
            }
            // minusNum2
            int minusNum2 = 0;
            if (i < n2) {
                minusNum2 = p2->number;
                p2 = p2->prev;
            }

            // borrow bit
            int result = 0;
            if (borrow > 0) {
                result--;
                borrow--;
            }
            if (bigger) {
                // p1 is bigger
                if (minusNum1 < minusNum2) {
                    // need borrow
                    result += 10000 + minusNum1 - minusNum2;
                    // see how many should be borrowed
                    struct node *bp = p1;
                    int b = 0;
                    while (bp != L1) {
                        b++;
                        if (bp->number > 0) {
                            break;
                        }
                        bp = bp->prev;
                    }
                    borrow += b;
                } else {
                    result += 10000 + minusNum1 - minusNum2;
                }
            } else {
                // p2 is bigger
                if (minusNum2 < minusNum1) {
                    // need borrow
                    result += 10000 + minusNum2 - minusNum1;
                    // see how many should be borrowed
                    struct node *bp = p2;
                    int b = 0;
                    while (bp != L2) {
                        b++;
                        if (bp->number > 0) {
                            break;
                        }
                        bp = bp->prev;
                    }
                    borrow += b;
                } else {
                    result += 10000 + minusNum2 - minusNum1;
                }
            }

            result = result % 10000;

            // new a node for L3
            p3->prev = (struct node *)malloc(sizeof(struct node));
            p3->prev->number = result;
            p3->prev->next = (p3 != *L3) ? p3 : (*L3)->next;
            p3->prev->prev = (*L3)->prev;
            (*L3)->next = p3->prev;
            (*L3)->number += sign;
            p3 = p3->prev;
        }
    }
}





