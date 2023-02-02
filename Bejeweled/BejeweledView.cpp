
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
	size(0),
	height(0),
	caseHeight(0),
	caseWidth(0),
	radius(0),
	sizeBoard(0),
	boardDraw(0),
	firstClickX(-1),
	firstClickY(-1),
	secondClickX(0),
	secondClickY(0)
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


	GetClientRect(rect);
	sizeBoard = pDoc->m_tailleTab;
	size = (rect.left + rect.right) / 3;
	height = size - (rect.Height() + rect.Width()) / 5;

	boardDraw = CRect(rect.left + size, rect.top + height, rect.right - size, rect.bottom - height);

	caseWidth = boardDraw.Width() / sizeBoard; // width of each case
	caseHeight = boardDraw.Height() / sizeBoard; // height of each case
	radius = (caseWidth < caseHeight) ? caseWidth / 2 : caseHeight / 2;
	radius *= 0.9; // decrease the radius by 20%



	CPen mulberryPen(PS_SOLID, 1, RGB(74, 16, 12));
	CPen* oldPen = pDC->SelectObject(&mulberryPen);
	CBrush mulberryBrush(RGB(32, 30, 32));
	CBrush* oldBrush = pDC->SelectObject(&mulberryBrush);
	pDC->Rectangle(rect);

	if (pDoc->flag == 1) {
		for (int i = 0; i < pDoc->getTaille(); i++) {

			// dessine le debug board
			pDC->TextOut(
				(rect.Width() / 10),
				(rect.Height() / 10 + 22 * (i + 1)),
				pDoc->getChaine()[i],
				pDoc->getChaine()[i].GetLength()
			);
		}
	}
	else if (pDoc->flag == 2) {


		CPen blackPen(PS_SOLID, 1, RGB(0, 0, 0));
		pDC->SelectObject(blackPen);
		pDC->Rectangle(boardDraw);


		CBrush blackBrush(RGB(224, 169, 109));
		pDC->SelectObject(&blackBrush);
		pDC->Rectangle(boardDraw);


		for (int i = 0; i < pDoc->m_tailleTab; i++) {
			for (int j = 0; j < pDoc->m_tailleTab; j++) {
				CBrush newBrush(pDoc->m_color[i * pDoc->m_tailleTab + j]);
				pDC->SelectObject(newBrush);

				int case_center_x = boardDraw.left + (i + 0.5) * caseWidth;
				int case_center_y = boardDraw.top + (j + 0.5) * caseHeight;
				pDC->Ellipse(case_center_x - radius, case_center_y - radius, case_center_x + radius, case_center_y + radius);
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

	if (firstClickX == -1) {
		firstClickX = point.x;
		firstClickY = point.y;
		return;
	}

	int firstJewelX = (firstClickX - rect.left - size) / caseWidth;
	int firstJewelY = (firstClickY - rect.top - height ) / caseHeight;

	int secondClickX = point.x;
	int secondClickY = point.y;


	int secondJewelX = (secondClickX - rect.left - size )/ caseWidth;
	int secondJewelY = (secondClickY - rect.top - height) / caseHeight;

	pDoc->invertJewels(firstJewelX, firstJewelY, secondJewelX, secondJewelY);

	firstClickX = -1;
	firstClickY = -1;

	RedrawWindow();

	
}
