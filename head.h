#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include "sprites.h"

typedef struct as {
	char name[17];
	long int score;
	struct as * next;
} per;


//#####################
//variable
per *start = NULL;
HANDLE Handle;
int x, y;
int nr, pos;
int speed;
long int score = 0;
int option = 0;
int Instr = 0;
char name[18];

//####################
//Functions 
void Random();
void Move(int x, int y);
void TColor(char color[32]);
void TurnC(BOOL t);
void DrawFig();
void DeleteFig();
void Prep();
void Box();
void Play();
void CheckLine();
void DrawScore();
int CheckGO();
void GameOver();
void AddScore();
void ShowTopScore();

//move cursor
void Move(int x, int y) {
	COORD c;
	c.X = y;
	c.Y = x;
	SetConsoleCursorPosition(Handle, c);
}

//text color
void TColor(char color[32]) {
	if (strcmp(color, "green") == 0)
		SetConsoleTextAttribute(Handle, FOREGROUND_GREEN);
	else if (strcmp(color, "red") == 0)
		SetConsoleTextAttribute(Handle, FOREGROUND_RED);
	else if (strcmp(color, "blue") == 0)
		SetConsoleTextAttribute(Handle, FOREGROUND_BLUE);
	else if (strcmp(color, "bgreen") == 0)
		SetConsoleTextAttribute(Handle, BACKGROUND_GREEN);
	else if (strcmp(color, "bblue") == 0)
		SetConsoleTextAttribute(Handle, BACKGROUND_BLUE);
	else if (strcmp(color, "bred") == 0)
		SetConsoleTextAttribute(Handle, BACKGROUND_RED);

}

//Cursor visibility
void TurnC(BOOL t) {
	CONSOLE_CURSOR_INFO inf;
	GetConsoleCursorInfo(Handle, &inf);
	inf.bVisible = t;
	SetConsoleCursorInfo(Handle, &inf);
}

//get random fig nr
void Random() {
	srand(time(NULL));
	nr = rand() % 7;
	pos = rand() % 4;
}

//prepare window
void Prep() {
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	TurnC(FALSE);
	TColor("green");
	//system("mode 100,51");
	SetConsoleDisplayMode(Handle, 1, NULL);
	FigPrep();
	Box();
	Move(7, 63);
	printf("Start");

	Move(8, 63);
	printf("Turn on instructions");

	Move(9, 63);
	printf("Exit");
}

//Draw box
void Box() {
	Move(0, 0);
	printf("%c", 186);//coltu stinga sus
	for (int i = 0; i < 60; i++)
		printf("%c", 0);
	printf("%c", 186);//coltu dreapta sus

	for (int i = 0; i < 45; i++)
	{
		printf("\n");
		printf("%c", 186);
		for (int j = 0; j < 60; j++)
		{
			printf("%c", 0);
		}
		printf("%c", 186);
	}
	printf("\n");
	printf("%c", 200);//coltu stinga sus
	for (int i = 0; i < 60; i++)
		printf("%c", 205);
	printf("%c", 188);//coltu dreapta sus

}

