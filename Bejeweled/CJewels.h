#pragma once
#include <iostream>
#include <vector>
using namespace std;

class CJewels
{
private:
	CString m_name;

public:
	CJewels(CString m_name);
	~CJewels();

	CString getNameJewels();

	static const CJewels SAPPHIRE;
	static const CJewels RUBY;
	static const CJewels EMERALD;
	static const CJewels TOPAZE;
	static const CJewels AMETHYST;
	static const CJewels OPALE;
	static const CJewels DIAMOND;
};

