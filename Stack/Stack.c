#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
    StackType s;

    init_stack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
}