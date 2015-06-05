#include "stdafx.h"
#include "MyFindPictureClass.h"

MyFindPictureClass::MyFindPictureClass(void)
{
	pLoadBmpBuffer=NULL;
	pWndBmpBuffer=NULL;
	loadWidth=0;
	loadHeight=0;
	wndWidth=0;
	wndHeight=0;

	m_helpXpoint = 0;
	m_helpYpoint = 0;
}

MyFindPictureClass::~MyFindPictureClass(void)
{
}

bool MyFindPictureClass::loadBitmap(wchar_t* path)
{
	///////////////////////////���ص�λͼ //////////////////////////
	HBITMAP hbmp = (HBITMAP)LoadImage(NULL,path,IMAGE_BITMAP,0,0,LR_LOADFROMFILE );
	if(hbmp==NULL)
	{
		//::MessageBox(NULL,L"����λͼʧ��",L"TC",0);
		return false;
	}

	BITMAP bitmap;
	GetObject(hbmp, sizeof(BITMAP), &bitmap);

	BITMAPINFO info;
	HDC dc;
	dc=::CreateDC(L"DISPLAY",NULL,NULL,NULL);
	
	// 24λͼ��BITMAPINFO
	BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
	memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
	BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
	pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
	pInfo_Header->biWidth =bitmap.bmWidth;   
	pInfo_Header->biHeight = bitmap.bmHeight;   
	pInfo_Header->biPlanes = 1;   
	pInfo_Header->biBitCount = 24;   
	pInfo_Header->biCompression = BI_RGB;

	
	long width = bitmap.bmWidth;
	long height = bitmap.bmHeight;
	info.bmiHeader.biBitCount=24;

	loadWidth = width;
	loadHeight = height;

	DWORD bufSize = ( width * 3 + 3) / 4 * 4 * height;
	BYTE *buffer=new BYTE[bufSize];
	memset(buffer,0,sizeof(BYTE)*bufSize);
	if(!GetDIBits(dc, hbmp, 0, bitmap.bmHeight, buffer, pBITMAPINFO, DIB_RGB_COLORS))
	{
		//::MessageBox(NULL,L"����λͼʧ��",L"TC",0);
		return false;
	}

	pLoadBmpBuffer = new COLORREF*[height];     ///// ��ά���� �����洢ͼ�����ɫֵ
	for(int i=0;i<height;i++)
	{
		pLoadBmpBuffer[i]=new COLORREF[width];
	}
	COLORREF helpcolor=0;
	int pitch=width%4;
	for(int i=0;i<height;i++)
	{
		int realPitch=i*pitch;
		for(int j=0;j<width;j++)
		{
			UCHAR b=buffer[(i*width+j)*3+realPitch];
			UCHAR g=buffer[(i*width+j)*3+1+realPitch];
			UCHAR r=buffer[(i*width+j)*3+2+realPitch];
			helpcolor=RGB(r,g,b);

			pLoadBmpBuffer[height-i-1][j]=helpcolor;	
		}
	}
	///////////////////////////��ü���λͼ ��ɫ�ɹ� //////////////////////////
	delete [] buffer;
	::DeleteDC(dc);
	::free(pBITMAPINFO);
	::DeleteObject(hbmp);
	return true;
}

// bool MyFindPictureClass::catchWindowBitmap()
// {
// 	///////////////////////////����λͼ //////////////////////////
// 	// Ŀ�괰�岻����С��	
// 	HWND src_hWnd = ::GetDesktopWindow();
//     RECT rc;
//     ::GetWindowRect(src_hWnd, &rc);
//     // 24λͼ��BITMAPINFO
//     BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
//     memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
//     BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
//     pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
//     pInfo_Header->biWidth = rc.right - rc.left;   
//     pInfo_Header->biHeight = (rc.bottom - rc.top);   
//     pInfo_Header->biPlanes = 1;   
//     pInfo_Header->biBitCount = 24;   
//     pInfo_Header->biCompression = BI_RGB;
// 
// 	HDC dc;
// 	dc=::CreateDC(L"DISPLAY",NULL,NULL,NULL);
// 	int Width=pInfo_Header->biWidth;
// 	int Height=pInfo_Header->biHeight;
// 	HBITMAP hBitmap=::CreateCompatibleBitmap(dc,Width,Height);
// 	HDC tdc;
// 	tdc=::CreateCompatibleDC(dc);
// 	HBITMAP hOldBitmap=(HBITMAP)::SelectObject(tdc,hBitmap);
// 	BitBlt(tdc,0,0,Width,Height,dc,0,0,SRCCOPY);
// 	hBitmap=(HBITMAP)::SelectObject(tdc,hOldBitmap);
// 
//     // �������buf
//     DWORD bufSize = (pInfo_Header->biWidth * 3 + 3) / 4 * 4 * pInfo_Header->biHeight;
//     BYTE * pBuffer = new BYTE[bufSize];
// 
// 	int aHeight=pInfo_Header->biHeight;
// 
//     if(::GetDIBits(tdc, hBitmap, 0, aHeight, pBuffer,pBITMAPINFO, DIB_RGB_COLORS) == 0)
//     {
//         ::MessageBox(NULL,L"ǰ̨��ͼ����λͼʧ��",L"TC",0);
// 		return false;
//     }
// 
// 	int width=pBITMAPINFO->bmiHeader.biWidth;
// 	int height=pBITMAPINFO->bmiHeader.biHeight;
// 
// 	wndWidth = width;
// 	wndHeight = height;
// 
// 	COLORREF helpcolor=0;
// /*	int x=0,y=0;*/
// 
// 	pWndBmpBuffer = new COLORREF*[height];     ///// ��ά���� �����洢ͼ�����ɫֵ
// 	for(int i=0;i<height;i++)
// 	{
// 		pWndBmpBuffer[i]=new COLORREF[width];
// 	}
// 
// 	int pitch=width%4;
// 	for(int i=0;i<height;i++)
// 	{
// 		int realPitch=i*pitch;
// 		for(int j=0;j<width;j++)
// 		{
// 			UCHAR b=pBuffer[(i*width+j)*3+realPitch];
// 			UCHAR g=pBuffer[(i*width+j)*3+1+realPitch];
// 			UCHAR r=pBuffer[(i*width+j)*3+2+realPitch];
// 			helpcolor=RGB(r,g,b);
// 
// 			pWndBmpBuffer[height-i-1][j]=helpcolor;	
// 		}
// 	}
// 
//     free(pBITMAPINFO);
//     ::DeleteObject(hBitmap);
// 	delete [] pBuffer;
//     ::DeleteDC(tdc);
// 	::DeleteDC(dc);
// 	return true;
// 	///////////////////////////��ȡ����λͼ�� ��ɫ�ɹ� //////////////////////////
// }
// 
// bool MyFindPictureClass::processBKWindows(HWND src_hWnd)
// {
// 	RECT rc;
//     ::GetClientRect(src_hWnd, &rc);
//     // 24λͼ��BITMAPINFO
//     BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
//     memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
//     BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
//     pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
//     pInfo_Header->biWidth = rc.right - rc.left;   
//     pInfo_Header->biHeight = (rc.bottom - rc.top);   
//     pInfo_Header->biPlanes = 1;   
//     pInfo_Header->biBitCount = 24;   
//     pInfo_Header->biCompression = BI_RGB;
// 
//     // ��������DC ��ӡĿ�괰��
//     HDC src_hdc = ::GetWindowDC(src_hWnd);        
//     HBITMAP hBitmap = ::CreateCompatibleBitmap(src_hdc,pInfo_Header->biWidth, pInfo_Header->biHeight);
//     HDC hdcCompatible = ::CreateCompatibleDC(src_hdc); 
//     ::SelectObject(hdcCompatible, hBitmap);
//     ::PrintWindow(src_hWnd, hdcCompatible,0);
//      //BitBlt(hdcCompatible,0,0,pInfo_Header->biWidth,pInfo_Header->biHeight,src_hdc,0,0,SRCCOPY);  
// 
//     // �������buf
//     DWORD bufSize = (pInfo_Header->biWidth * 3 + 3) / 4 * 4 * pInfo_Header->biHeight;
//     BYTE * pBuffer = new BYTE[bufSize];
// 
// 	int aHeight=pInfo_Header->biHeight;
// 
//     if(::GetDIBits(hdcCompatible, hBitmap, 0, aHeight, pBuffer,pBITMAPINFO, DIB_RGB_COLORS) == 0)
//     {
//        return false;
//     }
// 
// 	wndWidth=pBITMAPINFO->bmiHeader.biWidth;
// 	wndHeight=pBITMAPINFO->bmiHeader.biHeight;
// 
// 	pWndBmpBuffer = new COLORREF*[wndHeight];             /////��ά���� �����洢ͼ�����ɫֵ
// 
// 	for(int i=0;i<wndHeight;i++)
// 	{
// 		pWndBmpBuffer[i]=new COLORREF[wndWidth];
// 	}
// 
// 	COLORREF helpcolor=0;
// 	int pitch=wndWidth%4;
// 	for(int i=0;i<wndHeight;i++)
// 	{
// 		int realPitch=i*pitch;
// 		for(int j=0;j<wndWidth;j++)
// 		{
// 			UCHAR b=pBuffer[(i*wndWidth+j)*3+realPitch];
// 			UCHAR g=pBuffer[(i*wndWidth+j)*3+1+realPitch];
// 			UCHAR r=pBuffer[(i*wndWidth+j)*3+2+realPitch];
// 			helpcolor=RGB(r,g,b);
// 
// 			pWndBmpBuffer[wndHeight-i-1][j]=helpcolor;	
// 		}
// 	}
// 
//     ::ReleaseDC(src_hWnd, src_hdc);  
//     free(pBITMAPINFO);
//     ::DeleteDC(hdcCompatible);
//     ::DeleteObject(hBitmap);
// 	delete [] pBuffer;
// 	return true;
// }


