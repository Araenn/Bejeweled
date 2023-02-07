#include "pch.h"
#include "CBoard.h"

/**
	Constructeur: Creer un plateau carré de jeu de dimensions 8x8
		avec 6 pierres différentes. Assure qu'aucun combo de base
		n'existe
*/
CBoard::CBoard() {
	int size = 8;
	this->m_stoneNumber = 6;
	for (int i = 0; i < size; i++) {
		std::vector<CJewels> line;
		for (int j = 0; j < size; j++) {
			line.push_back(this->shuffleJewels());
		}
		this->m_grid.push_back(line);
	}
	this->m_size_grid = size;

	deleteAllCombo();
}

/**
	Constructeur: Creer un plateau carré de jeu de dimensions `size`x`size`
		avec `stone` pierres différentes. Assure qu'aucun combo de base
		n'existe

	Paramètres:
		- int size: largeur et hauteur du plateau 
		- int stone: nombre de pierre différentes que possedera le plateau
*/
CBoard::CBoard(int size = 8, int stone = 6) {
	this->m_stoneNumber = stone;

	for (int i = 0; i < size; i++) {
		std::vector<CJewels> line;
		for (int j = 0; j < size; j++) {
			line.push_back(this->shuffleJewels());
		}
		this->m_grid.push_back(line);
	}
	this->m_size_grid = size;

	deleteAllCombo();
}

vector<CJewels> CBoard::operator[](int index) {
	return this->m_grid[index];
}

/**
	Supprime tous les combo existant du plateau
*/
void CBoard::deleteAllCombo() {
	vector<vector<int>> comboJewels = getAllComboJewels();
	while (comboJewels.size() != 0) {
		disappearingJewels(comboJewels);
		applyGravity();
		makeFallingJewels();
		comboJewels = getAllComboJewels();
	}
}

/**
	Renvoie la largeur/hauteur du plateau
*/
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
			p_valueTab[i] = p_valueTab[i] + square_bracket[0] + this->m_grid[i][j].getNameJewels() + square_bracket[1];
		}
	}

	return p_valueTab;
}

/*!
 *  Shuffles the jewels.
 *
 *      @return a random jewel
 */
CJewels CBoard::shuffleJewels() {
	return m_listJewels[(rand() % min(m_listJewels.size(), this->m_stoneNumber))]; //rand between 0 and rand_max, modulo the size of list
}

/*!
 *  Interverts the jewels (x1, y1) and the jewel (x2, y2).
 *
 *      @param [in] x1
 *      @param [in] y1 
 *      @param [in] x2 
 *      @param [in] y2 
 */
void CBoard::intervertJewels(int x1, int y1, int x2, int y2) {
	CJewels temp = this->m_grid[x1][y1];
	this->m_grid[x1][y1] = this->m_grid[x2][y2];
	this->m_grid[x2][y2] = temp;
}

/*!
 *  Returns true if jewel (x1, y1) and jewel (x2, y2) is adjacent.
 *
 *      @param [in] x1 
 *      @param [in] y1 
 *      @param [in] x2 
 *      @param [in] y2 
 *
 *      @return True if adjacent. False if not.
 */
BOOL CBoard::isAdjacent(int x1, int y1, int x2, int y2) {
	return ManhattanDistance(x1, y1, x2, y2) == 1;
}

/*!
 *  Returns true if the jewel j1 == jewel j2
 *
 *      @param [in] j1 
 *      @param [in] j2 
 *
 *      @return True if same jewels. False if not.
 */
BOOL CBoard::isSameJewels(CJewels j1, CJewels j2) {
	return j1.getColorJewels() == j2.getColorJewels();
}

/*!
 *  Returns true if the board at pos (x, y) contains 3 jewel combo
 *
 *      @param [in] x 
 *      @param [in] y 
 *
 *      @return True if there is a 3 jewel combo. False if not.
 */
BOOL CBoard::isCombo(int x, int y) {
	int countLength = 1;
	int xPrime = x - 1;

	while (xPrime >= 0 && countLength <= 3 && isSameJewels(this->m_grid[xPrime][y], this->m_grid[x][y])) {
		xPrime--;
		countLength++;
	}

	if (countLength >= 3) {
		return TRUE;
	}

	xPrime = x + 1;
	while (xPrime < m_size_grid && countLength <= 3 && isSameJewels(this->m_grid[xPrime][y], this->m_grid[x][y])) {
		xPrime++;
		countLength++;
	}

	if (countLength >= 3) {
		return TRUE;
	}

	countLength = 1;
	int yPrime = y + 1;


	while (yPrime < m_size_grid && countLength <= 3 && isSameJewels(this->m_grid[x][yPrime], this->m_grid[x][y])) {
		yPrime++;
		countLength++;
	}

	yPrime = y - 1;
	while (yPrime >= 0 && countLength <= 3 && isSameJewels(this->m_grid[x][yPrime], this->m_grid[x][y])) {
		yPrime--;
		countLength++;
	}

	if (countLength >= 3) {
		return TRUE;
	}

	return FALSE;

}

/*!
 *  Returns the board's combo jewels from one pos.
 *
 *      @param [in]     x       
 *      @param [in]     y       
 *      @param [in,out] flagMap 
 *
 *      @return The combo jewels.
 */