//Main game function
void Play() {
	x = 0; y = 9;
	clock_t t1;
	t1 = clock();
	int delay = 0;
	while (1) {
		clock_t t2;
		//press down key
		if (GetAsyncKeyState(VK_DOWN)) {
			speed = 50;
			if (delay >= 30) {
				score += 1;
				delay = 0;
				DrawScore();
			}
			else
				delay++;
		}
		else speed = 500;
		//daca apas
		if (kbhit()) {
			int tmp1 = 0, tmp2 = 0;
			int c = getch();
			if (GetAsyncKeyState(0x50) & 1) {
				int test = 4000;
				TColor("red");
				while (1) {
					if (test > 4000)
						test = 0;
					else
						test++;
					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

					if (test < 3000) {
						Move(5, 63);
						printf("PAUSE");
					}
					else {
						Move(5, 63);
						printf("     ");
					}
					if (GetAsyncKeyState(0x50) & 1) {
						break;
					}
				}
				Move(5, 63);
				printf("     ");
				TColor("green");
			}
			for (int i = 0; i < 4; i++)
			{
				if ((box[x + fig[pos].figures[nr][i] / 4][y + fig[pos].figures[nr][i] % 4 - 1] == 1) || y + fig[pos].figures[nr][i] % 4 == 0)
					tmp1 = 1;
				if ((box[x + fig[pos].figures[nr][i] / 4][y + fig[pos].figures[nr][i] % 4 + 1] == 1) || y + fig[pos].figures[nr][i] % 4 == 19)
					tmp2 = 1;
			}
			//press left key
			if (c == 75 && tmp1 == 0) {
				DeleteFig();
				y--;
				DrawFig();
			}
			//press right key
			else if (c == 77 && tmp2 == 0)
			{
				DeleteFig();
				y++;
				DrawFig();
			}
			else if (c == 72) {
				DeleteFig();
				if (pos == 0)
					pos = 1;
				else if (pos == 1)
					pos = 2;
				else if (pos == 2)
					pos = 3;
				else if (pos == 3)
					pos = 0;
				DrawFig();
			}
		}
		t2 = clock();
		DrawFig();
		int tmp = 0;
		for (int i = 0; i < 4; i++)
		{
			if ((box[x + fig[pos].figures[nr][i] / 4 + 1][y + fig[pos].figures[nr][i] % 4] == 1) || x + fig[pos].figures[nr][i] / 4 == 22)
				tmp = 1;
		}
		if (tmp == 1)
			break;
		//daca a trecut timpul 
		if (t2 - t1 >= speed) {
			t1 = t2;
			DeleteFig();
			x++;
			DrawFig();


		}
	}
	for (int i = 0; i < 4; i++)
	{
		box[x + fig[pos].figures[nr][i] / 4][y + fig[pos].figures[nr][i] % 4] = 1;
	}
}

//game funtion
void Game() {
	TurnC(FALSE);
	score = 0;
	DrawScore();
	while (1) {
		Random();
		Play();
		if (CheckGO() == 1)
			return;
		CheckLine();
	}
}

//GameOver
void GameOver() {
	TColor("bred");
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			box[i][j] = 0;
			Move(i * 2, j * 3 + 1);
			printf("   ");
			Move(i * 2 + 1, j * 3 + 1);
			printf("   ");
		}
	}
	TColor("green");
	Move(22, 24);
	printf("Game Over");
	Move(24, 21);
	printf("Score: %d", score);
	Move(26, 21);
	printf("Press enter key to continue...");
	while (getch() != 13);
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			Move(i * 2, j * 3 + 1);
			printf("   ");
			Move(i * 2 + 1, j * 3 + 1);
			printf("   ");
		}
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	Move(26, 16);
	printf("Enter your name: ");
	name[0] = '\0';
	Move(28, 16);
	printf("Press enter to continue ...");
	Move(30, 16);
	printf("Press backspace to delete a character ...");
	Move(26, 33);
	TurnC(TRUE);
	for (int i = 0; i < 17;)
	{
		int c = getch();
		if (c == 8 && i > 0) {
			i--;
			name[i] = '\0';
			TurnC(FALSE);
			Move(26, 33);
			printf("                ");
			Move(26, 33);
			printf("%s", name);
			TurnC(TRUE);
		}
		else if (c == 13 && i == 0)
			continue;
		else if (c == 13)
			break;
		else if (i == 16) {
		}
		else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
			name[i] = c;
			i++;
			name[i] = '\0';
			TurnC(FALSE);
			Move(26, 33);
			printf("%s", name);
			TurnC(TRUE);
		}
	}
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			box[i][j] = 0;
			Move(i * 2, j * 3 + 1);
			printf("   ");
			Move(i * 2 + 1, j * 3 + 1);
			printf("   ");
		}
	}
	AddScore();
	ShowTopScore();
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			Move(i * 2, j * 3 + 1);
			printf("   ");
			Move(i * 2 + 1, j * 3 + 1);
			printf("   ");
		}
	}
	TurnC(FALSE);
}

