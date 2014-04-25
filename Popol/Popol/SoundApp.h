#pragma once

#include "..\MainWindow\sga.hpp"
#include "Sound.h"
#include "LoadResource.h"
#include "GameProgress.h"
#include "CharData.h"


class SoundApp : public MainWindow<SoundApp>
{
	typedef SoundApp Me;
	typedef MainWindow<SoundApp> Base;

	//enum mode_id
	//{
	//	INGAME_MODE,
	//	CONTROL_MODE,
	//};

public :
	SoundApp()
		: mode(MAIN_MODE1), gStruct(Simulation), gGenre(Baseball), tResult(Good)
		,job(pgrm), person(P1) 
		,GmProg(false), GmProg2(false), GmProg3(false)
		, GmProg4(false), GmProg5(false), GmProg6(false)
		, FPS_dt(0), FPS_frame(0)
		, bGrabWindow(false), hMainWnd(NULL)
		, dx(0), bg_update_dt(0), bg_update_delay(5)
		, ang(0.f)
	{
		//SetWindowTitle(_T("Alphablend Sample"));
		SetWindowSize(850, 700);
		SetWindowStyle(WS_POPUP | WS_VISIBLE);

		gStruct = Simulation;
		gGenre = Baseball;
	}

	~SoundApp()
	{
		mode = MAIN_MODE1;
		gStruct = Simulation;
		gGenre = Baseball;
		tResult = Good;
		GmProg = false;
		GmProg2 = false;
		GmProg3 = false;
		GmProg4 = false;
		GmProg5 = false;
		GmProg6 = false;
		person =P1;
		job = pgrm;
	}

