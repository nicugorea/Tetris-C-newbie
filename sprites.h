#pragma once

typedef struct figs {
	int figures[7][4];
}figs;


int block[2][3] = { 201, 205, 187,
					200, 205, 188 };

int box[25][20];
figs fig[4];

void FigPrep() {
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			box[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				fig[i].figures[j][k] = 0;
			}
		}
	}
	//pozitia 1
	int figures0[7][4] = {
		0,1,2,6,
		0,1,2,5,
		0,1,2,4,
		1,2,4,5,
		0,1,2,3,
		0,1,4,5,
		0,1,5,6
	};
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fig[0].figures[i][j] = figures0[i][j];
		}
	}
	//pozitia 2
	int figures1[7][4] = {
		1,5,8,9,
		1,4,5,9,
		0,1,5,9,
		0,4,5,9,
		1,5,9,13,
		0,1,4,5,
		2,5,6,9
	};
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fig[1].figures[i][j] = figures1[i][j];
		}
	}
	//pozitia 3
	int figures2[7][4] = {
		0,4,5,6,
		1,4,5,6,
		2,4,5,6,
		1,2,4,5,
		0,1,2,3,
		0,1,4,5,
		0,1,5,6
	};
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fig[2].figures[i][j] = figures2[i][j];
		}
	}
	//pozitia 4
	int figures3[7][4] = {
		1,2,5,9,
		1,5,6,9,
		1,5,9,10,
		0,4,5,9,
		1,5,9,13,
		0,1,4,5,
		2,5,6,9
	};
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fig[3].figures[i][j] = figures3[i][j];
		}
	}

}

