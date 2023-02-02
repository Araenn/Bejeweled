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
	vector<CJewels> listJewels = {
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
	CBoard(int size, int stone);
	CString * debug_board();
	int getBoardSize();
	CJewels shuffleJewels(int stone);
	void intervertJewels(int i, int j, CJewels p);
	vector<CJewels> operator[](int index);
};


#endif // !CBOARD_H