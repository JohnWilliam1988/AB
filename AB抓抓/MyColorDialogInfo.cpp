// MyColorDialogInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "AB抓抓.h"
#include "MyColorDialogInfo.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <Wingdi.h>
#include "MyWndHandleList.h"
// CMyColorDialogInfo 对话框
#define min3v(v1, v2, v3)   ((v1)>(v2)? ((v2)>(v3)?(v3):(v2)):((v1)>(v3)?(v3):(v2))) 
#define max3v(v1, v2, v3)   ((v1)<(v2)? ((v2)<(v3)?(v3):(v2)):((v1)<(v3)?(v3):(v1)))

IMPLEMENT_DYNAMIC(CMyColorDialogInfo, CMFCPropertyPage)

CMyColorDialogInfo::CMyColorDialogInfo()
	: CMFCPropertyPage(CMyColorDialogInfo::IDD)
	, m_Selecte16_Date(0)
{

}

CMyColorDialogInfo::~CMyColorDialogInfo()
{
}

void CMyColorDialogInfo::DoDataExchange(CDataExchange* pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_COLORSHOW, m_ColorShow);
	DDX_Control(pDX, IDC_CHECK_ISWNDHANDLE, m_IsCheckWndHandle);
	DDX_Control(pDX, IDC_BUTTON_SELECTWNDH, m_SelectWndHandle);
	DDX_Radio(pDX, IDC_RADIO_16DATE, m_Selecte16_Date);
	DDX_Control(pDX, IDC_STATIC_LOG1, m_LogText1);
	DDX_Control(pDX, IDC_STATIC_MAKE_RGBLOG, m_RGBTextLog);
	DDX_Control(pDX, IDC_BUTTON_MAKERGB, m_MakeColorValue);
	DDX_Control(pDX, IDC_BUTTON_LOOKRGB, m_MakeRGBValue);
	//DDX_Control(pDX, IDC_RADIO_16DATE, m_16DataCtrl);
	DDX_Control(pDX, IDC_STATIC_CC, m_ChangeDate);
}


BEGIN_MESSAGE_MAP(CMyColorDialogInfo, CMFCPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyColorDialogInfo::OnBnClickedButton1)
ON_EN_CHANGE(IDC_EDIT_XPOINT, &CMyColorDialogInfo::OnEnChangeEditXpoint)
ON_EN_CHANGE(IDC_EDIT_YPOINT, &CMyColorDialogInfo::OnEnChangeEditYpoint)
ON_EN_CHANGE(IDC_EDIT_INPUTHANDLE, &CMyColorDialogInfo::OnEnChangeEditInputhandle)
ON_BN_CLICKED(IDC_CHECK_ISWNDHANDLE, &CMyColorDialogInfo::OnBnClickedCheckIswndhandle)
ON_BN_CLICKED(IDC_BUTTON_SELECTWNDH, &CMyColorDialogInfo::OnBnClickedButtonSelectwndh)
ON_BN_CLICKED(IDC_BUTTON_MAKERGB, &CMyColorDialogInfo::OnBnClickedButtonMakergb)
ON_BN_CLICKED(IDC_BUTTON_LOOKRGB, &CMyColorDialogInfo::OnBnClickedButtonLookrgb)
ON_BN_CLICKED(IDC_RADIO_16DATE, &CMyColorDialogInfo::OnBnClickedRadio16date)
ON_BN_CLICKED(IDC_RADIO_10DATE, &CMyColorDialogInfo::OnBnClickedRadio10date)
ON_EN_CHANGE(IDC_EDIT_16JZ, &CMyColorDialogInfo::OnEnChangeEdit16jz)
ON_EN_CHANGE(IDC_EDIT_10JZ, &CMyColorDialogInfo::OnEnChangeEdit10jz)
END_MESSAGE_MAP()


// CMyColorDialogInfo 消息处理程序


