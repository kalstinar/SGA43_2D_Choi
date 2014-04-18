#pragma once

#include "D:\GitHub\SGA43_2D_Choi\Popol\MainWindow\sga.hpp"
#include "Input.h"
#include "button.h"
#include "Money.h"

class MoveApp : public MainWindow<MoveApp>
{
	typedef MoveApp Me;
	typedef MainWindow<MoveApp> Base;

	enum mode_id
	{
		INGAME_MODE = WM_USER + 1,
		CONTROL_MODE,
		SUBMENU_MODE1,
		SUBMENU_MODE2,
		SUBWIN_MODE1,
		SUBWIN_MODE2	
	};
	
public :
	MoveApp() 
		 :mode(INGAME_MODE), FPS_dt(0), FPS_frame(0)
		, bGrabWindow(false), hMainWnd(NULL), theta_t(0.f), theta_m(1.f), theta_y(1.f)
	//	, dx(0), bg_update_dt(0), bg_update_delay(5)
	{
		//SetWindowTitle(_T("Alphablend Sample"));
		SetWindowSize(850, 700);
		SetWindowStyle(WS_POPUP | WS_VISIBLE);
	}
	void Input(DWORD tick)
	{
		if (InputDevice.OnClick(VK_ESCAPE))
		{
			if (mode == CONTROL_MODE)
				mode = INGAME_MODE;
			else
				mode = CONTROL_MODE;
		}

		if (mode == CONTROL_MODE)
		{
			btnMini.Update(tick);
			btnClose.Update(tick);
			
			
			if (InputDevice[VK_LBUTTON])
			{
				bGrabWindow = true;
			}
			else
			{
				bGrabWindow = false;
			}

			ptPrev = ptMouse;
			ptMouse = InputDevice.getPos();
		}

		else if (mode == SUBMENU_MODE1)
		{
			btnMake.Update(tick);
			btnClMake.Update(tick);
		}

//인게임 버튼
		btnIGMenu1.Update(tick);
		btnIGMenu2.Update(tick);
		btnIGMenu3.Update(tick);
		btnIGMenu4.Update(tick);
		btnIGMenu5.Update(tick);
//서브메뉴 버튼
		btnJob.Update(tick);
		btnTrain.Update(tick);
		btnFire.Update(tick);
//서브윈도우 버튼
		btnNext.Update(tick);
		btnPrev.Update(tick);
		btnOk.Update(tick);
		btnCancel.Update(tick);
	}