bool MyFindPictureClass::my_WindowBitmap(HWND my_hWnd,int type) //type����ģʽ0��ǰ̨ 1:��̨
{
	///////////////////////////����λͼ //////////////////////////
	//type=0 ץȡwindowsλͼ type=1 ץȡ��̨λͼ type=0ʱ,hwnd����������Ϊ0
	// Ŀ�괰�岻����С��	
	HWND src_hWnd = 0;
	RECT rc;
	if(type==0)
	{
		src_hWnd = ::GetDesktopWindow();
		::GetWindowRect(src_hWnd, &rc);
	}
	else if(type==1)
	{
		src_hWnd = my_hWnd;
		::GetClientRect(src_hWnd, &rc);
	}

	// 24λͼ��BITMAPINFO
	BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
	memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
	BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
	pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
	pInfo_Header->biWidth = rc.right - rc.left;   
	pInfo_Header->biHeight = (rc.bottom - rc.top);   
	pInfo_Header->biPlanes = 1;   
	pInfo_Header->biBitCount = 24;   
	pInfo_Header->biCompression = BI_RGB;

	// ��������DC ��ӡĿ�괰��
	HDC src_hdc;
	HBITMAP hBitmap;
	if(type==0)
	{
		src_hdc = ::CreateDC(L"DISPLAY",NULL,NULL,NULL);
	}       
	else if(type==1)
	{
		src_hdc = ::GetWindowDC(src_hWnd); 
	}    
	hBitmap  = ::CreateCompatibleBitmap(src_hdc,pInfo_Header->biWidth, pInfo_Header->biHeight);
	HDC tdc = ::CreateCompatibleDC(src_hdc);    
	HBITMAP hOldBitmap;
	if(type==0)
	{
		hOldBitmap=(HBITMAP)::SelectObject(tdc,hBitmap);
		BitBlt(tdc,0,0,pInfo_Header->biWidth,pInfo_Header->biHeight,src_hdc,0,0,CAPTUREBLT|SRCCOPY);
		hBitmap=(HBITMAP)::SelectObject(tdc,hOldBitmap);
	}       
	else if(type==1)
	{
		::SelectObject(tdc, hBitmap);
		::PrintWindow(src_hWnd, tdc,0);
	}    

	// �������buf
	DWORD bufSize = (pInfo_Header->biWidth * 3 + 3) / 4 * 4 * pInfo_Header->biHeight;
	BYTE * pBuffer = new BYTE[bufSize];

	int aHeight=pInfo_Header->biHeight;

	if(::GetDIBits(tdc, hBitmap, 0, aHeight, pBuffer,pBITMAPINFO, DIB_RGB_COLORS) == 0)
	{
		//::MessageBox(NULL,L"����λͼʧ��",L"TC",0);
		return false;
	}

	wndWidth=pBITMAPINFO->bmiHeader.biWidth;
	wndHeight=pBITMAPINFO->bmiHeader.biHeight;

	pWndBmpBuffer = new COLORREF*[wndHeight];             /////��ά���� �����洢ͼ�����ɫֵ

	for(int i=0;i<wndHeight;i++)
	{
		pWndBmpBuffer[i]=new COLORREF[wndWidth];
	}

	COLORREF helpcolor=0;
	int pitch=wndWidth%4;
	for(int i=0;i<wndHeight;i++)
	{
		int realPitch=i*pitch;
		for(int j=0;j<wndWidth;j++)
		{
			UCHAR b=pBuffer[(i*wndWidth+j)*3+realPitch];
			UCHAR g=pBuffer[(i*wndWidth+j)*3+1+realPitch];
			UCHAR r=pBuffer[(i*wndWidth+j)*3+2+realPitch];
			helpcolor=RGB(r,g,b);

			pWndBmpBuffer[wndHeight-i-1][j]=helpcolor;	
		}
	}
	if(type==0)
	{
		::DeleteDC(src_hdc);
	}       
	else if(type==1)
	{
		::ReleaseDC(src_hWnd, src_hdc);
	}    	  
	free(pBITMAPINFO);
	::DeleteObject(hBitmap);
	delete [] pBuffer;
	::DeleteDC(tdc);	
	return true;
	///////////////////////////��ȡ����λͼ�� ��ɫ�ɹ� //////////////////////////
}

