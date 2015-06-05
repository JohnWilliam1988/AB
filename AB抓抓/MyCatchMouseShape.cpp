// MyCatchMouseShape.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyCatchMouseShape.h"
#include "afxdialogex.h"


// 获取鼠标的热键资源
#define IDC_USERHOTKEY_MOUSESHAPE1                  WM_USER+121    
#define IDC_USERHOTKEY_MOUSESHAPE2                  WM_USER+122
#define IDC_USERHOTKEY_MOUSESHAPE3                  WM_USER+123

// CMyCatchMouseShape 对话框

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


// CMyCatchMouseShape 消息处理程序


BOOL CMyCatchMouseShape::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	noteText.Format(_T("\r\n 鼠标特征码可以通过调用代码获取\r\n\r\n 整型 特征码 = 鼠标.获取特征码()\r\n\r\n 或者\r\n\r\n int mouseshape = mouse.getmouseshape()"));
	//this->GetDlgItem(IDC_EDIT_NOTETEXT)->SetWindowTextW(noteText);
	m_MouseShapeText.SetTextColor(RGB(6,121,50));
	m_MouseShapeText.SetWindowTextW(noteText);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
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
	//	::AfxMessageBox(_T("获取失败"));
	//}

	//HDC dDC = CreateDC(_T("DISPLAY"),NULL,NULL,NULL);
	//HDC hDC = CreateCompatibleDC(dDC);
	//HBITMAP hBitmap = CreateCompatibleBitmap(hDC, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON));
	//HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);
	////DrawIcon(hDC, 0, 0, pci.hCursor);
	//DrawIconEx(hDC,0,0,pci.hCursor,32,32,0,NULL,DI_NORMAL);
	//hBitmap=(HBITMAP)SelectObject(hDC, hOldBitmap);

	////////////// 记录 位图 的句柄//////////////////
	//m_HBitMap=hBitmap;              ///保存以便在热键里显示
	//////////////////////////////////////////////////
	//WORD    wBitCount=1;   
	//DWORD           dwPaletteSize=0,dwBmBitsSize;
	//BITMAP          Bitmap;              
	//BITMAPINFOHEADER   bi;
	////位图信息头结构 
	//LPBITMAPINFOHEADER lpbi; 
	//HANDLE       hDib;
	//HPALETTE     hOldPal=NULL;

	////设置位图信息头结构
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
	//// 单色图的解析
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
		::AfxMessageBox(_T("获取失败"));
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

	//////////// 记录 位图 的句柄//////////////////
	m_HBitMap=hBitmap;              ///保存以便在热键里显示
	////////////////////////////////////////////////

	DWORD           dwPaletteSize=0,dwBmBitsSize;
	BITMAP          Bitmap;              
	BITMAPINFOHEADER   bi;
	//位图信息头结构 
	LPBITMAPINFOHEADER lpbi; 
	HANDLE       hDib;
	HPALETTE     hOldPal=NULL;

	//设置位图信息头结构
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

	// 32位图进行解析
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

	// TODO:  在此添加您专用的创建代码
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_CONTROL|MOD_ALT,'Q');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_CONTROL|MOD_ALT,'W');
	RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_CONTROL|MOD_ALT,'E');

	m_HBitMap=NULL;
	
	return 0;
}


