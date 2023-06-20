#include <ncurses.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
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
int map[4][MAP_SIZE][MAP_SIZE] = { // 지금은 초기 배열에 할당했지만 나중엔 파일로 읽어와 맵을 바꿀 수 있게 변경
    {
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
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
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    },
    {
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    },
    {
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    },
    {
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    }
};

enum Direction{
    Up, Right, Down, Left
};

void placeGrowth(int level){
    // 성장 아이템 랜덤 배치
    bool flag=false;
    do{
        int a = rand()%21+1;
        int b = rand()%21+1;
        if(map[level][a][b]==0){
            map[level][a][b]=5;
            flag=true;
        }
    }while(flag!=true);
    
}

void poisionItem(int level){
    // 독 아이템
    bool flag=false;
    do{
        int a = rand()%21+1;
        int b = rand()%21+1;
        if(map[level][a][b]==0){
            map[level][a][b]=6;
            flag=true;
        }
    }while(flag!=true);
}

// 맵을 화면에 출력하는 함수
void drawMap(int level) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[level][i][j] == 1) {
                attron(COLOR_PAIR(1)); // 벽 색상
                mvprintw(i, j, "#");
                attroff(COLOR_PAIR(1));
            } else if (map[level][i][j] == 2) {
                attron(COLOR_PAIR(1)); // 게임 맵 테두리 색상
                mvprintw(i, j, "+");
                attroff(COLOR_PAIR(1));
            } 
            // else if (map[i][j] == 3) {
            //     attron(COLOR_PAIR(3)); // 지렁이 색상
            //     mvprintw(i, j, "@");
            //     attroff(COLOR_PAIR(3));
            // } else if (map[i][j] == 4) {
            //     attron(COLOR_PAIR(4)); // 몸통 색상
            //     mvprintw(i, j, "O");
            //     attroff(COLOR_PAIR(4));
            // }
            else if(map[level][i][j]==5){ // 성장 아이템
                attron(COLOR_PAIR(3)); // 지렁이 색상
                mvprintw(i, j, " ");
                attroff(COLOR_PAIR(3));
            }else if(map[level][i][j]==6){ // 독 아이템
                attron(COLOR_PAIR(6)); // 지렁이 색상
                mvprintw(i, j, " ");
                attroff(COLOR_PAIR(6));
            }else if (map[level][i][j] == 9){
                if(gateCheck==false){
                    gates.x1 = j; gates.y1=i;
                    gateCheck = true;
                }else{
                    gates.x2 =j; gates.y2=i;
                    gateCheck = false;
                }
                
                attron(COLOR_PAIR(5)); // Gate color
                mvprintw(gates.y1, gates.x1, "Q");
                mvprintw(gates.y2, gates.x2, "Q");
                attroff(COLOR_PAIR(5));
            }

            
        }
    }
}

void snake_draw(vector<Snake>& snake){
    int number = 0;
    for (vector<Snake>::const_iterator it = snake.begin(); it != snake.end(); ++it) {
        const Snake& s = *it;
        if(number == 0){
            attron(COLOR_PAIR(3));
            mvprintw(s.y, s.x, "@");
            attroff(COLOR_PAIR(3));
            number++;
        }
        else{
            attron(COLOR_PAIR(4));
            mvprintw(s.y, s.x, "O");
            attroff(COLOR_PAIR(4));
        }
    }
}

void ScreenStart()
{
    initscr();
    start_color();
    resize_term(21 + 4, 21 * 2);
    mvprintw(11, 15,  "2023 CPP Team.9");
    mvprintw(14, 7,  " HoJun.K / SeoHyun.B / Chohee.H ");
    mvprintw(17, 12, "    PRESS ANY KEY    ");
    border('#', '#', '#', '#', '#', '#', '#', '#');
    refresh();
    getch();
    clear();
    endwin();
}

void GameOverScene()
{
    initscr();
    start_color();
    resize_term(21 + 4, 21 * 2);
    mvprintw(11, 15,  "Game Over!!");
    mvprintw(17, 8, "'PRESS ANY KEY' ends the game");
    border('#', '#', '#', '#', '#', '#', '#', '#');
    refresh();
    getch();
    clear();
    endwin();
}

