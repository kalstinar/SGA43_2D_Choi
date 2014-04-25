#pragma once

#ifndef __SGA_HPP__
#define __SGA_HPP__

#include <windows.h>

#include "BaseType.h"
#include "utility.h"
#include "MainWindow.h"
#include "DoubleBuffer.h"
#include "image.h"
#include "animation.h"
#include "button.h"
#include "input.h"
#include "Manager.hpp"
#include <time.h>
#include <string>


#endif // __SGA_HPP__

//id모음


enum wm_id
{
	WM_CHANGEMODE = WM_USER + 1,
	WM_STCHANGEMODE,
	WM_GECHANGEMODE,
	WM_GMPRO,
	WM_GMPRO2,
	WM_GMPRO3
};

enum mode_id
{
	MAIN_MODE1 = 1,	//메인메뉴
	//MAIN_MODE2, //새 게임->회사이름, 사장직업 선택 ->생략 자동 지정되게
	//MAIN_MODE3, //로드 -> 이 것도 생략
	INGAME_MODE, //인게임
	CONTROL_MODE, //컨트롤
	SUBMENU_MODE1,
	SUBMENU_MODE2,
	MARKET_MODE,	//상점
	INFO_MODE,	//정보	
	MAKEMN_MODE,
	MAKE_MODE1,	//제작1(대장르)
	MAKE_MODE2,	//제작2(소장르)
	MAKE_MODE3,	//제작3(기본 설정)
	MAKE_MODE4,	
	MAKE_MODE5,	
	MAKE_MODE6,	
	//INMAKE_MODE	//게임제작 과정
};

enum Game_Struct
{
	Simulation = 100,
	RolePlaying,
	gAction,
	Sport
};

enum Game_Genre
{
	Baseball = 200,
	Strategy,
	Gun,
	Fantasy
};

enum Task_Result
{
	Good = 300,
	Normal,
	Bad
};

enum GameStat_id
{
	gJoy = 400,
	gCretive,
	gArt,
	gSound //403
};

enum skill_id //CEO직업
{
	Programmer = 404,
	Designer
};

enum job_id //직원 직업
{	
	pgrm = 410,
	writer,
	iller,
	sound
};

enum person_id
{
	P1 = 420,
	P2,
	P3,
	P4
};