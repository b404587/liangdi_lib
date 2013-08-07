// LdButton.cpp : 实现文件
//

#include "stdafx.h"
#include "LdButton.h"


// CLdButton

IMPLEMENT_DYNAMIC(CLdButton, CButton)

CLdButton::CLdButton()
{
	m_hBtnBmp = NULL;
	m_iBmpHeight = 0;
	m_iBmpWidth = 0;
	m_bPressed = false;
	m_bFocus = false;
}

CLdButton::~CLdButton()
{
}


BEGIN_MESSAGE_MAP(CLdButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CLdButton 消息处理程序




void CLdButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_bPressed = !m_bPressed;

	CButton::OnLButtonDown(nFlags, point);
}


void CLdButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnLButtonUp(nFlags, point);
}


BOOL CLdButton::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
	//return CButton::OnEraseBkgnd(pDC);
}


void CLdButton::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

	// TODO:  添加您的代码以绘制指定项
	DrawBtnBmp();
}


BOOL CLdButton::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CButton::OnCommand(wParam, lParam);
}

void CLdButton::DrawBtnBmp()
{
	if(!m_hBtnBmp)
		return;

	CClientDC Viewdc(this);
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&Viewdc);

	CBitmap* pMyBitmap1 = CBitmap().FromHandle(m_hBtnBmp);
	CBitmap* pOldBKBitmap1 = dcMemory.SelectObject(pMyBitmap1);

	
	int iLeft = 0, iTop = 0;
	if(m_bPressed)
	{
		if(m_bFocus)
			iLeft = m_iBmpWidth/4 *2;
		else
			iLeft = m_iBmpWidth/4 *3;
	}
	else
	{
		if(m_bFocus)
			iLeft = m_iBmpWidth/4 *1;
		else
			iLeft = 0;
	}
	
	Viewdc.BitBlt(0,  0, m_iBmpWidth/4, m_iBmpHeight , &dcMemory,
	iLeft, iTop, SRCCOPY);

	dcMemory.SelectObject(pOldBKBitmap1);
	dcMemory.DeleteDC();
}



void CLdButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//DrawBtnBmp();
	if(!m_bFocus)
	{
		TRACKMOUSEEVENT   tme;   
		tme.cbSize   =   sizeof(tme);   
		tme.hwndTrack   =   m_hWnd;   
		tme.dwFlags   =   TME_LEAVE;   
		_TrackMouseEvent(&tme); 

		m_bFocus = true;
		DrawBtnBmp();	
	}

	CButton::OnMouseMove(nFlags, point);
}


void CLdButton::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bFocus = false;
	DrawBtnBmp();

	CButton::OnMouseLeave();
}