	void Update(DWORD tick)
	{
		// FPS_dt(ms) : FPS_frame = 1000ms : x
		// FPS_frame*1000/FPS_dt = x
		if (FPS_dt > 1000)
		{
			FPS_dt -= 1000;
			FPS_frame = 0;
		}

		FPS_dt += tick;
		FPS_frame++;
		dwFPS = FPS_frame*1000/FPS_dt;

		//if (bg_update_dt > bg_update_delay)
		//{
		//	int count = bg_update_dt/bg_update_delay;

		//	for (int i = 0; i < count; i++)
		//	{
		//		dx--;
		//		if (dx <= -block.getRect().width())
		//			dx = 0;
		//	}

		//	bg_update_dt %= bg_update_delay;
		//}
		//bg_update_dt += tick;


		if (mode == CONTROL_MODE)
		{
			Point diff = ptMouse - ptPrev;

			if (bGrabWindow)
			{
				if (hMainWnd)
				{
					Rect rcWindow = rcClient.ToScreen(hMainWnd);
					::MoveWindow(hMainWnd, rcWindow.left + diff.x, rcWindow.top + diff.y, rcWindow.width(), rcWindow.height(), TRUE);
				}
			}
		}
	}
	void Render(DWORD tick)
	{
		buffer << RGB(100,255,255);

		//Size cBlock(block.getRect().width(), block.getRect().height());
		//for (int y = 0; y < rcClient.height(); y += cBlock.cy)
		//{
		//	for (int x = dx; x < rcClient.width(); x += cBlock.cx)
		//	{
		//		block.Draw(buffer, Rect(x, y, x+cBlock.cx, y+cBlock.cy));
		//	}
		//}

		//배경
		BkGround.Draw(buffer, Rect(0,50,700,550));
		IGMenu.Draw(buffer, Rect(700,50,850,550));
		CalendarBG.Draw(buffer, Rect(0,0,850,50));
		MakeBG.Draw(buffer, Rect(0,550,850,700));
		ClockBG.Draw(buffer, Rect(700,550,850,700));

		//책상&의자 배치
		Chair.Draw(buffer, Rect(145+15,160+20,145+15+70,160+20+85));
		CEO.Draw(buffer, Rect(160+15,140+20,160+15+50,140+20+65));
		Table.Draw(buffer, Rect(145,160,145+180,160+150));
		

		Chair1.Draw(buffer, Rect(323+15,220+20,323+15+70,220+20+85));
		Table1.Draw(buffer, Rect(323,220,323+180,220+150));
		
		Chair2.Draw(buffer, Rect(220+15,283,220+15+70,268+15+85));
		Table2.Draw(buffer, Rect(220,268,220+180,268+150));
		
		Table3.Draw(buffer, Rect(373,240,373+180,240+150));
		Chair3.Draw(buffer, Rect(373+78,240+49,373+78+70,240+49+85));

		Table4.Draw(buffer, Rect(267,290,267+180,290+150));
		Chair4.Draw(buffer, Rect(267+78,290+49,267+78+70,290+49+85));

		//인게임 버튼
		btnIGMenu1.Draw(buffer);
		btnIGMenu2.Draw(buffer);
		btnIGMenu3.Draw(buffer);
		btnIGMenu4.Draw(buffer);
		btnIGMenu5.Draw(buffer);

		

		//kirobot.AddImage();
		//arabprin.AddImage();
		

		if (mode == CONTROL_MODE)
		{
			BLENDFUNCTION bf;
			bf.BlendOp =  AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.AlphaFormat = 0;
			bf.SourceConstantAlpha = 200;	// 0(완전투명:transparent) ~ 255(완전불투명:opaque)

			::GdiAlphaBlend(HDC(buffer), 
							0, 0, rcClient.width(), rcClient.height(),
							hBitmapDC, 
							0, 0, 10, 10, bf);

			btnMini.Draw(buffer);
			btnClose.Draw(buffer);
		}
		
		if(mode == SUBMENU_MODE1)
		{
			SubMenu.Draw(buffer, Rect(540, 100, 690, 300));

			btnMake.Draw(buffer);
			btnClMake.Draw(buffer);
		}
		
		if(mode == SUBMENU_MODE2)
		{
			SubMenu2.Draw(buffer, Rect(540, 160, 690, 460));
			
			btnJob.Draw(buffer);
			btnTrain.Draw(buffer);
			btnFire.Draw(buffer);
		}

		if(mode == SUBWIN_MODE1)
		{
			SubWin.Draw(buffer, Rect(100,50,650,500));
			
			btnNext.Draw(buffer);
			btnCancel.Draw(buffer);
		}

		if(mode == SUBWIN_MODE2)
		{
			SubWin.Draw(buffer, Rect(100,50,650,500));
			
			btnPrev.Draw(buffer);
			btnOk.Draw(buffer);
		}

		TCHAR szDebug[200];
		_stprintf_s(szDebug, _T("FPS : %08d"), dwFPS);
		::DrawText(buffer, szDebug, -1, &rcClient, DT_LEFT | DT_TOP);

		buffer.Draw();
	}


	static void Proxy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		::SendMessage(hWnd, uMsg, wParam, lParam);
	}

protected :
	void SetEventMap()
	{
		AddEventHandler(WM_CREATE, &Me::OnCreate);
		AddEventHandler(WM_DESTROY, &Me::OnDestroy);
		//AddEventHandler(WM_SYSCOMMAND, &Me::OnSysCommand);
		AddEventHandler(WM_TIMER, &Me::OnTimer);		
		AddEventHandler(WM_CHANGMODE, &Me::ChngMode);
	}


	//LRESULT OnSysCommand(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	//{
	//	if (SC_MAXIMIZE == wParam)
	//	{
	//		::DefWindowProc(hWnd, uMsg, wParam, lParam);
	//		buffer.Attach(hWnd);
	//		::GetClientRect(hWnd, &rcClient);
	//	}
	//	else
	//	{
	//		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	//	}
	//	return 0;
	//}

	LRESULT OnCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		::SetTimer(hWnd, 0, 100, NULL);
		
		::GetClientRect(hWnd, &rcClient);
		hMainWnd = hWnd;

