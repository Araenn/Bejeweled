#include "pch.h"
#include "CJewels.h"

const CJewels CJewels::AMETHYST = CJewels(_T("Amethyst"), PURPLE);
const CJewels CJewels::DIAMOND = CJewels(_T("Diamond"), WHITE);
const CJewels CJewels::SAPPHIRE = CJewels(_T("Sapphire"), BLUE);
const CJewels CJewels::RUBY = CJewels(_T("Ruby"), RED);
const CJewels CJewels::TOPAZE = CJewels(_T("Topaze"), YELLOW);
const CJewels CJewels::EMERALD = CJewels(_T("Emerald"), GREEN);
const CJewels CJewels::OPALE = CJewels(_T("Opale"), PINK);

CJewels::CJewels(CString name, COLORREF m_color) {
	this->m_name = name;
	this->m_color = m_color;
}

CJewels::~CJewels() {

}

CString CJewels::getNameJewels() {
	return this->m_name;
}

COLORREF CJewels::getColorJewels() {
	return this->m_color;
}