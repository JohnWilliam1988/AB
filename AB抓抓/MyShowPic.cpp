// MyShowPic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ABץץ.h"
#include "MyShowPic.h"
#include "afxdialogex.h"
#include <WindowsX.h>
//#include "MyPicFullScreenShow.h"

//////////////////////////////���õ�ȫ�ֱ���///
//extern  CMyDrawPictureClass	g_DrawPicture;
extern  HWND				g_ProcessPicInfoHWND;
extern  CButton				g_PicCheck;
extern	HBITMAP				g_HbitMap;
extern	CMenu				g_MenuLeftMouseUp;
extern	CMenu				g_MenuRightMouseUp;
extern	CMyPicFullScreenShow g_fullScreenDlg;
extern	bool				g_IsFullScreen;
extern	 CString			g_CurrentExePath;
extern	CMyPickerColor		g_PickColorDlg;
// CMyShowPic �Ի���

IMPLEMENT_DYNAMIC(CMyShowPic, CDialogEx)

CMyShowPic::CMyShowPic(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyShowPic::IDD, pParent)
{
	/*g_MenuLeftMouseUp.LoadMenu(IDR_MENU_SAVEPIC);
	g_MenuRightMouseUp.LoadMenuW(IDR_MENU_RIGHTCLICK);
	g_fullScreenDlg.Create(IDD_DIALOG_FULLSCREENSHOW);*/
}

CMyShowPic::~CMyShowPic()
{
}

void CMyShowPic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC, m_PicShowControl);
}


BEGIN_MESSAGE_MAP(CMyShowPic, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_COMMAND(ID__32771, &CMyShowPic::OnClickSaveMenuBotton)
	ON_COMMAND(ID__AB32773, &CMyShowPic::OnClickShowFullScreenBotton)
	ON_COMMAND(ID_32774, &CMyShowPic::OnClickCallSystemMakePic)
	ON_COMMAND(ID_32775, &CMyShowPic::OnClickCallDefinePicBotton)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID__32787, &CMyShowPic::OnRightClickFullScreen)
	ON_COMMAND(ID__1, &CMyShowPic::OnAddColor1)
	ON_COMMAND(ID__32778, &CMyShowPic::OnAddColor2)
	ON_COMMAND(ID__32779, &CMyShowPic::OnAddColor3)
	ON_COMMAND(ID__32780, &CMyShowPic::OnAddColor4)
	ON_COMMAND(ID__32781, &CMyShowPic::OnAddColor5)
	ON_COMMAND(ID__32782, &CMyShowPic::OnAddColor6)
	ON_COMMAND(ID__32783, &CMyShowPic::OnAddColor7)
	ON_COMMAND(ID__32784, &CMyShowPic::OnAddColor8)
	ON_COMMAND(ID__32785, &CMyShowPic::OnAddColor9)
	ON_COMMAND(ID__32786, &CMyShowPic::OnAddColor10)
	ON_COMMAND(ID_32790, &CMyShowPic::OnRightClickCallDefineMakePic)
	ON_COMMAND(ID_32791, &CMyShowPic::OnRightClickCallSystemMakePic)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMyShowPic ��Ϣ�������
