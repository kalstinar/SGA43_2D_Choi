#pragma once

#include "D:\GitHub\SGA43_2D_Choi\Popol\MainWindow\sga.hpp"
#include "Input.h"
#include "button.h"

class MoveApp : public MainWindow<MoveApp>
{
	typedef MoveApp Me;
	typedef MainWindow<MoveApp> Base;

	enum mode_id
	{
		INGAME_MODE,
		CONTROL_MODE,
	};
	


public :
	MoveApp()
		: mode(INGAME_MODE) 
		, FPS_dt(0), FPS_frame(0)
		, bGrabWindow(false), hMainWnd(NULL)
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
			//btnMax.Update(tick);
			//btnBase.Update(tick);
			
			

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
		btnIGMenu1.Update(tick);
		btnIGMenu2.Update(tick);
		btnIGMenu3.Update(tick);
		btnIGMenu4.Update(tick);
		btnIGMenu5.Update(tick);
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

		//책상 배치
		Table.Draw(buffer, Rect(145,160,145+180,160+150));
		
		Table1.Draw(buffer, Rect(323,220,323+180,220+150));
		Table2.Draw(buffer, Rect(220,268,220+180,268+150));
		Table3.Draw(buffer, Rect(373,240,373+180,240+150));
		Table4.Draw(buffer, Rect(267,290,267+180,290+150));
		

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
			//btnMax.Draw(buffer);
			//btnBase.Draw(buffer);
			
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
		::GetClientRect(hWnd, &rcClient);
		hMainWnd = hWnd;

		//block.load(_T("block.bmp"));

/////////////////////////////////////////////////////////////////////////////

//배경 등록

		BkGround.load(_T("Base.bmp"), Rect(0, 0, 800,600));

		IGMenu.load(_T("IGMenu.bmp"), Rect(0, 0, 800,600));

		CalendarBG.load(_T("CalendarBG.bmp"), Rect(0, 0, 800,600));
		MakeBG.load(_T("MakeBG.bmp"), Rect(0, 0, 800,600));
		ClockBG.load(_T("Clock.bmp"), Rect(0, 0, 150,150));
		ClockBG.SetTransparent(RGB(255,0,255));

////////////////////////////////////////////////////////////////////////////
		
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
		btnMini.SetButtonRect(Rect(850-50*3, 0, 850- 50*2, 50));
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
		btnIGMenu1.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);

		btnIGMenu2.Attach(hWnd);
		btnIGMenu2.SetImageOn(_T("BtnIGMenu.bmp"), Rect(110,0,220,50));
		btnIGMenu2.SetImageOff(_T("BtnIGMenu.bmp"), Rect(110,0,220,50));
		btnIGMenu2.SetButtonRect(Rect(720, 190, 830, 240));
		btnIGMenu2.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);

		btnIGMenu3.Attach(hWnd);
		btnIGMenu3.SetImageOn(_T("BtnIGMenu.bmp"), Rect(220,0,330,50));
		btnIGMenu3.SetImageOff(_T("BtnIGMenu.bmp"), Rect(220,0,330,50));
		btnIGMenu3.SetButtonRect(Rect(720, 270, 830, 320));
		btnIGMenu3.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);

		btnIGMenu4.Attach(hWnd);
		btnIGMenu4.SetImageOn(_T("BtnIGMenu.bmp"), Rect(330,0,440,50));
		btnIGMenu4.SetImageOff(_T("BtnIGMenu.bmp"), Rect(330,0,440,50));
		btnIGMenu4.SetButtonRect(Rect(720, 350, 830, 400));
		btnIGMenu4.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);

		btnIGMenu5.Attach(hWnd);
		btnIGMenu5.SetImageOn(_T("BtnIGMenu.bmp"), Rect(440,0,550,50));
		btnIGMenu5.SetImageOff(_T("BtnIGMenu.bmp"), Rect(440,0,550,50));
		btnIGMenu5.SetButtonRect(Rect(720, 430, 830, 480));
		btnIGMenu5.SetAction(&MoveApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
///////////////////////////////////////////////////////////////////////////////////////////////////

		buffer.Attach(hWnd);
		return 0;
	}
	LRESULT OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		gray.release();
		::DeleteDC(hBitmapDC);
		::ReleaseDC(hWnd, hMainDC);

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
	
	//배경
	Image BkGround;
	//책상
	Image Table;
	Image Table1;
	Image Table2;
	Image Table3;
	Image Table4;

	//인게임 메뉴
	Image IGMenu;
	Image CalendarBG;
	Image MakeBG;
	Image ClockBG;

/////////////////////////////////////////////////////////////////////////////////////////////////////


	//Image block;

	int mode;

	// FPS 출력용도.
	// FPS : Frame Per Second.
	// FPS_dt(ms) : FPS_frame = 1000ms : x
	// FPS_frame*1000/FPS_dt = x
	
	DWORD FPS_dt;
	DWORD FPS_frame;
	DWORD dwFPS;

	//버튼
	Button btnMini;
	//Button btnMax;
	//Button btnBase;
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

	//애니메이션 변수 설정
	Animation kirobot;
	Animation arabprin;

	//////////////////////////
	// moving background...
	//LONG dx;
	//DWORD bg_update_dt;
	//DWORD bg_update_delay;


};
