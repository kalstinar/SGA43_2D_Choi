#pragma once

#include "D:\GitHub\SGA43_2D_Choi\Popol\MainWindow\sga.hpp"

class Money
{
public:
	Money()
		:GameSell(0), GamePrice(3), SumPay(0), Pay1(0), Pay2(0), Pay3(0), Pay4(0), BMoney(5000), MkSpend(0)
	{
		CMoney = BMoney;
	}

	~Money()
	{
	}

	int MakeSpend()
	{

		return MkSpend;
	}

	int Bill(int Pay1, int Pay2, int Pay3, int Pay4)
	{
		SumPay = Pay1 + Pay2 + Pay3 + Pay4; 
		return SumPay;
	}

	int CurrentMoney()
	{
		CMoney = (BMoney + (GamePrice * GameSell)) - (MoneySpend + SumPay);
		return CMoney;
	}

private:
	int MkSpend;
	int SumPay, Pay1, Pay2, Pay3, Pay4;
	int GameSell;
	int GamePrice;
	const int BMoney;
	static int CMoney;
	
};