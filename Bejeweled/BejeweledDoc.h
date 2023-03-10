
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
	int flag;
	int score;
	std::vector<COLORREF> m_color;
	CBoard* m_pBoard;


	afx_msg void OnDebug();
	afx_msg void OnStart();
	afx_msg void OnOptionsTailleduplateau();
	afx_msg void OnOptionsNombredepierres();

	
	CString *getChaine();
	int getTaille() const;
	void updateBoard();
	void updateView();
	int getScore();
	void addScore(int score);
};