	void Input(DWORD tick)
	{
		if (InputDevice.OnClick(VK_ESCAPE))
		{
			if (mode == CONTROL_MODE)
			{
				mode = INGAME_MODE;
			}
			else if (mode == MAIN_MODE1) 
			{
				mode = MAIN_MODE1;
			}
			else
			{	
				mode = CONTROL_MODE;
			}
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

		if(mode == MAIN_MODE1)
		{
			btnNew.Update(tick);
			//btnLoad.Update(tick);
			btnEnd.Update(tick);
		}

		if(mode != MAIN_MODE1 || mode != CONTROL_MODE)
		{
			btnIGMenu1.Update(tick);
			//btnIGMenu2.Update(tick);
			//btnIGMenu3.Update(tick);
			//btnIGMenu4.Update(tick);
			btnIGMenu5.Update(tick);
			if(GmProg3 == true)
			{
				btnGameProg.Update(tick);
			}
		}


		if(mode == SUBMENU_MODE1)
		{
			btnMake.Update(tick);
		}

		if(mode == MAKEMN_MODE)
		{
			if(GmProg3 == false)
			{
				btnStruct1.Update(tick);
				btnGenre1.Update(tick);
				btnNext1.Update(tick);
				btnPrev1.Update(tick);
			}

			else if(GmProg3 == true)
			{
				btnCancel.Update(tick);
			}
		}
		
		else if(mode == MAKE_MODE1)
		{
			btnStruct2.Update(tick);
			btnStruct3.Update(tick);
			btnStruct4.Update(tick);
			btnStruct5.Update(tick);
			btnNext2.Update(tick);
		}

		else if(mode == MAKE_MODE2)
		{
			btnGenre2.Update(tick);
			btnGenre3.Update(tick);
			btnGenre4.Update(tick);
			btnGenre5.Update(tick);
			btnNext2.Update(tick);
		}

		else if(mode == MAKE_MODE3)
		{
			if(GmProg == false)
			{
				btnNext4.Update(tick);
			}
			if(GmProg == true)
			{
				if(GmProg2 == false)	
					btnOk.Update(tick);
				else if(GmProg2 == true)	
					btnOk2.Update(tick);
			}
		}

//기타 버튼
		
		//else if (mode == INGAME_MODE)
		//{
		//	if (InputDevice.OnClick(VK_LBUTTON))
		//	{
		//		SoundDepot["explosion"]->Play();
		//	}
		//	else if (InputDevice.OnClick(VK_RBUTTON))
		//	{
		//		if (SoundDepot["bgSound"]->IsPlaying())
		//			SoundDepot["bgSound"]->Stop();
		//		else
		//			SoundDepot["bgSound"]->Play();
		//		//if (SoundDepot["bgSound"]->IsPaused())
		//		//	SoundDepot["bgSound"]->Pause(false);
		//		//else
		//		//	SoundDepot["bgSound"]->Pause(true);
		//	}
		//}
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

		if (bg_update_dt > bg_update_delay)
		{
			int count = bg_update_dt/bg_update_delay;

			/*for (int i = 0; i < count; i++)
			{
				dx--;
				if (dx <= -ImageDepot.get("block")->getRect().width())
					dx = 0;
			}*/

			ang += 1.f;
			if (ang >= 360.f)
				ang = 0.f;

			/*ImageDepot["test"]->Move(Rect(50,50,100,100));
			ImageDepot["test"]->Rotate(ang);*/

			bg_update_dt %= bg_update_delay;
		}
		bg_update_dt += tick;


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

		//Size cBlock(ImageDepot["block"]->getRect().width(),
		//	ImageDepot["block"]->getRect().height());
		//for (int y = 0; y < rcClient.height(); y += cBlock.cy)
		//{
		//	for (int x = dx; x < rcClient.width(); x += cBlock.cx)
		//	{
		//		ImageDepot["block"]->Move(Rect(x, y, x+cBlock.cx, y+cBlock.cy));
		//		ImageDepot["block"]->Draw(buffer);
		//	}
		//}


		////test.Draw(buffer, Rect(100,100,200,200));
		//ImageDepot["circle"]->Move(Rect(100,100,200,200));
		//ImageDepot["circle"]->Draw(buffer);

		//ImageDepot["test"]->Draw(buffer);

		//배경
		ImageDepot["Base"]->Move(Rect(0,50,700,550));
		ImageDepot["Base"]->Draw(buffer);

		ImageDepot["Calendar"]->Move(Rect(0,0,850,50));
		ImageDepot["Calendar"]->Draw(buffer);

		ImageDepot["IGMenu"]->Move(Rect(700,50,850,550));
		ImageDepot["IGMenu"]->Draw(buffer);

		ImageDepot["MakeBG"]->Move(Rect(0,550,850,700));
		ImageDepot["MakeBG"]->Draw(buffer);

		//좌석 배치
		//CEO
		ImageDepot["Chair"]->Move(Rect(145+15,160+20,145+15+70,160+20+85));
		ImageDepot["Chair"]->Draw(buffer);
		ImageDepot["CEO"]->Move(Rect(160+15,140+20,160+15+50,140+20+65));
		ImageDepot["CEO"]->Draw(buffer);
		ImageDepot["Table"]->Move(Rect(145,160,145+180,160+150));
		ImageDepot["Table"]->Draw(buffer);

		//직원
		//1
		ImageDepot["Chair"]->Move(Rect(323+15,220+20,323+15+70,220+20+85));
		ImageDepot["Chair"]->Draw(buffer);
		ImageDepot["Table"]->Move(Rect(323,220,323+180,220+150));
		ImageDepot["Table"]->Draw(buffer);
		//2
		ImageDepot["Chair"]->Move(Rect(220+15,283,220+15+70,268+15+85));
		ImageDepot["Chair"]->Draw(buffer);
		ImageDepot["Table"]->Move(Rect(220,268,220+180,268+150));
		ImageDepot["Table"]->Draw(buffer);
		//3
		ImageDepot["Table2"]->Move(Rect(373,240,373+180,240+150));
		ImageDepot["Table2"]->Draw(buffer);
		ImageDepot["Chair2"]->Move(Rect(373+78,240+49,373+78+70,240+49+85));
		ImageDepot["Chair2"]->Draw(buffer);
		//4
		ImageDepot["Table2"]->Move(Rect(267,290,267+180,290+150));
		ImageDepot["Table2"]->Draw(buffer);
		ImageDepot["Chair2"]->Move(Rect(267+78,290+49,267+78+70,290+49+85));
		ImageDepot["Chair2"]->Draw(buffer);

		
		//인게임 버튼
		btnIGMenu1.Draw(buffer);
		btnIGMenu2.Draw(buffer);
		btnIGMenu3.Draw(buffer);
		btnIGMenu4.Draw(buffer);
		btnIGMenu5.Draw(buffer);
		

		if(GmProg3 == true)
		{
			btnGameProg.Draw(buffer);

			ImageDepot["Point2"]->Move(Rect(300,570,360,620));
			ImageDepot["Point2"]->Draw(buffer);

			ImageDepot["Point3"]->Move(Rect(400,570,460,620));
			ImageDepot["Point3"]->Draw(buffer);
			
			ImageDepot["Point4"]->Move(Rect(500,570,560,620));
			ImageDepot["Point4"]->Draw(buffer);
			
			ImageDepot["Point5"]->Move(Rect(600,570,660,620));
			ImageDepot["Point5"]->Draw(buffer);
		}

		//창
		
		if(mode ==MAIN_MODE1)
		{
			ImageDepot["MainWindow"]->Move(rcClient);
			ImageDepot["MainWindow"]->Draw(buffer);
			
			btnNew.Draw(buffer);
			btnLoad.Draw(buffer);
			btnEnd.Draw(buffer);
		}

		//BkGround.Draw(buffer, Rect(0,50,700,550));
		//IGMenu.Draw(buffer, Rect(700,50,850,550));
		//CalendarBG.Draw(buffer, Rect(0,0,850,50));
		//MakeBG.Draw(buffer, Rect(0,550,850,700));
		//ClockBG.Draw(buffer, Rect(700,550,850,700));

/*
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
*/

		
		if (mode == CONTROL_MODE)
		{
			ImageDepot["gray"]->Move(rcClient);
			ImageDepot["gray"]->Draw(buffer);

			btnMini.Draw(buffer);
			btnClose.Draw(buffer);
		}

		if(mode == SUBMENU_MODE1)
		{
			ImageDepot["SubMenu1"]->Move(Rect(540, 100, 690, 300));
			ImageDepot["SubMenu1"]->Draw(buffer);
			
			btnMake.Draw(buffer);
			//btnClMake.Draw(buffer);
		}

		if(mode == MAKEMN_MODE)
		{
			if(GmProg3 == false)
			{
				ImageDepot["SubWin2"]->Move(Rect(50,75,650,525));
				ImageDepot["SubWin2"]->Draw(buffer);

				btnStruct1.Draw(buffer);
				btnGenre1.Draw(buffer);
				btnPrev1.Draw(buffer);
				btnNext1.Draw(buffer);

				ImageDepot["MenuText1"]->Move(Rect(420, 445, 570, 505));
				ImageDepot["MenuText1"]->Draw(buffer);

				ImageDepot["MenuText2"]->Move(Rect(120, 445, 270, 505));
				ImageDepot["MenuText2"]->Draw(buffer);
			

			

			switch(gStruct)
			{
			case Simulation:
				ImageDepot["BtnStruct1"]->Move(Rect(270, 280, 570, 340));
				ImageDepot["BtnStruct1"]->Draw(buffer);
				break;
			case RolePlaying:
				ImageDepot["BtnStruct2"]->Move(Rect(270, 280, 570, 340));
				ImageDepot["BtnStruct2"]->Draw(buffer);
				break;
			case gAction:
				ImageDepot["BtnStruct3"]->Move(Rect(270, 280, 570, 340));
				ImageDepot["BtnStruct3"]->Draw(buffer);
				break;
			case Sport:
				ImageDepot["BtnStruct4"]->Move(Rect(270, 280, 570, 340));
				ImageDepot["BtnStruct4"]->Draw(buffer);
				break;
			}
			switch(gGenre)
			{
			case Baseball:
				ImageDepot["BtnGenre1"]->Move(Rect(270, 350, 570, 410));
				ImageDepot["BtnGenre1"]->Draw(buffer);
				break;
			case Strategy:
				ImageDepot["BtnGenre2"]->Move(Rect(270, 350, 570, 410));
				ImageDepot["BtnGenre2"]->Draw(buffer);
				break;
			case Gun:
				ImageDepot["BtnGenre3"]->Move(Rect(270, 350, 570, 410));
				ImageDepot["BtnGenre3"]->Draw(buffer);
				break;
			case Fantasy:
				ImageDepot["BtnGenre4"]->Move(Rect(270, 350, 570, 410));
				ImageDepot["BtnGenre4"]->Draw(buffer);
				break;
				}
			}

			else if(GmProg3 == true)
			{
				btnCancel.Draw(buffer);

				ImageDepot["SubWin4"]->Move(Rect(70,130,630,430));
				ImageDepot["SubWin4"]->Draw(buffer);

				ImageDepot["White"]->Move(Rect(50,75,650,525));
				ImageDepot["White"]->Draw(buffer);

				ImageDepot["MenuText4"]->Move(Rect(270, 453, 430, 513));
				ImageDepot["MenuText4"]->Draw(buffer);
			}
		}
		//장르
		else if(mode == MAKE_MODE1)
		{
			ImageDepot["SubWin3"]->Move(Rect(50,75,650,525));
			ImageDepot["SubWin3"]->Draw(buffer);

			btnNext2.Draw(buffer);

			btnStruct2.Draw(buffer);
			btnStruct3.Draw(buffer);
			btnStruct4.Draw(buffer);
			btnStruct5.Draw(buffer);


			ImageDepot["BtnGS"]->Move(Rect(100, 200 + (60 * (gStruct%100)), 600, 260 + (60 * (gStruct%100))));
			ImageDepot["BtnGS"]->Draw(buffer);
			
			ImageDepot["BtnStruct1"]->Move(Rect(50, 200, 350, 260));
			ImageDepot["BtnStruct1"]->Draw(buffer);

			ImageDepot["BtnStruct2"]->Move(Rect(50, 260, 350, 320));
			ImageDepot["BtnStruct2"]->Draw(buffer);

			ImageDepot["BtnStruct3"]->Move(Rect(50, 320, 350, 380));
			ImageDepot["BtnStruct3"]->Draw(buffer);

			ImageDepot["BtnStruct4"]->Move(Rect(50, 380, 350, 440));
			ImageDepot["BtnStruct4"]->Draw(buffer);

			ImageDepot["MenuText2"]->Move(Rect(260, 445, 420, 505));
			ImageDepot["MenuText2"]->Draw(buffer);
		}
		//유형
		else if(mode == MAKE_MODE2)
		{
			ImageDepot["SubWin3"]->Move(Rect(50,75,650,525));
			ImageDepot["SubWin3"]->Draw(buffer);

			btnNext2.Draw(buffer);

			btnGenre2.Draw(buffer);
			btnGenre3.Draw(buffer);
			btnGenre4.Draw(buffer);
			btnGenre5.Draw(buffer);
			
			ImageDepot["BtnGS"]->Move(Rect(100, 200 + 60*(gGenre%200), 600, 260 + 60*(gGenre%200)));
			ImageDepot["BtnGS"]->Draw(buffer);

			ImageDepot["BtnGenre1"]->Move(Rect(50, 200, 350, 260));
			ImageDepot["BtnGenre1"]->Draw(buffer);
			
			ImageDepot["BtnGenre2"]->Move(Rect(50, 260, 350, 320));
			ImageDepot["BtnGenre2"]->Draw(buffer);
			
			ImageDepot["BtnGenre3"]->Move(Rect(50, 320, 350, 380));
			ImageDepot["BtnGenre3"]->Draw(buffer);
			
			ImageDepot["BtnGenre4"]->Move(Rect(50, 380, 350, 440));
			ImageDepot["BtnGenre4"]->Draw(buffer);
			
			ImageDepot["MenuText2"]->Move(Rect(260, 445, 420, 505));
			ImageDepot["MenuText2"]->Draw(buffer);
		}

		else if(mode == MAKE_MODE3)
		{
			ImageDepot["SubWin4"]->Move(Rect(50,75,650,525));
			ImageDepot["SubWin4"]->Draw(buffer);
			
			if(GmProg == false)
			{
				btnNext4.Draw(buffer);

				ImageDepot["Point"]->Move(Rect(380,155,440,355));
				ImageDepot["Point"]->Draw(buffer);

				ImageDepot["MenuText1"]->Move(Rect(430, 370, 580, 430));
				ImageDepot["MenuText1"]->Draw(buffer);
				
				switch(person)
				{
				case P1:
					ImageDepot["Programmer"]->Move(Rect(180,185,240,365));
					ImageDepot["Programmer"]->Draw(buffer);
					break;
				case P2:
					ImageDepot["Writer"]->Move(Rect(180,185,240,365));
					ImageDepot["Writer"]->Draw(buffer);
					break;
				case P3:
					ImageDepot["Artist"]->Move(Rect(180,185,240,365));
					ImageDepot["Artist"]->Draw(buffer);
					break;
				case P4:
					ImageDepot["SD"]->Move(Rect(180,185,240,365));
					ImageDepot["SD"]->Draw(buffer);
					break;
				}

				switch(job)
				{
				case pgrm:
					ImageDepot["Job1"]->Move(Rect(120,215,230,385));
					ImageDepot["Job1"]->Draw(buffer);
					break;
				case writer:
					ImageDepot["Job2"]->Move(Rect(120,215,230,385));
					ImageDepot["Job2"]->Draw(buffer);
					break;
				case iller:
					ImageDepot["Job3"]->Move(Rect(120,215,230,385));
					ImageDepot["Job3"]->Draw(buffer);
					break;
				case sound:
					ImageDepot["Job4"]->Move(Rect(120,215,230,385));
					ImageDepot["Job4"]->Draw(buffer);
					break;
				}
			}
			else if(GmProg == true)
			{
				if(GmProg2 == false)
				{
					btnOk.Draw(buffer);

					ImageDepot["White"]->Move(Rect(70,130,630,430));
					ImageDepot["White"]->Draw(buffer);

					ImageDepot["Point2"]->Move(Rect(250,255,310,305));
					ImageDepot["Point2"]->Draw(buffer);

					ImageDepot["Point3"]->Move(Rect(340,255,400,305));
					ImageDepot["Point3"]->Draw(buffer);

					ImageDepot["Point4"]->Move(Rect(430,255,490,305));
					ImageDepot["Point4"]->Draw(buffer);

					ImageDepot["Point5"]->Move(Rect(520,255,580,305));
					ImageDepot["Point5"]->Draw(buffer);

					ImageDepot["MenuText3"]->Move(Rect(270, 453, 430, 513));
					ImageDepot["MenuText3"]->Draw(buffer);
				}
				else if(GmProg2 == true)
				{
					btnOk2.Draw(buffer);
					
					ImageDepot["MenuText3"]->Move(Rect(270, 453, 430, 513));
					ImageDepot["MenuText3"]->Draw(buffer);

					GmProg3 = true;
				}
			}
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
		AddEventHandler(WM_CHANGEMODE, &Me::ChngMode);
		AddEventHandler(WM_STCHANGEMODE, &Me::StChngMode);
		AddEventHandler(WM_GECHANGEMODE, &Me::GeChngMode);
		//AddEventHandler(WM_SYSCOMMAND, &Me::OnSysCommand);
		AddEventHandler(WM_GMPRO, &Me::GmPro);
		AddEventHandler(WM_GMPRO2, &Me::GmPro2);
		AddEventHandler(WM_GMPRO3, &Me::GmPro3);
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
		//Sound* pSound = new Sound;
		//pSound->Load("송골매 - 어쩌다 마주친 그대.mp3");
		//pSound->SetLoop();
		////pSound->SetLoopRange(0, 20000);
		//SoundDepot.push("bgSound", pSound);
		//
		//pSound = new Sound;
		//pSound->Load("explosion-01.wav");
		//SoundDepot.push("explosion", pSound);


		//SoundDepot["bgSound"]->Play();

		Loader();

		::GetClientRect(hWnd, &rcClient);
		hMainWnd = hWnd;

		//Image* pImage = new Image;
		
		//pImage->load(_T("block.bmp"));

		//ImageDepot.push("block", pImage);

		//block.load(_T("block.bmp"));

		//test.load(_T("circle.bmp"), Rect(0, 0, 100,100));

		//hMainDC = ::GetDC(hWnd);
		//hBitmapDC = ::CreateCompatibleDC(hMainDC);
		//gray.load(_T("gray.bmp"), Rect(0,0,10,10));
		//Select(hBitmapDC, HBITMAP(gray));

		
		//메인메뉴 버튼 등록
		btnNew.Attach(hWnd);
		btnNew.SetImageOn(_T("BtnMainMenu.bmp"), Rect(0,0,355,70));
		btnNew.SetImageOff(_T("BtnMainMenu.bmp"), Rect(0,0,355,70));
		btnNew.SetTransparent(RGB(80,75,75));
		btnNew.SetButtonRect(Rect(250, 450, 605, 520));
		btnNew.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, INGAME_MODE, 0);

		btnEnd.Attach(hWnd);
		btnEnd.SetImageOn(_T("BtnMainMenu.bmp"), Rect(0,140,355,210));
		btnEnd.SetImageOff(_T("BtnMainMenu.bmp"), Rect(0,140,355,210));
		btnEnd.SetTransparent(RGB(80,75,75));
		btnEnd.SetButtonRect(Rect(250, 450+140, 605, 520+140));
		btnEnd.SetAction(&SoundApp::Proxy, hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);

//인게임 메뉴 버튼 등록
		btnIGMenu1.Attach(hWnd);
		btnIGMenu1.SetImageOn(_T("BtnIGMenu.bmp"), Rect(0,0,110,50));
		btnIGMenu1.SetImageOff(_T("BtnIGMenu.bmp"), Rect(0,0,110,50));
		btnIGMenu1.SetButtonRect(Rect(720, 115, 830, 165));
		btnIGMenu1.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, SUBMENU_MODE1, 0);

		//btnIGMenu2.Attach(hWnd);
		//btnIGMenu2.SetImageOn(_T("BtnIGMenu.bmp"), Rect(110,0,220,50));
		//btnIGMenu2.SetImageOff(_T("BtnIGMenu.bmp"), Rect(110,0,220,50));
		//btnIGMenu2.SetButtonRect(Rect(720, 190, 830, 240));
		//btnIGMenu2.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, SUBMENU_MODE2, 0);

		//btnIGMenu3.Attach(hWnd);
		//btnIGMenu3.SetImageOn(_T("BtnIGMenu.bmp"), Rect(220,0,330,50));
		//btnIGMenu3.SetImageOff(_T("BtnIGMenu.bmp"), Rect(220,0,330,50));
		//btnIGMenu3.SetButtonRect(Rect(720, 270, 830, 320));
		//btnIGMenu3.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, MARKET_MODE, 0);

		//btnIGMenu4.Attach(hWnd);
		//btnIGMenu4.SetImageOn(_T("BtnIGMenu.bmp"), Rect(330,0,440,50));
		//btnIGMenu4.SetImageOff(_T("BtnIGMenu.bmp"), Rect(330,0,440,50));
		//btnIGMenu4.SetButtonRect(Rect(720, 350, 830, 400));
		//btnIGMenu4.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, INFO_MODE, 0);

		btnIGMenu5.Attach(hWnd);
		btnIGMenu5.SetImageOn(_T("BtnIGMenu.bmp"), Rect(440,0,550,50));
		btnIGMenu5.SetImageOff(_T("BtnIGMenu.bmp"), Rect(440,0,550,50));
		btnIGMenu5.SetButtonRect(Rect(720, 430, 830, 480));
		btnIGMenu5.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, CONTROL_MODE, 0);
		
//컨트롤 메뉴 버튼 등록
		btnMini.Attach(hWnd);
		btnMini.SetImageOn(_T("button.bmp"), Rect(50,0,100,50));
		btnMini.SetImageOff(_T("button.bmp"), Rect(0,0,50,50));
		btnMini.SetTransparent(RGB(255,0,255));
		btnMini.SetButtonRect(Rect(850 - 50*2, 0, 850 - 50, 50));
		btnMini.SetAction(&SoundApp::Proxy, hWnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);