BOOL CMyColorDialogInfo::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_SelectWndHandle.m_bTransparent = TRUE;
	m_SelectWndHandle.m_nFlatStyle = CMFCButton::BUTTONSTYLE_SEMIFLAT;
	m_SelectWndHandle.SetImage(IDB_BTN1);
	m_SelectWndHandle.SetWindowText(_T("选择句柄"));
	m_SelectWndHandle.m_bRightImage = TRUE;
	m_SelectWndHandle.m_bTopImage = FALSE;
	m_SelectWndHandle.SetTooltip(_T("选择一个你需要捕获颜色的窗口句柄"));

	m_SelectWndHandle.SizeToContent();
	m_SelectWndHandle.Invalidate();
	m_SelectWndHandle.EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_R_SUB)->SetWindowTextW(_T("00"));
	GetDlgItem(IDC_EDIT_G_SUB)->SetWindowTextW(_T("00"));
	GetDlgItem(IDC_EDIT_B_SUB)->SetWindowTextW(_T("00"));
	GetDlgItem(IDC_EDIT_16COLOR)->SetWindowTextW(_T("000000"));
	GetDlgItem(IDC_EDIT_10COLOR)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_STATIC_MAKE_RGBLOG)->SetWindowTextW(_T("请输入R.G.B三值生成颜色值!"));

	m_MakeColorValue.SetTooltip(_T("输入R、G、B三值,点击此按钮获得颜色值数据。"));
	m_MakeRGBValue.SetTooltip(_T("输入颜色值,点击此按钮获得R、G、B三值数据。"));

	//m_16DataCtrl.SetTooltip(_T("RGB值16进制显示"));

	//m_LogText1.SetBkColor(RGB(6,121,50));
	m_LogText1.SetTextColor(RGB(6,121,50));
	m_RGBTextLog.SetTextColor(RGB(6,121,50));
	m_ChangeDate.SetTextColor(RGB(6,121,50));
	m_ChangeDate.SetWindowTextW(_T("<-- 输入数字自己转换为相应进制数据"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMyColorDialogInfo::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData();
	if(m_IsCheckWndHandle.GetCheck()==BST_UNCHECKED)
	{
		CatchColorInfoOnForeground();
	}
	else
	{
		CatchColorInfoOnForeground();
	}
}

// Converts RGB to HSL   
  
void CMyColorDialogInfo::RGBtoHSL(/*[in]*/const BYTE rColor,/*[in]*/const BYTE gColor,/*[in]*/const BYTE bColor)
{     
    float h=0, s=0, l=0;   
    // normalizes red-green-blue values   
    float r = rColor/255.f;   
    float g = gColor/255.f;  
    float b = bColor/255.f;  
    float maxVal = max3v(r, g, b);   
    float minVal = min3v(r, g, b);
  
    ///////////////////////////// hue////////////////
    if(maxVal == minVal)     
    {     
        h = 0; // undefined     
    }
    else if(maxVal==r && g>=b)     
    {     
        h = 60.0f*(g-b)/(maxVal-minVal);     
    }
    else if(maxVal==r && g<b)     
    {     
        h = 60.0f*(g-b)/(maxVal-minVal) + 360.0f;   
    }
    else if(maxVal==g)     
    {     
        h = 60.0f*(b-r)/(maxVal-minVal) + 120.0f;     
    }   
    else if(maxVal==b)     
    {     
        h = 60.0f*(r-g)/(maxVal-minVal) + 240.0f;     
    }   
  
    ////////////////////// luminance //////////////////
    l = (maxVal+minVal)/2.0f; 

    ///////////////////////// saturation ////////////////
    if(l == 0 || maxVal == minVal)   
    {     
        s = 0;     
    } 
    else if(0<l && l<=0.5f)   
    {     
        s = (maxVal-minVal)/(maxVal+minVal);     
    }   
    else if(l>0.5f)     
    {     
        s = (maxVal-minVal)/(2 - (maxVal+minVal)); //(maxVal-minVal > 0)?     
    }   
    float hue = (h>360)? 360 : ((h<0)?0:h);      
    float saturation = ((s>1)? 1 : ((s<0)?0:s))*100;     
    float luminance = ((l>1)? 1 : ((l<0)?0:l))*100; 

	m_Hue = 240 * hue / 360.f;     
	m_Saturation = 240 * saturation / 100.f;     
	m_Light = 240 * luminance / 100.f;
}    

void CMyColorDialogInfo::CatchColorInfoOnForeground()
{
	CString xPoint=_T("");
	CString yPoint=_T("");
	((CEdit*)this->GetDlgItem(IDC_EDIT_XPOINT))->GetWindowTextW(xPoint);
	((CEdit*)this->GetDlgItem(IDC_EDIT_YPOINT))->GetWindowTextW(yPoint);

	int x = ::wcstol(xPoint,NULL,10);
	int y = ::wcstol(yPoint,NULL,10);
	COLORREF ColorValue=0;
	HDC hDC = ::GetDC(NULL);
	ColorValue = ::GetPixel(hDC,x,y);
	::ReleaseDC(NULL,hDC);

	BYTE red = GetRValue(ColorValue);
	BYTE green = GetGValue(ColorValue);
	BYTE bule = GetBValue(ColorValue);

	RGBtoHSL(red,green,bule);

	CString  color16Str=_T("");
	CString  color10Str=_T("");
	CString  redStr16=_T("");
	CString  greenStr16=_T("");
	CString  buleStr16=_T("");
	CString  redStr=_T("");
	CString  greenStr=_T("");
	CString  buleStr=_T("");
	CString  hStr=_T("");
	CString  saturationStr=_T("");
	CString  lStr=_T("");

	/*if(ColorValue==0)
		color16Str.Format(_T("000000"));
	else if(ColorValue<=0XF)
		color16Str.Format(_T("00000%x"),ColorValue);
	else if(ColorValue<=0XFF)
		color16Str.Format(_T("0000%x"),ColorValue);
	else if(ColorValue<=0XFFF)
		color16Str.Format(_T("000%x"),ColorValue);
	else if(ColorValue<=0XFFFF)
		color16Str.Format(_T("00%x"),ColorValue);
	else if(ColorValue<=0XFFFFF)
		color16Str.Format(_T("0%x"),ColorValue);
	else*/
	color16Str.Format(_T("%06X"),ColorValue);
	//color16Str.MakeUpper();

	color10Str.Format(_T("%d"),(int)ColorValue);
	//if(red>0x0F)
	//	redStr16.Format(_T("%x"),red);
	//else
	redStr16.Format(_T("%02X"),red);
	//if(green>0x0F)
	//	greenStr16.Format(_T("%X"),green);
	//else
	greenStr16.Format(_T("%02X"),green);
	//if(bule>0x0F)
	//	buleStr16.Format(_T("%X"),bule);
	//else
		buleStr16.Format(_T("%02X"),bule);
	redStr16.MakeUpper();
	greenStr16.MakeUpper();
	buleStr16.MakeUpper();
	redStr.Format(_T("%d"),red);
	greenStr.Format(_T("%d"),green);
	buleStr.Format(_T("%d"),bule);
	hStr.Format(_T("%d"),m_Hue);
	saturationStr.Format(_T("%d"),m_Saturation);
	lStr.Format(_T("%d"),m_Light);

	m_ColorShow.SetBkColor(ColorValue);
	((CEdit*)this->GetDlgItem(IDC_EDIT_16JZ))->SetWindowTextW(color16Str);
	((CEdit*)this->GetDlgItem(IDC_EDIT_10JZ))->SetWindowTextW(color10Str);
	//////////////////////////////16进制显示 /////////////////////////////
	((CEdit*)this->GetDlgItem(IDC_EDIT_RED))->SetWindowTextW(redStr16);
	((CEdit*)this->GetDlgItem(IDC_EDIT_GREEN))->SetWindowTextW(greenStr16);
	((CEdit*)this->GetDlgItem(IDC_EDIT_BULE))->SetWindowTextW(buleStr16);
	/////////////////////////////10进制显示 /////////////////////////////
	((CEdit*)this->GetDlgItem(IDC_EDIT_RED2))->SetWindowTextW(redStr);
	((CEdit*)this->GetDlgItem(IDC_EDIT_GREEN2))->SetWindowTextW(greenStr);
	((CEdit*)this->GetDlgItem(IDC_EDIT_BULE2))->SetWindowTextW(buleStr);
	/////////////////////////////HSL显示 ////////////////////////////////
	((CEdit*)this->GetDlgItem(IDC_EDIT_COLORHEIGHT))->SetWindowTextW(hStr);
	((CEdit*)this->GetDlgItem(IDC_EDIT_COLORSATURATION))->SetWindowTextW(saturationStr);
	((CEdit*)this->GetDlgItem(IDC_EDIT_COLORLIGHT))->SetWindowTextW(lStr);

	return ;
}

BOOL CMyColorDialogInfo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	return CMFCPropertyPage::PreTranslateMessage(pMsg);
}


