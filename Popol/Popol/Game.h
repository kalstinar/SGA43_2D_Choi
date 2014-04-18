#pragma once

#include "D:\GitHub\SGA43_2D_Choi\Popol\MainWindow\sga.hpp"

class Game
{

	//게임 장르들
	enum Game_Struct
	{
		Simulation = 1,
		RolePlaying,
		Action,
		Sport
	};
	enum Game_Genre
	{
		Baseball = 5,
		Strategy,
		Gun,
		Fantasy
	};

	enum Task_Result
	{
		Good = 9,
		Nomal,
		Bad
	};

public:
	Game()
	{
	}

	~Game()
	{
	}

//작업의 결과 예정 산출
	int GoodTask(int gStruct, int gGenre)
	{
		if(G_Struct == 1 && G_Genre == 6)
		{
			T_Result = 9;
		}
		
		if(G_Struct == 2 && G_Genre == 8)
		{
			T_Result = 9;
		}

		if(G_Struct == 3 && G_Genre == 7)
		{
			T_Result = 9;
		}

		if(G_Struct == 4 && G_Genre == 5)
		{
			T_Result = 9;
		}

		if(G_Struct == 1 && G_Genre == 8)
		{
			T_Result = 11;
		}

		if(G_Struct == 2 && G_Genre == 5)
		{
			T_Result = 11;
		}

		if(G_Struct == 3 && G_Genre == 6)
		{
			T_Result = 11;
		}

		if(G_Struct == 4 && G_Genre == 7)
		{
			T_Result = 11;
		}

		else T_Result = 10;
	}

//작업 비용
	int GameMakeSpend()
	{
			
	}

private:
	int G_Struct;
	int G_Genre;
	int T_Result;
};