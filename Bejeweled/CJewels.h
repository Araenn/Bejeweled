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
constexpr COLORREF CYAN RGB(37, 253, 233);
constexpr COLORREF BLUE_GREY RGB(128, 208, 208);
constexpr COLORREF OIGNON RGB(213, 132, 144);
constexpr COLORREF ORANGE RGB(255, 127, 0);
constexpr COLORREF PAILLE RGB(254, 227, 71);
constexpr COLORREF CORAIL RGB(231, 62, 1);
constexpr COLORREF RED_FIRE RGB(150, 73, 1);
constexpr COLORREF DARK_BLUE RGB(15, 5, 107);
constexpr COLORREF GREEN_CYAN RGB(9, 189, 140);

class CJewels
{
private:
	CString m_name;
	COLORREF m_color;

public:
	CJewels(CString m_name, COLORREF m_color);
	~CJewels();
	COLORREF getColorJewels() ;
	CString getNameJewels();

	static const CJewels SAPPHIRE;
	static const CJewels RUBY;
	static const CJewels EMERALD;
	static const CJewels TOPAZE;
	static const CJewels AMETHYST;
	static const CJewels OPALE;
	static const CJewels DIAMOND;
	static const CJewels AQUA;
	static const CJewels CRYSTAL;
	static const CJewels TOURMALINE;
	static const CJewels KUNZITE;
	static const CJewels PHOENIX;
	static const CJewels SANDSTONE;
	static const CJewels SANGUINE;
	static const CJewels SUNSTONE;
	static const CJewels TURQUOISE;
};


#endif // !JEWELS_H