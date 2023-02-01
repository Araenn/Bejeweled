// DlgStoneNumber.cpp : fichier d'implémentation
//

#include "pch.h"
#include "Bejeweled.h"
#include "DlgStoneNumber.h"
#include "afxdialogex.h"


// boîte de dialogue de DlgStoneNumber

IMPLEMENT_DYNAMIC(DlgStoneNumber, CDialog)

DlgStoneNumber::DlgStoneNumber(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_STONENUMBER, pParent)
	, m_sliderStoneNumber(6)
{

}

DlgStoneNumber::~DlgStoneNumber()
{
}

void DlgStoneNumber::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER_STONENUMBER, m_sliderStoneNumber);
	DDV_MinMaxInt(pDX, m_sliderStoneNumber, 6, 15);
}



BEGIN_MESSAGE_MAP(DlgStoneNumber, CDialog)
END_MESSAGE_MAP()


// gestionnaires de messages de DlgStoneNumber
