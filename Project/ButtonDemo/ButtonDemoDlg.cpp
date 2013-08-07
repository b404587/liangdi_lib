
// ButtonDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ButtonDemo.h"
#include "ButtonDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CButtonDemoDlg 对话框




CButtonDemoDlg::CButtonDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CButtonDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CButtonDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CButtonDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CButtonDemoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CButtonDemoDlg::OnBnClickedCancel)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CButtonDemoDlg 消息处理程序

BOOL CButtonDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

//	HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAP1)); 
//	int x = 10;
//	CRect rtBt(x,x, x+58,x+58);
//	m_btnMpr.Create(NULL,WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,rtBt,this, IDC_BUTTON1);
//	m_btnMpr.SetBmp(hBmp);
//	
//	m_ToolTip.Create(this, TTS_ALWAYSTIP);
//	m_ToolTip.Activate(TRUE);

//	m_ToolTip.AddTool(GetDlgItem(IDC_BUTTON1), L"MPR");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CButtonDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CButtonDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CButtonDemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CButtonDemoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


int CButtonDemoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAP1)); 
	int x = 10;
	CRect rtBt(x,x, x+58,x+58);
	m_btnMpr.Create(NULL,WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,rtBt,this, IDC_BUTTON1);
	m_btnMpr.SetBmp(hBmp);
	
	m_ToolTip.Create(this, TTS_ALWAYSTIP);
	m_ToolTip.Activate(TRUE);

	m_ToolTip.AddTool(GetDlgItem(IDC_BUTTON1), L"MPR");

	
	return 0;
}


BOOL CButtonDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_ToolTip.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}
