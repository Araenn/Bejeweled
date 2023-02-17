
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
#include "Log.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

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
	ON_WM_TIMER()
END_MESSAGE_MAP()

// construction/destruction de CBejeweledView

CBejeweledView::CBejeweledView() noexcept :
	m_widthBoardDraw(0),
	m_heightBoardDraw(0),
	m_caseHeight(0),
	m_caseWidth(0),
	m_circleRadius(0),
	m_firstClickX(-1),
	m_firstClickY(-1),
	m_bAnimating(false),
	m_nAnimStep(0)
{
	// TODO: ajoutez ici du code de construction
}

CBejeweledView::~CBejeweledView()
{

}

int CBejeweledView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
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
	m_widthBoardDraw = (m_windowsRect.left + m_windowsRect.right) / 3;
	m_heightBoardDraw = m_widthBoardDraw - (m_windowsRect.Height() + m_windowsRect.Width()) / 5;

	m_boardDraw = CRect(m_windowsRect.left + m_widthBoardDraw, m_windowsRect.top + m_heightBoardDraw, m_windowsRect.right - m_widthBoardDraw, m_windowsRect.bottom - m_heightBoardDraw);

	m_caseWidth = m_boardDraw.Width() / pDoc->m_pBoard->getBoardSize(); // width of each case
	m_caseHeight = m_boardDraw.Height() / pDoc->m_pBoard->getBoardSize(); // m_heightBoardDraw of each case
	m_circleRadius = (m_caseWidth < m_caseHeight) ? m_caseWidth / 2 : m_caseHeight / 2;
	m_circleRadius = (int) (m_circleRadius * 0.9); // decrease the m_circleRadius by 20%


	
	CPen defaultPen(PS_SOLID, 1, BROWN);
	CPen* oldPen = pDC->SelectObject(&defaultPen);

	CPen mulberryPen(PS_SOLID, 1, RGB(32, 30, 32));
	pDC->SelectObject(mulberryPen);
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

		CBrush brownBrush(RGB(224, 169, 109));
		pDC->SelectObject(&brownBrush);
		pDC->Rectangle(m_boardDraw);


		for (int line = 0; line < pDoc->m_tailleTab; line++) {
			for (int col = 0; col < pDoc->m_tailleTab; col++) {
				const CJewels& test = pDoc->m_pBoard->get(line, col);
				
					CPen newPen(PS_SOLID, 1, pDoc->m_color[line * pDoc->m_tailleTab + col]);
					pDC->SelectObject(newPen);
					CBrush newBrush(pDoc->m_color[line * pDoc->m_tailleTab + col]);
					pDC->SelectObject(newBrush);

					int case_center_x = (int)(m_boardDraw.left + (col + 0.5) * m_caseWidth);
					int case_center_y = (int)(m_boardDraw.top + (line + 0.5) * m_caseHeight);
					pDC->Ellipse(case_center_x - m_circleRadius, case_center_y - m_circleRadius, case_center_x + m_circleRadius, case_center_y + m_circleRadius);
				
			}
		}
		drawFallingJewels();
		StartAnimation();

		//affichage du score
		CString temp;
		temp.Format(_T("%2i"), pDoc->getScore());
		temp = _T("Score : ") + temp;
		pDC->TextOut(
			(m_boardDraw.Width() / 2),
			(m_boardDraw.Height() / 2 + 20),
			temp,
			temp.GetLength()
		);

		pDC->SelectObject(&oldBrush);
		pDC->SelectObject(&oldPen);
	}
}


	// TODO: ajoutez ici le code de dessin pour les données natives

void CBejeweledView::StartAnimation()
{
	m_bAnimating = true;
	m_nAnimStep = 0;
	SetTimer(1, 1000, NULL);
}

void CBejeweledView::StopAnimation()
{
	m_bAnimating = false;
	KillTimer(1);
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

	CDC* pDC = GetDC();
	CView::OnLButtonDown(nFlags, point);

	if (m_firstClickX == -1) {
		int firstJewelY = (point.x - m_boardDraw.left) / m_caseWidth;
		int firstJewelX = (point.y - m_boardDraw.top) / m_caseHeight;
		if (firstJewelX >= 0 && firstJewelX < pDoc->m_pBoard->getBoardSize() &&
			firstJewelY >= 0 && firstJewelY < pDoc->m_pBoard->getBoardSize()) {
			m_firstClickX = point.x;
			m_firstClickY = point.y;
		}
		
		return;
	}

	int firstJewelY = (m_firstClickX - m_boardDraw.left) / m_caseWidth;
	int firstJewelX = (m_firstClickY - m_boardDraw.top) / m_caseHeight;

	int secondClickX = point.x;
	int secondClickY = point.y;


	int secondJewelY = (secondClickX - m_boardDraw.left) / m_caseWidth;
	int secondJewelX = (secondClickY - m_boardDraw.top) / m_caseHeight;

	if (secondJewelX >= 0 && secondJewelX < pDoc->m_pBoard->getBoardSize() &&
		secondJewelY >= 0 && secondJewelY < pDoc->m_pBoard->getBoardSize()) {

		pDoc->invertJewels(firstJewelX, firstJewelY, secondJewelX, secondJewelY);

		if (!pDoc->m_pBoard->isMoveLegal(firstJewelX, firstJewelY, secondJewelX, secondJewelY)) {
			pDoc->invertJewels(firstJewelX, firstJewelY, secondJewelX, secondJewelY);
			m_firstClickX = -1;
			m_firstClickY = -1;
			return;
		}


		comboJewels = pDoc->m_pBoard->getComboJewelsOnSwap(firstJewelX, firstJewelY, secondJewelX, secondJewelY);
		StartAnimation();
		

		get_log_file() << "score: " << pDoc->getScore() << std::endl;

		m_firstClickX = -1;
		m_firstClickY = -1;

		pDoc->updateView();
		StopAnimation();
	}
	
	m_firstClickX = -1;
	m_firstClickY = -1;
	
}

