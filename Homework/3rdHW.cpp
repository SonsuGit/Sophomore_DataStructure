#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
typedef char element;		// 교체!
                            // 차후에 스택이 필요하면 여기만 복사하여 붙인다. 
                            // ===== 스택 코드의 시작 ===== 
#define MAX_STACK_SIZE 100
typedef enum {
    leftparen, rightparen, plus, minus, multiply, divide, remainder, eos, operand
}words;
int error = 0;//검사실패시 결과값표시안하게 하려고 만듬
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init(StackType* s) {
    s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
    return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러push\n");
        return;
    }
    else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "괄호검사 실패!!!\n");
        error = 1;
    }
    else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "괄호검사 실패!!!\n");
        error = 1;
    }
    else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

// 연산자의 우선순위를 반환한다.
int prec(char op)
{
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    case '%': return 2; //추가됨
    }
    return -1;
}
// 중위 표기 수식 -> 후위 표기 수식
void infix_to_postfix(char* infix, char* postfix) {
    StackType s;
    init(&s);
    while (*infix != '\0') {
        if (*infix == '(') {
            push(&s, *infix);
            infix++;
        }
        else if (*infix == ')') {
            while (peek(&s) != '(') {
                *postfix++ = pop(&s);
                *postfix++ = ' ';
            }
            pop(&s);
            infix++;
        }
        else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/' || *infix == '%') {
            while (!is_empty(&s) && (prec(*infix) <= prec(peek(&s)))) {
                *postfix++ = pop(&s);
                *postfix++ = ' ';
            }
            push(&s, *infix);
            infix++;
        }
        else if (*infix >= '0' && *infix <= '9') {
            do {
                *postfix++ = *infix++;
            } while ((*infix >= '0' && *infix <= '9'));
            *postfix++ = ' ';
        }
        else
            infix++;
    }
    while (!is_empty(&s)) {
        *postfix++ = pop(&s);
        *postfix++ = ' ';
    }
    postfix--;
    *postfix = '\0';
}

//연산자인지 피연산자인지 구분
words classification(char* point) {
    switch (*point) {
    case '(': return leftparen;
    case ')': return rightparen;
    case '+': return plus;
    case '-': return minus;
    case '*': return multiply;
    case '/': return divide;
    case '%': return remainder;
    case '\\': return eos;
    default: return operand;
    }
}
//스트링에서 int로
int change_value(char* num, int* index) {
    int value;
    char temp[100];
    int i, k;
    for (i = 0; num[i] != ' '; i++)
        temp[i] = num[i];
    temp[i] = '\0';
    value = atoi(temp);
    k = *index;
    *index = k + i;
    return value;
}
// postfix표기식 계산하는 함수
int eval(char* postfix)
{
    words temp;
    int value, op1, op2;
    int i;
    StackType s;
    init(&s);
    for (i = 0; postfix[i] != '\0'; i++) {
        if (postfix[i] == ' ')
            i++;
        temp = classification(&postfix[i]);
        if (temp == operand) {
            value = change_value(&postfix[i], &i);
            push(&s, value);
        }
        else {
            op2 = pop(&s);
            op1 = pop(&s);

            switch (temp) {
            case plus: push(&s, op1 + op2); break;
            case minus: push(&s, op1 - op2); break;
            case multiply: push(&s, op1 * op2); break;
            case divide: push(&s, op1 / op2); break;
            case remainder: push(&s, op1 % op2); break;
            }
        }
    }
    return pop(&s);
}
//수식입력하고 후위표기식으로 변환된 값과 기존 수식과 답을 보여주어야 함
int main(void)
{
start:
    error = 0;
    char infix[100] = { 0 };
    char infix1[100] = { 0 };
    char postfix[100] = { 0 };
    printf("수식입력 (q:quit): ");
    scanf_s("%s", infix, 100);
    //printf("%s \n\n this is test \n\n\n", infix);
    if (infix[0] == 'q')
        exit(0);
    else {
        for (int i = 0; i < 100; i++)
            infix1[i] = infix[i];//대입
        infix_to_postfix(infix, postfix);
        int answer = eval(postfix);
        if (error == 1)
            goto start;
        printf("        후위표기식 : %s\n", postfix);
        printf("                  %s = %d\n\n", infix, answer);
    }
    goto start;
}