/////////////////////////////////////////////////////////////////////////////

//배경 등록

		BkGround.load(_T("Base.bmp"), Rect(0, 0, 800,600));

		IGMenu.load(_T("IGMenu.bmp"), Rect(0, 0, 800,600));

		CalendarBG.load(_T("CalendarBG.bmp"), Rect(0, 0, 800,600));
		MakeBG.load(_T("MakeBG.bmp"), Rect(0, 0, 800,600));
		ClockBG.load(_T("Clock.bmp"), Rect(0, 0, 150,150));
		ClockBG.SetTransparent(RGB(255,0,255));

		
////////////////////////////////////////////////////////////////////////
//서브메뉴&서브윈도우 버튼 등록
		
		SubMenu.load(_T("SubMenu.bmp"), Rect(0, 0, 150, 200));
		SubMenu2.load(_T("SubMenu.bmp"), Rect(0, 200, 150, 500));
		SubWin.load(_T("SubMenu.bmp"), Rect(0, 200, 150,500));


////////////////////////////////////////////////////////////////////////////
		
//자리 배정
		Table.load(_T("Table.bmp"), Rect(0,0,160,150));
		Table.SetTransparent(RGB(58,59,59));

		Table1.load(_T("Table.bmp"), Rect(0,0,160,150));
		Table1.SetTransparent(RGB(58,59,59));
		
		Table2.load(_T("Table.bmp"), Rect(0,0,160,150));
		Table2.SetTransparent(RGB(58,59,59));

		Table3.load(_T("Table.bmp"), Rect(160,0,320,150));
		Table3.SetTransparent(RGB(58,59,59));

		Table4.load(_T("Table.bmp"), Rect(160,0,320,150));
		Table4.SetTransparent(RGB(58,59,59));

		Chair.load(_T("Chair.bmp"), Rect(64,0,125,75));
		Chair.SetTransparent(RGB(59,59,59));

		Chair1.load(_T("Chair.bmp"), Rect(64,0,125,75));
		Chair1.SetTransparent(RGB(59,59,59));

		Chair2.load(_T("Chair.bmp"), Rect(64,0,125,75));
		Chair2.SetTransparent(RGB(59,59,59));

		Chair3.load(_T("Chair.bmp"), Rect(0,0,64,75));
		Chair3.SetTransparent(RGB(59,59,59));

		Chair4.load(_T("Chair.bmp"), Rect(0,0,64,75));
		Chair4.SetTransparent(RGB(59,59,59));

		CEO.load(_T("CEO.bmp"), Rect(0,0,16,21));
		CEO.SetTransparent(RGB(25,25,25));
		

////////////////////////////////////////////////////////////////////////////////////////////////

		hMainDC = ::GetDC(hWnd);
		hBitmapDC = ::CreateCompatibleDC(hMainDC);
		gray.load(_T("gray.bmp"), Rect(0,0,10,10));
		Select(hBitmapDC, HBITMAP(gray));

//////////////////////////////////////////////////////////////////////////////////////////////////
//Control Mode 버튼 등록
		btnMini.Attach(hWnd);
		btnMini.SetImageOn(_T("button.bmp"), Rect(50,0,100,50));
		btnMini.SetImageOff(_T("button.bmp"), Rect(0,0,50,50));
		btnMini.SetTransparent(RGB(255,0,255));
		btnMini.SetButtonRect(Rect(850-50*2, 0, 850- 50, 50));
		btnMini.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		//if(SC_MAXIMIZE == wParam)
	//	{
	//		btnBase.Attach(hWnd);
	//		btnBase.SetImageOn(_T("button.bmp"), Rect(250,0,300,50));
	//		btnBase.SetImageOff(_T("button.bmp"), Rect(200,0,250,50));
	//		btnBase.SetTransparent(RGB(255,0,255));
	//		btnBase.SetButtonRect(Rect(850 - 50*2, 0, 850 - 50, 50));
	//		btnBase.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_SIZE, 0);
	//	}
		
	//	if(SC_MAXIMIZE != wParam)
	//	{
	//		btnMax.Attach(hWnd);
	//		btnMax.SetImageOn(_T("button.bmp"), Rect(250,0,300,50));
	//		btnMax.SetImageOff(_T("button.bmp"), Rect(200,0,250,50));
	//		btnMax.SetTransparent(RGB(255,0,255));
	//		btnMax.SetButtonRect(Rect(850 - 50*2, 0, 850 - 50, 50));
	//		btnMax.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	//	}

		btnClose.Attach(hWnd);
		btnClose.SetImageOn(_T("button.bmp"), Rect(150,0,200,50));
		btnClose.SetImageOff(_T("button.bmp"), Rect(100,0,150,50));
		btnClose.SetTransparent(RGB(255,0,255));
		btnClose.SetButtonRect(Rect(850 - 50, 0, 850, 50));
		btnClose.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);

