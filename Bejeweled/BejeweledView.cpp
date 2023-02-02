
// BejeweledView.cpp : implémentation de la classe CBejeweledView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS peuvent être définis dans les gestionnaires d'aperçu, de miniature
// et de recherche d'implémentation de projet ATL, et permettent le partage de code de document avec ce projet.
#ifndef SHARED_HANDLERS
#include "Bejeweled.h"
#endif

#include "BejeweledDoc.h"
#include "BejeweledView.h"
#include "CBoard.h"
#include "CJewels.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CBejeweledView

IMPLEMENT_DYNCREATE(CBejeweledView, CView)

BEGIN_MESSAGE_MAP(CBejeweledView, CView)
	// Commandes d'impression standard
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBejeweledView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// construction/destruction de CBejeweledView

CBejeweledView::CBejeweledView() noexcept :
	m_widthBoardDrawDraw(0),
	m_heightBoardDraw(0),
	m_caseHeight(0),
	m_caseWidth(0),
	m_circleRadius(0),
	m_widthBoardDraw(0),
	m_firstClickX(-1),
	m_firstClickY(-1)
{
	// TODO: ajoutez ici du code de construction

}

CBejeweledView::~CBejeweledView()
{

}

BOOL CBejeweledView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// dessin de CBejeweledView

void CBejeweledView::OnDraw(CDC* pDC)
{
	CBejeweledDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	GetClientRect(m_windowsRect);
	m_widthBoardDraw = pDoc->m_tailleTab;
	m_widthBoardDrawDraw = (m_windowsRect.left + m_windowsRect.right) / 3;
	m_heightBoardDraw = m_widthBoardDrawDraw - (m_windowsRect.Height() + m_windowsRect.Width()) / 5;

	m_boardDraw = CRect(m_windowsRect.left + m_widthBoardDrawDraw, m_windowsRect.top + m_heightBoardDraw, m_windowsRect.right - m_widthBoardDrawDraw, m_windowsRect.bottom - m_heightBoardDraw);

	m_caseWidth = m_boardDraw.Width() / m_widthBoardDraw; // width of each case
	m_caseHeight = m_boardDraw.Height() / m_widthBoardDraw; // m_heightBoardDraw of each case
	m_circleRadius = (m_caseWidth < m_caseHeight) ? m_caseWidth / 2 : m_caseHeight / 2;
	m_circleRadius *= 0.9; // decrease the m_circleRadius by 20%



	CPen mulberryPen(PS_SOLID, 1, RGB(74, 16, 12));
	CPen* oldPen = pDC->SelectObject(&mulberryPen);
	CBrush mulberryBrush(RGB(32, 30, 32));
	CBrush* oldBrush = pDC->SelectObject(&mulberryBrush);
	pDC->Rectangle(m_windowsRect);

	if (pDoc->flag == 1) {
		for (int i = 0; i < pDoc->getTaille(); i++) {

			// dessine le debug board
			pDC->TextOut(
				(m_windowsRect.Width() / 10),
				(m_windowsRect.Height() / 10 + 22 * (i + 1)),
				pDoc->getChaine()[i],
				pDoc->getChaine()[i].GetLength()
			);
		}
	}
	else if (pDoc->flag == 2) {


		CPen blackPen(PS_SOLID, 1, RGB(0, 0, 0));
		pDC->SelectObject(blackPen);
		pDC->Rectangle(m_boardDraw);


		CBrush blackBrush(RGB(224, 169, 109));
		pDC->SelectObject(&blackBrush);
		pDC->Rectangle(m_boardDraw);


		for (int i = 0; i < pDoc->m_tailleTab; i++) {
			for (int j = 0; j < pDoc->m_tailleTab; j++) {
				CBrush newBrush(pDoc->m_color[i * pDoc->m_tailleTab + j]);
				pDC->SelectObject(newBrush);

				int case_center_x = m_boardDraw.left + (i + 0.5) * m_caseWidth;
				int case_center_y = m_boardDraw.top + (j + 0.5) * m_caseHeight;
				pDC->Ellipse(case_center_x - m_circleRadius, case_center_y - m_circleRadius, case_center_x + m_circleRadius, case_center_y + m_circleRadius);
			}
		}
		

		pDC->SelectObject(&oldBrush);
		pDC->SelectObject(&oldPen);
	}


	// TODO: ajoutez ici le code de dessin pour les données natives
}


// impression de CBejeweledView


void CBejeweledView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBejeweledView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// préparation par défaut
	return DoPreparePrinting(pInfo);
}

void CBejeweledView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ajoutez une initialisation supplémentaire avant l'impression
}

void CBejeweledView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ajoutez un nettoyage après l'impression
}

void CBejeweledView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBejeweledView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// diagnostics de CBejeweledView

#ifdef _DEBUG
void CBejeweledView::AssertValid() const
{
	CView::AssertValid();
}

void CBejeweledView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBejeweledDoc* CBejeweledView::GetDocument() const // la version non Debug est inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBejeweledDoc)));
	return (CBejeweledDoc*)m_pDocument;
}
#endif //_DEBUG

// gestionnaires de messages de CBejeweledView




void CBejeweledView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ajoutez ici le code de votre gestionnaire de messages et/ou les paramètres par défaut des appels
	CBejeweledDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CView::OnLButtonDown(nFlags, point);

	if (m_firstClickX == -1) {
		int firstJewelX = (point.x - m_windowsRect.left - m_widthBoardDrawDraw) / m_caseWidth;
		int firstJewelY = (point.y - m_windowsRect.top - m_heightBoardDraw) / m_caseHeight;
		if (firstJewelX >= 0 && firstJewelX < m_widthBoardDraw &&
			firstJewelY >= 0 && firstJewelY < m_widthBoardDraw) {
			m_firstClickX = point.x;
			m_firstClickY = point.y;
		}
		
		return;
	}

	int firstJewelX = (m_firstClickX - m_windowsRect.left - m_widthBoardDrawDraw) / m_caseWidth;
	int firstJewelY = (m_firstClickY - m_windowsRect.top - m_heightBoardDraw ) / m_caseHeight;

	int secondClickX = point.x;
	int secondClickY = point.y;


	int secondJewelX = (secondClickX - m_windowsRect.left - m_widthBoardDrawDraw )/ m_caseWidth;
	int secondJewelY = (secondClickY - m_windowsRect.top - m_heightBoardDraw) / m_caseHeight;

	if (secondJewelX >= 0 && secondJewelX < m_widthBoardDraw &&
		secondJewelY >= 0 && secondJewelY < m_widthBoardDraw) {

		pDoc->invertJewels(firstJewelX, firstJewelY, secondJewelX, secondJewelY);

		if ((!pDoc->m_pBoard->isMoveLegal(firstJewelX, firstJewelY, secondJewelX, secondJewelY))) {
			pDoc->invertJewels(firstJewelX, firstJewelY, secondJewelX, secondJewelY);
			m_firstClickX = -1;
			m_firstClickY = -1;
			return;
		}


		m_firstClickX = -1;
		m_firstClickY = -1;

		RedrawWindow();
	}
	
	m_firstClickX = -1;
	m_firstClickY = -1;
	
}
