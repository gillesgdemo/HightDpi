
// HightDpiView.h : interface of the CHightDpiView class
//

#pragma once


class CHightDpiView : public CView
{
protected: // create from serialization only
	CHightDpiView() noexcept;
	DECLARE_DYNCREATE(CHightDpiView)

// Attributes
public:
	CHightDpiDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CHightDpiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	std::wstring _path;

private:
	std::wstring GetCursorPath();

	void GetDPI();
	void GetCursorSize(HCURSOR cursor);

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};

#ifndef _DEBUG  // debug version in HightDpiView.cpp
inline CHightDpiDoc* CHightDpiView::GetDocument() const
   { return reinterpret_cast<CHightDpiDoc*>(m_pDocument); }
#endif

