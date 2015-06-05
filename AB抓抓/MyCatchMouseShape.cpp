// MyCatchMouseShape.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ABץץ.h"
#include "MyCatchMouseShape.h"
#include "afxdialogex.h"


// ��ȡ�����ȼ���Դ
#define IDC_USERHOTKEY_MOUSESHAPE1                  WM_USER+121    
#define IDC_USERHOTKEY_MOUSESHAPE2                  WM_USER+122
#define IDC_USERHOTKEY_MOUSESHAPE3                  WM_USER+123

// CMyCatchMouseShape �Ի���

IMPLEMENT_DYNAMIC(CMyCatchMouseShape, CMFCPropertyPage)

CMyCatchMouseShape::CMyCatchMouseShape()
	: CMFCPropertyPage(CMyCatchMouseShape::IDD)
{

}

CMyCatchMouseShape::~CMyCatchMouseShape()
{
}

void CMyCatchMouseShape::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SHAPE1, m_MouseShape1);
	DDX_Control(pDX, IDC_STATIC_SHAPE2, m_MouseShape2);
	DDX_Control(pDX, IDC_STATIC_SHAPE3, m_MouseShape3);
	DDX_Control(pDX, IDC_CHECK_CTRL, m_CtrlKey);
	DDX_Control(pDX, IDC_CHECK_ALT, m_AltKey);
	DDX_Control(pDX, IDC_STATIC_MOUSETEXT, m_MouseShapeText);
}


BEGIN_MESSAGE_MAP(CMyCatchMouseShape, CMFCPropertyPage)
	ON_WM_CREATE()
	ON_WM_HOTKEY()
	ON_BN_CLICKED(IDC_CHECK_CTRL, &CMyCatchMouseShape::OnBnClickedCheckCtrl)
	ON_BN_CLICKED(IDC_CHECK_ALT, &CMyCatchMouseShape::OnBnClickedCheckAlt)
	ON_BN_CLICKED(IDC_BUTTON_COPYCODE, &CMyCatchMouseShape::OnBnClickedButtonCopycode)
END_MESSAGE_MAP()


// CMyCatchMouseShape ��Ϣ�������


BOOL CMyCatchMouseShape::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rt;
	m_MouseShape1.GetWindowRect(&rt);
	this->ScreenToClient(&rt);
	m_MouseShape1.MoveWindow(rt.left,rt.top,32,32);

	m_MouseShape2.GetWindowRect(&rt);
	this->ScreenToClient(&rt);
	m_MouseShape2.MoveWindow(rt.left,rt.top,32,32);

	m_MouseShape3.GetWindowRect(&rt);
	this->ScreenToClient(&rt);
	m_MouseShape3.MoveWindow(rt.left,rt.top,32,32);

	m_CtrlKey.SetCheck(BST_CHECKED);
	m_AltKey.SetCheck(BST_CHECKED);

	CString noteText;
	noteText.Format(_T("\r\n ������������ͨ�����ô����ȡ\r\n\r\n ���� ������ = ���.��ȡ������()\r\n\r\n ����\r\n\r\n int mouseshape = mouse.getmouseshape()"));
	//this->GetDlgItem(IDC_EDIT_NOTETEXT)->SetWindowTextW(noteText);
	m_MouseShapeText.SetTextColor(RGB(6,121,50));
	m_MouseShapeText.SetWindowTextW(noteText);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

HBITMAP CMyCatchMouseShape::BitmapFromIcon(HICON hIcon)
{
	HDC dDC = CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
	HDC hDC = CreateCompatibleDC(dDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON));
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);
	DrawIcon(hDC, 0, 0, hIcon);
	hBitmap=(HBITMAP)SelectObject(hDC, hOldBitmap);
	DeleteDC(hDC);
	::DeleteDC(dDC);
	return hBitmap;
}