		btnClose.Attach(hWnd);
		btnClose.SetImageOn(_T("button.bmp"), Rect(150,0,200,50));
		btnClose.SetImageOff(_T("button.bmp"), Rect(100,0,150,50));
		btnClose.SetTransparent(RGB(255,0,255));
		btnClose.SetButtonRect(Rect(850 - 50, 0, 850, 50));
		btnClose.SetAction(&SoundApp::Proxy, hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);

//서브 메뉴 버튼
		//1
		btnMake.Attach(hWnd);
		btnMake.SetImageOn(_T("BtnSubMenu.bmp"), Rect(0,50,110,100));
		btnMake.SetImageOff(_T("BtnSubMenu.bmp"), Rect(0,50,110,100));
		btnMake.SetButtonRect(Rect(560, 130, 670, 180));
		btnMake.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, MAKEMN_MODE, 0);
		
//게임제작 개요 버튼
//MAKEMN
		btnStruct1.Attach(hWnd);
		btnStruct1.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnStruct1.SetImageOff(_T("BtnGS.bmp"), Rect(0,0,300,60));
		btnStruct1.SetButtonRect(Rect(270, 280, 570, 340));
		btnStruct1.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, MAKE_MODE1, 0);

		btnGenre1.Attach(hWnd);
		btnGenre1.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnGenre1.SetImageOff(_T("BtnGS.bmp"), Rect(0,0,300,60));
		btnGenre1.SetButtonRect(Rect(270, 350, 570, 410));
		btnGenre1.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, MAKE_MODE2, 0);

		btnPrev1.Attach(hWnd);
		btnPrev1.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnPrev1.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnPrev1.SetButtonRect(Rect(120, 445, 270, 505));
		btnPrev1.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, INGAME_MODE, 0);
		
		btnNext1.Attach(hWnd);
		btnNext1.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnNext1.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnNext1.SetButtonRect(Rect(420, 445, 570, 505));
		btnNext1.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, MAKE_MODE3, 0);

		btnCancel.Attach(hWnd);
		btnCancel.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnCancel.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnCancel.SetButtonRect(Rect(270, 453, 430, 513));
		btnCancel.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, INGAME_MODE, 0);
		
