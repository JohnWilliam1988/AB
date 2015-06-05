// CatchScreenDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ABץץ.h"
#include "CatchScreenDlg.h"
#include "afxdialogex.h"

// CCatchScreenDlg �Ի���
// CCatchScreenDlg ��Ϣ�������
//����ɵ�RGBֵ�ַ���
static CString strOld=_T("");

extern CString g_StartPortStr;
extern CString g_EndPortStr;
extern CString g_SizePicStr;
extern CString g_PicPathStr;
extern CString g_CurrentExePath;
extern HBITMAP g_HbitMap;

extern  CButton				g_PicCheck;
//extern  CMyDrawPictureClass	g_DrawPicture; ///����͸��ͼ
extern  CMyShowPic			g_ShowPic;
extern CABץץApp theApp;

/////////////ȡɫ��////////////
extern CMyPickerColor		g_PickColorDlg;
/////////////////////////////////////////////////////////////////////////////
// CCatchScreenDlg dialog
IMPLEMENT_DYNAMIC(CCatchScreenDlg, CDialog)

	CCatchScreenDlg::CCatchScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCatchScreenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCatchScreenDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32

	//*******************************************************************************
	//��ʼ����Ƥ����,������resizeMiddle ����
	m_rectTracker.m_nStyle=CMyTracker::resizeMiddle|CMyTracker::solidLine;  
	m_rectTracker.m_rect.SetRect(-1,-2,-3,-4);
	//���þ�����ɫ
	m_rectTracker.SetRectColor(RGB(10,100,130));
	//���þ��ε���ʱ���,Ĭ�ϵ�̫С��,Ū�˸�����
	m_rectTracker.SetResizeCursor(IDC_CURSOR6,IDC_CURSOR5,IDC_CURSOR2,IDC_CURSOR3,IDC_CURSOR4);

	m_hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR1);  


	m_bDraw=FALSE;
	m_bFirstDraw=FALSE;
	m_bQuit=FALSE;
	m_bShowMsg=FALSE;
	m_startPt=0;

	//��ȡ��Ļ�ֱ���
	m_xScreen = GetSystemMetrics(SM_CXSCREEN);
	m_yScreen = GetSystemMetrics(SM_CYSCREEN);

	//��ȡ��Ļ��λͼ��
	CRect rect(0, 0,m_xScreen,m_yScreen);
	m_pBitmap=CBitmap::FromHandle(CopyScreenToBitmap(&rect));

	//��ʼ��ˢ�´������� m_rgn
	m_rgn.CreateRectRgn(0,0,50,50);
	//*******************************************************************************
}

void CCatchScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCatchScreenDlg)
	DDX_Control(pDX, IDC_EDITINFO1, m_tipEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCatchScreenDlg, CDialog)
	//{{AFX_MSG_MAP(CCatchScreenDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONUP()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID__SAVEPIC, &CCatchScreenDlg::OnClickSaveBmp)
	ON_COMMAND(ID__EXITSCREEN, &CCatchScreenDlg::OnExitCatchScreen)
	ON_WM_CREATE()
	ON_COMMAND(ID_ABMAKEPIN, &CCatchScreenDlg::OnAbmakepin)
	ON_COMMAND(ID_SYSMAKEPIC, &CCatchScreenDlg::OnSysmakepic)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatchScreenDlg message handlers

