#include <ncurses.h>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// Snake의 구조체
struct Snake {
    int x, y;
};

// Gate의 구조체
struct Gate {
    int x1, y1;
    int x2, y2;
};

Gate gates;
bool gateCheck=false;

// 게임 맵의 크기
const int MAP_SIZE = 21;

// 게임 맵 배열
int map[MAP_SIZE][MAP_SIZE] = { // 지금은 초기 배열에 할당했지만 나중엔 파일로 읽어와 맵을 바꿀 수 있게 변경
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
};

// 맵을 화면에 출력하는 함수
void drawMap() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] == 1) {
                attron(COLOR_PAIR(1)); // 벽 색상
                mvprintw(i, j, "#");
                attroff(COLOR_PAIR(1));
            } else if (map[i][j] == 2) {
                attron(COLOR_PAIR(2)); // 게임 맵 테두리 색상
                mvprintw(i, j, "+");
                attroff(COLOR_PAIR(2));
            } else if (map[i][j] == 3) {
                attron(COLOR_PAIR(3)); // 지렁이 색상
                mvprintw(i, j, "@");
                attroff(COLOR_PAIR(3));
            } else if (map[i][j] == 4) {
                attron(COLOR_PAIR(4)); // 아이템 색상
                mvprintw(i, j, "O");
                attroff(COLOR_PAIR(4));
            } else if (map[i][j] == 9){
                if(gateCheck==false){
                    gates.x1 = i; gates.y1=j;
                    gateCheck = true;
                }else{
                    gates.x2 =i; gates.y2=j;
                    gateCheck = false;
                }
                
                attron(COLOR_PAIR(5)); // Gate color
                mvprintw(gates.y1, gates.x1, "+");
                mvprintw(gates.y2, gates.x2, "+");
                attroff(COLOR_PAIR(5));
            }

            
        }
    }
}

void randomGate(){
    srand(time(NULL));
    int cnt=0;
    for(int i=0; i<MAP_SIZE; i++){
        for(int j=0; j<MAP_SIZE; j++){
            if(map[i][j]==9) map[i][j]=2;
        }
    }
    do{
        int i=rand()%21+1;
        int j=rand()%21+1;
        if(map[i][j]==2){
            map[i][j] = 9;
            cnt++;
        }
        if(cnt>=2) break;
    }while(1);
}


int main(){

    // Snake의 초기 위치
    int startX = MAP_SIZE / 2;
    int startY = MAP_SIZE / 2;

    // Snake의 초기 방향
    int directionX = 1;
    int directionY = 0;

    // Snake의 몸통을 나타내는 벡터
    vector<Snake> body;
    Snake snake;
    snake.x = startX;
    snake.y = startY;
    body.push_back(snake);

    // 초기 길이를 3으로 만들기 위해 추가로 2개의 Snake 구조체를 더 추가
    Snake snake2;
    snake2.x = startX - 1;
    snake2.y = startY;
    body.push_back(snake2);

    Snake snake3;
    snake3.x = startX - 2;
    snake3.y = startY;
    body.push_back(snake3);

    // 게이트 초기 위치는 맵에 9로 표시해두고 시작

    initscr(); // Curses 모드 시작
    start_color(); // 색상 기능 활성화
    init_pair(1, COLOR_RED, COLOR_BLACK);   // 벽 색상
    init_pair(2, COLOR_WHITE, COLOR_BLACK);  // 게임 맵 테두리 색상
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // 지렁이 색상
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);// 지렁이 몸통 색상
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);

    nodelay(stdscr, true);
    keypad(stdscr, true);
    noecho();
    curs_set(0);

    // 게임 루프
    bool gameOver = false;
    int gatenum=0;
    while (!gameOver) {
        clear();
        drawMap();
        if(gatenum>100){
            randomGate();
            gatenum=0;
        }
        refresh();

        // 키 입력 처리
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                directionX = 0;
                directionY = -1;
                break;
            case KEY_DOWN:
                directionX = 0;
                directionY = 1;
                break;
            case KEY_LEFT:
                directionX = -1;
                directionY = 0;
                break;
            case KEY_RIGHT:
                directionX = 1;
                directionY = 0;
                break;
        }

        // Check for collision with the gates
        if ((body[0].x == gates.x1 && body[0].y == gates.y1) || (body[0].x == gates.x2 && body[0].y == gates.y2)) {
            // 원래거 하나씩 지우면서 반대편에 하나씩 생성

            
        }

        // Snake 이동
        int nextX = body[0].x + directionX;
        int nextY = body[0].y + directionY;

        // 벽 또는 자기 자신과의 충돌 체크
        if (nextX < 0 || nextX >= MAP_SIZE || nextY < 0 || nextY >= MAP_SIZE) {
            gameOver = true;
            break;
        }
        for (int i = 1; i < body.size(); i++) {
            if (body[i].x == nextX && body[i].y == nextY) {
                gameOver = true;
                break;
            }
        }

        // Snake의 머리 위치 업데이트
        snake.x = nextX;
        snake.y = nextY;
        body.insert(body.begin(), snake);

        // Snake의 꼬리 제거
        if (map[nextY][nextX] != 2|| map[nextY][nextX] != 1) {
            map[body.back().y][body.back().x] = 0;
            body.pop_back();
        }

        // Snake의 머리와 꼬리 표시
        map[nextY][nextX] = 3;
        map[body.back().y][body.back().x] = 4;

        drawMap();
        // 100ms 대기
        napms(100);
        gatenum++;
    }

    // 게임 종료 후 NCurses 정리
    endwin();
    return 0;
}