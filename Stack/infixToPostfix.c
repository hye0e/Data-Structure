#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType *s) {
    s->top = -1; // s 안에 있는 top에 -1로 초기화
}

// 공백 상태 검출
int is_empty(StackType *s) {
    return s->top == -1;
}

// 스택 포화상태 검출
int is_full(StackType *s) {
    return s -> top == (MAX_STACK_SIZE - 1); // index는 0부터 시작하기 때문에 -1을 해준다.
}

// 스택 삽입 함수
void push(StackType *s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택이 포화상태입니다. ");
        return;
    }
    else s->data[++(s->top)] = item; // 먼저 스택의 top을 증가시키고, 그 데이터에 아이템을 넣겠다. -> 스택은 위로 쌓아올리는 구조이기 때문에
} 

// 스택 삭제 함수
element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있습니다. ");
        exit(1);
    } 
    else return s->data[(s->top)--]; // 데이터에서 탑을 꺼낸 후 스택의 크기를 줄인다 
}

// 스택 피크 함수
element peek(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있습니다. ");
        exit(1);
    } 
    else return s->data[s->top]; // 단순히 스택에서 꺼내오는 함수
}

// 연산자의 우선순위를 리턴
int prec(char op) {
    switch (op)
    {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

// 중위 표기 수식 -> 후위 표기 수식
void infixToPostfit(char exp[]) {
    int i = 0;
    char ch, top_op;
    int len = strlen(exp);
    StackType s;

    init_stack(&s);
    for(i = 0; i <len; i++) {
        ch = exp[i];
        switch (ch)
        {
        case '+': case '-': case '*': case '/':// 연산자일 경우엔, push할 연산자와 안에 있는 연산자와 우선순위를 비교해사 넣어줘야한다
            while(!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
                // 비어있지 않고, 인에 있는 연산자가 우선순위가 낮다면 출력을 해줘야함
                printf("%c", pop(&s));
            }
            // pop 후 넣을 수 있다.
            push(&s, ch);
            break;
        case '(': // 우선 순위가 가장 높기 때문에 무조건 넣음
            push(&s, ch);
            break;
        case ')': // 오른쪽 괄호
            top_op = pop(&s);
            // 왼쪽 괄호를 만났을 떄까지 출력하고 pop하는 것을 반복
            while(top_op != '(') {
                printf("%c", top_op);
                top_op = pop(&s);
            }
            break;
        default: // 피연산자일 경우
            printf("%c", ch);
            break;
        }
    }
    while(!is_empty(&s)) // 스택에 저장된 모든 연산자들 출력
        printf("%c", pop(&s));
}

int main(void) {
    char *s = "(2+3)*4+9";
    infixToPostfit(s);
    return 0;
}