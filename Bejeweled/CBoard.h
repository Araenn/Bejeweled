#ifndef CBOARD_H
#define CBOARD_H



#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "CJewels.h"
using namespace std;

class CBoard
{
private:
	vector<vector<CJewels>> grid;
	int m_size_grid;

public:
	CBoard(int size);
	CString getGrid(int i, int j);
	CString * debug_board();
	int getBoardSize();
};


#endif // !CBOARD_H