BOOL CCatchScreenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//**************************************************************************
	//�ѶԻ������ó�ȫ�����㴰��
	::SetWindowPos(this->m_hWnd,HWND_TOPMOST,0,0,m_xScreen,m_yScreen,SWP_SHOWWINDOW);
	////// ���Դ��� ��С�����ڵ��Դ���
	//SetWindowPos(&wndNoTopMost/*wndTopMost*/,0,0,200,200,SWP_SHOWWINDOW);
	//::SetWindowPos(g_PickColorDlg.m_hWnd,HWND_TOP/*HWND_TOPMOST*/,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);

	//�ƶ�������ʾ����
	CRect rect;
	m_tipEdit.GetWindowRect(&rect);
	m_tipEdit.MoveWindow(10,10,rect.Width(),rect.Height());

	//��ʾ������ʾ��������
	DrawTip();
	////**************************************************************************

	// TODO: Add extra initialization here
	//KillTimer(1001);
	return TRUE;  // return TRUE  unless you set the focus to a control
}
////// OnCreate /////////////////////
int CCatchScreenDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//SetWindowPos(&wndTopMost,0,0,m_xScreen,m_yScreen,SWP_SHOWWINDOW);

	//�ƶ�������ʾ����
	/*CRect rect;
	m_tipEdit.GetWindowRect(&rect);
	m_tipEdit.MoveWindow(10,10,rect.Width(),rect.Height());*/

	//��ʾ������ʾ��������
	//DrawTip();
	return 0;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCatchScreenDlg::OnPaint() 
{

	//**************************************************************************
	CPaintDC dc(this);

	//��ʾ��ȡ���δ�С��Ϣ
	if(m_bShowMsg&&m_bFirstDraw)
	{
		//�õ���ǰ���δ�С
		CRect rect;
		m_rectTracker.GetTrueRect(&rect);
		//����CPaintDC ��Ϊ�˲����˴����ϻ���Ϣ
		DrawMessage(rect,&dc);
	}

	//������Ƥ�����
	if(m_bFirstDraw)
	{
		m_rectTracker.Draw(&dc);
	}

	//::SetWindowPos(g_PickColorDlg.m_hWnd,HWND_BOTTOM/*HWND_TOPMOST*/,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);

	//*************************************************************************
	CDialog::OnPaint();
}
///////////
void CCatchScreenDlg::OnOK() 
{
	// TODO: Add extra validation here
	//if(m_bFirstDraw)
	//{
	//	//ȡ���ѻ����α���
	//	m_bFirstDraw=FALSE;
	//	m_bDraw=FALSE;
	//	m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
	//	PaintWindow();
	//}
	//else
	{
		CDialog::OnOK();
	}

	//CDialog::OnOK();
}

void CCatchScreenDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	//***************************************************************
	if(m_bFirstDraw)
	{
		//ȡ���ѻ����α���
		m_bFirstDraw=FALSE;
		m_bDraw=FALSE;
		m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
		PaintWindow();
	}
	else
	{
		CDialog::OnCancel();
	}
	//*******************************************************************
}

//// ����ƶ�����
void CCatchScreenDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//**************************************************************************************
	if(m_bDraw)
	{
		//��̬�������δ�С,��ˢ�»���
		m_rectTracker.m_rect.SetRect(m_startPt.x+4,m_startPt.y+4,point.x,point.y);
		PaintWindow();
	}

	//�ֲ�������С��λ��ʱ,���ղ���MouseMove��Ϣ
	CRect rect;
	m_tipEdit.GetWindowRect(&rect);
	// if(rect.PtInRect(point))
	//m_tipEdit.SendMessage(WM_MOUSEMOVE);

	//ChangeRGB();

	DrawTip();
	//*****************************************************************************************
	CDialog::OnMouseMove(nFlags, point);
}
////// �������
void CCatchScreenDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//*****************************************************************************************
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);

	//�жϻ���λ��
	if(nHitTest<0)
	{
		if(!m_bFirstDraw)
		{
			//��һ�λ�����
			m_startPt=point;
			m_bDraw=TRUE;
			m_bFirstDraw=TRUE;
			//���õ�����갴��ʱ��С�ľ��δ�С
			m_rectTracker.m_rect.SetRect(point.x,point.y,point.x+4,point.y+4);	

			//��֤����굱��ʱ������ʾ��Ϣ
			if(m_bFirstDraw)
				m_bShowMsg=TRUE;		
			DrawTip();
			PaintWindow();
		}
	}
	else
	{
		//��֤����굱��ʱ������ʾ��Ϣ
		m_bShowMsg=TRUE;		
		PaintWindow();

		if(m_bFirstDraw)
		{
			//������Сʱ,Track���Զ��������δ�С,��Щ�ڼ�,��Ϣ��CRectTracker�ڲ�����
			m_rectTracker.Track(this,point,TRUE);
			//SendMessage(WM_LBUTTONUP,NULL,NULL);
			PaintWindow();

		}
	}
	//****************************************************************************************
	CDialog::OnLButtonDown(nFlags, point);
}

////// �������
void CCatchScreenDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//****************************************************************************************

	m_bShowMsg=FALSE;
	m_bDraw=FALSE;
	DrawTip();

	PaintWindow();
	//****************************************************************************************
	CDialog::OnLButtonUp(nFlags, point);
}

