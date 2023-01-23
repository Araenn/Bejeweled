#include "pch.h"
#include "CBoard.h"

CBoard::CBoard(int size) {
	for (int i = 0; i < size; i++) {
		vector<CJewels> line;
		for (int j = 0; j < size; j++) {
			line.push_back(CJewels::SAPPHIRE);
		}
		this->grid.push_back(line);
	}
	this->m_size_grid = size;
}


CString CBoard::getGrid(int i, int j) {
	return this->grid[i][j].getNameJewels();
}

int CBoard::getBoardSize() {
	return this->m_size_grid;
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