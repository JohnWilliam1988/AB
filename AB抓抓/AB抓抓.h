
// AB抓抓.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "MyInterfacePropSheet.h"
#include "MyDrawPictureClass.h"      //  制透明图处理类
#include "MyProcessPicInfo.h"
#include "MyPicFullScreenShow.h"
#include "MyPickerColor.h"			 //  取色器处理类
#include "MyShowPic.h"
// CAB抓抓App:
// 有关此类的实现，请参阅 AB抓抓.cpp
//

#define IDC_USER_CLOSEPICKERWND                 WM_USER+1001
#define IDC_USER_CLOSEMAKEPICWND                WM_USER+1001

class CAB抓抓App : public CWinApp
{
public:
	CAB抓抓App();

// 重写
public:
	virtual BOOL InitInstance();
	CMyInterfacePropSheet * pPropSheet;
// 实现

	DECLARE_MESSAGE_MAP()
};

extern CAB抓抓App theApp;