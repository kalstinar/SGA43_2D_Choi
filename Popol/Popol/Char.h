#pragma once

#include "D:\GitHub\SGA43_2D_Choi\Popol\MainWindow\sga.hpp"


class Char
{
	

public:

	Char()
		:skill(Programmer), job(pgrm), BasicSalery(500), pgrmJobLV(1),illerJobLV(1),writerJobLV(1),soundJobLV(1), Cname("재벌왕최재벌")
	{
	}

	~Char()
	{
		Salery = BasicSalery;
	}

///////////////////////////////////////////////////////////////////////
//CEO 직업
	void CEO()
	{
		if(skill == Programmer)
		{	
			Pskill * 1.2;
		}
		else if(skill == Designer)
		{
			
		}
	}

	char CEOname()
	{
		return Cname[64]; 
	}

/////////////////////////////////////////////////////////////////////
	//직원 직업
	void Staff()
	{
		if(job == pgrm)
		{
			Pskill = 40+(rand()%40);
			Iskill = 5+(rand()%5);;
			Wskill = 5+(rand()%5);;
			Sskill = 10+(rand()%10);;
		}
		else if(job == iller)
		{
			Pskill = 5+(rand()%5);
			Iskill = 35+(rand()%35);
			Wskill = 10+(rand()%10);
			Sskill = 10+(rand()%10);
		}
		else if(job == sound)
		{
			Pskill = 5+(rand()%5);
			Iskill = 5+(rand()%5);
			Wskill = 5+(rand()%5);
			Sskill = 45+(rand()%45);
		}
		else if(job = writer)
		{
			Pskill = 5+(rand()%5);
			Iskill = 5+(rand()%5);
			Wskill = 40+(rand()%40);
			Sskill = 10+(rand()%10);
		}
	}

	
///////////////////////////////////////////////////////////
	//연봉계산

	int SaleryCap()
	{
		Salery = Salery + ((Salery / 10)* (SumJobLevel - 4));
		
		return Salery;
	}
	

private:
	//직업 id;
	int skill;
	int job;

	//연봉
	static int Salery;
	const int BasicSalery;

	int SumJobLevel;
	int pgrmJobLV;
	int illerJobLV;
	int soundJobLV;
	int writerJobLV;

	int Pskill; //프로그래밍 능력
	int Iskill;	//일러스트 능력
	int Wskill;	//작가 능력
	int Sskill;	//사운드 능력

	char Cname[64];
};