//MAKE_MODE1
		btnStruct2.Attach(hWnd);
		btnStruct2.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnStruct2.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnStruct2.SetButtonRect(Rect(100, 200, 600, 260));
		btnStruct2.SetAction(&SoundApp::Proxy, hWnd, WM_STCHANGEMODE, Simulation, 0);

		btnStruct3.Attach(hWnd);
		btnStruct3.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnStruct3.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnStruct3.SetButtonRect(Rect(100, 260, 600, 320));
		btnStruct3.SetAction(&SoundApp::Proxy, hWnd, WM_STCHANGEMODE, RolePlaying, 0);

		btnStruct4.Attach(hWnd);
		btnStruct4.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnStruct4.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnStruct4.SetButtonRect(Rect(100, 320, 600, 380));
		btnStruct4.SetAction(&SoundApp::Proxy, hWnd, WM_STCHANGEMODE, gAction, 0);

		btnStruct5.Attach(hWnd);
		btnStruct5.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnStruct5.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnStruct5.SetButtonRect(Rect(100, 380, 600, 440));
		btnStruct5.SetAction(&SoundApp::Proxy, hWnd, WM_STCHANGEMODE, Sport, 0);

		btnNext2.Attach(hWnd);
		btnNext2.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnNext2.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnNext2.SetButtonRect(Rect(260, 445, 420, 505));
		btnNext2.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, MAKEMN_MODE, 0);

