
// BejeweledDoc.h : interface de la classe CBejeweledDoc
//
#include <vector>

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
	afx_msg void OnTestAffichagegrid();
	int m_tailleTab;
	int m_stoneNumber;
	CString *p_valueTab;
	CString *getChaine();
	int getTaille() const;
	afx_msg void OnTestDessinboard();
	int m_widthCase;
	int m_heightCase;
	int flag;
	std::vector<COLORREF> m_color;
	afx_msg void OnOptionsTailleduplateau();
	afx_msg void OnOptionsNombredepierres();
};
