//项目二 贪吃蛇 snake

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define Width 80
#define High 20
#define Mode "■"
#define Head "◎"
#define Body "□"
#define APPLE "◆"
#define UP 72 //方向键：上
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右
struct Snake {
	int x[Width * High];
	int y[Width * High];
	int Len;
} s;
struct apple {
	int x;
	int y;
} app;
void initGame_10230326() {
	s.Len = 3;
	s.x[0] = Width / 2;
	s.y[0] = High / 2;
	for (int i = 1; i < s.Len; i++) {
		s.x[i] = s.x[i - 1] - 1;
		s.y[i] = s.y[i - 1];
	}
	srand(time(NULL));
	app.x = rand() % (Width - 2) + 1;
	app.y = rand() % (High - 2) + 1;
}
void drawGame() {
	system("cls");
	for (int y = 0; y < High; y++) {
		for (int x = 0; x < Width; x++) {
			if (x == 0 || x == Width - 1 || y == 0 || y == High - 1) {
				printf("%s", Mode);
			} else if (x == app.x && y == app.y) {
				printf("%s", APPLE);
			} else {
				int found = 0;
				for (int i = 0; i < s.Len; i++) {
					if (x == s.x[i] && y == s.y[i]) {
						printf("%s", (i == 0) ? Head : Body);
						found = 1;
						break;
					}
				}
				if (!found) {
					printf(" ");
				}
			}
		}
		printf("\n");
	}
}
void updateSnake_10230326(int direction) {
	//movebody
	for (int i = s.Len - 1; i > 0; i--) {
		s.x[i] = s.x[i - 1];
		s.y[i] = s.y[i - 1];
	}
	//movehead
	switch (direction) {
		case UP:
			s.y[0]--;
			break;
		case DOWN:
			s.y[0]++;
			break;
		case RIGHT:
			s.x[0]++;
			break;
		case LEFT:
			s.x[0]--;
			break;
	}	
}
void placeNewApple_10230326() {
	srand(time(NULL));
	app.x = rand() % (Width - 2) + 1;
	app.y = rand() % (High - 2) + 1;
	for (int i = 0; i < s.Len; i++) {
		if (app.x == s.x[i] && app.y == s.y[i]) {
			placeNewApple_10230326();
			break;
		} else
			break;
	}
}
void checkApple_10230326(){
	if(s.x[0]==app.x&&s.y[0]==app.y){
		s.Len+=3;
		srand(time(NULL));
		app.x = rand() % (Width - 2) + 1;
		app.y = rand() % (High - 2) + 1;
		for (int i = 0; i < s.Len; i++) {
			if (app.x == s.x[i] && app.y == s.y[i]) {
				placeNewApple_10230326();
				break;
			} else
				break;
		}
	}
}
int checkCollision_10230326(){
	if(s.x[0] == 0 || s.x[0] == Width - 1 || s.y[0] == 0 || s.y[0] == High - 1 ){
		return 1;
	}
	for(int i=1;i<s.Len;i++){
		if(s.x[0]==s.x[i]&&s.y[0]==s.y[i]){
			return 1;
		}
	}
	return 0;
}
int main() {
	char ch;
	int direction = RIGHT;
	system("mode con cols=80 lines=20");//设置窗口大小。
	system("title 贪吃蛇");
	system("color 70");
	initGame_10230326();
	while (1) {
		if (kbhit()) {

			ch = getch();
			switch (ch) {
				case UP:
					if (direction != DOWN) direction = UP;
					break;
				case DOWN:
					if (direction != UP) direction = DOWN;
					break;
				case LEFT:
					if (direction != RIGHT) direction = LEFT;
					break;
				case RIGHT:
					if (direction != LEFT) direction = RIGHT;
					break;
				default:
					break;
			}
		}
		updateSnake_10230326(direction);
		char a;
		if (checkCollision_10230326()) { 
			printf("YOU LOSE!\n你输了！\n"); 
			printf("按任意键重新开始，按N/n+Enter退出\n");
			a=getch();
			if(a=='N'||a=='n'){
				break; 
			}
			else{
				initGame_10230326();
			}
		}  
		drawGame();
		checkApple_10230326();
		Sleep(200);
	}
	getchar();
	return 0;
}