void CBejeweledView::fallingAllJewels() {
	CBejeweledDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	std::vector<std::vector<CJewels>> &T = pDoc->m_pBoard->makeFallingJewels();
	unsigned int maxDepth = 0;
	for (unsigned int i = 0; i < T.size(); i++) {
		if (T[i].size() > maxDepth) {
			maxDepth = T[i].size();
		}
	}

	for (unsigned int i = 0; i < maxDepth; i++) {
		pDoc->m_pBoard->fallOneTime(T);
		StartAnimation();
	}
}


void CBejeweledView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ajoutez ici le code de votre gestionnaire de messages et/ou les paramètres par défaut des appels
	CBejeweledDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC* pDC = GetDC();
		
	//dessiner en couleur fond ceux qui sortent directement de makeJewelsFalling, puis dessiner avec cette fonction en faisant descendre PROGRESSIVEMENT les pierres
	pDoc->m_pBoard->disappearingJewels(comboJewels);
	//drawDefault();
	pDoc->m_pBoard->applyGravity();
	drawFallingJewels();
	pDoc->updateView();
	fallingAllJewels();
	pDoc->addScore(comboJewels.size() * comboJewels.size());

	comboJewels = pDoc->m_pBoard->getAllComboJewels();
	while (comboJewels.size() != 0) {
		pDoc->addScore(comboJewels.size() * comboJewels.size());

		pDoc->m_pBoard->disappearingJewels(comboJewels);
		//drawDefault();
		pDoc->m_pBoard->applyGravity();
		drawFallingJewels();
		fallingAllJewels();
		comboJewels = pDoc->m_pBoard->getAllComboJewels();
	}
	CView::OnTimer(nIDEvent);
}

/*
* draw the jewels which were in combo, so the disappeared one
* draw them in the color of the board game
*
*/

void CBejeweledView::drawDefault() {
	CBejeweledDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC* pDC = GetDC();

	for (int line = 0; line < pDoc->m_tailleTab; line++) {
		for (int col = 0; col < pDoc->m_tailleTab; col++) {
			const CJewels& test = pDoc->m_pBoard->get(line, col);
			if (pDoc->m_pBoard->isJewelsDefault(test)) {
				CPen defaultPen(PS_SOLID, 1, BROWN);
				CPen *oldPen = pDC->SelectObject(&defaultPen);
				CBrush defaultBrush(BROWN);
				CBrush *oldBrush = pDC->SelectObject(&defaultBrush);

				int case_center_x = (int)(m_boardDraw.left + (col + 0.5) * m_caseWidth);
				int case_center_y = (int)(m_boardDraw.top + (line + 0.5) * m_caseHeight);
				pDC->Ellipse(case_center_x - m_circleRadius, case_center_y - m_circleRadius, case_center_x + m_circleRadius, case_center_y + m_circleRadius);

				pDC->SelectObject(&oldPen);
				pDC->SelectObject(&oldBrush);
				ReleaseDC(pDC);
			}
		}
	}
	
}


/*
* draw the jewels that are falling in the board (aka the new one)
*
*/
void CBejeweledView::drawFallingJewels() {
	CBejeweledDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC* pDC = GetDC();

	std::vector<std::vector<CJewels>>& T = pDoc->m_pBoard->T;
	if (T.size() != 0) {
		for (int i = 0; i < T.size(); i++) {
			std::vector<CJewels>& t = T[i];

			if (t.size() == 0) {
				continue;
			}

			CPen newPen(PS_SOLID, 1, t[0].getColorJewels());
			CPen* oldPen = pDC->SelectObject(&newPen);
			CBrush newBrush(t[0].getColorJewels());
			CBrush* oldBrush = pDC->SelectObject(&newBrush);

			for (int j = 0; j < t.size(); j++) {
				int case_center_x = (int)(m_boardDraw.left + (i + 0.5) * m_caseWidth);
				int case_center_y = (int)(m_boardDraw.top + (t.size() - 1 + 0.5 + j) * m_caseHeight);
				pDC->Ellipse(case_center_x - m_circleRadius, case_center_y - m_circleRadius, case_center_x + m_circleRadius, case_center_y + m_circleRadius);
				t.erase(t.begin());
			}
			pDC->SelectObject(&oldPen);
			pDC->SelectObject(&oldBrush);
			
			ReleaseDC(pDC);
		}
	}
}