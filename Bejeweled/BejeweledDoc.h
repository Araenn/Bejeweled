
// BejeweledDoc.h : interface de la classe CBejeweledDoc
//
#include <vector>
#include "CBoard.h"

#pragma once

class CBejeweledDoc : public CDocument
{
protected: // création à partir de la sérialisation uniquement
	CBejeweledDoc() noexcept;
	DECLARE_DYNCREATE(CBejeweledDoc)

// Attributs
public:

// Opérations
public:

// Substitutions
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implémentation
public:
	virtual ~CBejeweledDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Fonction d'assistance qui définit le contenu de recherche pour un gestionnaire de recherche
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int m_tailleTab;
	int m_stoneNumber;
	CString* p_valueTab;
	int m_widthCase;
	int m_heightCase;
	int flag;
	std::vector<COLORREF> m_color;
	CBoard* m_pBoard;


	afx_msg void OnTestAffichagegrid();
	afx_msg void OnTestDessinboard();
	afx_msg void OnOptionsTailleduplateau();
	afx_msg void OnOptionsNombredepierres();

	
	CString *getChaine();
	int getTaille() const;
	void invertJewels(int x1, int y1, int x2, int y2);
	void updateBoard();
};