///////���˫�� �˳���ͼ��������λͼ��ճ������,bSave ΪTRUE,
void CCatchScreenDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);
	//������Ǿ����ڲ�˫��
	if(nHitTest==8)      
	{
		//����λͼ��ճ������,bSave ΪTRUE,
		HBITMAP hbmp = CopyScreenToBitmap(m_rectTracker.m_rect,TRUE);
		//PostQuitMessage(0);
		//g_ShowPic.LoadClipboardBMP();
		CString pathStr = g_CurrentExePath+ _T("abpic.bmp");
		theApp.pPropSheet->activeCurrentPage(2);
		g_ShowPic.SaveBmpFile(hbmp,pathStr);
		g_ShowPic.ShowBmp(pathStr);
		this->OnOK();
		//::PostQuitMessage(0);
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

///�Ҽ�����
void CCatchScreenDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//****************************************************************************************
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);
	//������ھ����ڲ��һ�
	if(nHitTest==8)
	{
		if(m_bFirstDraw)
		{
			POINT   pt;   
			GetCursorPos(&pt);
			CMenu menu;
			menu.LoadMenu(IDR_MENU_CATCHSCREEN);
			menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
		}
	}
	else
		if(m_bFirstDraw)
		{
			//����Ѿ���ȡ���������ȡ����
			m_bFirstDraw=FALSE;
			//������δ�С
			m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
			DrawTip();
			PaintWindow();
		}
		else
		{
			//�رճ���
			//PostQuitMessage(0);
			OnCancel();
		}
		//****************************************************************************************
		CDialog::OnRButtonUp(nFlags, point);
}
//���ò�����ʾ�����ı���ɫ
HBRUSH CCatchScreenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	// TODO: Return a different brush if the default is not desired
	//***********************************************************
	//���ò�����ʾ�����ı���ɫ
	if(pWnd->GetDlgCtrlID()==IDC_EDITINFO1)
	{
		pDC->SetTextColor(RGB(255,255,255));
	}
	//***************************************************************
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

//�������������ȫ���Ի��򱳾�
BOOL CCatchScreenDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	//**************************************************************************************
	//�������������ȫ���Ի��򱳾�
	BITMAP bmp;
	m_pBitmap->GetBitmap(&bmp);

	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);

	dcCompatible.SelectObject(m_pBitmap);

	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);

	return TRUE;
	//**************************************************************************************
	//return CDialog::OnEraseBkgnd(pDC);
}

//���øı��ȡ���δ�Сʱ���
BOOL CCatchScreenDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	// ***********************************************************************
	// ���øı��ȡ���δ�Сʱ���
	if (pWnd == this &&m_rectTracker.SetCursor(this, nHitTest)
		&&!m_bDraw &&m_bFirstDraw) //�˴��жϱ���ȡʱ����ʼ��Ϊ��ɫ���
	{
		return TRUE; 
	}

	//���ò�ɫ���
	SetCursor(m_hCursor);
	return TRUE;

	//*******************************************************************
	//return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