int  CMyCatchMouseShape::GetBitmapShape()
{
	//CURSORINFO pci;
	//pci.cbSize=sizeof(CURSORINFO);
	//pci.flags=0;
	//pci.hCursor=0;
	//if(GetCursorInfo(&pci))
	//{

	//}
	//else
	//{
	//	::AfxMessageBox(_T("��ȡʧ��"));
	//}

	//HDC dDC = CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
	//HDC hDC = CreateCompatibleDC(dDC);
	//HBITMAP hBitmap = CreateCompatibleBitmap(hDC, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON));
	//HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);
	////DrawIcon(hDC, 0, 0, pci.hCursor);
	//DrawIconEx(hDC,0,0,pci.hCursor,32,32,0,NULL,DI_NORMAL);
	//hBitmap=(HBITMAP)SelectObject(hDC, hOldBitmap);

	////////////// ��¼ λͼ �ľ��//////////////////
	//m_HBitMap=hBitmap;              ///�����Ա����ȼ�����ʾ
	//////////////////////////////////////////////////
	//WORD    wBitCount=1;   
	//DWORD           dwPaletteSize=0,dwBmBitsSize;
	//BITMAP          Bitmap;              
	//BITMAPINFOHEADER   bi;
	////λͼ��Ϣͷ�ṹ 
	//LPBITMAPINFOHEADER lpbi; 
	//HANDLE       hDib;
	//HPALETTE     hOldPal=NULL;

	////����λͼ��Ϣͷ�ṹ
	//GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);

	//dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)& ~31)/8*Bitmap.bmHeight;
	//BYTE* bmpDate = new BYTE[dwBmBitsSize];

	//bi.biSize            = sizeof(BITMAPINFOHEADER);
	//bi.biWidth           = Bitmap.bmWidth;
	//bi.biHeight          = Bitmap.bmHeight;
	//bi.biPlanes          = 1;
	//bi.biBitCount         = 1;
	//bi.biCompression      = BI_RGB;
	//bi.biSizeImage        = dwBmBitsSize;
	//bi.biXPelsPerMeter     = 0;
	//bi.biYPelsPerMeter     = 0;
	//bi.biClrUsed         = 0;
	//bi.biClrImportant      = 0;

	//hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));
	//lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	//*lpbi = bi;
	//GetDIBits(hDC,hBitmap,0,(UINT)Bitmap.bmHeight,bmpDate, (BITMAPINFO *)lpbi,DIB_RGB_COLORS);
	//DWORD num=0;
	//int height=Bitmap.bmHeight;
	//int width =Bitmap.bmWidth;
	//// ��ɫͼ�Ľ���
	//int n=0;
	//int color[100][100];
	//for(int i=0; i<height; i++)
	//	for(int j=0; j<width; j=j+8)
	//	{
	//		int k=7;
	//		while(k>=0)
	//		{
	//			color[i][k+j]=(bmpDate[n])%2;
	//			bmpDate[n]=(bmpDate[n])/2;
	//			k--;
	//		}
	//		n++;
	//	}

	//	for(int i=0; i<height; i++)
	//		for(int j=0; j<width; j++)
	//		{
	//			if(color[i][j] == 1)
	//			{
	//				num++;
	//			}
	//		}


	//////////////////////////////////////////////////////////////////////////
	//DWORD helpnum=num*RGB(255,255,0);
	//delete [] bmpDate;
	//::DeleteDC(hDC);
	//::DeleteDC(dDC);
	//:: GlobalFree(hDib); 
	CURSORINFO pci;
	pci.cbSize=sizeof(CURSORINFO);
	pci.flags=0;
	pci.hCursor=0;
	if(GetCursorInfo(&pci))
	{

	}
	else
	{
		::AfxMessageBox(_T("��ȡʧ��"));
	}
	HDC dDC = CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
	HDC hDC = CreateCompatibleDC(dDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(dDC, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON));
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);

	HBRUSH hbr;
	//hbr= (HBRUSH)GetStockObject(GRAY_BRUSH);
	hbr = CreateSolidBrush(RGB(192,192,192)); 
	//Brush cloneBrush
	//::FillRect(hDC,CRect(0,0,32,32),hbr);
	//CClientDC cDC(this);
	//DrawIcon(cDC.GetSafeHdc(),0,0,pci.hCursor);
	//::BitBlt(hDC,0,0,32,32,cDC.GetSafeHdc(),0,0,SRCCOPY);
	//::FillRect(hDC,CRect(0,0,32,32),hbr);
	DrawIcon(hDC,0,0,pci.hCursor);
	hBitmap=(HBITMAP)SelectObject(hDC, hOldBitmap);	 

	//////////// ��¼ λͼ �ľ��//////////////////
	m_HBitMap=hBitmap;              ///�����Ա����ȼ�����ʾ
	////////////////////////////////////////////////

	DWORD           dwPaletteSize=0,dwBmBitsSize;
	BITMAP          Bitmap;              
	BITMAPINFOHEADER   bi;
	//λͼ��Ϣͷ�ṹ 
	LPBITMAPINFOHEADER lpbi; 
	HANDLE       hDib;
	HPALETTE     hOldPal=NULL;

	//����λͼ��Ϣͷ�ṹ
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	WORD    wBitCount = Bitmap.bmBitsPixel;
	dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)& ~31)/8*Bitmap.bmHeight;
	BYTE* bmpDate = new BYTE[dwBmBitsSize];

	bi.biSize            = sizeof(BITMAPINFOHEADER);
	bi.biWidth           = Bitmap.bmWidth;
	bi.biHeight          = Bitmap.bmHeight;
	bi.biPlanes          = 1;
	bi.biBitCount         = wBitCount;
	bi.biCompression      = BI_RGB;
	bi.biSizeImage        = dwBmBitsSize;
	bi.biXPelsPerMeter     = 0;
	bi.biYPelsPerMeter     = 0;
	bi.biClrUsed         = 0;
	bi.biClrImportant      = 0;

	hDib  = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;
	GetDIBits(hDC,hBitmap,0,(UINT)Bitmap.bmHeight,bmpDate, (BITMAPINFO *)lpbi,DIB_RGB_COLORS);
	DWORD num=0;
	int height=Bitmap.bmHeight;
	int width =Bitmap.bmWidth;
	
	DWORD fristColor = RGB(bmpDate[0],bmpDate[1],bmpDate[2]);
	BYTE  b0 = bmpDate[0];
	BYTE  g0 = bmpDate[1];
	BYTE  r0 = bmpDate[2];

	// 32λͼ���н���
	if(Bitmap.bmBitsPixel==32)
	{
		{
			for(int i=0;i<height;i++)
			{
				for(int j=0;j<width;j++)
				{
					UCHAR b=bmpDate[(i*width+j)*4];
					UCHAR g=bmpDate[(i*width+j)*4+1];
					UCHAR r=bmpDate[(i*width+j)*4+2];
					if( b == b0 && g == g0 && r == r0 )
					{
						continue;
					}
					else
					{
						num++;
					}
				}
			}
		}
	}


	////////////////////////////////////////////////////////////////////////
	DWORD helpnum=num*RGB(255,255,0);
	delete [] bmpDate;
	:: GlobalFree(hDib);
	::DeleteDC(hDC);
	::DeleteDC(dDC);

	return (int)helpnum;
}

