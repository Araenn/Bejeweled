#include "pch.h"
#include "CBoard.h"

CBoard::CBoard(int size) {
	for (int i = 0; i < size; i++) {
		vector<int> line;
		for (int j = 0; j < size; j++) {
			line.push_back(1);
		}
		this->grid.push_back(line);
	}
	this->size_grid = size;
}