//*********************���ӵĺ���**********************************************************
//������Ļ,��δ������������� �Ǻ�
HBITMAP CCatchScreenDlg::CopyScreenToBitmap(LPRECT lpRect,BOOL bSave)
	//lpRect ����ѡ������
{
	HDC       hScrDC, hMemDC;      
	// ��Ļ���ڴ��豸������
	HBITMAP    hBitmap, hOldBitmap;   
	// λͼ���
	int       nX, nY, nX2, nY2;      
	// ѡ����������
	int       nWidth, nHeight;

	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
		return NULL;
	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);

	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	//ȷ��ѡ�������ǿɼ���
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > m_xScreen)
		nX2 = m_xScreen;
	if (nY2 > m_yScreen)
		nY2 = m_yScreen;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap
		(hScrDC, nWidth, nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	if(bSave)
	{
		//����������DC,��bSaveΪ��ʱ�ѿ�ʼ�����ȫ��λͼ,����ȡ���δ�С����
		CDC dcCompatible;
		dcCompatible.CreateCompatibleDC(CDC::FromHandle(hMemDC));
		dcCompatible.SelectObject(m_pBitmap);

		BitBlt(hMemDC, 0, 0, nWidth, nHeight,dcCompatible, nX, nY, CAPTUREBLT|SRCCOPY);

	}
	else
	{
		BitBlt(hMemDC, 0, 0, nWidth, nHeight,hScrDC, nX, nY, CAPTUREBLT|SRCCOPY);
	}

	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//�õ���Ļλͼ�ľ��
	//��� 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);

	if(bSave)
	{
		if (::OpenClipboard(NULL)) 
		{
			//��ռ�����
			EmptyClipboard();
			//����Ļ����ճ������������,
			//hBitmap Ϊ�ղŵ���Ļλͼ���
			SetClipboardData(CF_BITMAP, hBitmap);
			//�رռ�����
			CloseClipboard();
		}
	}
	// ����λͼ���
	return hBitmap;
}
HBITMAP CCatchScreenDlg::CopyRectToBitmap(LPRECT lpRect)
{
	HDC hScrDC, hMemDC;      
	// ��Ļ���ڴ��豸������
	HBITMAP hBitmap,hOldBitmap;   
	// λͼ���
	int       nX, nY, nX2, nY2;      
	// ѡ����������
	int       nWidth, nHeight;      
	// λͼ��Ⱥ͸߶�
	int       xScrn, yScrn;         
	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
		return NULL;

	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//ȷ��ѡ�������ǿɼ���
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > xScrn)
		nX2 = xScrn;
	if (nY2 > yScrn)
		nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;

	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, CAPTUREBLT|SRCCOPY);
	//�õ���Ļλͼ�ľ��
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//��� 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// ����λͼ���
	return hBitmap;
}
//��ʾ������ʾ��Ϣ
void CCatchScreenDlg::DrawTip()
{
	static COLORREF oldColor=0;

	//�õ�ǰ��������,
	CPoint pt;
	GetCursorPos(&pt);

	//������ǰR,G,B,������ֵ
	COLORREF color;
	CClientDC dc(this);
	color=dc.GetPixel(pt);
	BYTE rValue,gValue,bValue;
	rValue=GetRValue(color);
	gValue=GetGValue(color);
	bValue=GetGValue(color);

	if(oldColor==color)
		return ;

	oldColor=color;

	//����ʽ�ŷ��ַ���
	CString string;
	CString strTemp;
	string.Format(_T("\r\n\r\n\r\n ����ǰ����RGB (%d,%d,%d)\r\n"),rValue,gValue,bValue);

	if(!m_bDraw&&!m_bFirstDraw)
	{
		strTemp=_T("\r\n ����������������ѡ���ȡ\r\n ��Χ\r\n\r\n ����ESC��������Ҽ��˳�");
	}
	else
		if(m_bDraw&&m_bFirstDraw)
		{
			strTemp=_T("\r\n ���ɿ�������ȷ����ȡ��Χ\r\n\r\n ����ESC���˳�");
		}
		else
			if(m_bFirstDraw)
			{
				strTemp=_T("\r\n ����������������ȡ��Χ��\r\n ��С��λ��\r\n\r\n ����ȡ��Χ��˫����������\r\n ��ͼ�񣬽�������\r\n\r\n ���������Ҽ�����ѡ��");
			}
			string+=strTemp;
			//��ʾ���༩����,������ʾ����
			m_tipEdit.SetWindowText(string);
}

