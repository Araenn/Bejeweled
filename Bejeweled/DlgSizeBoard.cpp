// DlgSizeBoard.cpp : fichier d'implémentation
//

#include "pch.h"
#include "Bejeweled.h"
#include "DlgSizeBoard.h"
#include "afxdialogex.h"


// boîte de dialogue de DlgSizeBoard

IMPLEMENT_DYNAMIC(CDlgSizeBoard, CDialog)

CDlgSizeBoard::CDlgSizeBoard(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_SIZEBOARD, pParent)
	, m_sliderValue(8)
{
	
}

CDlgSizeBoard::~CDlgSizeBoard()
{
}

void CDlgSizeBoard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER_SIZEBOARD, m_sliderValue);
	DDV_MinMaxInt(pDX, m_sliderValue, 8, 50);
}


BEGIN_MESSAGE_MAP(CDlgSizeBoard, CDialog)
END_MESSAGE_MAP()

// gestionnaires de messages de DlgSizeBoard