bool CMyShowPic::ShowBmp(CString path)
{
	USES_CONVERSION;
	FILE *fp=fopen(W2A(path),"r");

	if(fp==NULL)
	{
		return false;
	}

	BITMAPFILEHEADER fileheader={0};
	BITMAPINFO info;

	fread(&fileheader,sizeof(fileheader),1,fp);	
	if(fileheader.bfType!=0x4D42)
	{
		//::MessageBox(NULL,_T("��λͼ�ļ� ��ѡ��λͼ�ļ�)"),_T("����"),MB_OK);
		fclose(fp);
		return false;
	}

	fread(&info.bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	if(info.bmiHeader.biBitCount != 24)
	{
		//::MessageBox(NULL,_T("��ѡ��24λλͼ�ļ�)"),_T("����"),MB_OK);
		CString trm=_T("");
		trm.Format(_T("%d"),info.bmiHeader.biBitCount);
		CFile file;
		file.Open(_T("AbLog.txt"),CFile::modeCreate|CFile::modeReadWrite);
		file.Write(trm,trm.GetLength());
		file.Close();
		fclose(fp);
		return false;
	}
	long width=m_Width=info.bmiHeader.biWidth;
	long height=m_Height=info.bmiHeader.biHeight;

	fclose(fp);

	CRect rect;
	this->GetWindowRect(&rect);
	if(width<rect.Width())
	{
		SetScrollRange(SB_HORZ,0,0);
	}
	else
	{
		int H = (m_Width-rect.Width()) / 2 + PIC_OFFSET;		
		SetScrollRange(SB_HORZ,0,H);
		
	}
	if(height <rect.Height())
	{
		SetScrollRange(SB_VERT,0,0);		
	}
	else
	{
		int V = (m_Height-rect.Height()) / 2 + PIC_OFFSET;
		SetScrollRange(SB_VERT,0,V);
	}
	HBITMAP hbmp = (HBITMAP)LoadImage( AfxGetInstanceHandle(),path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	if(hbmp==NULL)
	{
		return false;
	}

	g_HbitMap = hbmp;
	m_PicShowControl.SetBitmap(hbmp);

	this->Invalidate();

	return true;
}
///////ˮƽ������//////
void CMyShowPic::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  

	switch (nSBCode)  
	{  
	case SB_LINELEFT:  
		scrollinfo.nPos -= 1;  
		if (scrollinfo.nPos < 0)
		{  
			scrollinfo.nPos = scrollinfo.nMin;  
			return;
			break;  
		}  
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
		ScrollWindow(2,0);  
		break;  
	case SB_LINERIGHT:  
		scrollinfo.nPos += 1;  
		if (scrollinfo.nPos > scrollinfo.nMax)  
		{  
			scrollinfo.nPos = scrollinfo.nMax;  
			return;
			break;  
		}  
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
		ScrollWindow(-2,0);  
		break;  
	case SB_THUMBPOSITION:  
		break;  
	case SB_THUMBTRACK:  
		ScrollWindow((scrollinfo.nPos-nPos)*2,0);  
		scrollinfo.nPos = nPos;  
		SetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);  
		break;  
	case SB_ENDSCROLL:
		break;  
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
///////��ֱ������//////
void CMyShowPic::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
	switch (nSBCode)  
	{
	case SB_TOP:
		break;
	case SB_LINEUP:  
		scrollinfo.nPos -= 1;  
		if (scrollinfo.nPos<0)
		{  
			scrollinfo.nPos = scrollinfo.nMin;  
			//break;  
			return ;
		}  
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		ScrollWindow(0,2);  
		break;  
	case SB_LINEDOWN:  
		scrollinfo.nPos += 1;  
		if (scrollinfo.nPos>scrollinfo.nMax)  
		{  
			scrollinfo.nPos = scrollinfo.nMax; 
			return ;
			break;  
		}  
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		ScrollWindow(0,-2);  
		break;   
	case SB_ENDSCROLL:  
		break;  
	case SB_THUMBPOSITION:  
		break;  
	case SB_THUMBTRACK:  
		ScrollWindow(0,(scrollinfo.nPos-nPos)*2);  
		scrollinfo.nPos = nPos;  
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);  
		break;  
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CMyShowPic::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_StartPos = point;
	m_EndPos = point;

	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
	point.y = point.y + scrollinfo.nPos + scrollinfo.nTrackPos;
	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
	point.x = point.x + scrollinfo.nPos + scrollinfo.nTrackPos;	
	m_SizePos = point;
	m_MouseClickDown = true;
	this->InvalidateRect(&m_Rect);
	CRect rect;
	this->GetWindowRect(&rect);
	int left = rect.left;
	int top  = rect.top;

	int wndWidth = rect.Width();
	int wndHeight = rect.Height();

	if(point.x<m_Width&&point.y<m_Height)
		ClipCursor(&CRect(left,top,left+this->m_Width,top+this->m_Height));  //// �������ֻ����ͼƬ��С��Χ��
	/*CPoint tPoint = point;
	SCROLLINFO scrollinfo;
	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
	tPoint.y = tPoint.y + scrollinfo.nPos + scrollinfo.nTrackPos;
	GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
	tPoint.x = tPoint.x + scrollinfo.nPos + scrollinfo.nTrackPos;*/
	CString strPoint;
	strPoint.Format(_T("%d,%d"),point.x,point.y);
	COPYDATASTRUCT cds = { 0, ((DWORD)wcslen(strPoint) + 1) * sizeof(TCHAR), (PVOID)(strPoint.LockBuffer()) };
    FORWARD_WM_COPYDATA(g_ProcessPicInfoHWND, NULL, &cds, ::SendMessage);

	CDialogEx::OnLButtonDown(nFlags, point);   
}

void CMyShowPic::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_MouseClickDown&&point.x<this->m_Width&&point.y<this->m_Height)
	{
		CPoint tPoint = point;
		SCROLLINFO scrollinfo;
		GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL);
		tPoint.y = tPoint.y + scrollinfo.nPos + scrollinfo.nTrackPos;
		GetScrollInfo(SB_HORZ,&scrollinfo,SIF_ALL);
		tPoint.x = tPoint.x + scrollinfo.nPos + scrollinfo.nTrackPos;

		CString strPoint;
		strPoint.Format(_T("%d,%d"),tPoint.x,tPoint.y);
		COPYDATASTRUCT cds = { 1, ((DWORD)wcslen(strPoint) + 1) * sizeof(TCHAR), (PVOID)(strPoint.LockBuffer()) };
		FORWARD_WM_COPYDATA(g_ProcessPicInfoHWND, NULL, &cds, ::SendMessage);

		CString sizeStr;
		sizeStr.Format(_T("%d,%d"),::abs(tPoint.x-m_SizePos.x),abs(tPoint.y-m_SizePos.y));
		COPYDATASTRUCT cds2 = { 2, ((DWORD)wcslen(sizeStr) + 1) * sizeof(TCHAR), (PVOID)(sizeStr.LockBuffer()) };
		FORWARD_WM_COPYDATA(g_ProcessPicInfoHWND, NULL, &cds2, ::SendMessage);

		CClientDC dc(this);
		CPen* pOldPen = NULL;
		CBrush* pOldBrush = NULL;

		HPEN hpen = ::CreatePen(PS_DOT,1,RGB(255,0,0));
		pOldPen = dc.SelectObject(CPen::FromHandle(hpen));
		pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);

		dc.SetROP2(R2_NOTXORPEN);  //��Ļ����ɫ�����ʵ���ɫȡ��ɫ�����»��������Ͼ�ͼ,�൱��ɾ����ͼ�Ρ�
		dc.Rectangle(m_StartPos.x,m_StartPos.y,m_EndPos.x,m_EndPos.y);
		dc.Rectangle(m_StartPos.x,m_StartPos.y,point.x,point.y);

		if (pOldPen != NULL)
			dc.SelectObject(pOldPen);
		if (pOldBrush != NULL)
			dc.SelectObject(pOldBrush);
		DeleteObject(hpen); 

		m_Rect.SetRect(m_StartPos,point);
	}
	m_EndPos=point;
	CDialogEx::OnMouseMove(nFlags, point);
}