void randomGate(int level){ // gate를 랜덤으로 나타내는 함수
    srand(time(NULL));
    int cnt=0;
    for(int i=0; i<MAP_SIZE; i++){ //원래 생성되어 있던 게이트 닫기
        for(int j=0; j<MAP_SIZE; j++){
            if(map[level][i][j]==9) map[level][i][j]=2;
        }
    }
    do{ // 게이트 2개 생성될 때까지 루프
        int i=rand()%21;
        int j=rand()%21;
        int before_i = -1;
        int before_j = -1;
        if(map[level][i][j]==2 && (before_i != i && before_j != j)){
            map[level][i][j] = 9;
            cnt++;
            before_j = j;
            before_i = i;
        }
        if(cnt>=2) break;
    }while(1);
}
void mission(int size){
    int w = 18;
    int h = 20;
    int w_l = 1;
    int h_l = 25;
    WINDOW* window = newwin(w, h, w_l, h_l);
    refresh();
    box(window, 0, 0);
    const std::string length = std::to_string(size);
    mvwprintw(window, 2, 6, "<Score>");
    mvwprintw(window, 4, 3, "length : ");
    mvwprintw(window, 4, 12, length.c_str());
    mvwprintw(window, 8, 6, "<Mission>");
    if(size >= 5){
        mvwprintw(window, 10, 3, "length : 5 (V)");
    }
    else{
        mvwprintw(window, 10, 3, "length : 5 ( )");
    }
    wrefresh(window);
}