void CMyColorDialogInfo::OnEnChangeEditXpoint()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strTemp=_T("");
	CEdit* editHelp = ((CEdit*)(GetDlgItem(IDC_EDIT_XPOINT)));
	editHelp->GetWindowText(strTemp);
	int len = strTemp.GetLength();
	for (int i = 0; i < len; i ++)
	{
		if(strTemp.GetAt(i) < '0' || strTemp.GetAt(i) > '9')
		{
			strTemp = strTemp.Left(i);
			editHelp->SetWindowText(strTemp);
			editHelp->SetSel(i,i,TRUE);
			return;
		}
	}
}


void CMyColorDialogInfo::OnEnChangeEditYpoint()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strTemp=_T("");
	CEdit* editHelp = ((CEdit*)(GetDlgItem(IDC_EDIT_YPOINT)));
	editHelp->GetWindowText(strTemp);
	int len = strTemp.GetLength();
	for (int i = 0; i < len; i ++)
	{
		if(strTemp.GetAt(i) < '0' || strTemp.GetAt(i) > '9')
		{
			strTemp = strTemp.Left(i);
			editHelp->SetWindowText(strTemp);
			editHelp->SetSel(i,i,TRUE);
			return;
		}
	}
}


void CMyColorDialogInfo::OnEnChangeEditInputhandle()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strTemp=_T("");
	CEdit* editHelp = ((CEdit*)(GetDlgItem(IDC_EDIT_INPUTHANDLE)));
	editHelp->GetWindowText(strTemp);
	int len = strTemp.GetLength();
	for (int i = 0; i < len; i ++)
	{
		if(strTemp.GetAt(i) < '0' || strTemp.GetAt(i) > '9')
		{
			strTemp = strTemp.Left(i);
			editHelp->SetWindowText(strTemp);
			editHelp->SetSel(i,i,TRUE);
			return;
		}
	}
}