void CMyShowPic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC dc(this);
	CPen* pOldPen = NULL;
	CBrush* pOldBrush = NULL;
	if(m_MouseClickDown)
	{
		HPEN hpen = ::CreatePen(PS_DOT,1,RGB(255,0,0));
		pOldPen = dc.SelectObject(CPen::FromHandle(hpen));
		pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);

		dc.SetROP2(R2_NOTXORPEN);  //
		dc.Rectangle(m_StartPos.x,m_StartPos.y,m_EndPos.x,m_EndPos.y);//�������һ������ƶ����ľ��Ρ�
		dc.Rectangle(m_StartPos.x,m_StartPos.y,point.x,point.y);      // ���ػ��µľ���
		if (pOldPen != NULL)
			dc.SelectObject(pOldPen);
		if (pOldBrush != NULL)
			dc.SelectObject(pOldBrush);
		DeleteObject(hpen); 
	
		m_MouseClickDown = false;

		ClipCursor(NULL);       ////�ͷ����

		if(point.x<m_StartPos.x)
			m_Rect.SetRect(point,m_StartPos);
		else
			m_Rect.SetRect(m_StartPos,point);

		dc.SetROP2(R2_NOTXORPEN);  //
		dc.Rectangle(m_StartPos.x,m_StartPos.y,m_EndPos.x,m_EndPos.y);//�������һ������ƶ����ľ��Ρ�

		/////////////�����Զ���˵�////////////////
		POINT   pt;   
		GetCursorPos(&pt);
		if(m_StartPos!=point)
		{
			if(m_Rect.Height()<3 ||m_Rect.Width()<3)
			{
				g_MenuLeftMouseUp.GetSubMenu(0)->EnableMenuItem(0,0);
				g_MenuLeftMouseUp.GetSubMenu(0)->EnableMenuItem(1,0);
			}
			g_MenuLeftMouseUp.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
		}
		this->Invalidate();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}

