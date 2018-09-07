
// FreeCellStarter2010Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "FreeCellStarter2010.h"
#include "FreeCellStarter2010Dlg.h"
#include "afxdialogex.h"
#include "WindowsCards.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFreeCellStarter2010Dlg dialog




CFreeCellStarter2010Dlg::CFreeCellStarter2010Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFreeCellStarter2010Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFreeCellStarter2010Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFreeCellStarter2010Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CFreeCellStarter2010Dlg message handlers

BOOL CFreeCellStarter2010Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// Setup the cards
	bool ok = InitializeCards();
	if(!ok)
	{
		MessageBox(L"cards.dll failed to initialize", L"Error");
		return true;
	}

	// Initialize the 16 mCells here:
	for (int i = 0; i < 4; i++)
	{
		int l = spaceBetweenCells + i*(gCardWidth + cellToCardMargin * 2 + spaceBetweenCells);
		int t = spaceBetweenCells;
		int r = l + gCardWidth + cellToCardMargin * 2;
		int b = t + gCardHeight + cellToCardMargin * 2;
		mCells[i] = new TempCell(l, t, r, b);
	}

	//endcells
	for (int i = 4; i < 8; i++)
	{
		int l = spaceBetweenCells + i * (gCardWidth + cellToCardMargin * 2 + spaceBetweenCells);
		int t = spaceBetweenCells;
		int r = l + gCardWidth + cellToCardMargin * 2;
		int b = t + gCardHeight + cellToCardMargin * 2;
		mCells[i] = new EndCell(l, t, r, b);
	}

	//cardcells
	for (int i = 8; i < 16; i++)
	{
		int l = spaceBetweenCells + (i - 8) * (gCardWidth + cellToCardMargin * 2 + spaceBetweenCells);
		int t = (spaceBetweenCells*2) + gCardHeight + (cellToCardMargin * 2);
		int r = l + gCardWidth + cellToCardMargin * 2;
		int b = t + gCardHeight + cellToCardMargin * 2;
		mCells[i] = new StartCell(l, t, r, b);
	}

	// Put some card in the first cell, for testing:
	mCells[0]->AddCard(5);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFreeCellStarter2010Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFreeCellStarter2010Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting

		//// This code draws each card horizontally.
		//int x=2;
		//int y=130;
		//bool highlighted = false;
		//for(int index=0; index<52; index++)
		//{
		//	DrawCard(dc, x, y, index, highlighted);
		//	x += 26;
		//}

		// Draw all the cells
		for (int i = 0; i<16; i++)
		{
			mCells[i]->Draw(dc);
		}

		
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFreeCellStarter2010Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFreeCellStarter2010Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	UninstallCards();

	CDialogEx::OnClose();
}
