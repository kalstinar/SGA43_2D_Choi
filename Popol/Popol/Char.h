#pragma once

#include "D:\GitHub\SGA43_2D_Choi\Popol\MainWindow\sga.hpp"


struct CharInfo
{
	std::string Name;
	int Job;
	
	int prosk;
	int wrtsk;
	int illsk;
	int sndsk;

	int sumLV;
	int pgrmLV;
	int wrtLV;
	int illerLV;
	int soundLV;
};

class Char
{
public:
	

	Char()
		:skill(Programmer), job(pgrm), BasicSalery(500)
	{
	}

	~Char()
	{
		Salery = BasicSalery;
	}

///////////////////////////////////////////////////////////////////////
//CEO 직업
	/*void CEO()
	{
		if(skill == Programmer)
		{	
			Pskill * 1.2;
		}
		else if(skill == Designer)
		{
			
		}
	}*/

	void CEOname(std::string name)
	{
		Cname = name;
	}

/////////////////////////////////////////////////////////////////////
//직원 직업따른 능력치
	void Staff()
	{
		if(job == pgrm)
		{
			Pskill = 40+(rand()%40) + ((pgrmJobLV-1)*16);
			Iskill = 5+(rand()%5) + ((pgrmJobLV-1)*2);
			Wskill = 5+(rand()%5) + ((pgrmJobLV-1)*2);
			Sskill = 10+(rand()%10) + ((pgrmJobLV-1)*4);
		}
		else if(job == iller)
		{
			Pskill = 5+(rand()%5) + ((illerJobLV-1)*2);
			Iskill = 35+(rand()%35) + ((illerJobLV-1)*14);
			Wskill = 10+(rand()%10) + ((illerJobLV-1)*4);
			Sskill = 10+(rand()%10) + ((illerJobLV-1)*4);
		}
		else if(job == sound)
		{
			Pskill = 5+(rand()%5) + ((soundJobLV-1)*2);
			Iskill = 5+(rand()%5) + ((soundJobLV-1)*2);
			Wskill = 5+(rand()%5) + ((soundJobLV-1)*2);
			Sskill = 45+(rand()%45) + ((soundJobLV-1)*18);
		}
		else if(job = writer)
		{
			Pskill = 5+(rand()%5) + ((writerJobLV-1)*2);
			Iskill = 5+(rand()%5) + ((writerJobLV-1)*2);
			Wskill = 40+(rand()%40) + ((writerJobLV-1)*16);
			Sskill = 10+(rand()%10) + ((writerJobLV-1)*4);
		}
	}

///////////////////////////////////////////////////////////
//연봉계산

	int SaleryCap()
	{
		Salery = Salery + ((Salery / 10)* (SumJobLevel - 4));
		
		return Salery;
	}
	
//////////////////////////////////////////////////////////
//데이터 입력
	void StData(int id, int wp, char name[64], int plv, int wlv, int ilv, int slv)
	{
		staff[id].Name = name;
		staff[id].Job = wp;
		staff[id].prosk = Pskill;
		staff[id].illsk = Iskill;
		staff[id].wrtsk = Wskill;
		staff[id].sndsk = Sskill;
		staff[id].pgrmLV = plv;
		staff[id].wrtLV = wlv;
		staff[id].illerLV = ilv;
		staff[id].soundLV = slv;
	}

private:
	//직업 id;
	int skill;
	int job;

	//연봉
	static int Salery;
	const int BasicSalery;
	int Pskill; //프로그래밍 능력
	int Iskill;	//일러스트 능력
	int Wskill;	//작가 능력
	int Sskill;	//사운드 능력

	int SumJobLevel; //레벨 총합
	int pgrmJobLV;
	int illerJobLV;
	int soundJobLV;
	int writerJobLV;

	std::string Cname;

	CharInfo staff[4];
	
};