
// x,y가 최대값, 최소값에 부딪히면 ++를 --로 --를 ++로 이런식으로

#include <stdio.h>
#include <windows.h>
#include "test.h"

int  main() {
	
		int x, y, xv, yv;

		x = 17;
		y = 18;//시작 위치

		xv = yv = 1;  //방향전환을 위한 값
		int box_length = 76;
		int box_height = 21;
		int bar_x = 17;
		int block_height = 6;
		int block[] = { 10,20,30,40,50,60 };
		print_box(box_length, box_height, '*');
		char a;
		gotoxy(30, 15);
		printf("press ENTER to start!");

		while (1)
		{
			scanf("%c", &a);
			if (a == 32)
			break;
		}
		gotoxy(30, 15);
		printf("                        ");

		while (1)
		{

			delete_bar(x, y, bar_x);
			if (x <= MIN_X || x >= MAX_X)  xv *= -1;

			if (y >= MAX_Y)  yv *= -1;
			if (y <= MIN_Y) {
				yv = 0;
				gotoxy(25, 10);
				printf("game over");
			}


			if ((y == bar_x && (x >= bar_x && x <= bar_x + 7)))
				yv *= -1;

			if (GetAsyncKeyState(VK_LEFT)) {
				if (bar_x < 2)
					bar_x = bar_x;
				else bar_x--;
			}
			if (GetAsyncKeyState(VK_RIGHT)) {
				if (bar_x > 68)
					bar_x = bar_x;
				else bar_x++;
			}
			if (GetAsyncKeyState(VK_ESCAPE)) {
				clrscr();
				gotoxy(25, 10);
				system("종료합니다.");
				break;
			}
			x += xv;
			y += yv;

			for (int i = 0; i < 6; i++) {
				make_block(block[i]);
			}

			for (int a = 0; a < 6; a++) {
				if (x >= block[a] && x <= block[a] + 3 && y >= 5 && y <= 8) {
					delete_block(block[a]);
					block[a] = 100;
					gotoxy(80, 17);
				}
			}

			
				print_dot(x, y, '*');
				print_bar(bar_x);
				delay(50);
			
		}
return 0;
}