//MAKE_MODE2
		btnGenre2.Attach(hWnd);
		btnGenre2.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnGenre2.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnGenre2.SetButtonRect(Rect(100, 200, 600, 260));
		btnGenre2.SetAction(&SoundApp::Proxy, hWnd, WM_GECHANGEMODE, Baseball, 0);

		btnGenre3.Attach(hWnd);
		btnGenre3.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnGenre3.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnGenre3.SetButtonRect(Rect(100, 260, 600, 320));
		btnGenre3.SetAction(&SoundApp::Proxy, hWnd, WM_GECHANGEMODE, Strategy, 0);

		btnGenre4.Attach(hWnd);
		btnGenre4.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnGenre4.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnGenre4.SetButtonRect(Rect(100, 320, 600, 380));
		btnGenre4.SetAction(&SoundApp::Proxy, hWnd, WM_GECHANGEMODE, Gun, 0);

		btnGenre5.Attach(hWnd);
		btnGenre5.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnGenre5.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnGenre5.SetButtonRect(Rect(100, 380, 600, 440));
		btnGenre5.SetAction(&SoundApp::Proxy, hWnd, WM_GECHANGEMODE, Fantasy, 0);

//MAKE_MODE3
		btnNext4.Attach(hWnd);
		btnNext4.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnNext4.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnNext4.SetButtonRect(Rect(430, 370, 580, 430));
		btnNext4.SetAction(&SoundApp::Proxy, hWnd, WM_GMPRO, 0, 0);

		btnOk.Attach(hWnd);
		btnOk.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnOk.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnOk.SetButtonRect(Rect(270, 453, 430, 513));
		btnOk.SetAction(&SoundApp::Proxy, hWnd, WM_GMPRO2, 0, 0);

		btnOk2.Attach(hWnd);
		btnOk2.SetImageOn(_T("BtnGS.bmp"), Rect(0,60,300,120));
		btnOk2.SetImageOff(_T("BtnGS.bmp"), Rect(0,120,300,180));
		btnOk2.SetButtonRect(Rect(270, 453, 430, 513));
		btnOk2.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, INGAME_MODE, 0);
		
