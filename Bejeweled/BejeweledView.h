
// BejeweledView.h : interface de la classe CBejeweledView
//
#include "BejeweledDoc.h"
#pragma once


class CBejeweledView : public CView
{
protected: // création à partir de la sérialisation uniquement
	CBejeweledView() noexcept;
	DECLARE_DYNCREATE(CBejeweledView)

// Attributs
public:
	CBejeweledDoc* GetDocument() const;

// Opérations
public:

// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitué pour dessiner cette vue
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implémentation
public:
	virtual ~CBejeweledView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void fallingAllJewels(CBejeweledDoc* pDoc);

	int m_widthBoardDraw; // largeur en pixel du plateau de jeu
	int m_heightBoardDraw; // hauteur en pixel du plateau de jeu
	int m_caseWidth; // largeur en pixel d'une case du plateau de jeu
	int m_caseHeight; // hauteur en pixel d'une case du plateau de jeu
	int m_circleRadius;
	CRect m_windowsRect;
	CRect m_boardDraw;
	int m_firstClickX;
	int m_firstClickY;
};

#ifndef _DEBUG  // version Debug dans BejeweledView.cpp
inline CBejeweledDoc* CBejeweledView::GetDocument() const
   { return reinterpret_cast<CBejeweledDoc*>(m_pDocument); }
#endif

