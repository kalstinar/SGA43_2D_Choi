﻿#pragma once

#include "D:\GitHub\SGA43_2D_Choi\Popol\MainWindow\sga.hpp"


class Char
{
	enum skill_id
	{
		Programmer = 1,
		Designer
	};

	enum job_id
	{
		pgrm = 5,
		iller,
		sound,
		writer
	};

public:

	Char()
		:skill(Programmer), job(pgrm), BasicSalery(500), pgrmJobLV(1),illerJobLV(1),writerJobLV(1),soundJobLV(1)
	{
		Salery = BasicSalery;
	}

	~Char()
	{
	}

///////////////////////////////////////////////////////////////////////
//CEO 직업
	void CEO()
	{
		if(skill == Programmer)
		{	
			
		}
		else if(skill == Designer)
		{
			
		}
	}

/////////////////////////////////////////////////////////////////////
	//직원 직업
	void Staff()
	{
		if(job == pgrm)
		{
			
		}
		else if(job == iller)
		{
		
		}
		else if(job == sound)
		{
		
		}
		else if(job = writer)
		{
			
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


};