//��ʾ��ȡ������Ϣ
void CCatchScreenDlg::DrawMessage(CRect &inRect,CDC * pDC)
{
	//��ȡ���δ�С��Ϣ�������
	const int space=3;    
	//����������ɫ��С

	CPoint pt;
	CPen pen(PS_SOLID,1,RGB(147,147,147));

	//dc.SetTextColor(RGB(147,147,147));
	CFont font;
	CFont * pOldFont;
	font.CreatePointFont(90,_T("����"));
	pOldFont=pDC->SelectObject(&font);

	//�õ������Ⱥ͸߶�
	GetCursorPos(&pt);
	int OldBkMode;
	OldBkMode=pDC->SetBkMode(TRANSPARENT);

	TEXTMETRIC tm;
	int charHeight;
	CSize size;
	int	lineLength;
	pDC->GetTextMetrics(&tm);
	charHeight = tm.tmHeight+tm.tmExternalLeading;
	size=pDC->GetTextExtent(_T("����λ��  "),/*strlen*/wcslen(_T("����λ��  ")));
	lineLength=size.cx;

	//��ʼ������, �Ա�֤д����������
	CRect rect(pt.x+space,pt.y-charHeight*6-space,pt.x+lineLength+space,pt.y-space);

	//������ʱ����
	CRect rectTemp;
	//�����ε��������Եʱ��������ʹ�С
	if((pt.x+rect.Width())>=m_xScreen)
	{
		//�����Ϸ���ʾ���¾���
		rectTemp=rect;
		rectTemp.left=rect.left-rect.Width()-space*2;
		rectTemp.right=rect.right-rect.Width()-space*2;;
		rect=rectTemp;
	}

	if((pt.y-rect.Height())<=0)
	{
		//�����ҷ���ʾ���¾���
		rectTemp=rect;
		rectTemp.top=rect.top+rect.Height()+space*2;;
		rectTemp.bottom=rect.bottom+rect.Height()+space*2;;
		rect=rectTemp;

	}

	//�����ջ�ˢ������
	CBrush * pOldBrush;
	pOldBrush=pDC->SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)));

	pDC->Rectangle(rect);
	rect.top+=2;
	//�ھ�������ʾ����
	CRect outRect(rect.left,rect.top,rect.left+lineLength,rect.top+charHeight);
	CString string(_T("����λ��"));
	pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight,rect.left+lineLength,charHeight+rect.top+charHeight);
	string.Format(_T("(%d,%d)"),inRect.left,inRect.top);
	pDC->DrawText(string,outRect,DT_CENTER);


	outRect.SetRect(rect.left,rect.top+charHeight*2,rect.left+lineLength,charHeight+rect.top+charHeight*2);
	string=_T("���δ�С");
	pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight*3,rect.left+lineLength,charHeight+rect.top+charHeight*3);
	string.Format(_T("(%d,%d)"),inRect.Width(),inRect.Height());
	pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight*4,rect.left+lineLength,charHeight+rect.top+charHeight*4);
	string=_T("�������");
	pDC->DrawText(string,outRect,DT_CENTER);

	outRect.SetRect(rect.left,rect.top+charHeight*5,rect.left+lineLength,charHeight+rect.top+charHeight*5);
	string.Format(_T("(%d,%d)"),pt.x,pt.y);
	pDC->DrawText(string,outRect,DT_CENTER);

	pDC->SetBkMode(OldBkMode);
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldBrush);

	/*g_StartPortStr.Format(_T("%d , %d"),inRect.left,inRect.top);
	g_EndPortStr.Format(_T("%d , %d"),inRect.right-m_rectTracker,inRect.bottom);
	g_SizePicStr.Format(_T("%d , %d"),inRect.Width(),inRect.Height());*/
}
//�ػ�����
void CCatchScreenDlg::PaintWindow()
{
	//��ȡ��ȫ���Ի��򴰿ڴ�С
	CRect rect1;
	GetWindowRect(rect1);

	//��ȡ�༭�򴰿ڴ�С
	CRect rect2;
	//m_tipEdit.GetWindowRect(rect2);

	CRgn rgn1,rgn2;
	rgn1.CreateRectRgnIndirect(rect1);
	//rgn2.CreateRectRgnIndirect(rect2);

	//��ȡ��������,���ǳ��˱༭�򴰿ڲ�����
	//m_rgn.CombineRgn(&rgn1,&rgn2,RGN_DIFF);

	InvalidateRgn(&rgn1);
}
//�ı������ʾ���ڵ�RGBֵ
void CCatchScreenDlg::ChangeRGB()
{
	CPoint pt;
	GetCursorPos(&pt);

	//������ǰR,G,B,������ֵ
	COLORREF color;
	CClientDC dc(this);
	color=dc.GetPixel(pt);
	BYTE rValue,gValue,bValue;
	rValue=GetRValue(color);
	gValue=GetGValue(color);
	bValue=GetGValue(color);

	//����ʽ�ŷ��ַ���
	CString string;
	string.Format(_T("(%d,%d,%d)"),rValue,gValue,bValue);
	//�����ǰ��ɫû����ˢ��RGBֵ,���ⴰ���и�����˸
	if(strOld!=string)
	{
		//�õ�RGB�ı���һ�е��ı�����
		int LineLength=m_tipEdit.LineLength(6);
		//��ѡRGBֵ�ı�,Ҳ����(255,255,255)��ʽ
		m_tipEdit.SetSel(20,LineLength+6);

		//�滻RGB����
		m_tipEdit.ReplaceSel(string);
	}

	strOld=string;

}

