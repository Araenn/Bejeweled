#include "pch.h"
#include "CBoard.h"

CBoard::CBoard() {
	int size = 8;
	int stone = 6;
	for (int i = 0; i < size; i++) {
		std::vector<CJewels> line;
		for (int j = 0; j < size; j++) {
			line.push_back(this->shuffleJewels(stone));
		}
		this->m_grid.push_back(line);
	}
	this->m_size_grid = size;
}

CBoard::CBoard(int size, int stone) {
	for (int i = 0; i < size; i++) {
		std::vector<CJewels> line;
		for (int j = 0; j < size; j++) {
			line.push_back(this->shuffleJewels(stone));
		}
		this->m_grid.push_back(line);
	}
	this->m_size_grid = size;
}

vector<CJewels> CBoard::operator[](int index) {
	return this->m_grid[index];
}

int CBoard::getBoardSize() {
	return this->m_size_grid;
}

CString* CBoard::debug_board() {
	int m_tailleTab = getBoardSize();
	CString temp;

	CString *p_valueTab = new CString[m_tailleTab];
	CString square_bracket[] = { (CString)'[', (CString)']' };

	for (int i = 0; i < m_tailleTab; i++) {
		temp.Format(_T("%2i"), i);
		for (int j = 0; j < m_tailleTab; j++) {
			p_valueTab[i] = p_valueTab[i] + square_bracket[0] + this->m_grid[i][j].getNameJewels() + square_bracket[1]; //ameliorer le debug avec [
		}
	}

	return p_valueTab;
}

/*
return a random jewel from the list
*/
CJewels CBoard::shuffleJewels(int stone) {
	return m_listJewels[(rand() % min(m_listJewels.size(), stone))]; //rand between 0 and rand_max, modulo the size of list
}

void CBoard::intervertJewels(int i, int j, int x, int y) {
	
	
	CJewels temp = this->m_grid[i][j];
	this->m_grid[i][j] = this->m_grid[x][y];
	this->m_grid[x][y] = temp;
}

BOOL CBoard::isAdjacent(int x1, int y1, int x2, int y2) {
	return ManhattanDistance(x1, y1, x2, y2) == 1;
}

BOOL CBoard::isSameJewels(CJewels j1, CJewels j2) {
	return j1.getColorJewels() == j2.getColorJewels();
}


BOOL CBoard::formLine(int x, int y) {
	int countLength = 1;
	int xprime = x + 1;

	while (xprime < m_size_grid  && isSameJewels(this->m_grid[xprime][y], this->m_grid[x][y])) {
		xprime++;
		countLength++;
	}

	xprime = x - 1;
	while (xprime >= 0 && isSameJewels(this->m_grid[xprime][y], this->m_grid[x][y])) {
		xprime--;
		countLength++;
	}

	if (countLength >= 3) return TRUE;

	int yprime = y + 1;
	countLength = 1;
	while (yprime < m_size_grid && isSameJewels(this->m_grid[x][yprime], this->m_grid[x][y])) {
		yprime++;
		countLength++;
	}

	yprime = y - 1;
	while (yprime >= 0 && isSameJewels(this->m_grid[x][yprime], this->m_grid[x][y])) {
		yprime--;
		countLength++;
	}

	if (countLength >= 3) return TRUE;

	return FALSE;
}

BOOL CBoard::isMoveLegal(int x1, int y1, int x2, int y2) {
	return isAdjacent(x1, y1, x2, y2) && ( formLine(x2, y2) || formLine(x1, y1) );
}