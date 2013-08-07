
// ButtonDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ButtonDemo.h"
#include "ButtonDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CButtonDemoDlg �Ի���




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


// CButtonDemoDlg ��Ϣ�������

BOOL CButtonDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

//	HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(),  MAKEINTRESOURCE(IDB_BITMAP1)); 
//	int x = 10;
//	CRect rtBt(x,x, x+58,x+58);
//	m_btnMpr.Create(NULL,WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,rtBt,this, IDC_BUTTON1);
//	m_btnMpr.SetBmp(hBmp);
//	
//	m_ToolTip.Create(this, TTS_ALWAYSTIP);
//	m_ToolTip.Activate(TRUE);

//	m_ToolTip.AddTool(GetDlgItem(IDC_BUTTON1), L"MPR");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CButtonDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CButtonDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CButtonDemoDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CButtonDemoDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


int CButtonDemoDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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
	// TODO: �ڴ����ר�ô����/����û���
	m_ToolTip.RelayEvent(pMsg);
	return CDialogEx::PreTranslateMessage(pMsg);
}