void CMyColorDialogInfo::OnBnClickedCheckIswndhandle()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_IsCheckWndHandle.GetCheck()==1)
	{
		m_SelectWndHandle.EnableWindow();
	}
	else
	{
		m_SelectWndHandle.EnableWindow(FALSE);
	}
}


void CMyColorDialogInfo::OnBnClickedButtonSelectwndh()
{
	// TODO: 在此添加控件通知处理程序代码
	CMyWndHandleList wndDLG;
	wndDLG.DoModal();

	this->GetDlgItem(IDC_EDIT_INPUTHANDLE)->SetWindowTextW(wndDLG.m_ListWndHandle);
}

bool CMyColorDialogInfo::processBKWindow(HWND src_hWnd,int &color,int x,int y)
{
	RECT rc;
	::GetWindowRect(src_hWnd, &rc);

	if(x>rc.right||y>rc.bottom)
	{
		::MessageBox(NULL,_T("XY坐标值超出后台窗口大小"),_T("AB抓抓警告"),MB_ICONEXCLAMATION|MB_ICONWARNING);
		return false;
	}
	// 24位图的BITMAPINFO
	BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
	memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
	BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
	pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
	pInfo_Header->biWidth = rc.right - rc.left;   
	pInfo_Header->biHeight = (rc.bottom - rc.top);   
	pInfo_Header->biPlanes = 1;   
	pInfo_Header->biBitCount = 24;   
	pInfo_Header->biCompression = BI_RGB;

	// 创建兼容DC 打印目标窗体
	HDC src_hdc = ::GetWindowDC(src_hWnd);        
	HBITMAP hBitmap = ::CreateCompatibleBitmap(src_hdc,pInfo_Header->biWidth, pInfo_Header->biHeight);
	HDC hdcCompatible = ::CreateCompatibleDC(src_hdc); 
	::SelectObject(hdcCompatible, hBitmap);
	::PrintWindow(src_hWnd, hdcCompatible, 0);
	::ReleaseDC(src_hWnd, src_hdc);    
	if(hBitmap==NULL)
	{
		//::MessageBox(NULL,_T("获取后台图失败"),_T("AB抓抓警告"),MB_ICONEXCLAMATION|MB_ICONWARNING);
		::DeleteDC(hdcCompatible);
		return false;
	}

	// 获得数据buf
	DWORD bufSize = (pInfo_Header->biWidth * 3 + 3) / 4 * 4 * pInfo_Header->biHeight;
	BYTE * pBuffer = new BYTE[bufSize];

	int aHeight=pInfo_Header->biHeight;

	if(::GetDIBits(hdcCompatible, hBitmap, 0, aHeight, pBuffer,pBITMAPINFO, DIB_RGB_COLORS) == 0)
	{
		//::MessageBox(NULL,_T("获取BK位图数据失败"),_T("AB抓抓警告"),MB_ICONEXCLAMATION|MB_ICONWARNING);
		delete [] pBuffer;
		::DeleteDC(hdcCompatible);
		::DeleteObject(hBitmap);
		return false;
	}

	int width=pBITMAPINFO->bmiHeader.biWidth;
	int height=pBITMAPINFO->bmiHeader.biHeight;

	COLORREF** pColorBuffer = new COLORREF*[height];     ///// 二维数组 用来存储图像的颜色值
	for(int i=0;i<height;i++)
	{
		pColorBuffer[i]=new COLORREF[width];
	}
	
	COLORREF helpcolor=0;
	BYTE r1=0,g1=0,b1=0;
	int pitch=width%4;
	for(int i=0;i<height;i++)
	{
		int realPitch=i*pitch;
		for(int j=0;j<width;j++)
		{
			UCHAR b=pBuffer[(i*width+j)*3+realPitch];
			UCHAR g=pBuffer[(i*width+j)*3+1+realPitch];
			UCHAR r=pBuffer[(i*width+j)*3+2+realPitch];
			helpcolor=RGB(r,g,b);

			pColorBuffer[height-i-1][j]=helpcolor;	
		}
	}

	if(color==0)
	{
		color=pColorBuffer[y][x];
	}

	free(pBITMAPINFO);
	::DeleteObject(hdcCompatible);
	::DeleteObject(hBitmap);

	for(int i=0;i<height;i++)
	{
		delete [] pColorBuffer[i];
	}

	delete [] pColorBuffer;
	pColorBuffer=NULL;

	delete [] pBuffer;

	return true;
}