vector<vector<int>> CBoard::getComboJewels(int x, int y, vector<vector<int>> &flagMap) {
	vector<vector<int>> comboJewels;

	// Add abcisse jewels
	int countLengthX = 1;
	int xMin = x - 1;
	while (xMin >= 0 && isSameJewels(this->m_grid[xMin][y], this->m_grid[x][y])) {
		countLengthX++;
		xMin--;
	}

	int xMax = x + 1;
	while (xMax < m_size_grid && isSameJewels(this->m_grid[xMax][y], this->m_grid[x][y])) {
		countLengthX++;
		xMax++;
	}

	if (countLengthX >= 3) {
		for (int xprime = xMin + 1; xprime < xMax; xprime++) {
			if (!flagMap[xprime][y]) {
				comboJewels.push_back({ xprime, y });
				flagMap[xprime][y] = 1;
			}
		}
	}


	int countLengthY = 1;

	int yMin = y - 1;
	while (yMin >= 0 && isSameJewels(this->m_grid[x][yMin], this->m_grid[x][y])) {
		countLengthY++;
		yMin--;
	}

	int yMax = y + 1;
	while (yMax < m_size_grid && isSameJewels(this->m_grid[x][yMax], this->m_grid[x][y])) {
		countLengthY++;
		yMax++;
	}

	if (countLengthY >= 3) {
		for (int yprime = yMin + 1; yprime < yMax; yprime++) {
			if (!flagMap[x][yprime]) {
				comboJewels.push_back({ x, yprime });
				flagMap[x][yprime] = 1;
			}
		}
	}

	return comboJewels;
}

/*!
 *  Returns true if the user can move two jewels.
 *
 *      @param [in] x1 
 *      @param [in] y1 
 *      @param [in] x2 
 *      @param [in] y2 
 *
 *      @return True if move is legal. False if not.
 */
BOOL CBoard::isMoveLegal(int x1, int y1, int x2, int y2) {
	return isAdjacent(x1, y1, x2, y2) && ( isCombo(x2, y2) || isCombo(x1, y1) );
}

/*!
 *  Returns the board's all combo jewels. (for each position)
 *
 *      @return The all combo jewels.
 */
vector<vector<int>> CBoard::getAllComboJewels() {
	vector<vector<int>> flagMap;

	// Fill the flag map
	for (int i = 0; i < m_size_grid; i++) {
		vector<int> line(m_size_grid, 0);
		flagMap.push_back(line);
	}

	// get all combo jewels
	vector<vector<int>> jewelsToRemove;
	for (int line = 0; line < m_size_grid; line++) {
		for (int col = 0; col < m_size_grid; col++) {
			vector<vector<int>> comboJewels = getComboJewels(line, col, flagMap);
			jewelsToRemove.insert(jewelsToRemove.begin(), comboJewels.begin(), comboJewels.end());
		}
	}

	return jewelsToRemove;
}

/*!
 *  Returns the board's combo jewels on swap.
 *
 *      @param [in] x1 
 *      @param [in] y1 
 *      @param [in] x2 
 *      @param [in] y2 
 *
 *      @return The combo jewels on swap.
 */
vector<vector<int>> CBoard::getComboJewelsOnSwap(int x1, int y1, int x2, int y2) {
	vector<vector<int>> flagMap;

	// Fill the flag map
	for (int i = 0; i < m_size_grid; i++) {
		vector<int> line(m_size_grid, 0);
		flagMap.push_back(line);
	}

	vector<vector<int>> comboJewels = getComboJewels(x1, y1, flagMap);
	vector<vector<int>> comboJewels2 = getComboJewels(x2, y2, flagMap);
	comboJewels.insert(comboJewels.begin(), comboJewels2.begin(), comboJewels2.end());

	return comboJewels;
}

/*!
 *  Disappearings the jewels at positions stored in jewelsCoords
 *
 *      @param [in,out] jewelsCoords 
 */
void CBoard::disappearingJewels(vector<vector<int>> &jewelsCoords) {

	for (int i = 0; i < jewelsCoords.size(); i++) {
		vector<int> coords = jewelsCoords[i];
		this->m_grid[coords[0]][coords[1]] = CJewels::DEFAULT;
	}

}

/*!
 *  Applies the gravity on col. (or make bubble, as you want)
 *
 *      @param [in] col 
 */
void CBoard::applyGravityOnCol(int col) {
	for (int line = m_size_grid - 1; line >= 0; line--) {
		if (!isSameJewels(m_grid[line][col], CJewels::DEFAULT)) {
			// On a une pierre, on la fait descendre
			for (int k = line + 1; k < m_size_grid && isSameJewels(m_grid[k][col], CJewels::DEFAULT); k++) {
				CJewels tmp = m_grid[k - 1][col];
				m_grid[k - 1][col] = m_grid[k][col];
				m_grid[k][col] = tmp;
			}
		}
	}
}


void CBoard::applyGravity() {
	for (int col = 0; col < m_size_grid; col++) { // On itère dans les colonnes
		applyGravityOnCol(col);
	}
}

/*!
 *  Makes the falling jewels. (generate on top of each collumns)
 *
 *      @param [in] stone 
 */
void CBoard::makeFallingJewels() {
	for (int col = 0; col < m_size_grid; col++) {
		for (int line = 0; line < m_size_grid && isSameJewels(m_grid[line][col], CJewels::DEFAULT); line++) {
			m_grid[line][col] = shuffleJewels();
		}
	}
}