////////////////////////////////////////////////////////////////////////////////////////////////		
//인게임 버튼 등록

		btnIGMenu1.Attach(hWnd);
		btnIGMenu1.SetImageOn(_T("BtnIGMenu.bmp"), Rect(0,0,110,50));
		btnIGMenu1.SetImageOff(_T("BtnIGMenu.bmp"), Rect(0,0,110,50));
		btnIGMenu1.SetButtonRect(Rect(720, 115, 830, 165));
		btnIGMenu1.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		btnIGMenu2.Attach(hWnd);
		btnIGMenu2.SetImageOn(_T("BtnIGMenu.bmp"), Rect(110,0,220,50));
		btnIGMenu2.SetImageOff(_T("BtnIGMenu.bmp"), Rect(110,0,220,50));
		btnIGMenu2.SetButtonRect(Rect(720, 190, 830, 240));
		btnIGMenu2.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		btnIGMenu3.Attach(hWnd);
		btnIGMenu3.SetImageOn(_T("BtnIGMenu.bmp"), Rect(220,0,330,50));
		btnIGMenu3.SetImageOff(_T("BtnIGMenu.bmp"), Rect(220,0,330,50));
		btnIGMenu3.SetButtonRect(Rect(720, 270, 830, 320));
		btnIGMenu3.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		btnIGMenu4.Attach(hWnd);
		btnIGMenu4.SetImageOn(_T("BtnIGMenu.bmp"), Rect(330,0,440,50));
		btnIGMenu4.SetImageOff(_T("BtnIGMenu.bmp"), Rect(330,0,440,50));
		btnIGMenu4.SetButtonRect(Rect(720, 350, 830, 400));
		btnIGMenu4.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		btnIGMenu5.Attach(hWnd);
		btnIGMenu5.SetImageOn(_T("BtnIGMenu.bmp"), Rect(440,0,550,50));
		btnIGMenu5.SetImageOff(_T("BtnIGMenu.bmp"), Rect(440,0,550,50));
		btnIGMenu5.SetButtonRect(Rect(720, 430, 830, 480));
		btnIGMenu5.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		
///////////////////////////////////////////////////////////////////////////////////////////////////
//서브메뉴 버튼 등록
		//1
		btnMake.Attach(hWnd);
		btnMake.SetImageOn(_T("BtnSubMenu.bmp"), Rect(0,50,110,100));
		btnMake.SetImageOff(_T("BtnSubMenu.bmp"), Rect(0,50,110,100));
		btnMake.SetButtonRect(Rect(560, 130, 670, 180));
		btnMake.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		
		btnClMake.Attach(hWnd);
		btnClMake.SetImageOn(_T("BtnSubMenu.bmp"), Rect(0,100,110,150));
		btnClMake.SetImageOff(_T("BtnSubMenu.bmp"), Rect(0,100,110,150));
		btnClMake.SetButtonRect(Rect(560, 200, 670, 250));
		btnClMake.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		//2
		btnJob.Attach(hWnd);
		btnJob.SetImageOn(_T("BtnSubMenu.bmp"), Rect(0,150,110,200));
		btnJob.SetImageOff(_T("BtnSubMenu.bmp"), Rect(0,150,110,200));
		btnJob.SetButtonRect(Rect(560, 200, 670, 250));
		btnJob.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		
		btnTrain.Attach(hWnd);
		btnTrain.SetImageOn(_T("BtnSubMenu.bmp"), Rect(0,200,110,250));
		btnTrain.SetImageOff(_T("BtnSubMenu.bmp"), Rect(0,200,110,250));
		btnTrain.SetButtonRect(Rect(560, 270, 670, 320));
		btnTrain.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		btnFire.Attach(hWnd);
		btnFire.SetImageOn(_T("BtnSubMenu.bmp"), Rect(0,0,110,50));
		btnFire.SetImageOff(_T("BtnSubMenu.bmp"), Rect(0,0,110,50));
		btnFire.SetButtonRect(Rect(560, 340, 670, 390));
		btnFire.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