BOOL CMyShowPic::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_MouseClickDown = false;
	m_Rect.SetRect(-1,-2,-3,-4);

	////  �������������Ҽ��Լ�ȫ��ʱ�Ĳ˵���Դ/////////
	g_MenuLeftMouseUp.LoadMenu(IDR_MENU_SAVEPIC);
	g_MenuRightMouseUp.LoadMenuW(IDR_MENU_RIGHTCLICK);
	g_fullScreenDlg.Create(IDD_DIALOG_FULLSCREENSHOW);

	//LoadClipboardBMP();

	/////�˶�ʱ�������ڼ���������Print Screen��/////
	this->SetTimer(101,600,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMyShowPic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	//if(m_MouseClickDown)
	//{	
	//	CDC * pDC = &dc;
	//	CPen* pOldPen = NULL;
	//	CBrush* pOldBrush = NULL;
	//	HPEN hpen = ::CreatePen(PS_DOT,1,RGB(255,0,0));
	//	pOldPen = pDC->SelectObject(CPen::FromHandle(hpen));
	//	pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	//	int nOldROP = pDC->SetROP2(R2_COPYPEN);
	//	m_Rect.InflateRect(+1, +1);   // borders are one pixel outside
	//	pDC->Rectangle(m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	//	pDC->SetROP2(nOldROP);

	//	if (pOldPen != NULL)
	//		pDC->SelectObject(pOldPen);
	//	if (pOldBrush != NULL)
	//		pDC->SelectObject(pOldBrush);
	//	DeleteObject(hpen); 
	//}
	//*************************************************************************
	//LoadClipboardBMP();
	CDialog::OnPaint();
}

