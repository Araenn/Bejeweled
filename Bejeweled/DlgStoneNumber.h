#pragma once


// boîte de dialogue de DlgStoneNumber

class CDlgStoneNumber : public CDialog
{
	DECLARE_DYNAMIC(CDlgStoneNumber)

public:
	CDlgStoneNumber(CWnd* pParent = nullptr);   // constructeur standard
	virtual ~CDlgStoneNumber();

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STONENUMBER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	int m_sliderStoneNumber;
};
