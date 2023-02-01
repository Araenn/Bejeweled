
// BejeweledDoc.cpp : implémentation de la classe CBejeweledDoc
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS peuvent être définis dans les gestionnaires d'aperçu, de miniature
// et de recherche d'implémentation de projet ATL, et permettent le partage de code de document avec ce projet.
#ifndef SHARED_HANDLERS
#include "Bejeweled.h"
#endif

#include "BejeweledDoc.h"
#include "CBoard.h"
#include "DlgSizeBoard.h"
#include "DlgStoneNumber.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBejeweledDoc

IMPLEMENT_DYNCREATE(CBejeweledDoc, CDocument)

BEGIN_MESSAGE_MAP(CBejeweledDoc, CDocument)
	ON_COMMAND(ID_TEST_AFFICHAGEGRID, &CBejeweledDoc::OnTestAffichagegrid)
	ON_COMMAND(ID_TEST_DESSINBOARD, &CBejeweledDoc::OnTestDessinboard)
	ON_COMMAND(ID_OPTIONS_TAILLEDUPLATEAU, &CBejeweledDoc::OnOptionsTailleduplateau)
	ON_COMMAND(ID_OPTIONS_NOMBREDEPIERRES, &CBejeweledDoc::OnOptionsNombredepierres)
END_MESSAGE_MAP()


// construction/destruction de CBejeweledDoc

CBejeweledDoc::CBejeweledDoc() noexcept :
	p_valueTab(NULL),
	m_tailleTab(8),
	m_stoneNumber(6),
	m_widthCase(0),
	m_heightCase(0),
	flag(0)
{
	// TODO: ajoutez ici le code d'une construction unique


}

CBejeweledDoc::~CBejeweledDoc()
{
	if (this->p_valueTab != NULL) delete[] this->p_valueTab;

}

BOOL CBejeweledDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ajoutez ici le code de réinitialisation
	// (les documents SDI réutiliseront ce document)

	return TRUE;
}




// sérialisation de CBejeweledDoc

void CBejeweledDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ajoutez ici le code de stockage
	}
	else
	{
		// TODO: ajoutez ici le code de chargement
	}
}

#ifdef SHARED_HANDLERS

// Prise en charge des miniatures
void CBejeweledDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modifier ce code pour dessiner les données du document
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support pour les gestionnaires de recherche
void CBejeweledDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Définir le contenu de recherche à partir des données du document.
	// Les parties du contenu doivent être séparées par ";"

	// Par exemple :  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBejeweledDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// diagnostics de CBejeweledDoc

#ifdef _DEBUG
void CBejeweledDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBejeweledDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// commandes de CBejeweledDoc


void CBejeweledDoc::OnTestAffichagegrid()
{
	this->flag = 1;
	CBoard board(m_tailleTab, m_stoneNumber);
	if (p_valueTab != NULL) delete[] p_valueTab;
	p_valueTab = board.debug_board();
	UpdateAllViews(0);
}

CString *CBejeweledDoc::getChaine() {
	return this->p_valueTab;
}

int CBejeweledDoc::getTaille() const {
	return this->m_tailleTab;
}

void CBejeweledDoc::OnTestDessinboard()
{
	m_color.clear();
	this->flag = 2;
	CBoard board(m_tailleTab, m_stoneNumber);
	for (int i = 0; i < m_tailleTab; i++) {
		for (int j = 0; j < m_tailleTab; j++) {
			m_color.push_back(board[i][j].getColorJewels());
		}
	}

	UpdateAllViews(0);

	// TODO: ajoutez ici le code de votre gestionnaire de commande
}


void CBejeweledDoc::OnOptionsTailleduplateau()
{
	// TODO: ajoutez ici le code de votre gestionnaire de commande
	DlgSizeBoard dlg;
	dlg.DoModal();
	m_tailleTab = (int) dlg.m_sliderValue;
	OnTestDessinboard();
}


void CBejeweledDoc::OnOptionsNombredepierres()
{
	// TODO: ajoutez ici le code de votre gestionnaire de commande
	DlgStoneNumber dlg;
	dlg.DoModal();
	m_stoneNumber = dlg.m_sliderStoneNumber;
	OnTestDessinboard();
}
