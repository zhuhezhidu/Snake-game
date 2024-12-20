CCB
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define WIDE 20
#define HIGH 10
#define SIZE 100
typedef struct {                      // 蛇身和食物位置
    int x;
    int y;
} Point;

Point snake[SIZE];                              // 蛇身
int snakeLength = 1;                         // 蛇长
Point food;                                        // 食物
int score = 0;
int gameOver = 0;                   // 标志位，检查游戏是否结束

void Wall();
void input();
void logic();
void Food();
void Gamestart();
void Rules();
void Gameover();

void Food() {
    food.x = rand() % WIDE;//确保不越界
    food.y = rand() % HIGH;
}

void Rules() {
    printf("游戏规则：\n");
    printf("1. 使用方向键控制蛇的移动。\n");
    printf("2. 每次吃到食物，蛇的长度会增加。\n");
    printf("3. 蛇撞到墙壁或自己时，游戏结束。\n");
    printf("4. 通过得分增加挑战，尽可能让蛇变得更长。\n");
    printf("按任意键返回菜单...");
    _getch();
}

void Gameover() {
    printf("感谢你的参与！\n");
    exit(0); //终止整个程序
}

void input() {                                  // 控制蛇
    if (_kbhit()) {                                 // 检查是否有键被按下
        char key = _getch();                    // 获取按键
        switch (key) {
            case 'w':
                if (snake[0].y > 0)
                    snake[0].y--;
                break;
            case 's':
                if (snake[0].y < HIGH-1)
                    snake[0].y++;
                break;
            case 'a':
                if (snake[0].x > 0)
                    snake[0].x--;
                break;
            case 'd':
                if (snake[0].x < WIDE-1)
                    snake[0].x++;
                break;
        }
    }
}

void Gamestart() {
    gameOver = 0;
    score = 0;
    snakeLength = 1;
    snake[0].x = WIDE / 2;              //初始蛇在中间
    snake[0].y = HIGH / 2;
    Food();                                 // 在随机位置生成食物
    while (!gameOver) {          //内需要逻辑函数来判断何时终止循环
        Wall();                         //每次循环清屏，更新位置
        input();                        //每次循环接收新输入
        logic();                            //判断是否死亡
    }

    printf("游戏结束！你的得分是：%d\n", score);
    printf("按任意键返回菜单...");
    _getch();                                               //接收输入返回菜单
}

void Wall() {                                        // 屏幕更新
    system("cls");                                  // win清屏
    for (int i = 0; i < WIDE + 2; i++)  //顶部边框
        printf("#");
    printf("\n");
    for (int i = 0; i < HIGH; i++) {                  //行
        for (int j = 0; j < WIDE; j++) {            //列
            if (j == 0)                                       //左边
                printf("#");
            else if (j == WIDE - 1)                      //右边
                printf("#");
            else if (i == food.y && j == food.x)    //食物
                printf("@");
            else {
                int isbody = 0;                                //判断是否为蛇身
                for (int k = 0; k < snakeLength; k++) {
                    if (snake[k].x == j && snake[k].y == i) {
                        isbody = 1;
                        break;
                    }
                }
                if (isbody)
                    printf("O");                                            // 蛇身
                else
                    printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDE + 2; i++)                                // 底边
        printf("#");
    printf("\n");

    printf("得分: %d\n", score);
}


void logic() {
    for (int i = snakeLength - 1; i > 0; i--) {         // 移动蛇身
        snake[i] = snake[i - 1];
    }
    switch (_getch()) {                                                 // 移动蛇头
        case 'w':
            snake[0].y--;
            break;
        case 's':
            snake[0].y++;
            break;
        case 'a':
            snake[0].x--;
            break;
        case 'd':
            snake[0].x++;
            break;
    }
    if (snake[0].x<=0 || snake[0].x>=WIDE-1 || snake[0].y<=0 || snake[0].y >= HIGH-1) {             // 是否撞墙
        gameOver = 1;
    }
    for (int i = 1; i < snakeLength; i++) {                                                                                              //是否撞己
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            gameOver = 1;
            break;
        }
    }
    if (snake[0].x == food.x && snake[0].y == food.y) {                                                                      //是否吃到食物
        score += 1;
        snakeLength++;
        Food();
    }
}

int main() {
    int menu;
    while (1) {
        printf("1. 开始游戏\n");
        printf("2. 查看游戏规则\n");
        printf("3. 退出游戏\n");
        printf("请输入数字 1—3: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                Gamestart();
                break;
            case 2:
                Rules();
                break;
            case 3:
                Gameover();
                break;
            default:
                printf("无效选择，请重新输入！\n");
        }
    }
    return 0;
}
