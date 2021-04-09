#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6

typedef struct {
    short r; // 행
    short c; // 열
} element;

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

element here = {1, 0}, entry = {1, 0};
char maze[MAZE_SIZE][MAZE_SIZE] = {
    { '1', '1', '1', '1', '1', '1' },
    { 'e', '0', '1', '0', '0', '1' },
    { '1', '0', '0', '0', '1', '1' },
    { '1', '1', '1', '0', '1', '1' },
    { '1', '1', '1', '0', '0', 'x' },
    { '1', '1', '1', '1', '1', '1' }
}; // e: 현위치 x: 출구 1: 벽 0: 길 .: 방문

// 위치를 스택에 삽입
void push_loc(StackType *s, int r, int c) {
    if(r < 0 || c < 0) return;
    // 벽이 아니고, 방문한 곳이 아니면 push -> 갈수있는 길만 push
    if(maze[r][c] != '1' && maze[r][c] != '.') {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

// 미로를 화면에 출력
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
    }
    printf("\n");
}

int main(void) {
    int r,c;
    StackType s;

    init_stack(&s);
    here = entry;

    // 출구를 만날 때까지 반복
    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;
        // 방문한 위치 표시
        maze[r][c] = '.';
        maze_print(maze);
        // 상
        push_loc(&s, r - 1, c);
        // 하
        push_loc(&s, r + 1, c);
        // 좌
        push_loc(&s, r, c - 1);
        // 우
        push_loc(&s, r, c + 1);

        if (is_empty(&s)) {
            printf("탈출 불가 미로 입니다.");
            return 0;
        } else {
            here = pop(&s); // 성공
        }
    }
    printf("성공!");
    return 0;
}