int MyFindPictureClass::findPicture(HWND hwnd, int left, int top, int right, int bottom, 
									wchar_t* path,  int colorOffset, double simi, int dir,
									int &xpos, int &ypos)
{
	int index = -1;
	int retIndex=-1;
	bool isFind=false;
	m_colorOffsR = GetRValue(colorOffset);
	m_colorOffsG = GetGValue(colorOffset);
	m_colorOffsB = GetBValue(colorOffset);
	/*m_sim = simi;*/  //δʹ�øñ���
	m_simColor = 0;
	if(simi==0.5)
		m_simColor=49;

	else if(simi==0.6)
		m_simColor=38;

	else if(simi==0.7)
		m_simColor=29;

	else if(simi==0.8)
		m_simColor=18;

	else if(simi==0.9)
		m_simColor=9;
	/////////////////////////////////////

	m_Dir = dir;
	if(hwnd)
	{
		//if(!processBKWindows(hwnd))
		if(my_WindowBitmap(hwnd,1) == 0)  //1 ��̨
			return retIndex; //��û�м��سɹ��������Ҳ���� -1
	}
	else
	{
		//if(catchWindowBitmap()==0)
		if(my_WindowBitmap(hwnd,0) == 0) //0 ǰ̨
		{
			return retIndex;
		}
	}

	/////////////////////////////�����ĵ�ı߽�ֵ�Է�ֹԽ��//////////////////////////
	wchar_t pathBuffer[MAX_PATH]={0};	
	m_Left = left;
	m_Top = top;
	m_Right = right;
	m_bottom = bottom;

	if(left<0)
		m_Left = left =0;
	if(left >= wndWidth)
		m_Left = wndWidth-1;
	
    if(top<0)
		m_Top = top =0;
	if(top >= wndHeight)
		m_Top = wndHeight-1;

    if(right >= wndWidth)
		m_Right=wndWidth-1;

	if(bottom >= wndHeight)
		m_bottom=wndHeight-1;

	/////////////////// �������ͼ /////////////////////
	int col=0;

    while(*path)
    {
        if(*path!=L'|')
        {
            pathBuffer[col++]=*path;
            path++;
            continue;
        }
        else
        {
            if(findImage(pathBuffer,xpos,ypos))
            {
                index++;
                retIndex=index;
                break;
            }

            ::memset(pathBuffer,0,sizeof(wchar_t)*MAX_PATH);
            col=0;
            path++;
            index++; 
        }
    }

    //////////////���һ��ͼ������ֻ��һ��ͼ///////////
    if(retIndex==-1)
    {		
        if(findImage(pathBuffer,xpos,ypos))
        {
            index++;
            retIndex=index;
        }
    }

	for(int i=0;i<wndHeight;i++)
	{
		delete [] pWndBmpBuffer[i];
		pWndBmpBuffer[i] = NULL;
	}

	delete [] pWndBmpBuffer;
	pWndBmpBuffer=NULL;
	return retIndex;
}

bool MyFindPictureClass::findImage(wchar_t* path,int &xpos,int &ypos)
{
	bool isFind=false;

	if(loadBitmap(path)==0)
	{
		return false;
	}

	switch(this->m_Dir)
	{
	case 0:
		isFind=leftToRightFromTop(xpos,ypos); //0:������,���ϵ���
		break;

	case 1:
		isFind=leftToRightFromBottom(xpos,ypos);//1:���ҵ���,���ϵ���
		break;

	case 2:
		isFind=rightToLeftFromTop(xpos,ypos);//2:������,���µ���
		break;
	
	case 3:
		isFind=rightToLeftFromBottom(xpos,ypos);//3:���ҵ���,���µ���
		break;	
	}
	for(int i=0;i<loadHeight;i++)
	{
		delete [] pLoadBmpBuffer[i];
		pLoadBmpBuffer[i] = NULL;
	}

	delete [] pLoadBmpBuffer;
	pLoadBmpBuffer=NULL;

	return isFind;
}

