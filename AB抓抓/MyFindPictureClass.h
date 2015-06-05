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

	//////////////////��ͼ   ֧�ֵ���24λλͼ/////////////////////
	////  ͼƬ��ʽ�������û�ҵ�ͼƬ����������-1
	////  ����             ˵��
	////  hwnd           ���ڵľ��,ΪNULL��ʾǰ̨����,��ΪNULL��ʾ��̨����
	////  left           ���Ͻ�x
	////  top            ���Ͻ�y
	////  right          ���½�x
	////  bottom         ���½�y
	////  path           ͼƬ��·��,֧�ֶ���ͼƬ,ʹ��"|"����
	////  colorOffset    ɫƫ ����"102030"
	////  simi           ���ƶ�
	////  dir            ������ʽ
	////  xpos           ���ص�ͼƬ�����Ͻ�x����
	////  ypos           ���ص�ͼƬ�����Ͻ�y����
	int findPicture(HWND hwnd, int left, int top, int right, int bottom, wchar_t* path, int colorOffset, double simi, int dir, int &xpos, int &ypos);

	/////// ��ɫ�ڴ洦���� ����ٶ� //////////////////////
	bool processCreenWindow(int color,int left,int top,int right,int bottom,double simi,int dir,int &x,int &y,wchar_t* colorStr=NULL,bool isMulitColor=false);

	/////// ��̨��ɫ�ڴ洦���� ����ٶ� //////////////////////
	bool processBKWindow(HWND hwnd,int &color,int left,int top,int right,int buttom,double simi,int dir,int &x,int &y);

private:
	int loadWidth;
	int loadHeight;
	int wndWidth;
	int wndHeight;
	COLORREF** pLoadBmpBuffer;
	COLORREF** pWndBmpBuffer;

	BYTE       m_colorOffsR; // R��ƫ����
	BYTE       m_colorOffsG; // G��ƫ����
	BYTE       m_colorOffsB; // B��ƫ����
	/*double     m_sim;        // ���ƶ�*/  //δʹ�øñ���
	int        m_Dir;        // ������ʽ
	int		   m_simColor;	 //	���ƶȵ���ɫ�߽�ֵ

	//////////////////////////////�洢���������ĵ�ķ�Χ/////////////
	int        m_Left;       // ���ϵ�
	int        m_Top ;       // ���˵�
	int        m_Right ;      // ���µ�
	int        m_bottom ;    // �׶˵�

	///////////////////////////// ����͸��ͼ�Ĵ��� /////////////
	int        m_helpXpoint;
	int        m_helpYpoint; 

	bool loadBitmap(wchar_t* path);
// 	bool catchWindowBitmap();
// 	bool processBKWindows(HWND src_hWnd);
	bool my_WindowBitmap(HWND my_hWnd,int type);//����catchWindowBitmap() processBKWindows() �������� type����ģʽ0��ǰ̨ 1:��̨

	bool findImage(wchar_t* path,int &x,int &y);

	//////////////// ���� ��ʽ //////////////////
	//////////////////////////////////0:������,���ϵ���/////////////////////
	bool leftToRightFromTop(int &x,int &y);
	//////������ɫΪ͸����ͼƬ////////////////
	bool comparaLeftToRightFromTop(int h,int w,int startX,int startY);
	//////������ɫΪ��͸����ͼƬ////////////////
	bool comparaLeftToRightFromTopEx(int h,int w);
	
	////////////////////////////////////1:������,���µ���//////////////////
	bool leftToRightFromBottom(int &x,int &y);
	////////������ɫΪ͸����ͼƬ////////////////
	bool comparaLeftToRightFromBottom(int h,int w,int startX,int startY);
	////////������ɫΪ��͸����ͼƬ////////////////
	bool comparaLeftToRightFromBottomEx(int h,int w);

	////////////////////////////////////2:���ҵ���,���ϵ���//////////////////
	bool rightToLeftFromTop(int &x,int &y);
	////////������ɫΪ͸����ͼƬ////////////////
	bool comparaRightToLeftFromTop(int h,int w,int startX,int startY);
	////////������ɫΪ��͸����ͼƬ////////////////
	bool comparaRightToLeftFromTopEx(int h,int w);	
	
	//////////////////////////////////3:���ҵ���,���µ���///////////////////
	bool rightToLeftFromBottom(int &x,int &y);
	////////������ɫΪ͸����ͼƬ////////////////
	bool comparaRightToLeftFromBottom(int h,int w,int startX,int startY);
	////////������ɫΪ��͸����ͼƬ////////////////
	bool comparaRightToLeftFromBottomEx(int h,int w);
	
};
#endif