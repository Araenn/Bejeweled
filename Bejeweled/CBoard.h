#ifndef CBOARD_H
#define CBOARD_H



#pragma once
#include <vector>
using namespace std;

class CBoard
{
private:
	vector<vector<int>> grid;
	int size_grid;

public:
	CBoard();
	~CBoard();
	CBoard(int size);
};


#endif // !CBOARD_H