//draw a figure
void DrawFig() {
	TurnC(FALSE);
	for (int i = 0; i < 4; i++)
	{
		Move((x + fig[pos].figures[nr][i] / 4) * 2, (y + fig[pos].figures[nr][i] % 4) * 3 + 1);
		printf("%c%c%c", 201, 205, 187);
		Move((x + fig[pos].figures[nr][i] / 4) * 2 + 1, (y + fig[pos].figures[nr][i] % 4) * 3 + 1);
		printf("%c%c%c", 200, 205, 188);
		box[x + fig[pos].figures[nr][i] / 4][y + fig[pos].figures[nr][i] % 4] = 2;
	}
}

//draw score
void DrawScore() {
	TColor("green");
	Move(1, 63);
	printf("      %c%c%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	Move(2, 63);
	printf("Score %c000,000,000%c", 186, 186);
	Move(3, 63);
	printf("      %c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);

	TColor("bblue");
	if (score > 999 && score < 999999) {
		long int t = score;
		int i = 0;
		for (; i < 3; i++)
		{
			Move(2, 80 - i);
			printf("%d", t % 10);
			t = t / 10;
		}
		i++;
		for (; i < 7; i++)
		{
			Move(2, 80 - i);
			printf("%d", t % 10);
			t = t / 10;
		}
	}
	else if (score > 999999) {
		long int t = score;
		int i = 0;
		for (; i < 3; i++)
		{
			Move(2, 80 - i);
			printf("%d", t % 10);
			t = t / 10;
		}
		i++;
		for (; i < 7; i++)
		{
			Move(2, 80 - i);
			printf("%d", t % 10);
			t = t / 10;
		}
		i++;
		for (; i < 11; i++)
		{
			Move(2, 80 - i);
			printf("%d", t % 10);
			t = t / 10;
		}
	}
	else {
		long int t = score;
		for (int i = 0; i < 3; i++)
		{
			Move(2, 80 - i);
			printf("%d", t % 10);
			t = t / 10;
		}
	}
	TColor("green");
}

//check line
void CheckLine() {
	for (int i = 0; i < 23; i++)
	{
		int k = 0;
		for (int j = 0; j < 20; j++)
		{
			if (box[i][j] == 1)
				k++;
		}
		if (k == 20) {

			for (int i1 = i; i1 > 0; i1--)
				for (int j1 = 0; j1 < 20; j1++)
					box[i1][j1] = box[i1 - 1][j1];
			for (int i1 = 0; i1 < 20; i1++)
			{
				box[0][i1] = 0;
			}
			for (int i = 0; i < 23; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					Move(i * 2, j * 3 + 1);
					printf("   ");
					Move(i * 2 + 1, j * 3 + 1);
					printf("   ");
				}
			}

			for (int i = 0; i < 23; i++)
				for (int j = 0; j < 20; j++)
					if (box[i][j] == 1) {
						Move(i * 2, j * 3 + 1);
						printf("%c%c%c", 201, 205, 187);
						Move(i * 2 + 1, j * 3 + 1);
						printf("%c%c%c", 200, 205, 188);

					}

			score += 200;
			DrawScore();
		}

	}

}

//gameover check
int CheckGO() {
	for (int i = 0; i < 18; i++)
	{
		if (box[0][i] == 1)
			return 1;
	}
}

//delete figure
void DeleteFig() {
	for (int i = 0; i < 4; i++)
	{
		Move((x + fig[pos].figures[nr][i] / 4) * 2, (y + fig[pos].figures[nr][i] % 4) * 3 + 1);
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				printf(" ");
			}
			Move((x + fig[pos].figures[nr][i] / 4) * 2 + 1, (y + fig[pos].figures[nr][i] % 4) * 3 + 1);
		}

		box[x + fig[pos].figures[nr][i] / 4][y + fig[pos].figures[nr][i] % 4] = 0;
	}
}