/////////////////////////////////////////////////////////////////////////////////////////////////////
		
		btnPrev.Attach(hWnd);
		btnPrev.SetImageOn(_T("BtnSubWin.bmp"), Rect(0,0,110,50));
		btnPrev.SetImageOff(_T("BtnSubWin.bmp"), Rect(0,0,110,50));
		btnPrev.SetButtonRect(Rect(560, 340, 670, 390));
		btnPrev.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		
		btnNext.Attach(hWnd);
		btnNext.SetImageOn(_T("BtnSubWin.bmp"), Rect(110,0,220,50));
		btnNext.SetImageOff(_T("BtnSubWin.bmp"), Rect(110,0,220,50));
		btnNext.SetButtonRect(Rect(560, 340, 670, 390));
		btnNext.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		btnOk.Attach(hWnd);
		btnOk.SetImageOn(_T("BtnSubWin.bmp"), Rect(220,0,330,50));
		btnOk.SetImageOff(_T("BtnSubWin.bmp"), Rect(220,0,330,50));
		btnOk.SetButtonRect(Rect(560, 340, 670, 390));
		btnOk.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		btnCancel.Attach(hWnd);
		btnCancel.SetImageOn(_T("BtnSubWin.bmp"), Rect(330,0,440,50));
		btnCancel.SetImageOff(_T("BtnSubWin.bmp"), Rect(330,0,440,50));
		btnCancel.SetButtonRect(Rect(560, 340, 670, 390));
		btnCancel.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

/////////////////////////////////////////////////////////////////////////////////////////////////////

		buffer.Attach(hWnd);
		return 0;
	}

	LRESULT OnTimer(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		
		return 0;
	}

	LRESULT ChngMode(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//인게임 메뉴
		

		return 0;
	}

	LRESULT OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		gray.release();
		::DeleteDC(hBitmapDC);
		::ReleaseDC(hWnd, hMainDC);

		::KillTimer(hWnd, 0);
		::PostQuitMessage(0);
		return 0;

		
	}

private :
	DoubleBuffer buffer;
	Rect rcClient;

	HDC hMainDC;
	HDC hBitmapDC;
	Image gray;
	
/////////////////////////////////////////////////////////////////////////////////////////////////	
	int mode;

	//배경
	Image BkGround;
	//책상
	Image Table;
	Image Table1;
	Image Table2;
	Image Table3;
	Image Table4;

	//의자
	Image Chair;
	Image Chair1;
	Image Chair2;
	Image Chair3;
	Image Chair4;

	//인게임 메뉴
	Image IGMenu;
	Image CalendarBG;
	Image MakeBG;
	Image ClockBG;

	//서브메뉴창
	Image SubMenu;
	Image SubMenu2;
	Button btnMake;
	Button btnClMake;
	Button btnJob;
	Button btnTrain;
	Button btnFire;

	//보조창
	Image SubWin;
	Button btnNext;
	Button btnPrev;
	Button btnOk;
	Button btnCancel;

/////////////////////////////////////////////////////////////////////////////////////////////////////

	// FPS 출력용도.
	// FPS : Frame Per Second.
	// FPS_dt(ms) : FPS_frame = 1000ms : x
	// FPS_frame*1000/FPS_dt = x
	
	DWORD FPS_dt;
	DWORD FPS_frame;
	DWORD dwFPS;

	//버튼
	Button btnMini;
	Button btnClose;

	//인게임 메뉴 버튼
	Button btnIGMenu1;
	Button btnIGMenu2;
	Button btnIGMenu3;
	Button btnIGMenu4;
	Button btnIGMenu5;

	HWND hMainWnd;
	Point ptPrev;
	Point ptMouse;
	bool bGrabWindow;

	//인물&애니메이션 변수 설정
	Image CEO;
	
	Animation kirobot;
	Animation arabprin;

	//시간 설정
	float theta_t;
	float theta_m;
	float theta_y;

	//////////////////////////
	// moving background...
	//LONG dx;
	//DWORD bg_update_dt;
	//DWORD bg_update_delay;


};
