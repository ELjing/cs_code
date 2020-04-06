/*

	Title : my first Greedy Snake program
	Time : 2020-3-28
	Author : Furtherun 
	
*/

#include <cstdio>
#include <stdlib.h>
#include <windows.h> // to use cursor API
#include <time.h>    // for random time
#include <conio.h>   // monitor buttons

/*
	define the map informations 
*/

#define MAPHEIGHT 25
#define MAPWIDTH  60

/*
	define the max size of snake
*/

#define MAXSNAKESIZE 50

/*
	game struct: food and snake
*/
class Food{
public:
	int x, y;
};
class Snake{
public:
	int x[MAXSNAKESIZE];
	int y[MAXSNAKESIZE];
	int len;
	int speed;
	Snake() {
		len = 3;
		speed = 300;
		x[0] = MAPWIDTH/2;
		y[0] = MAPHEIGHT/2;
	}
};

Food food;
Snake snake;

/*
	== global variables list ==
	key : the initial orientation
	changeFlag : if direction change, falg = 1 
*/
int key = 'w';
bool changeFlag = false;
 
/*
	== function list ==
	void drawMap();    			draw the initial map
	void createFood(); 			generate a food point
	void keyWown();    			push a key
	bool snakeState(); 			monitor if the game is over
	void gotoxy(int x, int y);  set point
*/
void drawMap();
void createFood();
void keyDown();
bool snakeState();
void gotoxy(int x, int y);

int main() {
	drawMap();
	while(true) {
		createFood();
		Sleep(snake.speed);
		keyDown();
		if(snakeState() == false) {
			gotoxy(MAPWIDTH/2 -5, MAPHEIGHT/2);
			printf("Game over!");
			break;
		}
	}
//	printf(" == GameOver == \n");
	system("pause");
	return 0;
}

void drawMap() {
	//set the edge of the map is 2
	for(int i = 0; i <= MAPHEIGHT; ++i) {
		gotoxy(0, i);
		printf("¡ö");
		gotoxy(MAPWIDTH, i);
		printf("¡ö");
	}
	for(int i = 0; i <= MAPWIDTH; i += 2) { //take care of the token size
		gotoxy(i, 0);
		printf("¡ö");
		gotoxy(i, MAPHEIGHT);
		printf("¡ö");
	}
	//food: ¡Ñ snake: ¡ö
	//init snake
	gotoxy(snake.x[0], snake.y[0]);
	printf("¡ö");
	for(int i = 1; i < snake.len; ++ i) {
		snake.x[i] = snake.x[i-1] + 2;
		snake.y[i] = snake.y[i-1];
		gotoxy(snake.x[i], snake.y[i]);
		printf("¡ö");
	}
	//init food
	srand((unsigned int) time(NULL));
	food.x = rand() % (MAPWIDTH - 4) + 2;
	food.y = rand() % (MAPHEIGHT - 2) + 1;
	while(food.x % 2 == 1) { //make the initial food x is even
		food.x = rand() % (MAPWIDTH - 4) + 2;
	}
	gotoxy(food.x, food.y);
	printf("¡Ñ");
};
void createFood() {
	if(snake.x[0] == food.x && snake.y[0] == food.y) { //snake eat food
		srand((unsigned int) time(NULL));
		while(true) {
			bool flag = true;
			food.x = rand() %(MAPWIDTH - 4) + 2;
			food.y = rand() %(MAPHEIGHT - 2) + 1;
			for(int i = 0; i < snake.len; ++ i) {
				if(snake.x[i] == food.x && snake.y[i] == food.y) {
					flag = false; //the new food in the snake body
					break;
				}
			}
			if(flag == true && food.x % 2 == 0) {
				break;
			}
		}
		snake.len ++; 
		gotoxy(food.x, food.y);
		printf("¡Ñ");
		changeFlag = true;
	}
};
void keyDown() {
	if(_kbhit()) {
		fflush(stdin);
		key = _getch();
	}
	if(!changeFlag) {
		gotoxy(snake.x[snake.len-1], snake.y[snake.len-1]);
		printf("  "); //delete the last one snake union  
	}
	for(int i = snake.len-1; i > 0; -- i) {
		snake.x[i] = snake.x[i-1];
		snake.y[i] = snake.y[i-1];
	}
	switch(key) {
		case 'w':
		case 'W':
			snake.y[0] --;
			break;
		case 'a':
		case 'A':
			snake.x[0] -= 2;
			break;
		case 's':
		case 'S':
			snake.y[0] ++;
			break;
		case 'd':
		case 'D':
			snake.x[0] += 2;
			break;
	}
	gotoxy(snake.x[0], snake.y[0]); //draw the snake head
	printf("¡ö");
	changeFlag = false;
	gotoxy(MAPHEIGHT + 2, 0); //remove the cursor
};
bool snakeState() {
	if(snake.x[0] == 0 || snake.x[0] == MAPWIDTH - 2 ||
		snake.y[0] == 0 || snake.y[0] == MAPHEIGHT - 1) {
		return false;
	}
	for(int i = 1; i < snake.len; ++ i) {
		if(snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i]) {
			return false;
		}
	}
	return true;
};
void gotoxy(int x, int y) {
	//get the window position
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//set point
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
};
 