//menu
void Options() {
	while (1) {

		if (option == 0) {
			TColor("blue");
			Move(7, 63);
			printf("Start");
			int c = getch();
			if (c == 13) {
				Game();
				GameOver();


			}
			if (c == 80) {
				TColor("green");
				Move(7, 63);
				printf("Start");
				option = 1;
			}
			if (c == 72) {
				TColor("green");
				Move(7, 63);
				printf("Start");
				option = 2;
			}
		}
		else if (option == 1) {
			TColor("blue");
			Move(8, 63);
			if (Instr == 0)
				printf("Turn on instructions ");
			else
				printf("Turn off instructions");
			int c = getch();
			if (c == 13) {
				if (Instr == 0) {
					Instr = 1;
					TColor("green");
					Move(11, 63);
					printf("Left and Right arrow keys move figure");
					Move(12, 63);
					printf("Up arrow key rotate figure");
					Move(13, 63);
					printf("Down arrow key increase figure speed");
					Move(14, 63);
					printf("P key pause the game");
				}
				else {
					Instr = 0;
					Move(11, 63);
					printf("                                     ");
					Move(12, 63);
					printf("                          ");
					Move(13, 63);
					printf("                                    ");
					Move(14, 63);
					printf("                    ");
				}

			}
			if (c == 80) {
				TColor("green");
				Move(8, 63);
				if (Instr == 0)
					printf("Turn on instructions ");
				else
					printf("Turn off instructions");
				option = 2;
			}
			if (c == 72) {
				TColor("green");
				Move(8, 63);
				if (Instr == 0)
					printf("Turn on instructions ");
				else
					printf("Turn off instructions");
				option = 0;
			}

		}
		else if (option == 2) {
			TColor("blue");
			Move(9, 63);
			printf("Exit");
			int c = getch();
			if (c == 13)
				exit(1);

			if (c == 80) {
				TColor("green");
				Move(9, 63);
				printf("Exit");
				option = 0;
			}
			if (c == 72) {
				TColor("green");
				Move(9, 63);
				printf("Exit");
				option = 1;
			}
		}
	}
}

//prepare list
void PrepList() {
	char line[25];
	FILE *input;
	input = fopen("score.txt", "r");
	
	start = (per*)malloc(sizeof(per));
	per *p = start;
	int k = 0;
	while (fgets(line, 25, input)) {
		k++;
		if (start == NULL) {
			start = (per*)malloc(sizeof(per));
			p = start;
			sscanf(line, "%s %d", start->name, &start->score);
		}
		else {
			p->next = (per*)malloc(sizeof(per));
			p = p->next;
			sscanf(line, "%s %d", p->name, &p->score);
		}
	}
	if (start->next != NULL)
		start = start->next;
	p->next = NULL;
	fclose(input);
	if (k == 0) {
		start = NULL;
	}
}


//save list
void SaveList() {
	FILE *input;
	input = fopen("score.txt", "w");
	per *p = start;
	while (p != NULL) {
		fprintf(input, "%s %d\n", p->name, p->score);
		p = p->next;
	}
	fclose(input);
}

//add score
void AddScore() {
	int added = 0;
	PrepList();
	per *p = start;
	if (start == NULL) {
		start = (per*)malloc(sizeof(per));
		strcpy(start->name, name);
		start->score = score;
		start->next = NULL;
		added = 1;
	}
	else
		while (p->next != NULL) {
			if (start->score < score) {
				per *n;
				n = (per*)malloc(sizeof(per));
				strcpy(n->name, name);
				n->score = score;
				n->next = start;
				start = n;
				added++;
				break;
			}
			else if (p->next->score < score)
			{
				per *n;
				n = (per*)malloc(sizeof(per));
				strcpy(n->name,name);
				n->score = score;
				n->next = p->next;
				p->next = n;
				added++;
				break;
			}

			p = p->next;
		}
	if (added == 0) {
		p = start;
		while (p->next != NULL)
			p = p->next;
		p->next = (per*)malloc(sizeof(per));
		p = p->next;
		strcpy(p->name, name);
		p->score = score;
		p->next = NULL;

	}


	SaveList();
}

//show score
void ShowTopScore() {
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			Move(i * 2, j * 3 + 1);
			printf("   ");
			Move(i * 2 + 1, j * 3 + 1);
			printf("   ");
		}
	}
	per *p = start;
	for (int i = 0; i < 10; i++)
	{
		Move(7 + i, 9);
		printf("Name: %s", p->name);
		Move(7 + i, 32);
		printf("Score: %d", p->score);
		p = p->next;
		if (p == NULL)
			break;
	}
	Move(18, 9);
	printf("Press ESC to continue...");
	int key = getch;
	while (key != 27) {
		int k = getch();
		if (k == 27 || k == 13)
			break;
	}

}