//*******************************************************************************************

BOOL CCatchScreenDlg::CreateBitmapInfoStruct(HBITMAP hBmp,PBITMAPINFO& pbmi)
{ 
	BITMAP bmp; 
	// Retrieve the bitmap color format, width, and height. 
	if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
	{
		return FALSE;
	}

	int width = ::GetSystemMetrics(SM_CXSCREEN);
	int height = ::GetSystemMetrics(SM_CYSCREEN);
	if(2*width<bmp.bmWidth||2*height<bmp.bmHeight)
	{
		//////��ʾ�����ʱ��������쳣������ʧ�ܣ�������
		return false;
	}

	pbmi = (PBITMAPINFO) LocalAlloc(LPTR,sizeof(BITMAPINFOHEADER)); 

	// Initialize the fields in the BITMAPINFO structure. 

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	pbmi->bmiHeader.biWidth = bmp.bmWidth; 
	pbmi->bmiHeader.biHeight = bmp.bmHeight; 
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
	pbmi->bmiHeader.biBitCount = /*bmp.bmBitsPixel*/24; 

	// If the bitmap is not compressed, set the BI_RGB flag. 
	pbmi->bmiHeader.biCompression = BI_RGB; 

	// Compute the number of bytes in the array of color 
	// indices and store the result in biSizeImage. 
	// For Windows NT, the width must be DWORD aligned unless 
	// the bitmap is RLE compressed. This example shows this. 
	// For Windows 95/98/Me, the width must be WORD aligned unless the 
	// bitmap is RLE compressed.
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * 24 +31) & ~31) /8
		* pbmi->bmiHeader.biHeight; 
	// Set biClrImportant to 0, indicating that all of the 
	// device colors are important. 
	pbmi->bmiHeader.biClrImportant = 0; 
	return TRUE; 
} 

BOOL CCatchScreenDlg::CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC) 
{ 
	HANDLE hf;                 // file handle 
	BITMAPFILEHEADER hdr;       // bitmap file-header 
	PBITMAPINFOHEADER pbih;     // bitmap info-header 
	LPBYTE lpBits;              // memory pointer 
	DWORD dwTotal;              // total count of bytes 
	DWORD cb;                   // incremental count of bytes 
	BYTE *hp;                   // byte pointer 
	DWORD dwTmp; 

	pbih = (PBITMAPINFOHEADER) pbi; 
	lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits) 
		return FALSE;

	// Retrieve the color table (RGBQUAD array) and the bits 
	// (array of palette indices) from the DIB. 
	if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, 
		DIB_RGB_COLORS)) 
	{
		return FALSE;
	}

	// Create the .BMP file. 
	hf = CreateFile(pszFile, 
		GENERIC_READ | GENERIC_WRITE, 
		(DWORD) 0, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		(HANDLE) NULL); 
	if (hf == INVALID_HANDLE_VALUE) 
		return FALSE;
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
	// Compute the size of the entire file. 
	hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof(RGBQUAD) + pbih->biSizeImage); 
	hdr.bfReserved1 = 0; 
	hdr.bfReserved2 = 0; 

	// Compute the offset to the array of color indices. 
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
		pbih->biSize + pbih->biClrUsed 
		* sizeof (RGBQUAD); 

	// Copy the BITMAPFILEHEADER into the .BMP file. 
	if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
		(LPDWORD) &dwTmp,  NULL)) 
	{
		return FALSE;
	}

	// Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
	if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
		+ pbih->biClrUsed * sizeof (RGBQUAD), 
		(LPDWORD) &dwTmp, ( NULL))) 
		return FALSE;

	// Copy the array of color indices into the .BMP file. 
	dwTotal = cb = pbih->biSizeImage; 
	hp = lpBits; 
	if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) 
		return FALSE;
	// Close the .BMP file. 
	if (!CloseHandle(hf)) 
		return FALSE;

	// Free memory. 
	GlobalFree((HGLOBAL)lpBits);

	return TRUE;
}