bool running(int level){
    clear();
    // Snake의 초기 방향
    int directionX = 1;
    int directionY = 0;

    // Snake의 몸통을 나타내는 벡터
    vector<Snake> body;
    int length = 3;
    for (int i = 0; i < length; ++i) {
        body.push_back({MAP_SIZE/2 - i, 2}); //시작지점
    }
    bool gameOver = false;
    int gatenum=0;
    while (!gameOver) {
        clear();
        drawMap(level);
        if(gatenum>50){
            randomGate(level);
            gatenum=0;
            for(int i=0; i<MAP_SIZE; i++){
                for(int j=0; j<MAP_SIZE; j++){
                    if(map[level][i][j]==5 || map[level][i][j] ==6){
                        map[level][i][j]=0;
                    }
                }
            }
            placeGrowth(level);
            poisionItem(level);
        }
        // drawMap();
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
            // 들어가는 게이트에서 머리부터 하나씩 지우면서 반대편에 게이트에서 스네이크 머리부터 하나씩 생성

            // // 게이트에 들어갈 때 몸통을 임시 저장할 배열
            // vector<Snake> tempBody;

            // // 스네이크의 머리부터 몸통을 임시 배열에 복사
            // for (int i = 0; i < body.size(); i++) {
            //     tempBody.push_back(body[i]);
            // }

            // 들어가는 게이트에서 머리부터 하나씩 지우면서 반대편에 게이트에서 스네이크 머리부터 하나씩 생성
            if (body[0].x == gates.x1 && body[0].y == gates.y1) {
                // 게이트 1에서 게이트 2로 이동
                if(directionX == -1 && directionY == 0){ // 왼쪽으로 들어갈 떄
                    if( map[level][gates.y2][gates.x2-1] == 0 &&  gates.x2 - 1 > 0 ){ //왼쪽
                        body[0].y = gates.y2;
                        body[0].x = gates.x2-1;
                    } 
                    if( map[level][gates.y2-1][gates.x2] == 0 &&  gates.y2 - 1 > 0 ){ // 위
                        body[0].y = gates.y2 - 1;
                        body[0].x = gates.x2;
                        directionX = 0;
                        directionY = -1;
                    } 
                    if( map[level][gates.y2][gates.x2+1] == 0 &&  gates.x2 +1 < MAP_SIZE-1 ){ // 오른쪽
                        body[0].y = gates.y2;
                        body[0].x = gates.x2+1;
                        directionX = 1;
                        directionY = 0;
                    } 
                    if( map[level][gates.y2+1][gates.x2] == 0 &&  gates.y2 + 1 <MAP_SIZE-1 ){ //아래
                        body[0].y = gates.y2+1;
                        body[0].x = gates.x2;
                        directionX = 0;
                        directionY = 1;
                    } 
                }
                if(directionX == 0 && directionY == -1){ // 위쪽으로 들어갈 떄
                    if( map[level][gates.y2-1][gates.x2] == 0 &&  gates.y2 - 1 > 0 ){ // 위
                        body[0].y = gates.y2 - 1;
                        body[0].x = gates.x2;
                    } 
                    if( map[level][gates.y2][gates.x2+1] == 0 &&  gates.x2 +1 < MAP_SIZE-1 ){ // 오른쪽
                        body[0].y = gates.y2;
                        body[0].x = gates.x2+1;
                        directionX = 1;
                        directionY = 0;
                    } 
                    if( map[level][gates.y2+1][gates.x2] == 0 &&  gates.y2 + 1 <MAP_SIZE-1 ){ //아래
                        body[0].y = gates.y2+1;
                        body[0].x = gates.x2;
                        directionX = 0;
                        directionY = 1;
                    } 
                    if( map[level][gates.y2][gates.x2-1] == 0 &&  gates.x2 - 1 > 0 ){ //왼쪽
                        body[0].y = gates.y2;
                        body[0].x = gates.x2-1;
                        directionX = -1;
                        directionY = 0;
                    } 
                }
                if(directionX == 1 && directionY == 0){ // 오른쪽으로 들어갈 떄
                    if( map[level][gates.y2][gates.x2+1] == 0 &&  gates.x2 +1 < MAP_SIZE-1 ){ // 오른쪽
                        body[0].y = gates.y2;
                        body[0].x = gates.x2+1;
                    } 
                    if( map[level][gates.y2+1][gates.x2] == 0 &&  gates.y2 + 1 <MAP_SIZE-1 ){ //아래
                        body[0].y = gates.y2+1;
                        body[0].x = gates.x2;
                        directionX = 0;
                        directionY = 1;
                    } 
                    if( map[level][gates.y2][gates.x2-1] == 0 &&  gates.x2 - 1 > 0 ){ //왼쪽
                        body[0].y = gates.y2;
                        body[0].x = gates.x2-1;
                        directionX = -1;
                        directionY = 0;
                    } 
                    if( map[level][gates.y2-1][gates.x2] == 0 &&  gates.y2 - 1 > 0 ){ // 위
                        body[0].y = gates.y2 - 1;
                        body[0].x = gates.x2;
                        directionX = 0;
                        directionY = -1;
                    } 
                }
                if(directionX == 0 && directionY == 1){ // 아래쪽으로 들어갈 떄
                    if( map[level][gates.y2+1][gates.x2] == 0 &&  gates.y2 + 1 <MAP_SIZE-1 ){ //아래
                        body[0].y = gates.y2+1;
                        body[0].x = gates.x2;
                    } 
                    if( map[level][gates.y2][gates.x2-1] == 0 &&  gates.x2 - 1 > 0 ){ //왼쪽
                        body[0].y = gates.y2;
                        body[0].x = gates.x2-1;
                        directionX = -1;
                        directionY = 0;
                    } 
                    if( map[level][gates.y2-1][gates.x2] == 0 &&  gates.y2 - 1 > 0 ){ // 위
                        body[0].y = gates.y2 - 1;
                        body[0].x = gates.x2;
                        directionX = 0;
                        directionY = -1;
                    } 
                    if( map[level][gates.y2][gates.x2+1] == 0 &&  gates.x2 +1 < MAP_SIZE-1 ){ // 오른쪽
                        body[0].y = gates.y2;
                        body[0].x = gates.x2+1;
                        directionX = 1;
                        directionY = 0;
                    } 
                }
            }
            else {
                // 게이트 1에서 게이트 2로 이동
                if(directionX == -1 && directionY == 0){ // 왼쪽으로 들어갈 떄
                    if( map[level][gates.y1][gates.x1-1] == 0 &&  gates.x1 - 1 > 0 ){ //왼쪽
                        body[0].y = gates.y1;
                        body[0].x = gates.x1-1;
                    } 
                    if( map[level][gates.y1-1][gates.x1] == 0 &&  gates.y1 - 1 > 0 ){ // 위
                        body[0].y = gates.y1 - 1;
                        body[0].x = gates.x1;
                        directionX = 0;
                        directionY = -1;
                    } 
                    if( map[level][gates.y1][gates.x1+1] == 0 &&  gates.x1 +1 < MAP_SIZE-1 ){ // 오른쪽
                        body[0].y = gates.y1;
                        body[0].x = gates.x1+1;
                        directionX = 1;
                        directionY = 0;
                    } 
                    if( map[level][gates.y1+1][gates.x1] == 0 &&  gates.y1 + 1 <MAP_SIZE-1 ){ //아래
                        body[0].y = gates.y1+1;
                        body[0].x = gates.x1;
                        directionX = 0;
                        directionY = 1;
                    } 
                }
                if(directionX == 0 && directionY == -1){ // 위쪽으로 들어갈 떄
                    if( map[level][gates.y1-1][gates.x1] == 0 &&  gates.y1 - 1 > 0 ){ // 위
                        body[0].y = gates.y1 - 1;
                        body[0].x = gates.x1;
                    } 
                    if( map[level][gates.y1][gates.x1+1] == 0 &&  gates.x1 +1 < MAP_SIZE-1 ){ // 오른쪽
                        body[0].y = gates.y1;
                        body[0].x = gates.x1+1;
                        directionX = 1;
                        directionY = 0;
                    } 
                    if( map[level][gates.y1+1][gates.x1] == 0 &&  gates.y1 + 1 <MAP_SIZE-1 ){ //아래
                        body[0].y = gates.y1+1;
                        body[0].x = gates.x1;
                        directionX = 0;
                        directionY = 1;
                    } 
                    if( map[level][gates.y1][gates.x1-1] == 0 &&  gates.x1 - 1 > 0 ){ //왼쪽
                        body[0].y = gates.y1;
                        body[0].x = gates.x1-1;
                        directionX = -1;
                        directionY = 0;
                    } 
                }
                if(directionX == 1 && directionY == 0){ // 오른쪽으로 들어갈 떄
                    if( map[level][gates.y1][gates.x1+1] == 0 &&  gates.x1 +1 < MAP_SIZE-1 ){ // 오른쪽
                        body[0].y = gates.y1;
                        body[0].x = gates.x1+1;
                    } 
                    if( map[level][gates.y1+1][gates.x1] == 0 &&  gates.y1 + 1 <MAP_SIZE-1 ){ //아래
                        body[0].y = gates.y1+1;
                        body[0].x = gates.x1;
                        directionX = 0;
                        directionY = 1;
                    } 
                    if( map[level][gates.y1][gates.x1-1] == 0 &&  gates.x1 - 1 > 0 ){ //왼쪽
                        body[0].y = gates.y1;
                        body[0].x = gates.x1-1;
                        directionX = -1;
                        directionY = 0;
                    } 
                    if( map[level][gates.y1-1][gates.x1] == 0 &&  gates.y1 - 1 > 0 ){ // 위
                        body[0].y = gates.y1 - 1;
                        body[0].x = gates.x1;
                        directionX = 0;
                        directionY = -1;
                    } 
                }
                if(directionX == 0 && directionY == 1){ // 아래쪽으로 들어갈 떄
                    if( map[level][gates.y1+1][gates.x1] == 0 &&  gates.y1 + 1 <MAP_SIZE-1 ){ //아래
                        body[0].y = gates.y1+1;
                        body[0].x = gates.x1;
                    } 
                    if( map[level][gates.y1][gates.x1-1] == 0 &&  gates.x1 - 1 > 0 ){ //왼쪽
                        body[0].y = gates.y1;
                        body[0].x = gates.x1-1;
                        directionX = -1;
                        directionY = 0;
                    } 
                    if( map[level][gates.y1-1][gates.x1] == 0 &&  gates.y1 - 1 > 0 ){ // 위
                        body[0].y = gates.y1 - 1;
                        body[0].x = gates.x1;
                        directionX = 0;
                        directionY = -1;
                    } 
                    if( map[level][gates.y1][gates.x1+1] == 0 &&  gates.x1 +1 < MAP_SIZE-1 ){ // 오른쪽
                        body[0].y = gates.y1;
                        body[0].x = gates.x1+1;
                        directionX = 1;
                        directionY = 0;
                    } 
                }
            }

        }



        //         for (int i = 0; i < tempBody.size(); i++) {
        //             tempBody[i].x = gates.x2;
        //             tempBody[i].y = gates.y2;
        //         }
        //         if(gates.x2 == 0) {
        //             directionX = 1;
        //             directionY = 0;
        //         }else if(gates.x2 == MAP_SIZE){
        //             directionX = -1;
        //             directionY = 0;
        //         }else if(gates.y2 ==0){
        //             directionX = 0;
        //             directionY = -1;
        //         }else{
        //             directionX = 0;
        //             directionY = 1;
        //         }
        //     } else {
        //         // 게이트 2에서 게이트 1로 이동
        //         for (int i = 0; i < tempBody.size(); i++) {
        //             body[i].x = gates.x1;
        //             body[i].y = gates.y1;
        //         }
        //         if(gates.x1 == 0) {
        //             directionX = 1;
        //             directionY = 0;
        //         }else if(gates.x1 == MAP_SIZE){
        //             directionX = -1;
        //             directionY = 0;
        //         }else if(gates.y1 ==0){
        //             directionX = 0;
        //             directionY = -1;
        //         }else{
        //             directionX = 0;
        //             directionY = 1;
        //         }
        //     }
        //     // 스네이크 몸통을 업데이트
        //     for (int i = 0; i < body.size(); i++) {
        //         body[i].x = tempBody[i].x;
        //         body[i].y = tempBody[i].y;
        //     }
        // }

        // Snake 이동
        int nextX = body[0].x + directionX;
        int nextY = body[0].y + directionY;

        // 아이템 충돌
        if(map[level][nextY][nextX]==5){
            Snake newBodyPart;
            newBodyPart.x = nextX;
            newBodyPart.y = nextY;
            body.insert(body.begin(), newBodyPart);
            map[level][nextY][nextX] = 0;
        }

        if(map[level][nextY][nextX]==6){ // 독 아이템
            map[level][nextY][nextX] = 0;
            if(body.size()>3){
                body.pop_back();
            }else{
                gameOver = true;
            }
        }

        // 벽 또는 자기 자신과의 충돌 체크
        if (map[level][nextY][nextX] == 2) {
            if(map[level][nextY][nextX]==9) continue;
            gameOver = true;
            break;
        }
        for (int i = 1; i < body.size(); i++) {
            if (body[i].x == nextX && body[i].y == nextY) {
                gameOver = true;
                break;
            }
        }
        
        int l = body.size();
        // Snake의 머리 위치 업데이트
        body.insert(body.begin(), {nextX,nextY});
        if (body.size() > l) {
            body.pop_back();
        }
        // Snake의 꼬리 제거
        // if (map[nextY][nextX] != 2|| map[nextY][nextX] != 1) {
        //     map[body.back().y][body.back().x] = 0;
        //     body.pop_back();
        // }

        // // Snake의 머리와 꼬리 표시
        // map[nextY][nextX] = 3;
        // map[body.back().y][body.back().x] = 4;

        
        snake_draw(body);
        mission(body.size());
        refresh();
        // 100ms 대기
        napms(100);
        gatenum++;
        if(body.size() == 5) return true;
    }
    return false;
}