// R G B 三值字符串转换成整型数据
int     CMyColorDialogInfo::RGBStrToIntDate(CString value)
{
	value.Trim();
	value.MakeUpper();
	int date =0, length=0;
	//length = value.GetLength();
	if(1==m_Selecte16_Date)
	{
		date = ::wcstol(value,NULL,10);
	}
	if(0==m_Selecte16_Date)
	{
		if(value.GetLength()>=3)
			return 1000;
		date = ::wcstol(value,NULL,16);
	}

	/*if(length==2&&(value[0]>'A'&&value[0]<'F')||(value[1]>'A'&&value[1]<'F'))
	{
		///是十六进制数据 如：1F  AE
		date = ::wcstol(value,NULL,16);
	}
	else if(length==1&&(value[0]>'A'&&value[0]<'F'))
	{
		///是十六进制数据 如：F  E  C
		date = ::wcstol(value,NULL,16);
	}
	else 
	{
		date = ::wcstol(value,NULL,16);
	}*/
	return date;
}


void CMyColorDialogInfo::OnBnClickedButtonMakergb()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData();

	CString R_G_BStr=_T(""),RGBColorStr=_T("");
	DWORD ColorResult=0,r_data=0,g_data=0,b_data=0;

	GetDlgItem(IDC_EDIT_R_SUB)->GetWindowTextW(R_G_BStr);
	r_data = RGBStrToIntDate(R_G_BStr);
	GetDlgItem(IDC_EDIT_G_SUB)->GetWindowTextW(R_G_BStr);
	g_data = RGBStrToIntDate(R_G_BStr);
	GetDlgItem(IDC_EDIT_B_SUB)->GetWindowTextW(R_G_BStr);
	b_data = RGBStrToIntDate(R_G_BStr);

	if(r_data==1000)
	{
		GetDlgItem(IDC_STATIC_MAKE_RGBLOG)->SetWindowTextW(_T("生成失败,输入R值错误!"));
		return ;
	}
	if(g_data==1000)
	{
		GetDlgItem(IDC_STATIC_MAKE_RGBLOG)->SetWindowTextW(_T("生成失败,输入G值错误!"));
		return ;
	}
	if(b_data==1000)
	{
		GetDlgItem(IDC_STATIC_MAKE_RGBLOG)->SetWindowTextW(_T("生成失败,输入B值错误!"));
		return ;
	}

	ColorResult = RGB(r_data,g_data,b_data);
	RGBColorStr.Format(_T("%d"),ColorResult);
	GetDlgItem(IDC_EDIT_10COLOR)->SetWindowTextW(RGBColorStr);

	//if(ColorResult==0)
	//	RGBColorStr.Format(_T("000000"));
	//else if(ColorResult<=0XF)
	//	RGBColorStr.Format(_T("00000%x"),ColorResult);
	//else if(ColorResult<=0XFF)
	//	RGBColorStr.Format(_T("0000%x"),ColorResult);
	//else if(ColorResult<=0XFFF)
	//	RGBColorStr.Format(_T("000%x"),ColorResult);
	//else if(ColorResult<=0XFFFF)
	//	RGBColorStr.Format(_T("00%x"),ColorResult);
	//else if(ColorResult<=0XFFFFF)
	//	RGBColorStr.Format(_T("0%x"),ColorResult);
	//else
	RGBColorStr.Format(_T("%06X"),ColorResult);

	RGBColorStr.MakeUpper();

	GetDlgItem(IDC_EDIT_16COLOR)->SetWindowTextW(RGBColorStr);

	GetDlgItem(IDC_STATIC_MAKE_RGBLOG)->SetWindowTextW(_T("生成完成……"));

	return;
}