//INGAME_MODE - MAKE
		//1
		btnGameProg.Attach(hWnd);
		btnGameProg.SetImageOn(_T("BtnGS.bmp"), Rect(0,180,800,550));
		btnGameProg.SetImageOff(_T("BtnGS.bmp"), Rect(0,330,800,550));
		btnGameProg.SetButtonRect(Rect(0, 550, 850, 700));
		btnGameProg.SetAction(&SoundApp::Proxy, hWnd, WM_CHANGEMODE, MAKEMN_MODE, 0);
		//2
		btnOk3.

		buffer.Attach(hWnd);
		return 0;
	}


	
//모드체인지
	LRESULT ChngMode(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{	
		mode = wParam;

		return 0;
	}

	//장르변환
	LRESULT StChngMode(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{	
		gStruct = wParam;

		return 0;
	}

	//유형변환
	LRESULT GeChngMode(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{	
		gGenre = wParam;

		return 0;
	}

	//bool로 판별할 요소들을 위한 요소
	LRESULT GmPro(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if(GmProg == true)
		{
			GmProg = false;
		}
		else if(GmProg == false)
		{
			GmProg = true;
		}

		return GmProg;
	}
	LRESULT GmPro2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if(GmProg2 == true)
		{
			GmProg2 = false;
		}
		else if(GmProg2 == false)
		{
			GmProg2 = true;
		}

		return GmProg2;
	}
	LRESULT GmPro3(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if(GmProg3 == true)
		{
			GmProg3 = false;
		}
		else if(GmProg3 == false)
		{
			GmProg3 = true;
		}

		return GmProg3;
	}

	LRESULT OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		//gray.release();
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
	//Image gray;
	//Image test;

	//Image block;

	int mode;
	int gGenre;
	int gStruct;
	int tResult; 
	int job; //직업번호
	int person;//직원번호

	bool GmProg; //중간 진행 애니메이션 로드
	bool GmProg2; //진행상황 세부 버튼
	bool GmProg3; //시작
	bool GmProg4; //미술
	bool GmProg5; //음악
	bool GmProg6; //1~5를 전부 다시 false로


	

	GameProgress GMPS;

	// FPS 출력용도.
	// FPS : Frame Per Second.
	// FPS_dt(ms) : FPS_frame = 1000ms : x
	// FPS_frame*1000/FPS_dt = x
	DWORD FPS_dt;
	DWORD FPS_frame;
	DWORD dwFPS;

	//컨트롤 모드 버튼
	Button btnMini;
	Button btnClose;

	//창 이동 위한 설정
	HWND hMainWnd;
	Point ptPrev;
	Point ptMouse;
	bool bGrabWindow;

	//메인메뉴 버튼
	Button btnNew;
	Button btnLoad;
	Button btnEnd;

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

	//인게임 메뉴 버튼
	Button btnIGMenu1;
	Button btnIGMenu2;
	Button btnIGMenu3;
	Button btnIGMenu4;
	Button btnIGMenu5;

	//서브메뉴창
	Image SubMenu;
	Image SubMenu2;
	Button btnMake;
	Button btnClMake;
	Button btnJob;
	Button btnTrain;
	Button btnFire;

	//장르 설정 버튼
	Button btnStruct1;
	Button btnGenre1;
	
	//대장르 소장르 설정 관련 버튼
	Button btnStruct2;
	Button btnStruct3;
	Button btnStruct4;
	Button btnStruct5;
	Button btnGenre2;
	Button btnGenre3;
	Button btnGenre4;
	Button btnGenre5;

	//서브 윈도우 진행관련 버튼
	Button btnNext1; //MAKEMN
	Button btnPrev1;
	Button btnNext2; //MAKE1, MAKE2
	Button btnNext4; //MAKE3
	Button btnOk; //MAKE3-2
	Button btnOk2; //MAKE3-3
	Button btnOk3; //미술->
	Button btnOk4; //음악->
	Button btnOk5; //버그체크->
	Button btnOk6; //모두 false로 초기화!
	Button btnCancel;
	

	//게임제작모드
	Button btnGameProg;
	
	
	//////////////////////////
	// moving background...
	LONG dx;
	DWORD bg_update_dt;
	DWORD bg_update_delay;

	/////////////////////////
	// rotate 
	float ang;
};