int main(){
    time(0);
    // Snake의 초기 위치
    int startX = MAP_SIZE / 2;
    int startY = MAP_SIZE / 2;

    
    ScreenStart();
    // 게이트 초기 위치는 맵에 9로 표시해두고 시작

    initscr(); // Curses 모드 시작
    start_color(); // 색상 기능 활성화
    init_pair(1, COLOR_WHITE, COLOR_WHITE);   // 벽 색상
    init_pair(2, COLOR_BLACK, COLOR_WHITE);  // 게임 맵 테두리 색상 안쓰겠습니다.
    init_pair(3, COLOR_GREEN, COLOR_GREEN); // 지렁이 색상
    init_pair(4, COLOR_YELLOW, COLOR_YELLOW);// 지렁이 몸통 색상
    init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA); // 게이트 색
    init_pair(6, COLOR_RED, COLOR_RED); // 독 아이템

    nodelay(stdscr, true);
    keypad(stdscr, true);
    noecho();
    curs_set(0);

    // 게임 루프
    int level = 0;
    if(running(level)){
        level = 1;
        if(running(level)){
            level = 2;
            if(running(level)){
                level = 3;
                if(running(level)){
                    endwin();
                    std::cout << "you win" << std::endl;
                    return 0;
                }
            }
        }
    }

    // 게임 종료 후 NCurses 정리
    endwin();
    GameOverScene();
    std::cout << "you lose" << std::endl;
    return 0;
}