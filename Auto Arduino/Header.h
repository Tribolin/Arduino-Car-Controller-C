#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <fstream>


struct Vec
{
	float degree = 0;
	float distance = 0;
};

namespace newUI
{
	int getX(std :: string);
	int getY(std :: string);
}
namespace Serial
{
	void init(int);
	void Communicate(std :: vector<Vec>);
	std ::string readSer();
}
bool newUi();
bool equel(char[7]);
