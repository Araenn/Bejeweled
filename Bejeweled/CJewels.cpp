#include "pch.h"
#include "CJewels.h"

const CJewels CJewels::AMETHYST = CJewels(_T("Amethyst"), PURPLE);
const CJewels CJewels::DIAMOND = CJewels(_T("Diamond"), WHITE);
const CJewels CJewels::SAPPHIRE = CJewels(_T("Sapphire"), BLUE);
const CJewels CJewels::RUBY = CJewels(_T("Ruby"), RED);
const CJewels CJewels::TOPAZE = CJewels(_T("Topaze"), YELLOW);
const CJewels CJewels::EMERALD = CJewels(_T("Emerald"), GREEN);
const CJewels CJewels::OPALE = CJewels(_T("Opale"), PINK);
const CJewels CJewels::AQUA = CJewels(_T("Aqua"), CYAN);
const CJewels CJewels::CRYSTAL = CJewels(_T("Aqua"), BLUE_GREY);
const CJewels CJewels::KUNZITE = CJewels(_T("Aqua"), OIGNON);
const CJewels CJewels::PHOENIX = CJewels(_T("Aqua"), ORANGE);
const CJewels CJewels::SANDSTONE = CJewels(_T("Aqua"), PAILLE);
const CJewels CJewels::SANGUINE = CJewels(_T("Aqua"), CORAIL);
const CJewels CJewels::SUNSTONE = CJewels(_T("Aqua"), RED_FIRE);
const CJewels CJewels::TOURMALINE = CJewels(_T("Aqua"), DARK_BLUE);
const CJewels CJewels::TURQUOISE = CJewels(_T("Aqua"), GREEN_CYAN);
const CJewels CJewels::DEFAULT = CJewels(_T("Default"), BLACK);


CJewels::CJewels(CString name, COLORREF m_color) {
	this->m_name = name;
	this->m_color = m_color;
}

CJewels::~CJewels() {

}

CString CJewels::getNameJewels() {
	return this->m_name;
}

COLORREF CJewels::getColorJewels()  {
	return this->m_color;
}