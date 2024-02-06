
// HightDpiView.cpp : implementation of the CHightDpiView class
//




#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HightDpi.h"
#endif

#include "HightDpiDoc.h"
#include "HightDpiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace fs = std::filesystem;

struct MYICON_INFO
{
	int     nWidth;
	int     nHeight;
	int     nBitsPerPixel;
};


// CHightDpiView

IMPLEMENT_DYNCREATE(CHightDpiView, CView)

BEGIN_MESSAGE_MAP(CHightDpiView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// CHightDpiView construction/destruction

CHightDpiView::CHightDpiView() noexcept
{
	_path = GetCursorPath();
	fs::path f = _path;
	if (fs::exists(f) == false)
	{
		AfxMessageBox(_T("Cursor file not found"));
	}
}

CHightDpiView::~CHightDpiView()
{
}

BOOL CHightDpiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CHightDpiView drawing

void CHightDpiView::OnDraw(CDC* /*pDC*/)
{
	CHightDpiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CHightDpiView printing

BOOL CHightDpiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHightDpiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHightDpiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CHightDpiView diagnostics

#ifdef _DEBUG
void CHightDpiView::AssertValid() const
{
	CView::AssertValid();
}

void CHightDpiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHightDpiDoc* CHightDpiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHightDpiDoc)));
	return (CHightDpiDoc*)m_pDocument;
}
#endif //_DEBUG


// CHightDpiView message handlers

std::wstring CHightDpiView::GetCursorPath()
{
	TCHAR buffer[MAX_PATH * sizeof(TCHAR)];
	std::wstring wstrPath;

	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(_T("\\/"));

	wstrPath = std::wstring(buffer).substr(0, pos);

	return wstrPath + _T("\\") + L"Wii normal.cur";
}


BOOL CHightDpiView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	HCURSOR hCursor = (HCURSOR)LoadImage(AfxGetInstanceHandle(), _path.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
	GetDPI();
	GetCursorSize(hCursor);

	SetCursor(hCursor);
	return TRUE;
	
}

// Get the DPI of the monitor
void CHightDpiView::GetDPI()
{
	if (GetDC() == nullptr)
	{
		return;
	}
	int dpiX = GetDC()->GetDeviceCaps(LOGPIXELSX);
	int dpiY = GetDC()->GetDeviceCaps(LOGPIXELSY);
	
	std::wstring output = L"DPI X: " + std::to_wstring(dpiX) + L" DPI Y: " + std::to_wstring(dpiY);
	OutputDebugString(output.c_str());
	OutputDebugString(L"\n");
}

// Get the cusror size
void CHightDpiView::GetCursorSize(HCURSOR cursor)
{
	CSize size;
	ICONINFOEX ii{};
	MYICON_INFO myinfo;
	ZeroMemory(&myinfo, sizeof(myinfo));

	ii.cbSize = sizeof(ICONINFOEX);

	GetIconInfoEx(cursor, &ii);
	
	
	BITMAP bmp;
	ZeroMemory(&bmp, sizeof(bmp));

	if (ii.hbmColor)
	{
		const int nWrittenBytes = GetObject(ii.hbmColor, sizeof(bmp), &bmp);
		if (nWrittenBytes > 0)
		{
			myinfo.nWidth = bmp.bmWidth;
			myinfo.nHeight = bmp.bmHeight;
			myinfo.nBitsPerPixel = bmp.bmBitsPixel;
		}
	}
	else if (ii.hbmMask)
	{
		// Icon has no color plane, image data stored in mask
		const int nWrittenBytes = GetObject(ii.hbmMask, sizeof(bmp), &bmp);
		if (nWrittenBytes > 0)
		{
			myinfo.nWidth = bmp.bmWidth;
			myinfo.nHeight = bmp.bmHeight / 2;
			myinfo.nBitsPerPixel = 1;
		}
	}

	if (ii.hbmColor)
		DeleteObject(ii.hbmColor);
	if (ii.hbmMask)
		DeleteObject(ii.hbmMask);

	

	//GetBitmapDimensionEx(ii.hbmColor, &size);
	
	std::wstring output = L"cursor Width: " + std::to_wstring(myinfo.nWidth) + L" Height: " + std::to_wstring(myinfo.nHeight);
	OutputDebugString(output.c_str());
	OutputDebugString(L"\n");

}