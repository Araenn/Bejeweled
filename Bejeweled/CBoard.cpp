#include "pch.h"
#include "CBoard.h"

CBoard::CBoard(int size) {
	for (int i = 0; i < size; i++) {
		vector<int> line;
		for (int j = 0; j < size; j++) {
			line.push_back(5);
		}
		this->grid.push_back(line);
	}
	this->size_grid = size;
}


CString CBoard::getGrid(int i, int j) {
	CString temp;
	temp.Format(_T("%2i"), this->grid[i][j]);
	return temp;
}
