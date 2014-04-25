#pragma once

#include <windows.h>
#include <tchar.h>
#include "..\MainWindow\sga.hpp"
#include <fstream>
#include <string>

class LoadRes : public singleton<LoadRes>
{
	friend class singleton<LoadRes>;
private :
	LoadRes();
	~LoadRes();

public :
	void Load();
	void operator ()();

private :
	LPCTSTR szFileName;
};

#define Loader LoadRes::getReference()