#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y)		// Ŀ���� x,y��ǥ�� �̵�
{
	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int wherex()					// Ŀ���� x ��ǥ�� ����
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);

	return BufInfo.dwCursorPosition.X;
}

int wherey()					// Ŀ���� y��ǥ�� ����
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);

	return BufInfo.dwCursorPosition.Y;
}

void setcursortype(int cur_t)	// Ŀ�� �����
{
	CONSOLE_CURSOR_INFO ccInfo;

	if (cur_t == 0)		// NOCURSOR
	{
		ccInfo.dwSize = 20;
		ccInfo.bVisible = FALSE;
	}
	else if (cur_t == 1)	// SOLIDCURSOR
	{
		ccInfo.dwSize = 100;
		ccInfo.bVisible = TRUE;
	}
	else				// NORMALCURSOR
	{
		ccInfo.dwSize = 20;
		ccInfo.bVisible = TRUE;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ccInfo);
}

BOOL gettext(int left, int top, int right, int bottom, void *destin)    // ���� �����ϱ�
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordBufSize = { right - left + 1, bottom - top + 1 };
	COORD coordBufCoord = { 0, 0 };
	SMALL_RECT region = { left, top, right, bottom };

	return ReadConsoleOutput(hConsole, destin, coordBufSize, coordBufCoord, &region);
}

BOOL puttext(int left, int top, int right, int bottom, void *source)    // ������ ���� �ǵ�����
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordBufSize = { right - left + 1, bottom - top + 1 };
	COORD coordBufCoord = { 0, 0 };
	SMALL_RECT region = { left, top, right, bottom };

	return WriteConsoleOutput(hConsole, source, coordBufSize, coordBufCoord, &region);
}

int getscr(int x, int y)    // x, y ��ǥ ������ �ƽ�Ű�ڵ带 ����
{
	CHAR_INFO dest;

	gettext(x, y, x, y, &dest);

	return dest.Char.AsciiChar;
}

int getattr(int x, int y)   // x, y ��ǥ ������ �Ӽ�(����)�� ����
{
	CHAR_INFO dest;

	gettext(x, y, x, y, &dest);

	return dest.Attributes;
}

int getcolor(int x, int y)	// ���� ���� ���� getcolor(���ڻ�);
{
	short   attr;
	DWORD   dummy;
	COORD   pos = { x, y };

	ReadConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), &attr, 1, pos, &dummy);

	return (attr & 0xf);
}

int getbkcolor(int x, int y)	// ��� ���� ���� getcolor(����);
{
	short   attr;
	DWORD   dummy;
	COORD   pos = { x, y };

	ReadConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), &attr, 1, pos, &dummy);

	return (attr & 0xf0) >> 4;
}

void textattr(int color)		// ���� ���� : textattr(���ڻ�|����<<4)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(color));
}

void setcolor(int textcolor)    // ���� ���� ���� setcolor(���ڻ�);
{
	WORD    attr;
	DWORD   dummy;
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &BufInfo);
	ReadConsoleOutputAttribute(hConsole, &attr, 1, BufInfo.dwCursorPosition, &dummy);

	attr = textcolor | (attr & 0xf0);
	SetConsoleTextAttribute(hConsole, (WORD)(attr));

}

void setbkcolor(int color)        // ��� ���� ���� setbkcolor(����);
{
	WORD    attr;
	DWORD   dummy;
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &BufInfo);
	ReadConsoleOutputAttribute(hConsole, &attr, 1, BufInfo.dwCursorPosition, &dummy);

	attr = (attr & 0xf) | (color << 4);
	SetConsoleTextAttribute(hConsole, (WORD)(attr));

}

print_box(int x, int y, char ch) {
	int i, j;
	for (i = 0; i <= x; i++)
		for (j = 0; j <= y; j++) {
			if (i == 0 || i == x || j == y || j == 0) {
				gotoxy(i, j);
				printf("%c", ch);
			}
		}
}

print_dot(int x, int y, char ch)
{
	gotoxy(x, y);
	printf("%c", ch);
}

void print_bar(int bar_x) {
	gotoxy(bar_x, 20);
	printf("-------");
}

void delete_bar(int x, int y, int bar_x) {
	int i;
	print_dot(x, y, ' ');
	for (i = bar_x; i < bar_x + 7; i++) {
		print_dot(i, 20, ' ');
	}
}

void make_block(int a) {
	int i, j;
	for (i = a; i < a + 3; i++) {
		for (j = 5; j < 8; j++) {
			gotoxy(i, j);
			printf("O");
		}
	}
}

void delete_block(int a) {
	int  i, j;
	for (i = a; i < a + 3; i++) {
		for (j = 5; j < 8; j++) {
			gotoxy(i, j);
			printf(" ");
		}
	}


}