
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
END_MESSAGE_MAP()

// construction/destruction de CBejeweledView

CBejeweledView::CBejeweledView() noexcept
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


	CRect rect;
	GetClientRect(rect);

	if (pDoc->flag == 1) {
		for (int i = 0; i < pDoc->getTaille(); i++)
		{
			pDC->TextOut((int)(rect.Width() / 10), (int)(rect.Height() / 10 +
				22 * (i + 1)), pDoc->getChaine()[i], pDoc->getChaine()[i].GetLength());
		}
	}
	else if (pDoc->flag == 2) {
		int size = (rect.left + rect.right) / 3;
		int height = size - (rect.Height() + rect.Width()) / 5;

		CRect boardDraw(rect.left + size, rect.top + height, rect.right - size, rect.bottom - height);
		int caseWidth = boardDraw.Width() / 8; // width of each case
		int caseHeight = boardDraw.Height() / 8; // height of each case
		int radius = (caseWidth < caseHeight) ? caseWidth / 2 : caseHeight / 2;
		radius *= 0.8; // decrease the radius by 20%

		CPen blackPen;
		blackPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* oldPen = pDC->SelectObject(&blackPen);
		pDC->Rectangle(boardDraw);


		CBrush blackBrush(RGB(0, 0, 0));
		CBrush* oldBrush = pDC->SelectObject(&blackBrush);
		pDC->Rectangle(boardDraw);		

		std::vector<std::unique_ptr<CPen>> listPen;
		listPen.push_back(std::make_unique<CPen>(PS_SOLID, 1, RGB(0, 0, 255)));
		listPen.push_back(std::make_unique<CPen>(PS_SOLID, 1, RGB(128, 0, 128)));
		listPen.push_back(std::make_unique<CPen>(PS_SOLID, 1, RGB(255, 255, 255)));
		listPen.push_back(std::make_unique<CPen>(PS_SOLID, 1, RGB(255, 0, 0)));
		listPen.push_back(std::make_unique<CPen>(PS_SOLID, 1, RGB(0, 255, 255)));
		listPen.push_back(std::make_unique<CPen>(PS_SOLID, 1, RGB(0, 255, 0)));
		listPen.push_back(std::make_unique<CPen>(PS_SOLID, 1, RGB(255, 192, 203)));

		CPen brownPen;
		brownPen.CreatePen(PS_SOLID, 1, RGB(88, 57, 39));
		CBrush brownBrush(RGB(88, 57, 39));
		pDC->SelectObject(&brownPen);
		pDC->SelectObject(&brownBrush);
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				int case_center_x = boardDraw.left + (i + 0.5) * caseWidth;
				int case_center_y = boardDraw.top + (j + 0.5) * caseHeight;
				pDC->Ellipse(case_center_x - radius, case_center_y - radius, case_center_x + radius, case_center_y + radius);
			}
		}

		pDC->SelectObject(&oldBrush);
		pDC->SelectObject(&oldPen);
		listPen.clear();
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


