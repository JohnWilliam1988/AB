
// ABץץ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "MyInterfacePropSheet.h"
#include "MyDrawPictureClass.h"      //  ��͸��ͼ������
#include "MyProcessPicInfo.h"
#include "MyPicFullScreenShow.h"
#include "MyPickerColor.h"			 //  ȡɫ��������
#include "MyShowPic.h"
// CABץץApp:
// �йش����ʵ�֣������ ABץץ.cpp
//

#define IDC_USER_CLOSEPICKERWND                 WM_USER+1001
#define IDC_USER_CLOSEMAKEPICWND                WM_USER+1001

class CABץץApp : public CWinApp
{
public:
	CABץץApp();

// ��д
public:
	virtual BOOL InitInstance();
	CMyInterfacePropSheet * pPropSheet;
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CABץץApp theApp;