#pragma once


// CLdButton

class CLdButton : public CButton
{
	DECLARE_DYNAMIC(CLdButton)

public:
	CLdButton();
	virtual ~CLdButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

	void DrawBtnBmp();

	HBITMAP m_hBtnBmp;
	void SetBmp(HBITMAP hBtnBmp)
	{
		BITMAP bitmapH;
		::GetObject(hBtnBmp, sizeof(BITMAP), &bitmapH);		
		m_iBmpWidth = bitmapH.bmWidth;
		m_iBmpHeight= bitmapH.bmHeight;
		m_hBtnBmp = hBtnBmp;
	}

	int m_iBmpHeight;
	int m_iBmpWidth;
	bool m_bPressed;
	bool m_bFocus;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};


