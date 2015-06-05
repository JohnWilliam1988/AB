////////////////////////////////////////////////////////////////////////////////////

#if !defined(MYFINDPICTURECLASS_H)
#define MYFINDPICTURECLASS_H

#include <windows.h>

class MyFindPictureClass
{
public:
	MyFindPictureClass(void);
	~MyFindPictureClass(void);

	enum RUNTYPE{TurnUP=0,TurnDOWN,TurnLEFT,TurnRIGHT,TurnERRORR};

	//////////////////找图   支持的是24位位图/////////////////////
	////  图片格式错误或者没找到图片，函数返回-1
	////  参数             说明
	////  hwnd           窗口的句柄,为NULL表示前台查找,不为NULL表示后台查找
	////  left           左上角x
	////  top            左上角y
	////  right          右下角x
	////  bottom         右下角y
	////  path           图片的路径,支持多张图片,使用"|"隔开
	////  colorOffset    色偏 例如"102030"
	////  simi           相似度
	////  dir            检索方式
	////  xpos           返回的图片的左上角x坐标
	////  ypos           返回的图片的左上角y坐标
	int findPicture(HWND hwnd, int left, int top, int right, int bottom, wchar_t* path, int colorOffset, double simi, int dir, int &xpos, int &ypos);

	/////// 颜色内存处理。。 提高速度 //////////////////////
	bool processCreenWindow(int color,int left,int top,int right,int bottom,double simi,int dir,int &x,int &y,wchar_t* colorStr=NULL,bool isMulitColor=false);

	/////// 后台颜色内存处理。。 提高速度 //////////////////////
	bool processBKWindow(HWND hwnd,int &color,int left,int top,int right,int buttom,double simi,int dir,int &x,int &y);

private:
	int loadWidth;
	int loadHeight;
	int wndWidth;
	int wndHeight;
	COLORREF** pLoadBmpBuffer;
	COLORREF** pWndBmpBuffer;

	BYTE       m_colorOffsR; // R的偏移量
	BYTE       m_colorOffsG; // G的偏移量
	BYTE       m_colorOffsB; // B的偏移量
	/*double     m_sim;        // 相似度*/  //未使用该变量
	int        m_Dir;        // 检索方式
	int		   m_simColor;	 //	相似度的颜色边界值

	//////////////////////////////存储传进来的四点的范围/////////////
	int        m_Left;       // 左上点
	int        m_Top ;       // 顶端点
	int        m_Right ;      // 右下点
	int        m_bottom ;    // 底端点

	///////////////////////////// 助记透明图的处理 /////////////
	int        m_helpXpoint;
	int        m_helpYpoint; 

	bool loadBitmap(wchar_t* path);
// 	bool catchWindowBitmap();
// 	bool processBKWindows(HWND src_hWnd);
	bool my_WindowBitmap(HWND my_hWnd,int type);//整合catchWindowBitmap() processBKWindows() 两个函数 type控制模式0：前台 1:后台

	bool findImage(wchar_t* path,int &x,int &y);

	//////////////// 检索 方式 //////////////////
	//////////////////////////////////0:从左到右,从上倒下/////////////////////
	bool leftToRightFromTop(int &x,int &y);
	//////处理背景色为透明的图片////////////////
	bool comparaLeftToRightFromTop(int h,int w,int startX,int startY);
	//////处理背景色为不透明的图片////////////////
	bool comparaLeftToRightFromTopEx(int h,int w);
	
	////////////////////////////////////1:从左到右,从下倒上//////////////////
	bool leftToRightFromBottom(int &x,int &y);
	////////处理背景色为透明的图片////////////////
	bool comparaLeftToRightFromBottom(int h,int w,int startX,int startY);
	////////处理背景色为不透明的图片////////////////
	bool comparaLeftToRightFromBottomEx(int h,int w);

	////////////////////////////////////2:从右到左,从上倒下//////////////////
	bool rightToLeftFromTop(int &x,int &y);
	////////处理背景色为透明的图片////////////////
	bool comparaRightToLeftFromTop(int h,int w,int startX,int startY);
	////////处理背景色为不透明的图片////////////////
	bool comparaRightToLeftFromTopEx(int h,int w);	
	
	//////////////////////////////////3:从右到左,从下倒上///////////////////
	bool rightToLeftFromBottom(int &x,int &y);
	////////处理背景色为透明的图片////////////////
	bool comparaRightToLeftFromBottom(int h,int w,int startX,int startY);
	////////处理背景色为不透明的图片////////////////
	bool comparaRightToLeftFromBottomEx(int h,int w);
	
};
#endif