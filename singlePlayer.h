#pragma once
#include "stdafx.h"
#include "common.h"
using std::cout;
using std::endl;
using std::cin;

void singlePlayer();

void singlePlayerHard();

void singlePlayerEasy();

void easyMainGameLoop(int &turn, const std::string &p1Name, const std::string &p2Name);

void hardMainGameLoop(int &turn, const std::string &p1Name, const std::string &p2Name);