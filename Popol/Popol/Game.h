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
	/*
	void GoodTask(int gStruct, int gGenre, int tRe)
	{
		if(gStruct == Simulation && gGenre == Strategy)
		{
			tRe = Good;
		}
		
		if(gStruct == RolePlaying && gGenre == Fantasy)
		{
			tRe = Good;
		}

		if(G_Struct == gAction && gGenre == Gun)
		{
			tRe = Good;
		}

		if(gStruct == Sport && gGenre == Baseball)
		{
			tRe = Good;
		}

		if(gStruct == Simulation && gGenre == Fantasy)
		{
			tRe = Bad;
		}

		if(gStruct == RolePlaying && gGenre == Baseball)
		{
			tRe = Bad;
		}

		if(G_Struct == gAction && gGenre == Strategy)
		{
			tRe = Bad;
		}

		if(gStruct == Sport && gGenre == Gun)
		{
			tRe = Bad;
		}

		else tRe = Normal;

		
	}
	*/
	

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