void CCatchScreenDlg::OnClickSaveBmp()
{
	// TODO: �ڴ���������������
	SYSTEMTIME time;
	::GetLocalTime(&time);
	CString lpTime=_T("");
	if(time.wMinute<10&&time.wSecond<10)
		lpTime.Format(_T("TC��ͼ%d%d%d%d%0d%0d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	else if(time.wMinute<10)
		lpTime.Format(_T("TC��ͼ%d%d%d%d%0d%d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	else if(time.wSecond<10)
		lpTime.Format(_T("TC��ͼ%d%d%d%d%d%0d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	else
		lpTime.Format(_T("TC��ͼ%d%d%d%d%d%d"),time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);

	TCHAR fileBuffer[256]={_T("TC")};
	::memset(fileBuffer,0,256*sizeof(TCHAR));
	::memcpy(fileBuffer,lpTime.LockBuffer(),lpTime.GetLength()*sizeof(TCHAR));

	TCHAR OldPath[MAX_PATH]={0};
	::GetCurrentDirectoryW(MAX_PATH,OldPath);

	CFileDialog PathDlg(FALSE, _T("*.bmp"), fileBuffer, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Save File(*.bmp)|*.bmp||"));

	PathDlg.m_ofn.lpstrDefExt=_T("bmp");

	HBITMAP tbmp;

	if(PathDlg.DoModal()==IDOK)
	{
		if(m_rectTracker.m_rect.left>m_rectTracker.m_rect.right)
		{
			int left = m_rectTracker.m_rect.left;
			int top = m_rectTracker.m_rect.top;
			m_rectTracker.m_rect.left = m_rectTracker.m_rect.right;
			m_rectTracker.m_rect.top  = m_rectTracker.m_rect.bottom;
			m_rectTracker.m_rect.right = left;
			m_rectTracker.m_rect.bottom = top;
		}
		if(m_rectTracker.m_rect.top>m_rectTracker.m_rect.bottom)
		{
			int bottom = m_rectTracker.m_rect.bottom;
			int top = m_rectTracker.m_rect.top;
			m_rectTracker.m_rect.top = bottom;
			m_rectTracker.m_rect.bottom = top;
		}
		tbmp=CopyScreenToBitmap(m_rectTracker.m_rect,TRUE);

		if(tbmp==NULL)
		{
			this->OnOK();
			/*::AfxMessageBox(_T("ͼƬδ���棡"));*/
		}

		g_HbitMap = tbmp;

		PBITMAPINFO pbmp;
		if(!CreateBitmapInfoStruct(tbmp, pbmp))
		{
			return;
		}

		g_PicPathStr = PathDlg.GetPathName();

		if(!CreateBMPFile(g_PicPathStr.LockBuffer(), pbmp, tbmp, GetDC()->GetSafeHdc()))
		{
			//::AfxMessageBox(_T("λͼ����ʧ��!"));
			this->OnOK();
			return ;
		}

		g_StartPortStr.Format(_T("%d , %d"),m_rectTracker.m_rect.left,m_rectTracker.m_rect.top);
		g_EndPortStr.Format(_T("%d , %d"),m_rectTracker.m_rect.right-1,m_rectTracker.m_rect.bottom-1);
		g_SizePicStr.Format(_T("%d , %d"),m_rectTracker.m_rect.Width()-1,m_rectTracker.m_rect.Height()-1);

		::SetCurrentDirectoryW(OldPath);

		this->OnOK();
	}
	else
	{
		this->OnOK();
		::SetCurrentDirectoryW(OldPath);
	}
}

void CCatchScreenDlg::OnExitCatchScreen()
{
	// TODO: �ڴ���������������
	//�رճ���
	//PostQuitMessage(1);
	this->OnCancel();
}


void CCatchScreenDlg::OnAbmakepin()
{
	// TODO: �ڴ���������������
	if(m_rectTracker.m_rect.left>m_rectTracker.m_rect.right)
	{
		int left = m_rectTracker.m_rect.left;
		int top = m_rectTracker.m_rect.top;
		m_rectTracker.m_rect.left = m_rectTracker.m_rect.right;
		m_rectTracker.m_rect.top  = m_rectTracker.m_rect.bottom;
		m_rectTracker.m_rect.right = left;
		m_rectTracker.m_rect.bottom = top;
	}
	if(m_rectTracker.m_rect.top>m_rectTracker.m_rect.bottom)
	{
		int bottom = m_rectTracker.m_rect.bottom;
		int top = m_rectTracker.m_rect.top;
		m_rectTracker.m_rect.top = bottom;
		m_rectTracker.m_rect.bottom = top;
	}
	HBITMAP tbmp;
	CRect m_Rect/* = m_rectTracker.m_rect*/;
	m_Rect.SetRect(m_rectTracker.m_rect.left+2,m_rectTracker.m_rect.top+2,m_rectTracker.m_rect.right-2,m_rectTracker.m_rect.bottom-2);
	this->ClientToScreen(&m_Rect);

	tbmp=CopyRectToBitmap(m_Rect);
	if(tbmp==NULL)
	{
		this->OnOK();
		::DeleteObject(tbmp);
		return ;
	}

	PBITMAPINFO pbmp;
	if(!CreateBitmapInfoStruct(tbmp, pbmp))
	{
		this->OnOK();
		::DeleteObject(tbmp);
		return;
	}

	::Sleep(500);

	bool IsSaveOK = true;
	HDC hdc = ::GetDC(NULL);
	CString pathStr = g_CurrentExePath+_T("tctemp.bmp");
	if(!CreateBMPFile(pathStr.LockBuffer(), pbmp, tbmp, hdc))
	{
		IsSaveOK = false;
	}

	this->OnOK();

	if(IsSaveOK)
	{
		//if(g_DrawPicture.IsWindowVisible())
		//{
		//	//::AfxMessageBox(_T("copyλͼ����ͼ����"));
		//	g_DrawPicture.Loadbmp(pathStr);
		//}
		//else
		//{
		//	g_PicCheck.SetCheck(BST_CHECKED);
		//	g_DrawPicture.ShowWindow(TRUE);
		//	g_DrawPicture.Loadbmp(pathStr);
		//}

		theApp.pPropSheet->activeCurrentPage(5);
		theApp.pPropSheet->m_DrawPicWnd.Loadbmp(pathStr);
	}

	::ReleaseDC(NULL,hdc);
	::DeleteObject(tbmp);
}


void CCatchScreenDlg::OnSysmakepic()
{
	// TODO: �ڴ���������������
	this->OnOK();
	if(m_rectTracker.m_rect.left>m_rectTracker.m_rect.right)
	{
		int left = m_rectTracker.m_rect.left;
		int top = m_rectTracker.m_rect.top;
		m_rectTracker.m_rect.left = m_rectTracker.m_rect.right;
		m_rectTracker.m_rect.top  = m_rectTracker.m_rect.bottom;
		m_rectTracker.m_rect.right = left;
		m_rectTracker.m_rect.bottom = top;
	}
	
	if(m_rectTracker.m_rect.top>m_rectTracker.m_rect.bottom)
	{
		int bottom = m_rectTracker.m_rect.bottom;
		int top = m_rectTracker.m_rect.top;
		m_rectTracker.m_rect.top = bottom;
		m_rectTracker.m_rect.bottom = top;
	}
	HBITMAP tbmp;
	CRect m_Rect = m_rectTracker.m_rect;
	this->ClientToScreen(&m_Rect);

	tbmp=CopyRectToBitmap(m_Rect);
	if(tbmp==NULL)
	{
		::DeleteObject(tbmp);
		return ;
	}

	PBITMAPINFO pbmp;
	if(!CreateBitmapInfoStruct(tbmp, pbmp))
	{
		::DeleteObject(tbmp);
		return;
	}
	bool IsSaveOK = true;
	HDC hdc = ::GetDC(NULL);
	CString pathStr = g_CurrentExePath+_T("tctemp.bmp");
	if(!CreateBMPFile(pathStr.LockBuffer(), pbmp, tbmp, hdc))
	{
		IsSaveOK = false;
	}

	if(IsSaveOK)
	{
		char path[MAX_PATH]={0};
		USES_CONVERSION;
		::strcat(path,"mspaint.exe ");
		::strcat(path,W2A(pathStr.LockBuffer()));
		::WinExec(path,SW_SHOWNORMAL);
	}

	::ReleaseDC(NULL,hdc);
	::DeleteObject(tbmp);
}