void CMyColorDialogInfo::OnBnClickedButtonLookrgb()
{
	// TODO: 在此添加控件通知处理程序代码
	this->UpdateData();

	CString RGBColorStr;
	GetDlgItem(IDC_EDIT_16COLOR)->GetWindowTextW(RGBColorStr);
	RGBColorStr.Trim();
	if(RGBColorStr.IsEmpty())
		return ;

	DWORD ColorValue;
	ColorValue = ::wcstol(RGBColorStr,NULL,16);
	CString helpStr;
	helpStr.Format(_T("%d"),ColorValue);
	GetDlgItem(IDC_EDIT_10COLOR)->SetWindowTextW(helpStr);

	int rgb=0;
	CString rgb_Str=_T("");
	if(m_Selecte16_Date==1)
	{
		rgb = GetRValue(ColorValue);
		rgb_Str.Format(_T("%d"),rgb);
		GetDlgItem(IDC_EDIT_R_SUB)->SetWindowTextW(rgb_Str);

		rgb = GetGValue(ColorValue);
		rgb_Str.Format(_T("%d"),rgb);
		GetDlgItem(IDC_EDIT_G_SUB)->SetWindowTextW(rgb_Str);

		rgb = GetBValue(ColorValue);
		rgb_Str.Format(_T("%d"),rgb);
		GetDlgItem(IDC_EDIT_B_SUB)->SetWindowTextW(rgb_Str);
	}
	if(m_Selecte16_Date==0)
	{
		rgb = GetRValue(ColorValue);
		rgb_Str.Format(_T("%02X"),rgb);
		GetDlgItem(IDC_EDIT_R_SUB)->SetWindowTextW(rgb_Str);

		rgb = GetGValue(ColorValue);
		rgb_Str.Format(_T("%02X"),rgb);
		GetDlgItem(IDC_EDIT_G_SUB)->SetWindowTextW(rgb_Str);

		rgb = GetBValue(ColorValue);
		//if(rgb==0)
		//	rgb_Str.Format(_T("00"));
		//else if(rgb<=0xF)
		//	rgb_Str.Format(_T("0%x"),rgb);
		//else
		rgb_Str.Format(_T("%02X"),rgb);
		//rgb_Str.MakeUpper();
		GetDlgItem(IDC_EDIT_B_SUB)->SetWindowTextW(rgb_Str);
	}
}


void CMyColorDialogInfo::OnBnClickedRadio16date()
{
	// TODO: 在此添加控件通知处理程序代码
	/*this->UpdateData();
	if(m_Selecte16_Date)
		m_Selecte16_Date = FALSE;
	else
		m_Selecte16_Date = TRUE;
	this->UpdateData();*/
	CString rgb_Str1,rgb_Str2,rgb_Str3;
	GetDlgItem(IDC_EDIT_R_SUB)->GetWindowTextW(rgb_Str1);
	GetDlgItem(IDC_EDIT_G_SUB)->GetWindowTextW(rgb_Str2);
	GetDlgItem(IDC_EDIT_B_SUB)->GetWindowTextW(rgb_Str3);

	rgb_Str1.Format(_T("%02X"),::wcstol(rgb_Str1,NULL,10));
	rgb_Str2.Format(_T("%02X"),::wcstol(rgb_Str2,NULL,10));
	rgb_Str3.Format(_T("%02X"),::wcstol(rgb_Str3,NULL,10));
	rgb_Str1.MakeUpper();
	rgb_Str2.MakeUpper();
	rgb_Str3.MakeUpper();
	GetDlgItem(IDC_EDIT_R_SUB)->SetWindowTextW(rgb_Str1);
	GetDlgItem(IDC_EDIT_G_SUB)->SetWindowTextW(rgb_Str2);
	GetDlgItem(IDC_EDIT_B_SUB)->SetWindowTextW(rgb_Str3);

	return ;
}


