#include "pch.h"
#include "CJewels.h"

const CJewels CJewels::AMETHYST = CJewels(_T("_T(Amethyst"));
const CJewels CJewels::DIAMOND = CJewels(_T("Diamond"));
const CJewels CJewels::SAPPHIRE = CJewels(_T("Sapphire"));
const CJewels CJewels::RUBY = CJewels(_T("Ruby"));
const CJewels CJewels::TOPAZE = CJewels(_T("Topaze"));
const CJewels CJewels::EMERALD = CJewels(_T("Emerald"));
const CJewels CJewels::OPALE = CJewels(_T("Opale"));

CJewels::CJewels(CString name) {
	this->m_name = name;
}

CJewels::~CJewels() {

}

CString CJewels::getNameJewels() {
	return this->m_name;
}
