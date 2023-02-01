#pragma once


// boîte de dialogue de DlgSizeBoard

class DlgSizeBoard : public CDialog
{
	DECLARE_DYNAMIC(DlgSizeBoard)

public:
	DlgSizeBoard(CWnd* pParent = nullptr);   // constructeur standard
	virtual ~DlgSizeBoard();

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SIZEBOARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_sliderValue;
};
