#define _CRT_SECURE_NO_WARNINGS//자꾸 오류가 떠서(scanf_s)추가함
#include <stdio.h>
#include <string.h>//strcpy를 위해
#include <stdlib.h>
#include <time.h>//랜덤위해

void displayboard(int array[5][5]);//보드를 표시하는 함수
int win(int array[5][5]);//그 턴에 이기면 1을 표시하는 함수
void displayscoreboard(struct score score[]);//스코어보드를 표현
void sortscoreboard(struct score score[]);//스코어보드 점수순으로 sort
struct score {
    char name[1000];
    int turn;
};
struct score scores[11];//마지막 11번째 값은 sort이전에 값을 임시로 넣어놓고, sort이후엔 displayscoreboard에서 표시하지않음
int main(void) {
BEGIN:
    int board[5][5] = { 0, };
    char name1[30], name2[30];//이름
    int turn1 = 0; 
    int turn2 = 0; //각각의 턴수
    int re = 0; //다시할건지
    int pv = 0; //인간or컴퓨터
    printf("첫플레이어는 1으로 표시, 두번째 플레이어나 컴퓨터는 2로 표시됩니다.\n\n");
    //컴퓨터랑 할건지 인간이랑 할건지 물어보기
    printf("사람대 사람을 하고싶다면 0 컴퓨터와 하고싶다면 1을 입력해주세요: ");
    scanf("%d", &pv);
    if (pv == 1)
        goto PVE;
    //인간vs인간
    printf("첫번째 플레이어의 이름을 입력하세요: ");
    scanf("%s", name1);
    printf("\n");
    printf("두번째 플레이어의 이름을 입력하세요: ");
    scanf("%s", name2);
    printf("\n");
    while (1) {
        int x, y;
    PVP_P1:
        printf("%s의 차례입니다 좌표를 입력해주세요(e.g. 0,1이면 0 1): ", name1);
        scanf_s("%d %d", &x, &y);
        if (x > 4 || y > 4) {
            printf("잘못된 좌표 입력입니다 X,Y좌표 모두 2이하의 값을 입력해주세요\n\n");
            goto PVP_P1;
        }
        if (board[x][y] == 0)
            board[x][y] = 1;
        else {
            printf("이미 체크한 곳 입니다.\n\n");
            goto PVP_P1;
        }
        turn1++;
        displayboard(board);
        printf("\n");
        if (win(board) == 1) {
            printf("%d턴만의 %s의 승리입니다 축하합니다!\n", turn1, name1);
            strcpy(scores[10].name, name1);
            scores[10].turn = turn1;
            break;
        }
    PVP_P2:
        printf("%s의 차례입니다 좌표를 입력해주세요(e.g. 0,1이면 0 1): ", name2);
        scanf_s("%d%d", &x, &y);
        if (x > 4 || y > 4) {
            printf("잘못된 좌표 입력입니다 X,Y좌표 모두 2이하의 값을 입력해주세요\n\n");
            goto PVP_P2;
        }
        if (board[x][y] == 0)
            board[x][y] = 2;
        else {
            printf("이미 체크한 곳 입니다.\n\n");
            goto PVP_P2;
        }
        turn2++;
        displayboard(board);
        printf("\n");
        if (win(board) == 1) {
            printf("%d턴만의 %s의 승리입니다 축하합니다!\n", turn2, name2);
            strcpy(scores[10].name, name2);
            scores[10].turn = turn2;
            break;
        }
    };
    sortscoreboard(scores);
    displayscoreboard(scores);
    printf("다시하고싶으시다면 1 을 입력해주세요: ");
    scanf("%d", &re);
    printf("\n");
    if (re == 1)
        goto BEGIN;
    //인간vs컴
PVE:
    printf("\n");
    printf("컴퓨터와의 대결입니다.\n\n");
    strcpy(name2, "Computer");
    printf("플레이어의 이름을 입력하세요: ");
    scanf("%s", name1);
    printf("\n");
    while (1) {
        int x, y;
    PVE_P:
        printf("%s의 차례입니다 좌표를 입력해주세요(e.g. 0,1이면 0 1): ", name1);
        scanf_s("%d %d", &x, &y);
        if (x > 4 || y > 4) {
            printf("잘못된 좌표 입력입니다 X,Y좌표 모두 2이하의 값을 입력해주세요\n\n");
            goto PVE_P;
        }
        if (board[x][y] == 0)
            board[x][y] = 1;
        else {
            printf("이미 체크한 곳 입니다.\n\n");
            goto PVE_P;
        }
        turn1++;
        displayboard(board);
        printf("\n");
        if (win(board) == 1) {
            printf("%d턴만의 %s의 승리입니다 축하합니다!\n", turn1, name1);
            strcpy(scores[10].name, name1);
            scores[10].turn = turn1;
            break;
        }
        //아래부터 컴퓨터 턴
        printf("컴퓨터의 차례입니다. \n");
        PVE_E:
        x = rand() % 5;
        y = rand() % 5; //컴퓨터의 xy좌표값 랜덤 생성

        if (x > 4 || y > 4) {
            goto PVE_E;
        }
        if (board[x][y] == 0)
            board[x][y] = 2;
        else {
            goto PVE_E;
        }
        turn2++;
        displayboard(board);
        printf("\n");
        if (win(board) == 1) {
            printf("%d턴만의 %s의 승리입니다\n", turn2, name2);
            strcpy(scores[10].name, name2);
            scores[10].turn = turn2;
            break;
        }
    };
    sortscoreboard(scores);
    displayscoreboard(scores);
    printf("다시하고싶으시다면 1 을 입력해주세요: ");
    scanf("%d", &re);
    printf("\n");
    if (re == 1)
        goto BEGIN;

}
void displayboard(int array[5][5]) {
    for (int i = 0; i < 5; i++) {
        printf("   ---|---|---|---|---\n");
        printf("    %d | %d | %d | %d | %d\n", array[i][0], array[i][1], array[i][2], array[i][3], array[i][4]);
    }
    printf("   ---|---|---|---|---\n");
}
int win(int array[5][5]) {//그 당시 턴에 이겼는지 체크, 맨앞 0과 같지않음은 사용하지 않으면 비어있을때도 승리로 체크하기에 추가함
    for (int i = 0; i < 5; i++) {
        if (array[i][0] != 0 
            && array[i][0] == array[i][1] && array[i][1] == array[i][2] 
            && array[i][2] == array[i][3] && array[i][3] == array[i][4])
            return 1;//가로체크
    }
    for (int u = 0; u < 3; u++) {
        if (array[0][u] != 0 
            && array[0][u] == array[1][u] && array[1][u] == array[2][u]
            && array[2][u] == array[3][u] && array[3][u] == array[4][u])
            return 1;//세로체크
    }
    if (array[0][0] != 0 
        && array[0][0] == array[1][1] && array[1][1] == array[2][2]
        && array[2][2] == array[3][3] && array[3][3] == array[4][4])
        return 1;//10시 중앙 4시 체크
    if (array[0][4] != 0 
        && array[0][4] == array[1][3] && array[1][3] == array[2][2]
        && array[2][2] == array[3][1] && array[3][1] == array[4][0])
        return 1;//2시 중앙 8시 체크
    return 0;
}
void displayscoreboard(struct score score[]) {
    printf("\n      점수표         \n\n");
    printf("-------------------------------------------\n");
    for (int i = 10; i >= 0; i--) {//스코어 구조체배열에서 인덱스번호가 큰순으로 print(턴값이 0인,비어있는 값은 출력안함)
        if (score[i].turn != 0) {
            printf("   이름: %6s   걸린 턴수: %d\n", score[i].name, score[i].turn);
            printf("-------------------------------------------\n");
        }
    }
}
void sortscoreboard(struct score score[]) {//
    struct score temp;
    for (int n = 10; n > 0; n--) {
        for (int r = 0; r < n; r++) {
            if (score[r].turn < score[r + 1].turn) {//r보다 r+1번 구조체배열요소의 턴(점수의 역)이 높으면 교환
                temp = score[r + 1];
                score[r + 1] = score[r];
                score[r] = temp;
            }//결론적으로 이길때 걸린 턴수가 가장 높은 사람이 인덱스번호의 0번으로 이동함
        }
    }
}
/*char test[10]="guy";
strcpy(scores[9].name, test);
scores[9].turn = 4;
sortscoreboard(scores);
displayscoreboard(scores);*/
//테스트용코드