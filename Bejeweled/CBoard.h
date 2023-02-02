#ifndef CBOARD_H
#define CBOARD_H



#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "CJewels.h"
#include <stdlib.h>
#include "CMathUtils.h"

using namespace std;

class CBoard
{
private:
	std::vector<std::vector<CJewels>> m_grid;
	int m_size_grid;	
	int m_stoneNumber;
	vector<CJewels> m_listJewels = {
		CJewels::AMETHYST,
		CJewels::DIAMOND,
		CJewels::EMERALD,
		CJewels::OPALE,
		CJewels::RUBY,
		CJewels::SAPPHIRE,
		CJewels::TOPAZE,
		CJewels::AQUA,
		CJewels::CRYSTAL,
		CJewels::KUNZITE,
		CJewels::PHOENIX,
		CJewels::SANDSTONE,
		CJewels::SANGUINE,
		CJewels::SUNSTONE,
		CJewels::TOURMALINE,
		CJewels::TURQUOISE
	};

public:
	CBoard();
	CBoard(int size, int stone);
	CString * debug_board();
	int getBoardSize();
	CJewels shuffleJewels(int stone);
	void intervertJewels(int i, int j, int x, int y);
	vector<CJewels> operator[](int index);
	BOOL isAdjacent(int x1, int y1, int x2, int y2);
};


#endif // !CBOARD_H