////////////////// ���� ��ʽ //////////////////
////////////////////////////////////////////////0��������,���ϵ���//////////////////////////
bool MyFindPictureClass::leftToRightFromTop(int &xpos,int &ypos)
{
	bool isFind=false;
	COLORREF pColor = pLoadBmpBuffer[0][0];  //// Ŀ��ͼƬ�ı���ɫ
	if(pLoadBmpBuffer[0][0]==pLoadBmpBuffer[0][loadWidth-1]&&
		pLoadBmpBuffer[0][0]==pLoadBmpBuffer[loadHeight-1][loadWidth-1]&&
		pLoadBmpBuffer[0][0]==pLoadBmpBuffer[loadHeight-1][0])
    {
        int startx=0,starty=0;
        for(int m=0;m<loadHeight;m++)
        {
            for(int n=0;n<loadWidth;n++)
            {
                if(pLoadBmpBuffer[m][n]==pColor)  
                {
                    //////���˵�������ı���͸��ɫ
                    continue;
                }
                else
                {
					//2012.2.28 �޸����Ƶ�ͼ�޷�ʶ�������.
                    startx=n;
                    starty=m;
                    goto toSerch;
                }
            }
        }


toSerch:
		for(int i=m_Top; i<= m_bottom;i++)
		{
			if(m_bottom-i<loadHeight)
			{
				goto end;
			}
			for(int j=m_Left;j<=m_Right;j++)
			{
				if(m_Right-j<loadWidth)
				{
					break;
				}
				if(comparaLeftToRightFromTop(i,j,startx,starty))
				{
					isFind=true;
					xpos=j;
					ypos=i;
					goto end;
				}
			}
		}
	}
	else
	{
		::MessageBox(NULL,_T("Ŀ��ͼƬ����͸��ͼ������ͼƬ�ĸ�������ɫ�Ƿ�һ�£�"),_T(""),0);
		for(int i=m_Top; i<= m_bottom;i++)
		{
			if(m_bottom-i<loadHeight)
			{
				goto end;
			}
			for(int j=m_Left;j<=m_Right;j++)
			{
				if(m_Right-j<loadWidth)
				{
					break;
				}
				if(comparaLeftToRightFromTopEx(i,j))
				{
					isFind=true;
					xpos=j;
					ypos=i;
					goto end;
				}
			}
        }
    }
end:

	return isFind;
}
////////������ɫΪ͸����ͼƬ////////////////
bool MyFindPictureClass::comparaLeftToRightFromTop(int h,int w,int startX,int startY)
{
	int fristX=0;
	int fristY=0;
	bool isFrist=true;
	COLORREF pColor = pLoadBmpBuffer[0][0];  //// Ŀ��ͼƬ�ı���ɫ

	BYTE loadR=0, loadG=0, loadB=0;
	BYTE wndR =0, wndG =0, wndB =0;
	int absResult =0;
	COLORREF pLoadColor = 0,pWndColor = 0;
	for(int i=startY;i<loadHeight;i++)
	{
		for(int j=0;j<loadWidth;j++)
		{
			if(pLoadBmpBuffer[i][j]==pColor)  
			{
				//////���˵�������ı���͸��ɫ
				continue;
			}
			else
			{				
				//if(isFrist)
				//{
    //                COLORREF colorLoad=pLoadBmpBuffer[i][j];
				//	loadR = GetRValue(colorLoad);
				//	loadG = GetGValue(colorLoad);
				//	loadB = GetBValue(colorLoad);
    //                COLORREF colorHwnd=pWndBmpBuffer[h+i/*-fristY*/][w+j/*-fristX*/];
				//	wndR = GetRValue(colorHwnd);
				//	wndG = GetGValue(colorHwnd);
				//	wndB = GetBValue(colorHwnd);
				//	if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
				//	{
				//		fristX=j;
				//		fristY=i;
				//		m_helpXpoint = j;
				//		m_helpYpoint = i;
    //                  isFrist = false;
    //                    continue;

				//	}
				//	else
				//	{
				//		///////////�����,��������///////////
				//		return false;
				//	}
				//}

                pLoadColor=pLoadBmpBuffer[i][j];
				loadR = GetRValue(pLoadColor);
				loadG = GetGValue(pLoadColor);
				loadB = GetBValue(pLoadColor);

                pWndColor=pWndBmpBuffer[h+i/*-fristY*/][w+j/*-fristX*/];
				wndR = GetRValue(pWndColor);
				wndG = GetGValue(pWndColor);
				wndB = GetBValue(pWndColor);
				absResult=abs(loadR-wndR)+abs(loadG-wndG)+abs(loadB-wndB);   ///�������ƶȱȽ�
				///////������ǻ��ϵ��
				if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB ||absResult<=m_simColor)
				{
					continue;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return true;
}
////////������ɫΪ��͸����ͼƬ////////////////
bool MyFindPictureClass::comparaLeftToRightFromTopEx(int h,int w)
{	
	BYTE loadR=0, loadG=0, loadB=0;
	BYTE wndR =0, wndG =0, wndB =0;
	int absResult =0;
	COLORREF pLoadColor = 0,pWndColor = 0;
	for(int i=0;i<loadHeight;i++)
	{
		for(int j=0;j<loadWidth;j++)
		{

            pLoadColor=pLoadBmpBuffer[i][j];
			loadR = GetRValue(pLoadColor);
			loadG = GetGValue(pLoadColor);
			loadB = GetBValue(pLoadColor);

            pWndColor=pWndBmpBuffer[h+i][w+j];
			wndR = GetRValue(pWndColor);
			wndG = GetGValue(pWndColor);
			wndB = GetBValue(pWndColor);

			//absResult=(loadR-wndR)+abs(loadG-wndG)+abs(loadB-wndB);   ///�������ƶȱȽ�
			//if(pLoadBmpBuffer[i][j] == pWndBmpBuffer[h+i][w+j])
			if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
			{
				continue;
			}
			else
			{
				return false;
			}

		}
	}
	return true;
}


///////////////////////////////////////////////1��������,���µ���//////////////////////////
bool MyFindPictureClass::leftToRightFromBottom(int &xpos,int &ypos)
{
	bool isFind=false;
	COLORREF pColor = pLoadBmpBuffer[0][0];  //// Ŀ��ͼƬ�ı���ɫ
	if(pLoadBmpBuffer[0][0]==pLoadBmpBuffer[0][loadWidth-1]&&
		pLoadBmpBuffer[0][0]==pLoadBmpBuffer[loadHeight-1][loadWidth-1]&&
		pLoadBmpBuffer[0][0]==pLoadBmpBuffer[loadHeight-1][0])
	{
		int startx=0,starty=0;
        for(int m=loadHeight-1;m>=0;m--)
        {
            for(int n=0;n<loadWidth;n++)
            {
                if(pLoadBmpBuffer[m][n] == pColor)  
                {
                    //////���˵�������ı���͸��ɫ
                    continue;
                }
                else
                {
					//2012.2.28 �޸����Ƶ�ͼ�޷�ʶ�������.
                    startx=n;
                    starty=m;
                    goto toSerch;
                }
            }
        }

toSerch:
		for(int i=m_bottom-1;i>=m_Top;i--)
		{
			if( i-m_Top < loadHeight)	goto end;

			for(int j=m_Left;j<m_Right;j++)
			{
				if(m_Right-j < loadWidth) break;

				if(comparaLeftToRightFromBottom(i,j,startx,starty))
				{
					isFind=true;
					xpos=j/*-m_helpXpoint*/;
					//ypos=i/*+m_helpYpoint-loadHeight+1*/;
					ypos=i - loadHeight + 1;
					goto end;
				}
			}
		}
	}
	else
	{
		for(int i=m_bottom-1;i>=m_Top;i--)
		{
			if( i-m_Top < loadHeight)	goto end;

			for(int j=m_Left;j<m_Right;j++)
			{
				if(m_Right-j < loadWidth) break;

				if(comparaLeftToRightFromBottomEx(i,j))
				{
					isFind=true;
					xpos=j;
					ypos=i-loadHeight+1;
					goto end;
				}
			}
		}
	}

end:
	return isFind;
}
////////������ɫΪ͸����ͼƬ////////////////
bool MyFindPictureClass::comparaLeftToRightFromBottom(int h,int w,int startX,int startY)
{
	int fristX=0;
	int fristY=0;
	bool isFrist=true;
	COLORREF pColor = pLoadBmpBuffer[0][0];  //// Ŀ��ͼƬ�ı���ɫ

	BYTE loadR=0, loadG=0, loadB=0;
	BYTE wndR =0, wndG =0, wndB =0;
	int absResult =0;
	//int colAdd =-1;
	COLORREF pLoadColor = 0,pWndColor = 0;
	for(int i=startY;i>=0;i--)
	{
		//colAdd++;
		for(int j=0;j<loadWidth;j++)
		{
			if(pLoadBmpBuffer[i][j]==pColor)  
			{
				//////���˵�������ı���͸��ɫ
				continue;
			}
			else
			{
				//if(isFrist)
				//{
				//	loadR = GetRValue(pLoadBmpBuffer[i][j]);
				//	loadG = GetGValue(pLoadBmpBuffer[i][j]);
				//	loadB = GetBValue(pLoadBmpBuffer[i][j]);

				//	wndR = GetRValue(pWndBmpBuffer[h][w]);
				//	wndG = GetGValue(pWndBmpBuffer[h][w]);
				//	wndB = GetBValue(pWndBmpBuffer[h][w]);

				//	if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
				//	{
				//		fristX=j;
				//		fristY=i;
				//		m_helpXpoint = j;
				//		m_helpYpoint = colAdd;
				//	}
				//	else
				//	{
				//		///////////����ȡ�����������///////////
				//		return false;
				//	}
				//	isFrist = false;
				//}

				pLoadColor = pLoadBmpBuffer[i][j];
				loadR = GetRValue(pLoadColor);
				loadG = GetGValue(pLoadColor);
				loadB = GetBValue(pLoadColor);

				pWndColor = pWndBmpBuffer[h-(loadHeight-i-1)][w+j];
				wndR = GetRValue(pWndColor);
				wndG = GetGValue(pWndColor);
				wndB = GetBValue(pWndColor);
				absResult=(loadR-wndR)+abs(loadG-wndG)+abs(loadB-wndB);   ///�������ƶȱȽ�

				//if(pLoadBmpBuffer[i][j] == pWndBmpBuffer[h-colAdd][w+(j-fristX)])
				if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
				{
					continue;
				}
				else
				{
					return false;
				}
			}
		}
	}
	return true;
}
////////������ɫΪ��͸����ͼƬ////////////////
bool MyFindPictureClass::comparaLeftToRightFromBottomEx(int h,int w)
{
	BYTE loadR=0, loadG=0, loadB=0;
	BYTE wndR =0, wndG =0, wndB =0;
	int absResult =0;
	//int colAdd =-1;
	COLORREF pLoadColor = 0,pWndColor = 0;
	for(int i=loadHeight -1;i>=0;i--)
	{
		//colAdd++;
		for(int j=0;j<loadWidth;j++)
		{
			pLoadColor = pLoadBmpBuffer[i][j];
			loadR = GetRValue(pLoadColor);
			loadG = GetGValue(pLoadColor);
			loadB = GetBValue(pLoadColor);

			pWndColor = pWndBmpBuffer[h-(loadHeight-i-1)][w+j];
			wndR = GetRValue(pWndColor);
			wndG = GetGValue(pWndColor);
			wndB = GetBValue(pWndColor);

			absResult=(loadR-wndR)+abs(loadG-wndG)+abs(loadB-wndB);   ///�������ƶȱȽ�
			//if(pLoadBmpBuffer[i][j] == pWndBmpBuffer[h+i][w+j])
			if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
			{
				continue;
			}
			else
			{
				return false;
			}

		}
	}
	return true;
}

////////////////////////////////////////////////2�����ҵ���,���ϵ���////////////////////////
bool MyFindPictureClass::rightToLeftFromTop(int &xpos,int &ypos)
{
	bool isFind=false;
	COLORREF pColor = pLoadBmpBuffer[0][0];  //// Ŀ��ͼƬ�ı���ɫ
	if(pLoadBmpBuffer[0][0]==pLoadBmpBuffer[0][loadWidth-1]&&
		pLoadBmpBuffer[0][0]==pLoadBmpBuffer[loadHeight-1][loadWidth-1]&&
		pLoadBmpBuffer[0][0]==pLoadBmpBuffer[loadHeight-1][0])
	{
		int startx=0,starty=0;
        for(int m=0;m<loadHeight;m++)
        {
            for(int n=loadWidth-1;n>=0;n--)
            {
                if(pLoadBmpBuffer[m][n]==pColor)  
                {
                    //////���˵�������ı���͸��ɫ
                    continue;
                }
                else
                {
					//2012.2.28 �޸����Ƶ�ͼ�޷�ʶ�������.
                    startx=n;
                    starty=m;
                    goto toSerch;
                }
            }
        }

toSerch:
		for(int i=m_Top; i<= m_bottom;i++)
		{
			if(m_bottom-i < loadHeight) goto end;

			for(int j=m_Right-1;j>=m_Left;j--)
			{
				if(j - m_Left < loadWidth) break;

				if(comparaRightToLeftFromTop(i,j,startx,starty))
				{
					isFind=true;
					//xpos=j/*+m_helpXpoint-loadWidth+1*/;
					xpos=j-loadWidth+1;
					ypos=i/*-m_helpYpoint*/;
					goto end;
				}
			}
		}
	}
	else
	{
		for(int i=m_Top; i<= m_bottom;i++)
		{
			if(m_bottom-i < loadHeight) goto end;

			for(int j=m_Right-1;j>=m_Left;j--)
			{		
				if(j - m_Left < loadWidth) break;

				if(comparaRightToLeftFromTopEx(i,j))
				{
					isFind=true;
					xpos=j-loadWidth+1;
					ypos=i;
					goto end;
				}
			}
		}
	}

end:

	return isFind;
}
////////������ɫΪ͸����ͼƬ////////////////
bool MyFindPictureClass::comparaRightToLeftFromTop(int h,int w,int startX,int startY)
{
	int fristX=0;
	int fristY=0;
	bool isFrist=true;
	COLORREF pColor = pLoadBmpBuffer[0][0];  //// Ŀ��ͼƬ�ı���ɫ

	BYTE loadR=0, loadG=0, loadB=0;
	BYTE wndR =0, wndG =0, wndB =0;
	int absResult =0;

	//int lineAdd =-1;
	COLORREF pLoadColor = 0,pWndColor = 0;
	for(int i=startY;i<loadHeight;i++)
	{
		//lineAdd =-1;
		for(int j=loadWidth-1;j>=0;j--)
		{
			//lineAdd++;
			if(pLoadBmpBuffer[i][j]==pColor)  
			{
				//////���˵�������ı���͸��ɫ
				continue;
			}
			//else
			//{
			//	if(isFrist)
			//	{
			//		loadR = GetRValue(pLoadBmpBuffer[i][j]);
			//		loadG = GetGValue(pLoadBmpBuffer[i][j]);
			//		loadB = GetBValue(pLoadBmpBuffer[i][j]);

			//		wndR = GetRValue(pWndBmpBuffer[h][w]);
			//		wndG = GetGValue(pWndBmpBuffer[h][w]);
			//		wndB = GetBValue(pWndBmpBuffer[h][w]);
			//		//if(pLoadBmpBuffer[i][j]==pWndBmpBuffer[h][w])
			//		if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
			//		{
			//			fristX=j;
			//			fristY=i;
			//			m_helpXpoint = lineAdd;
			//			m_helpYpoint = i;
			//		}
			//		else
			//		{
			//			///////////����ȡ�����������///////////
			//			return false;
			//		}
			//		isFrist = false;
			//	}

				pLoadColor = pLoadBmpBuffer[i][j];
				loadR = GetRValue(pLoadColor);
				loadG = GetGValue(pLoadColor);
				loadB = GetBValue(pLoadColor);

				//wndR = GetRValue(pWndBmpBuffer[h+i-fristY][w+j-fristX]);
				//wndG = GetGValue(pWndBmpBuffer[h+i-fristY][w+j-fristX]);
				//wndB = GetBValue(pWndBmpBuffer[h+i-fristY][w+j-fristX]);
				pWndColor = pWndBmpBuffer[h+i][w-(loadWidth-j-1)];
				wndR = GetRValue(pWndColor);
				wndG = GetGValue(pWndColor);
				wndB = GetBValue(pWndColor);

				absResult=(loadR-wndR)+abs(loadG-wndG)+abs(loadB-wndB);   ///�������ƶȱȽ�

				//if(pLoadBmpBuffer[i][j] == pWndBmpBuffer[h+i][w+(/ *fristX* /0-lineAdd)])
				if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
				{
					continue;
				}
				else
				{
					return false;
				}
			//}
		}
	}
	return true;
}
////////������ɫΪ��͸����ͼƬ////////////////
bool MyFindPictureClass::comparaRightToLeftFromTopEx(int h,int w)
{
	BYTE loadR=0, loadG=0, loadB=0;
	BYTE wndR =0, wndG =0, wndB =0;
	int absResult =0;

	//int lineAdd =-1;
	COLORREF pLoadColor = 0,pWndColor = 0;
	for(int i=0;i<loadHeight;i++)
	{
		//lineAdd = -1;
		for(int j=loadWidth-1;j>=0;j--)
		{
			//lineAdd++;
			pLoadColor = pLoadBmpBuffer[i][j];
			loadR = GetRValue(pLoadColor);
			loadG = GetGValue(pLoadColor);
			loadB = GetBValue(pLoadColor);

			pWndColor = pWndBmpBuffer[h+i][w-(loadWidth-j-1)];
			wndR = GetRValue(pWndColor);
			wndG = GetGValue(pWndColor);
			wndB = GetBValue(pWndColor);

			absResult=(loadR-wndR)+abs(loadG-wndG)+abs(loadB-wndB);   ///�������ƶȱȽ�
			//if(pLoadBmpBuffer[i][j] == pWndBmpBuffer[h+i][w+j])
			if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
			{
				continue;
			}
			else
			{
				return false;
			}

		}
	}
	return true;
}

///////////////////////////////////////////////////3�����ҵ���,���µ���////////////////////
bool MyFindPictureClass::rightToLeftFromBottom(int &xpos,int &ypos)
{
	bool isFind=false;
	COLORREF pColor = pLoadBmpBuffer[0][0];  //// Ŀ��ͼƬ�ı���ɫ
	if(pLoadBmpBuffer[0][0]==pLoadBmpBuffer[0][loadWidth-1]&&
		pLoadBmpBuffer[0][0]==pLoadBmpBuffer[loadHeight-1][loadWidth-1]&&
		pLoadBmpBuffer[0][0]==pLoadBmpBuffer[loadHeight-1][0])
	{
		int startx=0,starty=0;
        for(int m=loadHeight-1;m>=0;m--)
        {
            for(int n=loadWidth-1;n>=0;n--)
            {
                if(pLoadBmpBuffer[m][n]==pColor)  
                {
                    //////���˵�������ı���͸��ɫ
                    continue;
                }
                else
                {
					//2012.2.28 �޸����Ƶ�ͼ�޷�ʶ�������.
                    startx=n;
                    starty=m;
                    goto toSerch;
                }
            }
        }

toSerch:

		for(int i=m_bottom-1;i>=m_Top;i--)
		{
            if(i - m_Top<loadHeight)
            {
                goto end;
            }

			for(int j=m_Right-1;j>=m_Left;j--)
			{
                if(j - m_Left<loadWidth)
                {
                    break;
                }

				if(comparaRightToLeftFromBottom(i,j,startx,starty))
				{
					isFind=true;
					xpos=j - loadWidth + 1;
					ypos=i - loadHeight + 1;
					goto end;
				}
			}
		}
	}
	else
	{
		for(int i=m_bottom-1;i>=m_Top;i--)
		{
            if(i - m_Top<loadHeight)
            {
                goto end;
            }

			for(int j=m_Right-1;j>=m_Left;j--)
			{
                if(j - m_Left<loadWidth)
                {
                    break;
                }

				if(comparaRightToLeftFromBottomEx(i,j))
				{
					isFind=true;
					xpos=j - loadWidth +1;
					ypos=i - loadHeight +1;
					goto end;
				}
			}
		}
	}
end:
	return isFind;
}
	////////������ɫΪ͸����ͼƬ////////////////
bool MyFindPictureClass::comparaRightToLeftFromBottom(int h,int w,int startX,int startY)
{
	int fristX=0;
	int fristY=0;
	bool isFrist=true;
	COLORREF pColor = pLoadBmpBuffer[0][0];  //// Ŀ��ͼƬ�ı���ɫ

	BYTE loadR=0, loadG=0, loadB=0;
	BYTE wndR =0, wndG =0, wndB =0;
	int absResult =0;

	//int lineAdd=-1;
	//int colAdd =-1;
	COLORREF pLoadColor = 0,pWndColor = 0;
	for(int i=startY; i>=0; i--)
	{
		//colAdd ++;
		//lineAdd=-1;
		for(int j=loadWidth-1;j>=0;j--)
		{
			//lineAdd++;
			if(pLoadBmpBuffer[i][j]==pColor)  
			{
				//////���˵�������ı���͸��ɫ
				continue;
			}
			else
			{
				//if(isFrist)
				//{
				//	loadR = GetRValue(pLoadBmpBuffer[i][j]);
				//	loadG = GetGValue(pLoadBmpBuffer[i][j]);
				//	loadB = GetBValue(pLoadBmpBuffer[i][j]);

				//	wndR = GetRValue(pWndBmpBuffer[h][w]);
				//	wndG = GetGValue(pWndBmpBuffer[h][w]);
				//	wndB = GetBValue(pWndBmpBuffer[h][w]);

				//	if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
				//	{
				//		fristX=j;
				//		fristY=i;

				//		m_helpXpoint = lineAdd;
				//		m_helpYpoint = colAdd;
				//	}
				//	else
				//	{
				//		///////////����ȡ�����������///////////
				//		return false;
				//	}
				//	isFrist = false;
				//}
                pLoadColor=pLoadBmpBuffer[i][j];

				loadR = GetRValue(pLoadColor);
				loadG = GetGValue(pLoadColor);
				loadB = GetBValue(pLoadColor);
				
                //COLORREF colorWnd=pWndBmpBuffer[h-colAdd/*-fristY*/][w-lineAdd/*-fristX*/];
				pWndColor=pWndBmpBuffer[h-(loadHeight-i-1)][w-(loadWidth-j-1)];
				wndR = GetRValue(pWndColor);
				wndG = GetGValue(pWndColor);
				wndB = GetBValue(pWndColor);

				//absResult=(loadR-wndR)+abs(loadG-wndG)+abs(loadB-wndB);   ///�������ƶȱȽ�

				if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
				{
					continue;
				}
				else
				{
					return false;
				}
			}
		}
	}

	return true;
}
	////////������ɫΪ��͸����ͼƬ////////////////
bool MyFindPictureClass::comparaRightToLeftFromBottomEx(int h,int w)
{
	BYTE loadR=0, loadG=0, loadB=0;
	BYTE wndR =0, wndG =0, wndB =0;
	int absResult =0;

	//int lineAdd=-1;
	//int colAdd =-1;
	COLORREF pLoadColor = 0,pWndColor = 0;
	for(int i=loadHeight-1;i>=0;i--)
	{
		//colAdd ++;
		//lineAdd=-1;
		for(int j=loadWidth-1;j>=0;j--)
		{
			//lineAdd++;

            pLoadColor=pLoadBmpBuffer[i][j];
			loadR = GetRValue(pLoadColor);
			loadG = GetGValue(pLoadColor);
			loadB = GetBValue(pLoadColor);

            //COLORREF colorWnd=pWndBmpBuffer[h-colAdd][w-lineAdd];
			pWndColor=pWndBmpBuffer[h-(loadHeight-i-1)][w-(loadWidth-j-1)];
			wndR = GetRValue(pWndColor);
			wndG = GetGValue(pWndColor);
			wndB = GetBValue(pWndColor);

			//absResult=(loadR-wndR)+abs(loadG-wndG)+abs(loadB-wndB);   ///�������ƶȱȽ�
			if(abs(loadR-wndR)<=m_colorOffsR && abs(loadG-wndG)<=m_colorOffsG && abs(loadB-wndB)<=m_colorOffsB )
			{
				continue;
			}
			else
			{
				return false;
			}

		}
	}
	return true;
}

/////// ��ɫ�ڴ洦���� ����ٶ� //////////////////////
bool MyFindPictureClass::processCreenWindow(int color,int left,int top,int right,int bottom,double simi,int dir,int &x,int &y,wchar_t* colorStr,bool isMulitColor)
{
	int Width=GetSystemMetrics(SM_CXSCREEN);
	int Height=GetSystemMetrics(SM_CYSCREEN);

	////////////////////////////�ĵ�ı߽�ֵ�ж�////////////////
	if(right<left || top>bottom)
		return false;

	if(left<0)
		left=0;

	if(top<0)
		top=0;

	if(left>=Width)
		left=Width-1;

	if(top>=Height)
		top=Height-1;

	if(right>=Width)
		right=Width-1;

	if(bottom>=Height)
		bottom=Height-1;
	////////////////////////////////////////////////////////////

	// 24λͼ��BITMAPINFO
	BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
	memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
	BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
	pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
	pInfo_Header->biWidth = right - left;      //���
	pInfo_Header->biHeight = (bottom - top);   //����
	pInfo_Header->biPlanes = 1;				   //Ŀ���豸��λƽ����
	pInfo_Header->biBitCount = 24; //����ÿ�����ص��ֽ��� 24:16M���ɫͼ,һ��û�е�ɫ��,ͼ��������ÿ3���ֽڱ�ʾһ������,ÿ���ֽڱ�ʾһ��RGB����
	pInfo_Header->biCompression = BI_RGB; //��ʵλͼʱ�������ɫ�� 0:��ʾ������ɫ

	HDC dc;
	dc=::CreateDC(L"DISPLAY",NULL,NULL,NULL);

	HBITMAP hBitmap=::CreateCompatibleBitmap(dc,Width,Height);
	HDC tdc;
	tdc=::CreateCompatibleDC(dc);
	HBITMAP hOldBitmap=(HBITMAP)::SelectObject(tdc,hBitmap);
	BitBlt(tdc,0,0,pInfo_Header->biWidth,pInfo_Header->biHeight,dc,left,top,CAPTUREBLT|SRCCOPY);
	hBitmap=(HBITMAP)::SelectObject(tdc,hOldBitmap);

	// �������buf
	DWORD bufSize = (pInfo_Header->biWidth * 3 + 3) / 4 * 4 * pInfo_Header->biHeight;
	BYTE * pBuffer = new BYTE[bufSize];

	int aHeight=pInfo_Header->biHeight;

	if(::GetDIBits(tdc, hBitmap, 0, aHeight, pBuffer,pBITMAPINFO, DIB_RGB_COLORS) == 0)
	{
		//::MessageBox(NULL,L"��ȡColorλͼ����ʧ��",L"TC",0);
		return false;
	}

	int width=pBITMAPINFO->bmiHeader.biWidth;
	int height=pBITMAPINFO->bmiHeader.biHeight;

	COLORREF** pColorBuffer = new COLORREF*[height];     ///// ��ά���� �����洢ͼ�����ɫֵ
	for(int i=0;i<height;i++)
	{
		pColorBuffer[i]=new COLORREF[width];
	}

	int help_simi=0;
	if(simi==0.5)
		help_simi=49;

	else if(simi==0.6)
		help_simi=38;

	else if(simi==0.7)
		help_simi=29;

	else if(simi==0.8)
		help_simi=18;

	else if(simi==0.9)
		help_simi=9;

	COLORREF helpcolor=0;
	/*BYTE r1=0,g1=0,b1=0;*/
	int pitch=width%4;
	for(int i=0;i<height;i++)		//��ȡ��Χ��������ɫֵ,������
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

	//ת���������ɫֵ����
	BYTE rValue=0,gValue=0,bValue=0;
	rValue=GetRValue((DWORD)color);
	gValue=GetGValue((DWORD)color);
	bValue=GetBValue((DWORD)color);

	BYTE rHelpValue=0,gHelpValue=0,bHelpValue=0;

	//////////////////////////////�ĵ�ı߽�ֵ�ж�////////////////
	//if(left<0)
	//	left=0;
	//if(left>=Width)
	//	left=Width-1;
	//if(top<0)
	//	top=0;
	//if(top>=Height)
	//	top=Height-1;

	//if(right>=Width)
	//	right=Width-1;
	//if(bottom>=Height)
	//	bottom=Height-1;
	//////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	if(isMulitColor)  // // //////  �����ɫֵ����ɫ����
	{
		/////////////////////0 ������ ���ϵ��� ��ʽ����///////////////
		int absResult = 0;
		for(int i=0;i<bottom-top;i++)
		{
			for(int j=0;j<right-left;j++)
			{
				rHelpValue=GetRValue(pColorBuffer[i][j]);
				gHelpValue=GetGValue(pColorBuffer[i][j]);
				bHelpValue=GetBValue(pColorBuffer[i][j]);
				absResult=abs(rHelpValue-rValue)+abs(gHelpValue-gValue)+abs(bHelpValue-bValue);
				///////////////////�жϵ�һ����ɫֵ///////////////////////
				if(absResult<=help_simi)
				{
					bool IsTrue = false;
					int  c_col=0,c_xpoint=-1,c_ypoint=-1,c_num=0,colorValue=0,helpColor=0;
					wchar_t pointAndcolor[20]={0};
					int lenght = ::wcslen(colorStr);
					while(c_col<lenght&&lenght!=0)
					{
						//////��һ��xƫ������
						while(colorStr[c_col]!='|')
						{
							pointAndcolor[c_num] = colorStr[c_col];
							c_num ++;
							c_col++;
						}
						c_xpoint = ::wcstol(pointAndcolor,NULL,10);
						::memset(pointAndcolor,0,sizeof(wchar_t)*20);
						c_num = 0;
						c_col++;
						//////�ڶ���Yƫ������
						while(colorStr[c_col]!='|')
						{
							pointAndcolor[c_num] = colorStr[c_col];
							c_num ++;
							c_col++;
						}
						c_ypoint = ::wcstol(pointAndcolor,NULL,10);
						::memset(pointAndcolor,0,sizeof(wchar_t)*20);
						c_num = 0;
						c_col++;

						//////��������ɫֵ
						while(colorStr[c_col]!=','&&colorStr[c_col])
						{
							pointAndcolor[c_num] = colorStr[c_col];
							c_num ++;
							c_col++;
						}
						colorValue = ::wcstol(pointAndcolor,NULL,16);
						::memset(pointAndcolor,0,sizeof(wchar_t)*20);
						c_num = 0;
						c_col++;
						////////������Ѿ�������Ļ�ķ�Χ /////////
						//if(i+c_ypoint>=Height||j+c_xpoint>=Width)
						if(i+c_ypoint>=height||j+c_xpoint>=width)
							break;
						helpColor = pColorBuffer[i+c_ypoint][j+c_xpoint];
						absResult=abs(GetRValue(helpColor)-GetRValue(colorValue))+abs(GetGValue(helpColor)-GetGValue(colorValue))+abs(GetBValue(helpColor)-GetBValue(colorValue));
						if(absResult<=help_simi)
						{
							IsTrue = true;
						}
						else
						{
							IsTrue = false;
							break;
						}
					}

					if(IsTrue)
					{
						x=j+left;
						y=i+top;
						goto end;
					}
				}
			}
		}
	}
	else
	{
		// // //////  ������ɫֵ����ɫ����
		if(dir == 0)
		{
			/////////////////////0 ������ ���ϵ��� ��ʽ����///////////////
			int absResult = 0;
			for(int i=0;i<bottom-top;i++)
			{
				for(int j=0;j<right-left;j++)
				{
					rHelpValue=GetRValue(pColorBuffer[i][j]);
					gHelpValue=GetGValue(pColorBuffer[i][j]);
					bHelpValue=GetBValue(pColorBuffer[i][j]);

					absResult=abs(rHelpValue-rValue)+abs(gHelpValue-gValue)+abs(bHelpValue-bValue);

					if(absResult<=help_simi)
					{
						x=j+left;
						y=i+top;
						goto end;
					}
				}
			}
		}
		else if(dir == 1)
		{
			/////////////////////1 �����ĵ����� ������ʽ����///////////////
			int px = (right - left)/2 ;
			int py = (bottom - top)/2 ;

			int VisitCount=0;
			int count = 1;

			int ii =0;
			int absResult = 0;

			RUNTYPE runType = TurnUP;

			while(VisitCount<(right - left)*(bottom - top))
			{
				for(ii=0; ii<count; ii++)
				{
					if(px>=0 && px<right-left && py>=0 && py<bottom-top)
					{
						VisitCount++;   ///ִ�д����ۼ�
						rHelpValue=GetRValue(pColorBuffer[py][px]);
						gHelpValue=GetGValue(pColorBuffer[py][px]);
						bHelpValue=GetBValue(pColorBuffer[py][px]);
						absResult =abs(rHelpValue-rValue)+abs(gHelpValue-gValue)+abs(bHelpValue-bValue);
						if(absResult<=help_simi)
						{	// �ҵ����˳�ѭ��
							x=px+left;
							y=py+top;
							goto end;
						}
					}
					//// ����x,y�仯
					switch(runType)
					{
					case TurnUP:
						py--;
						break;

					case TurnDOWN:
						py++;
						break;

					case TurnLEFT:
						px--;
						break;

					case TurnRIGHT:
						px++;
						break;
					}
				}  //endfor
				/////���� ������ʽ���̵�����
				switch(runType)
				{
				case TurnUP:
					runType = TurnRIGHT;
					break;

				case TurnDOWN:
					runType = TurnLEFT;
					break;

				case TurnLEFT:
					runType = TurnUP;
					count ++;
					break;

				case TurnRIGHT:
					runType = TurnDOWN;
					count ++;
					break;
				}
			} ////endwhile
		}///end else if

		else if(dir == 2)
		{
			/////////////////////0 ���ҵ��� ���µ��� ��ʽ����///////////////
			for(int i=bottom-top-1;i>=0;i--)
			{
				for(int j=right-left-1;j>=0;j--)
				{
					rHelpValue=GetRValue(pColorBuffer[i][j]);
					gHelpValue=GetGValue(pColorBuffer[i][j]);
					bHelpValue=GetBValue(pColorBuffer[i][j]);

					int absResult=abs(rHelpValue-rValue)+abs(gHelpValue-gValue)+abs(bHelpValue-bValue);

					if(absResult<=help_simi)
					{
						x=j+left;
						y=i+top;
						goto end;
					}
				}
			}
		}
	}
end:
	free(pBITMAPINFO);
	::DeleteObject(hBitmap);

	::DeleteDC(dc);
	::DeleteDC(tdc);

	for(int i=0;i<height;i++)
	{
		delete [] pColorBuffer[i];
		pColorBuffer[i]=NULL;
	}

	delete [] pColorBuffer;
	pColorBuffer=NULL;

	delete [] pBuffer;
	
	return true;
}
/////// ��̨��ɫ�ڴ洦���� ����ٶ�//////////////////////
bool MyFindPictureClass::processBKWindow(HWND src_hWnd,int &color,int left,int top,int right,int bottom,double simi,int dir,int &x,int &y)
{
	RECT rc;
	::GetClientRect(src_hWnd, &rc);
	// 24λͼ��BITMAPINFO
	BITMAPINFO *pBITMAPINFO = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
	memset(pBITMAPINFO, 0, sizeof(BITMAPINFOHEADER));
	BITMAPINFOHEADER *pInfo_Header = (BITMAPINFOHEADER *)pBITMAPINFO;
	pInfo_Header->biSize = sizeof(BITMAPINFOHEADER);   
	pInfo_Header->biWidth = rc.right - rc.left;   
	pInfo_Header->biHeight = (rc.bottom - rc.top);   
	pInfo_Header->biPlanes = 1;   
	pInfo_Header->biBitCount = 24;   
	pInfo_Header->biCompression = BI_RGB;

	////////////////////////////�ĵ�ı߽�ֵ�ж�////////////////
	if(left<0)
		left=0;
	if(left>=rc.right)
		left=rc.right-1;
	if(top<0)
		top=0;
	if(top>=rc.bottom)
		top=rc.bottom-1;
	if(right>=rc.right)
		right=rc.right-1;
	if(bottom>=rc.bottom)
		bottom=rc.bottom-1;
	////////////////////////////////////////////////////////////

	// ��������DC ��ӡĿ�괰��
	HDC src_hdc = ::GetWindowDC(src_hWnd);        
	HBITMAP hBitmap = ::CreateCompatibleBitmap(src_hdc,pInfo_Header->biWidth, pInfo_Header->biHeight);
	HDC hdcCompatible = ::CreateCompatibleDC(src_hdc); 
	::SelectObject(hdcCompatible, hBitmap);
	::PrintWindow(src_hWnd, hdcCompatible, 0);
	::ReleaseDC(src_hWnd, src_hdc);    

	// �������buf
	DWORD bufSize = (pInfo_Header->biWidth * 3 + 3) / 4 * 4 * pInfo_Header->biHeight;
	BYTE * pBuffer = new BYTE[bufSize];

	int aHeight=pInfo_Header->biHeight;

	if(::GetDIBits(hdcCompatible, hBitmap, 0, aHeight, pBuffer,pBITMAPINFO, DIB_RGB_COLORS) == 0)
	{
		//::MessageBox(NULL,L"��ȡBKλͼ����ʧ��",L"TC",0);
		return false;
	}

	int width=pBITMAPINFO->bmiHeader.biWidth;
	int height=pBITMAPINFO->bmiHeader.biHeight;

	COLORREF** pColorBuffer = new COLORREF*[height];     ///// ��ά���� �����洢ͼ�����ɫֵ
	for(int i=0;i<height;i++)
	{
		pColorBuffer[i]=new COLORREF[width];
	}

	int help_simi=0;
	if(simi==0.5)
		help_simi=49;

	else if(simi==0.6)
		help_simi=38;

	else if(simi==0.7)
		help_simi=29;

	else if(simi==0.8)
		help_simi=18;

	else if(simi==0.9)
		help_simi=9;

	COLORREF helpcolor=0;
	/*BYTE r1=0,g1=0,b1=0;*/
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
		color=pColorBuffer[top][left];
		goto end;
	}

	BYTE rValue=0,gValue=0,bValue=0;
	rValue=GetRValue(color);
	gValue=GetGValue(color);
	bValue=GetBValue(color);

	BYTE rHelpValue=0,gHelpValue=0,bHelpValue=0;

	if(dir == 0)
	{
		/////////////////////0 ������ ���ϵ��� ��ʽ����///////////////
		for(int i=top;i<=bottom;i++)
		{
			for(int j=left;j<=right;j++)
			{
				rHelpValue=GetRValue(pColorBuffer[i][j]);
				gHelpValue=GetGValue(pColorBuffer[i][j]);
				bHelpValue=GetBValue(pColorBuffer[i][j]);

				int absResult=abs(rHelpValue-rValue)+abs(gHelpValue-gValue)+abs(bHelpValue-bValue);

				if(absResult<=help_simi)
				{
					x=j;
					y=i;
					goto end;
				}
			}
		}
	}
	else if(dir == 1)
	{
		/////////////////////1 �����ĵ����� ������ʽ����///////////////
		int px = (right - left)/2 + left;
		int py = (bottom - top)/2 + top;

		int VisitCount=0;
		int count = 1;

		int ii =0;
		int absResult = 0;

		RUNTYPE runType = TurnUP;

		while(VisitCount<(right - left)*(bottom - top))
		{
			for(ii=0; ii<count; ii++)
			{
				if(px>=left && px<right && py>=top && py<bottom)
				{
					VisitCount++;   ///ִ�д����ۼ�
					rHelpValue=GetRValue(pColorBuffer[py][px]);
					gHelpValue=GetGValue(pColorBuffer[py][px]);
					bHelpValue=GetBValue(pColorBuffer[py][px]);
					absResult =abs(rHelpValue-rValue)+abs(gHelpValue-gValue)+abs(bHelpValue-bValue);
					if(absResult<=help_simi)
					{	// �ҵ����˳�ѭ��
						x=px;
						y=py;
						goto end;
					}
				}
				//// ����x,y�仯
				switch(runType)
				{
				case TurnUP:
					py--;
					break;

				case TurnDOWN:
					py++;
					break;

				case TurnLEFT:
					px--;
					break;

				case TurnRIGHT:
					px++;
					break;
				}
			}  //endfor
			/////���� ������ʽ���̵�����
			switch(runType)
			{
			case TurnUP:
				runType = TurnRIGHT;
				break;

			case TurnDOWN:
				runType = TurnLEFT;
				break;

			case TurnLEFT:
				runType = TurnUP;
				count ++;
				break;

			case TurnRIGHT:
				runType = TurnDOWN;
				count ++;
				break;
			}
		} ////endwhile
	}
	else if(dir == 2)
	{
		/////////////////////0 ���ҵ��� ���µ��� ��ʽ����///////////////
		for(int i=bottom;i>top;i--)
		{
			for(int j=right;j>left;j--)
			{
				rHelpValue=GetRValue(pColorBuffer[i][j]);
				gHelpValue=GetGValue(pColorBuffer[i][j]);
				bHelpValue=GetBValue(pColorBuffer[i][j]);

				int absResult=abs(rHelpValue-rValue)+abs(gHelpValue-gValue)+abs(bHelpValue-bValue);

				if(absResult<=help_simi)
				{
					x=j;
					y=i;
					goto end;
				}
			}
		}
	}

end:
	free(pBITMAPINFO);
	::DeleteObject(hdcCompatible);
	::DeleteObject(hBitmap);

	for(int i=0;i<height;i++)
	{
		delete [] pColorBuffer[i];
		pColorBuffer[i]=NULL;
	}

	delete [] pColorBuffer;
	pColorBuffer=NULL;

	delete [] pBuffer;

	return true;
}