int CMyCatchMouseShape::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_CONTROL|MOD_ALT,'Q');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_CONTROL|MOD_ALT,'W');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_CONTROL|MOD_ALT,'E');

	m_HBitMap=NULL;
	
	return 0;
}


void CMyCatchMouseShape::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString shapeNum;
	switch(nHotKeyId)
	{
	case IDC_USERHOTKEY_MOUSESHAPE1:
		shapeNum.Format(_T("%d"),GetBitmapShape());
		m_MouseShape1.SetBitmap(m_HBitMap);
		//::DeleteObject(m_HBitMap);
		this->GetDlgItem(IDC_EDIT_MOUSESHAPE1)->SetWindowTextW(shapeNum);
		break;

	case IDC_USERHOTKEY_MOUSESHAPE2:
		shapeNum.Format(_T("%d"),GetBitmapShape());
		m_MouseShape2.SetBitmap(m_HBitMap);
		//::DeleteObject(m_HBitMap);
		this->GetDlgItem(IDC_EDIT_MOUSESHAPE2)->SetWindowTextW(shapeNum);
		break;

	case IDC_USERHOTKEY_MOUSESHAPE3:
		shapeNum.Format(_T("%d"),GetBitmapShape());
		m_MouseShape3.SetBitmap(m_HBitMap);
		//::DeleteObject(m_HBitMap);
		this->GetDlgItem(IDC_EDIT_MOUSESHAPE3)->SetWindowTextW(shapeNum);
		break;
	default:
		::DeleteObject(m_HBitMap);
		break;	
	}
	CMFCPropertyPage::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CMyCatchMouseShape::OnBnClickedCheckCtrl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData();
	//ѡ��Ctrl��Ϊѡ��״̬ʱ��Atl������ѡ��״̬
	if(m_CtrlKey.GetCheck()==BST_CHECKED&&m_AltKey.GetCheck()==BST_CHECKED)  
	{
		//////ѡ�о�ע���ȼ�
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_CONTROL|MOD_ALT,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_CONTROL|MOD_ALT,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_CONTROL|MOD_ALT,'E');
	}
	//ѡ��Ctrl��Ϊѡ��״̬ʱ��Atl������δѡ��״̬
	else if(m_CtrlKey.GetCheck()==BST_CHECKED&&m_AltKey.GetCheck()==BST_UNCHECKED)  
	{
		//////δѡ�о��ͷ��ȼ�
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);
		//////ѡ�о�ע���ȼ�
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_CONTROL,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_CONTROL,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_CONTROL,'E');
	}
	//ѡ��Ctrl��Ϊѡ��״̬ʱ��Atl������ѡ��״̬
	else if(m_CtrlKey.GetCheck()==BST_UNCHECKED&&m_AltKey.GetCheck()==BST_CHECKED) 
	{
		//////δѡ�о��ͷ��ȼ�
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);

		////////////����ע��altϵͳ��///////////////
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_ALT,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_ALT,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_ALT,'E');
		
	}
	//ѡ��Ctrl��Ϊδѡ��״̬ʱ��Atl������δѡ��״̬
	else if(m_CtrlKey.GetCheck()==BST_UNCHECKED&&m_AltKey.GetCheck()==BST_UNCHECKED)
	{
		//////δѡ�о��ͷ��ȼ�
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);

		////////////����ע��altϵͳ��///////////////
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,NULL,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,NULL,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,NULL,'E');
		
	}
}


