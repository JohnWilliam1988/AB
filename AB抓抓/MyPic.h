#pragma once

class CMyPic : public CStatic
{
// Construction
public:
	CMyPic();
// Implementation
public:
	virtual ~CMyPic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyPic)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CStatic m_mypic;
};