void CMyShowPic::SaveBmpFile(CRect lpRect,CString path)
{
	// ��Ļ���ڴ��豸������
	HDC hScrDC, hMemDC;      
	// λͼ���
	HBITMAP hBitmap,hOldBitmap;   
	// ѡ����������
	int       nX, nY, nX2, nY2;      
	// λͼ��Ⱥ͸߶� 
	int       nWidth, nHeight;      
	
	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
		return ;

	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX = lpRect.left;
	nY = lpRect.top;
	nX2 = lpRect.right;
	nY2 = lpRect.bottom;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;

	POINT point;
	point.x = nX;
	point.y = nY;
	::ScreenToClient(m_hWnd,&point);

	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	CClientDC ddc(this);
	BitBlt(hMemDC,0,0, nWidth,nHeight,/*hScrDC, nX, nY,*/ ddc.GetSafeHdc(),point.x,point.y,CAPTUREBLT|SRCCOPY);
	//�õ���Ļλͼ�ľ��
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);

		// 24λͼ��BITMAPINFO
    BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
    memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
    BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
    pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
    pInfo_Header->biWidth = nWidth;   
    pInfo_Header->biHeight = nHeight;   
    pInfo_Header->biPlanes = 1;   
    pInfo_Header->biBitCount = 24;   
    pInfo_Header->biCompression = BI_RGB;

	 // �������buf
    DWORD bufSize = (pInfo_Header->biWidth * 3 + 3) / 4 * 4 * pInfo_Header->biHeight;
    BYTE * pBuffer = new BYTE[bufSize];

	int aHeight=pInfo_Header->biHeight;

    if(::GetDIBits(hMemDC, hBitmap, 0, aHeight, pBuffer,pBITMAPINFO, DIB_RGB_COLORS) == 0)
    {
       return ;
    }

	//���浽�ļ�������λͼ�ṹ
	BITMAPFILEHEADER bmfh;
	ZeroMemory(&bmfh,sizeof(BITMAPFILEHEADER));

	*((char*)&bmfh.bfType) = 'B';
	*(((char*)&bmfh.bfType) + 1) = 'M';

	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + (m_Width * m_Height) * pInfo_Header->biBitCount / 8;
	CFile file;
	if(file.Open(path.LockBuffer(),CFile::modeWrite|CFile::modeCreate))
	{
		file.Write(&bmfh,sizeof(BITMAPFILEHEADER));
		file.Write(&(pBITMAPINFO->bmiHeader),sizeof(BITMAPINFOHEADER));
		file.Write(pBuffer,bufSize);
		file.Close();
	}

	//��� 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	::DeleteObject(hBitmap);
}
void CMyShowPic::SaveBmpFile(HBITMAP hBitmap,CString path)
{
	// ��Ļ���ڴ��豸������
	HDC hScrDC, hMemDC;      
	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ����λͼѡ���ڴ��豸��������
	::SelectObject(hMemDC,hBitmap);
	BITMAP bitmap;
	::GetObjectW(hBitmap,sizeof(BITMAP),&bitmap);
	// 24λͼ��BITMAPINFO
    BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
    memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
    BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
    pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
	pInfo_Header->biWidth = bitmap.bmWidth;   
	pInfo_Header->biHeight = bitmap.bmHeight;   
    pInfo_Header->biPlanes = 1;   
    pInfo_Header->biBitCount = 24;   
    pInfo_Header->biCompression = BI_RGB;

	 // �������buf
    DWORD bufSize = (pInfo_Header->biWidth * 3 + 3) / 4 * 4 * pInfo_Header->biHeight;
    BYTE * pBuffer = new BYTE[bufSize];

	int aHeight=pInfo_Header->biHeight;

    if(::GetDIBits(hMemDC, hBitmap, 0, aHeight, pBuffer,pBITMAPINFO, DIB_RGB_COLORS) == 0)
    {
       return ;
    }

	//���浽�ļ�������λͼ�ṹ
	BITMAPFILEHEADER bmfh;
	ZeroMemory(&bmfh,sizeof(BITMAPFILEHEADER));

	*((char*)&bmfh.bfType) = 'B';
	*(((char*)&bmfh.bfType) + 1) = 'M';

	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmfh.bfSize = bmfh.bfOffBits + (m_Width * m_Height) * pInfo_Header->biBitCount / 8;
	CFile file;
	if(file.Open(path.LockBuffer(),CFile::modeWrite|CFile::modeCreate))
	{
		file.Write(&bmfh,sizeof(BITMAPFILEHEADER));
		//file.Write(&(pBITMAPINFO->bmiHeader),sizeof(BITMAPINFOHEADER));
		file.Write(pInfo_Header,sizeof(BITMAPINFOHEADER));
		file.Write(pBuffer,bufSize);
		file.Close();
	}

	//��� 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	//::DeleteObject(hBitmap);
}

HBITMAP CMyShowPic::CopyRectToBitmap(LPRECT lpRect)
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
//*******************************************************************************************

BOOL CMyShowPic::CreateBitmapInfoStruct(HBITMAP hBmp,PBITMAPINFO& pbmi)
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