void CMyCatchMouseShape::OnBnClickedCheckAlt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData();
	//ѡ��Ctrl��Ϊѡ��״̬ʱ��Atl������ѡ��״̬
	if(m_CtrlKey.GetCheck()==BST_CHECKED&&m_AltKey.GetCheck()==BST_CHECKED)  
	{
		//////ѡ�о�ע���ȼ�
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_CONTROL|MOD_ALT,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_CONTROL|MOD_ALT,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_CONTROL|MOD_ALT,'E');
	}
	//ѡ��Ctrl��Ϊѡ��״̬ʱ��Atl������δѡ��״̬
	else if(m_CtrlKey.GetCheck()==BST_CHECKED&&m_AltKey.GetCheck()==BST_UNCHECKED)  
	{
		//////δѡ�о��ͷ��ȼ�
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);
		//////ѡ�о�ע���ȼ�
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_CONTROL,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_CONTROL,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_CONTROL,'E');
	}
	//ѡ��Ctrl��Ϊѡ��״̬ʱ��Atl������ѡ��״̬
	else if(m_CtrlKey.GetCheck()==BST_UNCHECKED&&m_AltKey.GetCheck()==BST_CHECKED) 
	{
		//////δѡ�о��ͷ��ȼ�
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);

		////////////����ע��altϵͳ��///////////////
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_ALT,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_ALT,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_ALT,'E');
		
	}
	//ѡ��Ctrl��Ϊδѡ��״̬ʱ��Atl������δѡ��״̬
	else if(m_CtrlKey.GetCheck()==BST_UNCHECKED&&m_AltKey.GetCheck()==BST_UNCHECKED)
	{
		//////δѡ�о��ͷ��ȼ�
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);

		////////////����ע��altϵͳ��///////////////
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,NULL,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,NULL,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,NULL,'E');
		
	}
}


void CMyCatchMouseShape::OnBnClickedButtonCopycode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString codeText=_T("���� ������=���.��ȡ������()");
	HANDLE hClip;
	if(::OpenClipboard(NULL))
	{
		//���������������
		EmptyClipboard();
		//�ֽڳ���
		int leng=(codeText.GetLength()+1)*sizeof(TCHAR);
		//�ڶ��Ϸ�����ƶ����ڴ�飬���򷵻�һ���ڴ���
		hClip=GlobalAlloc(GHND | GMEM_SHARE,leng);
		//����ָ���ַ��͵�ָ�����
		TCHAR * buff;
		//�Է�����ڴ����м��������ڴ����ת����һ��ָ��,������Ӧ�����ü�������һ
		buff=(TCHAR *)GlobalLock(hClip);
		//���û���������ݿ�����ָ������У�ʵ���Ͼ��ǿ�����������ڴ����
		memcpy(buff,codeText,leng);
		//����д����ϣ����н����������������ü��������ּ�һ
		GlobalUnlock(hClip);
		//����������ݵ��ڴ�������������Դ������
		HANDLE help = SetClipboardData(/*CF_TEXT*/CF_UNICODETEXT,hClip);
		//�رռ����壬�ͷż�������Դ��ռ��Ȩ
		GlobalFree(hClip);
		CloseClipboard();
	}

	::AfxMessageBox(_T("�����Ѿ����Ƶ����а���!"));
}
