#pragma once

#include "D:\GitHub\SGA43_2D_Choi\Popol\MainWindow\sga.hpp"
#include "Money.h"
#include "Char.h"

class Game
{

	////게임 장르들
	//enum Game_Struct
	//{
	//	Simulation = 1,
	//	RolePlaying,
	//	Action,
	//	Sport
	//};
	//enum Game_Genre
	//{
	//	Baseball = 5,
	//	Strategy,
	//	Gun,
	//	Fantasy
	//};

	//enum Task_Result
	//{
	//	Good = 9,
	//	Nomal,
	//	Bad
	//};

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
		if(G_Struct == Simulation && G_Genre == Strategy)
		{
			T_Result = Good;
		}
		
		if(G_Struct == RolePlaying && G_Genre == Fantasy)
		{
			T_Result = Good;
		}

		if(G_Struct == Action && G_Genre == Gun)
		{
			T_Result = Good;
		}

		if(G_Struct == Sport && G_Genre == Baseball)
		{
			T_Result = Good;
		}

		if(G_Struct == Simulation && G_Genre == Fantasy)
		{
			T_Result = Bad;
		}

		if(G_Struct == RolePlaying && G_Genre == Baseball)
		{
			T_Result = Bad;
		}

		if(G_Struct == Action && G_Genre == Strategy)
		{
			T_Result = Bad;
		}

		if(G_Struct == Sport && G_Genre == Gun)
		{
			T_Result = Bad;
		}

		else T_Result = Normal;
	}

//작업 비용
	int GameMakeSpend()
	{
		return G_Spend;
	}

	int GameResultMoney()
	{
		if(T_Result == Good)
		{
			
			return G_RMoney;
		}
		
		if(T_Result == Normal)
		{
			return G_RMoney;
		}

		if(T_Result == Bad)
		{
			return G_RMoney;
		}
	}

private:
	int G_Struct;
	int G_Genre;
	int T_Result;
	int G_Spend;
	int G_RMoney;
};