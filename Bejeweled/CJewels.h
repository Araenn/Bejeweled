#ifndef CJEWELS_H
#define CJEWELS_H



#pragma once
#include <iostream>
#include <vector>
using namespace std;

constexpr COLORREF BLUE RGB(0, 0, 255);
constexpr COLORREF PURPLE RGB(128, 0, 128);
constexpr COLORREF WHITE RGB(255, 255, 255);
constexpr COLORREF RED RGB(255, 0, 0);
constexpr COLORREF YELLOW RGB(255, 255, 0);
constexpr COLORREF GREEN RGB(0, 255, 0);
constexpr COLORREF PINK  RGB(255, 192, 203);
constexpr COLORREF DEEP_PURPLE RGB(20, 0, 20);

class CJewels
{
private:
	CString m_name;
	COLORREF m_color;

public:
	CJewels(CString m_name, COLORREF m_color);
	~CJewels();
	COLORREF getColorJewels();
	CString getNameJewels();

	static const CJewels SAPPHIRE;
	static const CJewels RUBY;
	static const CJewels EMERALD;
	static const CJewels TOPAZE;
	static const CJewels AMETHYST;
	static const CJewels OPALE;
	static const CJewels DIAMOND;
	static const CJewels OBSIDIAN;
};


#endif // !JEWELS_H