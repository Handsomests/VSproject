#pragma once
#include<cstdlib>
#include<iostream>
#include<conio.h>
using namespace std;
class Maze
{
	char **maze;
	int row, col;
	int inx, iny, outx, outy;
	void AllPath(int x, int y);
public:
	explicit Maze(char* m[], int row, int col, int inx, int iny, int outx, int outy);
	~Maze(void);
	void AllPath(void) { AllPath(inx, iny); }
	void PrintMaze(void);
};
Maze::Maze(char* m[], int row, int col, int inx, int iny, int outx, int outy)
{
	this->row = row;
	this->col = col;
	this->inx = inx;
	this->iny = iny;
	this->outx = outx;
	this->outy = outy;
	maze = new char*[row];
	for (int i = 0; i < row; i++)
		maze[i] = new char[col];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			maze[i][j] = m[i][j];
}
Maze::~Maze(void)
{
	for (int i = 0; i < row; i++)
		delete[]maze[i];
	delete[]maze;
}
void Maze::PrintMaze(void)
{
	static int count = 0;
	count++;
	cout << count << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << maze[i][j] << ' ';
		cout << endl;
	}
}
void Maze::AllPath(int x, int y)
{
	static int d[4][2] = { { 1,0 },{ 0,1 },{ -1,0 },{ 0,-1 } };
	maze[y][x] = '*';
	if (y == outy&&x == outx)
	{
		PrintMaze();
		cout << "press any key to show" << endl;
		_getch();
		return;
	}
	for (int i = 0; i<4; i++)
		if (maze[y + d[i][1]][x + d[i][0]] == '0')
		{
			AllPath(x + d[i][0], y + d[i][1]);
			maze[y + d[i][1]][x + d[i][0]] = '0';
		}
}