void CMyCatchMouseShape::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData();
	//选择Ctrl键为选中状态时，Atl键处于选中状态
	if(m_CtrlKey.GetCheck()==BST_CHECKED&&m_AltKey.GetCheck()==BST_CHECKED)  
	{
		//////选中就注册热键
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_CONTROL|MOD_ALT,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_CONTROL|MOD_ALT,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_CONTROL|MOD_ALT,'E');
	}
	//选择Ctrl键为选中状态时，Atl键处于未选中状态
	else if(m_CtrlKey.GetCheck()==BST_CHECKED&&m_AltKey.GetCheck()==BST_UNCHECKED)  
	{
		//////未选中就释放热键
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);
		//////选中就注册热键
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_CONTROL,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_CONTROL,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_CONTROL,'E');
	}
	//选择Ctrl键为选中状态时，Atl键处于选中状态
	else if(m_CtrlKey.GetCheck()==BST_UNCHECKED&&m_AltKey.GetCheck()==BST_CHECKED) 
	{
		//////未选中就释放热键
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);

		////////////重新注册alt系统键///////////////
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_ALT,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_ALT,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_ALT,'E');
		
	}
	//选择Ctrl键为未选中状态时，Atl键处于未选中状态
	else if(m_CtrlKey.GetCheck()==BST_UNCHECKED&&m_AltKey.GetCheck()==BST_UNCHECKED)
	{
		//////未选中就释放热键
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);

		////////////重新注册alt系统键///////////////
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,NULL,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,NULL,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,NULL,'E');
		
	}
}


void CMyCatchMouseShape::OnBnClickedCheckAlt()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData();
	//选择Ctrl键为选中状态时，Atl键处于选中状态
	if(m_CtrlKey.GetCheck()==BST_CHECKED&&m_AltKey.GetCheck()==BST_CHECKED)  
	{
		//////选中就注册热键
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_CONTROL|MOD_ALT,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_CONTROL|MOD_ALT,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_CONTROL|MOD_ALT,'E');
	}
	//选择Ctrl键为选中状态时，Atl键处于未选中状态
	else if(m_CtrlKey.GetCheck()==BST_CHECKED&&m_AltKey.GetCheck()==BST_UNCHECKED)  
	{
		//////未选中就释放热键
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);
		//////选中就注册热键
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_CONTROL,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_CONTROL,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_CONTROL,'E');
	}
	//选择Ctrl键为选中状态时，Atl键处于选中状态
	else if(m_CtrlKey.GetCheck()==BST_UNCHECKED&&m_AltKey.GetCheck()==BST_CHECKED) 
	{
		//////未选中就释放热键
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);

		////////////重新注册alt系统键///////////////
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,MOD_ALT,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,MOD_ALT,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,MOD_ALT,'E');
		
	}
	//选择Ctrl键为未选中状态时，Atl键处于未选中状态
	else if(m_CtrlKey.GetCheck()==BST_UNCHECKED&&m_AltKey.GetCheck()==BST_UNCHECKED)
	{
		//////未选中就释放热键
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2);
		::UnregisterHotKey(m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3);

		////////////重新注册alt系统键///////////////
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE1,NULL,'Q');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE2,NULL,'W');
		RegisterHotKey(this->m_hWnd,IDC_USERHOTKEY_MOUSESHAPE3,NULL,'E');
		
	}
}


void CMyCatchMouseShape::OnBnClickedButtonCopycode()
{
	// TODO: 在此添加控件通知处理程序代码
	CString codeText=_T("整型 特征码=鼠标.获取特征码()");
	HANDLE hClip;
	if(::OpenClipboard(NULL))
	{
		//将剪贴板内容清空
		EmptyClipboard();
		//字节长度
		int leng=(codeText.GetLength()+1)*sizeof(TCHAR);
		//在堆上分配可移动的内存块，程序返回一个内存句柄
		hClip=GlobalAlloc(GHND | GMEM_SHARE,leng);
		//定义指向字符型的指针变量
		TCHAR * buff;
		//对分配的内存块进行加锁，将内存块句柄转化成一个指针,并将相应的引用计数器加一
		buff=(TCHAR *)GlobalLock(hClip);
		//将用户输入的数据拷贝到指针变量中，实际上就是拷贝到分配的内存块中
		memcpy(buff,codeText,leng);
		//数据写入完毕，进行解锁操作，并将引用计数器数字减一
		GlobalUnlock(hClip);
		//将存放有数据的内存块放入剪贴板的资源管理中
		HANDLE help = SetClipboardData(/*CF_TEXT*/CF_UNICODETEXT,hClip);
		//关闭剪贴板，释放剪贴板资源的占用权
		GlobalFree(hClip);
		CloseClipboard();
	}

	::AfxMessageBox(_T("代码已经复制到剪切板中!"));
}
