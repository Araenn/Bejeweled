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

int CBoard::getBoardSize() {
	return this->size_grid;
}

CString* CBoard::debug_board() {
	int m_tailleTab = getBoardSize();
	CString temp;

	CString *p_valueTab;
	p_valueTab = new CString[m_tailleTab];
	for (int i = 0; i < m_tailleTab; i++) {
		p_valueTab[i] = "[";
		temp.Format(_T("%2i"), i);
		for (int j = 0; j < m_tailleTab; j++) {
			p_valueTab[i] = p_valueTab[i] + this->getGrid(i, j) + (CString)"]"; //ameliorer le debug avec [
		}
	}

	return p_valueTab;
}