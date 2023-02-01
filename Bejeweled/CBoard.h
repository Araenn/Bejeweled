#ifndef CBOARD_H
#define CBOARD_H



#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "CJewels.h"
#include <stdlib.h>

using namespace std;

class CBoard
{
private:
	std::vector<std::vector<CJewels>> grid;
	int m_size_grid;
	
	int m_stoneNumber;

public:
	CBoard(int size);
	CString * debug_board();
	int getBoardSize();
	CJewels shuffleJewels();
	void intervertJewels(int i, int j, CJewels p);
	vector<CJewels> operator[](int index);
};


#endif // !CBOARD_H