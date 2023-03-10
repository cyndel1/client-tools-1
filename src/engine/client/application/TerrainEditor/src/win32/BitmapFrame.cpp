//
// BitmapFrame.cpp
//
// copyright 2004, sony online entertainment
//

//-------------------------------------------------------------------

#include "FirstTerrainEditor.h"
#include "BitmapFrame.h"

#include "BitmapView.h"
#include "TerrainEditor.h"
#include "TerrainEditorDoc.h"

//-------------------------------------------------------------------

IMPLEMENT_DYNCREATE(BitmapFrame, CMDIChildWnd)

//-------------------------------------------------------------------

BitmapFrame::BitmapFrame() :
	CMDIChildWnd (),
	m_windowName (),
	m_wndToolBar ()
{
	m_windowName = "Bitmaps";
}

//-------------------------------------------------------------------

BitmapFrame::~BitmapFrame()
{
}

//-------------------------------------------------------------------

BEGIN_MESSAGE_MAP(BitmapFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(BitmapFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-------------------------------------------------------------------

int BitmapFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//-- create tool bar
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_BITMAPGROUPFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	TerrainEditorApp* app = static_cast<TerrainEditorApp*>(AfxGetApp());
	if(!app->RestoreWindowPosition(this,"BitmapFrame"))
	{
		CRect mainRect;
		AfxGetApp()->GetMainWnd ()->GetClientRect (&mainRect);
		mainRect.right  -= 2; // allow for frame
		mainRect.bottom -= 64; // allow for toolbars, etc.
	
		IGNORE_RETURN (SetWindowPos (&wndTop, (mainRect.right*1/2), (mainRect.bottom*1/2), (mainRect.right*1/4), (mainRect.bottom*1/4), SWP_SHOWWINDOW));
	}

	return 0;
}

//-------------------------------------------------------------------

void BitmapFrame::OnDestroy() 
{
	//-- tell document we're being destroyed
	TerrainEditorDoc* const doc = dynamic_cast<TerrainEditorDoc*> (GetActiveDocument ());
	if (doc)
		doc->setBitmapFrame (0);

	TerrainEditorApp* app = static_cast<TerrainEditorApp*>(AfxGetApp());
	app->SaveWindowPosition(this,"BitmapFrame");
	//-- chain to base 
	CMDIChildWnd::OnDestroy();
}

//-------------------------------------------------------------------

BOOL BitmapFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.lpszName = m_windowName;
	cs.style &= ~FWS_ADDTOTITLE;
	cs.style &= ~FWS_PREFIXTITLE;

	return CMDIChildWnd::PreCreateWindow(cs);
}

//-------------------------------------------------------------------

void BitmapFrame::reset () const
{
	BitmapView* bitmapView = dynamic_cast<BitmapView*> (GetActiveView ());
	if (bitmapView)
	{
		bitmapView->reset ();
	}
}

//-------------------------------------------------------------------