BOOL CMyShowPic::CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi,HBITMAP hBMP, HDC hDC) 
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
////////////////////////////////////////////////////////
/////
/////             �����������˵��Ĵ���
/////
////////////////////////////////////////////////////////
///////////////////�˵��еı���λͼ���� ///////////////////
void CMyShowPic::OnClickSaveMenuBotton()
{
	// TODO: �ڴ���������������
	this->UpdateData();
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

	////////////////////////////////////////////////////////////////////////
	CRect helpRect = m_Rect;
	HBITMAP tbmp;
	this->ClientToScreen(&helpRect);
	int off = 1;
	helpRect.left = helpRect.left+off;
	helpRect.top = helpRect.top+off;
	helpRect.right = helpRect.right-off;
	helpRect.bottom = helpRect.bottom-off;

	tbmp=CopyRectToBitmap(helpRect);
	if(tbmp==NULL)
	{
		//::AfxMessageBox(_T("��Ļλͼʧ��!"));
		::DeleteObject(tbmp);
		return;
	}

	PBITMAPINFO pbmp;
	if(!CreateBitmapInfoStruct(tbmp, pbmp))
	{
		//::AfxMessageBox(_T("λͼ����ʧ��!"));
		::DeleteObject(tbmp);
		return;
	}
	//////////////////////////////////////////////////////////////////////////////

	CFileDialog PathDlg(FALSE, _T("*.bmp"), fileBuffer, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Save File(*.bmp)|*.bmp||"));

	PathDlg.m_ofn.lpstrDefExt=_T("bmp");
	CString pathStr=_T("");	

	if(PathDlg.DoModal()==IDOK)
	{		
		pathStr = PathDlg.GetPathName();
		HDC hdc = ::GetDC(NULL);
		if(!CreateBMPFile(pathStr.LockBuffer(), pbmp, tbmp,hdc))
		{
			//::AfxMessageBox(_T("λͼ����ʧ��!"));
		}
		::ReleaseDC(NULL,hdc);		
	}
	::DeleteObject(tbmp);
	::SetCurrentDirectoryW(OldPath);
	this->InvalidateRect(&m_Rect);
}

///////////////////�˵��е�ȫ����ʾ���� ///////////////////
void CMyShowPic::OnClickShowFullScreenBotton()
{
	// TODO: �ڴ���������������	
	g_fullScreenDlg.ShowWindow(TRUE);
	g_fullScreenDlg.paintWindow();
	g_IsFullScreen = true;
	(g_MenuLeftMouseUp.GetSubMenu(0))->CheckMenuItem(ID__AB32773,MF_CHECKED | MF_BYCOMMAND);
}

///////////////////�˵��е�ϵͳ����༭���� ///////////////////
void CMyShowPic::OnClickCallSystemMakePic()
{
	// TODO: �ڴ���������������
	HBITMAP tbmp;
	this->ClientToScreen(&m_Rect);
	int off = 1;
	m_Rect.left = m_Rect.left+off;
	m_Rect.top = m_Rect.top+off;
	m_Rect.right = m_Rect.right-off;
	m_Rect.bottom = m_Rect.bottom-off;
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

///////////////////�˵��е��Զ�����ͼ�༭���� ///////////////////
void CMyShowPic::OnClickCallDefinePicBotton()
{
	// TODO: �ڴ���������������
	HBITMAP tbmp;
	this->ClientToScreen(&m_Rect);
	int off = 1;
	m_Rect.left = m_Rect.left+off;
	m_Rect.top = m_Rect.top+off;
	m_Rect.right = m_Rect.right-off;
	m_Rect.bottom = m_Rect.bottom-off;
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

////////////////////////////////////////////////////////
/////
/////             ����Ҽ������˵��Ĵ���
/////
////////////////////////////////////////////////////////
////////////////��������Ҽ�ʱ���������˵�//////////////////////
void CMyShowPic::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint pt = point;
	m_RightPos.x=point.x;
	m_RightPos.y=point.y;

	ClientToScreen(&pt);
	g_MenuRightMouseUp.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);

	CDialogEx::OnRButtonUp(nFlags, point);
}

void CMyShowPic::OnRightClickFullScreen()
{
	// TODO: �ڴ���������������
	g_fullScreenDlg.ShowWindow(TRUE);
	g_fullScreenDlg.paintWindow();
	g_IsFullScreen = true;
	(g_MenuRightMouseUp.GetSubMenu(0))->CheckMenuItem(ID__32787,MF_CHECKED | MF_BYCOMMAND);
}


void CMyShowPic::OnAddColor1()
{
	// TODO: �ڴ���������������
	CPoint pt;
	pt.x=m_RightPos.x;
	pt.y=m_RightPos.y;
	ClientToScreen(&pt);
	g_PickColorDlg.RightClickPickColor(1,pt,m_RightPos);
}


void CMyShowPic::OnAddColor2()
{
	// TODO: �ڴ���������������
	CPoint pt;
	pt.x=m_RightPos.x;
	pt.y=m_RightPos.y;
	ClientToScreen(&pt);
	g_PickColorDlg.RightClickPickColor(2,pt,m_RightPos);
}


void CMyShowPic::OnAddColor3()
{
	// TODO: �ڴ���������������
	CPoint pt;
	pt.x=m_RightPos.x;
	pt.y=m_RightPos.y;
	ClientToScreen(&pt);
	g_PickColorDlg.RightClickPickColor(3,pt,m_RightPos);
}


void CMyShowPic::OnAddColor4()
{
	// TODO: �ڴ���������������
	CPoint pt;
	pt.x=m_RightPos.x;
	pt.y=m_RightPos.y;
	ClientToScreen(&pt);
	g_PickColorDlg.RightClickPickColor(4,pt,m_RightPos);
}


void CMyShowPic::OnAddColor5()
{
	// TODO: �ڴ���������������
	CPoint pt;
	pt.x=m_RightPos.x;
	pt.y=m_RightPos.y;
	ClientToScreen(&pt);
	g_PickColorDlg.RightClickPickColor(5,pt,m_RightPos);
}


void CMyShowPic::OnAddColor6()
{
	// TODO: �ڴ���������������
	CPoint pt;
	pt.x=m_RightPos.x;
	pt.y=m_RightPos.y;
	ClientToScreen(&pt);
	g_PickColorDlg.RightClickPickColor(6,pt,m_RightPos);
}


void CMyShowPic::OnAddColor7()
{
	// TODO: �ڴ���������������
	CPoint pt;
	pt.x=m_RightPos.x;
	pt.y=m_RightPos.y;
	ClientToScreen(&pt);
	g_PickColorDlg.RightClickPickColor(7,pt,m_RightPos);
}


void CMyShowPic::OnAddColor8()
{
	// TODO: �ڴ���������������
	CPoint pt;
	pt.x=m_RightPos.x;
	pt.y=m_RightPos.y;
	ClientToScreen(&pt);
	g_PickColorDlg.RightClickPickColor(8,pt,m_RightPos);
}


void CMyShowPic::OnAddColor9()
{
	// TODO: �ڴ���������������
	CPoint pt;
	pt.x=m_RightPos.x;
	pt.y=m_RightPos.y;
	ClientToScreen(&pt);
	g_PickColorDlg.RightClickPickColor(9,pt,m_RightPos);
}


void CMyShowPic::OnAddColor10()
{
	// TODO: �ڴ���������������
	CPoint pt;
	pt.x=m_RightPos.x;
	pt.y=m_RightPos.y;
	ClientToScreen(&pt);
	g_PickColorDlg.RightClickPickColor(10,pt,m_RightPos);
}


void CMyShowPic::OnRightClickCallDefineMakePic()
{
	// TODO: �ڴ���������������
	//OnClickCallDefinePicBotton();
	if(g_HbitMap)
	{
		HBITMAP tbmp=g_HbitMap;	

		PBITMAPINFO pbmp;
		if(!CreateBitmapInfoStruct(tbmp, pbmp))
		{
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
			theApp.pPropSheet->m_DrawPicWnd.Loadbmp(pathStr);
		}

		::ReleaseDC(NULL,hdc);
	}
}


void CMyShowPic::OnRightClickCallSystemMakePic()
{
	// TODO: �ڴ���������������
	if(g_HbitMap)
	{
		HBITMAP tbmp=g_HbitMap;	

		PBITMAPINFO pbmp;
		if(!CreateBitmapInfoStruct(tbmp, pbmp))
		{
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
	}
}

void CMyShowPic::LoadClipboardBMP()
{
	if(::OpenClipboard(NULL))
	{
		//Get   the   clipboard   data
		HBITMAP dhBmp = (HBITMAP)GetClipboardData(CF_BITMAP);	
		/*if(dhBmp==0)
			return;*/
		SaveBmpFile(dhBmp,g_CurrentExePath+ _T("abpic.bmp"));
		ShowBmp(g_CurrentExePath+ _T("abpic.bmp"));		
		CloseClipboard();
	}   
	return ;
}


void CMyShowPic::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case 101:
		if(0x8000 & GetAsyncKeyState(VK_SNAPSHOT))
		{
			////////////////�û����˼����ϵĽ�����////////////////////
			LoadClipboardBMP();
		}
		break;
	default:
		break;	
	}
	CDialogEx::OnTimer(nIDEvent);
}
