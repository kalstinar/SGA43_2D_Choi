#pragma once

#include "D:\GitHub\SGA43_2D_Choi\Popol\MainWindow\sga.hpp"
#include "Char.h"

class CharData
{
public:
	CharData()
	{
		Stf.StData(0, pgrm, "짝퉁강철남", 1,1,1,1);
		Stf.StData(1, writer, "홍일점?", 1,1,1,1);
		Stf.StData(2, iller, "그림이취미", 1,1,1,1);
		Stf.StData(3, sound, "복면다로", 1,1,1,1);
	}
	~CharData()
	{}

	

private:
	Char Stf;
};