void CMyColorDialogInfo::OnBnClickedRadio10date()
{
	// TODO: 在此添加控件通知处理程序代码
	CString rgb_Str1,rgb_Str2,rgb_Str3;
	GetDlgItem(IDC_EDIT_R_SUB)->GetWindowTextW(rgb_Str1);
	GetDlgItem(IDC_EDIT_G_SUB)->GetWindowTextW(rgb_Str2);
	GetDlgItem(IDC_EDIT_B_SUB)->GetWindowTextW(rgb_Str3);

	rgb_Str1.Format(_T("%d"),::wcstol(rgb_Str1,NULL,16));
	rgb_Str2.Format(_T("%d"),::wcstol(rgb_Str2,NULL,16));
	rgb_Str3.Format(_T("%d"),::wcstol(rgb_Str3,NULL,16));

	GetDlgItem(IDC_EDIT_R_SUB)->SetWindowTextW(rgb_Str1);
	GetDlgItem(IDC_EDIT_G_SUB)->SetWindowTextW(rgb_Str2);
	GetDlgItem(IDC_EDIT_B_SUB)->SetWindowTextW(rgb_Str3);

	return ;
}


void CMyColorDialogInfo::OnEnChangeEdit16jz()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strTemp=_T("");
	CEdit* editHelp = ((CEdit*)(GetDlgItem(IDC_EDIT_16JZ)));
	if(editHelp != GetFocus())
		return ;
	editHelp->GetWindowText(strTemp);
	int len = strTemp.GetLength();
	if(len > 6)
	{
		strTemp = strTemp.Left(6);
		editHelp->SetWindowText(strTemp);
		editHelp->SetSel(6,6,TRUE);
	}
	else
	{
		for (int i = 0; i < len; i ++)
		{
			if(strTemp.GetAt(i) < '0' || (strTemp.GetAt(i) > '9'&&strTemp.GetAt(i) < 'A')||strTemp.GetAt(i) > 'F')
			{
				strTemp = strTemp.Left(i);
				editHelp->SetWindowText(strTemp);
				editHelp->SetSel(i,i,TRUE);
			}
		}
	}
	long color = ::wcstol(strTemp,NULL,16);
	strTemp.Format(_T("%d"),color);
	SetDlgItemText(IDC_EDIT_10JZ,strTemp);
}


void CMyColorDialogInfo::OnEnChangeEdit10jz()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CMFCPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strTemp=_T("");
	CEdit* editHelp = ((CEdit*)(GetDlgItem(IDC_EDIT_10JZ)));
	if(editHelp != GetFocus())
		return ;
	editHelp->GetWindowText(strTemp);
	int len = strTemp.GetLength();
	for (int i = 0; i < len; i ++)
	{
		if(strTemp.GetAt(i) < '0' || strTemp.GetAt(i) > '9')
		{
			strTemp = strTemp.Left(i);
			editHelp->SetWindowText(strTemp);
			editHelp->SetSel(i,i,TRUE);
			break;
		}
	}
	long color = GetDlgItemInt(IDC_EDIT_10JZ);
	if(color > 0xFFFFFF)
	{
		//for (int i = 0; i < len; i ++)
		//{
		//	if(strTemp.GetAt(i) < '0' || strTemp.GetAt(i) > '9')
		//	{
		//		strTemp = strTemp.Left(i);
		//		editHelp->SetWindowText(strTemp);
		//		editHelp->SetSel(i,i,TRUE);
		//		break;
		//	}
		//}
		strTemp = strTemp.Left(len -1);
		editHelp->SetWindowText(strTemp);
		editHelp->SetSel(len -1,len-1,TRUE);
	}
	color = GetDlgItemInt(IDC_EDIT_10JZ);
	strTemp.Format(_T("%06X"),color);
	SetDlgItemText(IDC_EDIT_16JZ,strTemp);
}
