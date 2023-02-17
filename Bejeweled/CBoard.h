#ifndef CBOARD_H
#define CBOARD_H



#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "CJewels.h"
#include <stdlib.h>
#include "CMathUtils.h"
#include "Log.h"

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
	int getBoardSize();
	CJewels& get(int line, int col);

	CString* debugBoard();

	CJewels shuffleJewels();
	void intervertJewels(int i, int j, int x, int y);
	vector<CJewels>& operator[](int index);

	BOOL isJewelsDefault(CJewels j);
	BOOL isAdjacent(int x1, int y1, int x2, int y2);
	BOOL isCombo(int x, int y);
	BOOL isMoveLegal(int x1, int y1, int x2, int y2);
	BOOL isSameJewels(CJewels j1, CJewels j2);

	vector<vector<int>> getComboJewels(int x, int y, vector<vector<int>>& flagMap);
	vector<vector<int>> getComboJewelsOnSwap(int x1, int y1, int x2, int y2);
	vector<vector<int>> getAllComboJewels();

	void deleteAllCombo();
	void disappearingJewels(vector<vector<int>>& jewelsCoords);
	void applyGravityOnCol(int col);
	void applyGravity();
	std::vector<std::vector<CJewels>> makeFallingJewels();
	void CBoard::fallOneTime(std::vector<std::vector<CJewels>>& T);
	void addJewels(std::vector<std::vector<CJewels>>& T);

	std::vector<std::vector<CJewels>> T;
};


#endif // !CBOARD_H