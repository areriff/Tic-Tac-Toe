#pragma once
#include "stdafx.h"
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <random>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
#include <Windows.h>
#include "singlePlayer.h"
#include "multiPlayer.h"
#include "hallOfFame.h"
#include <ctime>
#include <set>


void delay(clock_t sec);

using namespace std::literals;

std::map<unsigned int, char> initBoard();
std::string initPlayer();
void displayBoard(const std::map<unsigned int, char> &masterBoard,
				  const unsigned int &playerOneScore,
				  const unsigned int &playerTwoScore,
				  const char &turns);
bool playAgain();
void swapTurn(char &turn);
void swapTurn(int &turn);
bool checkVictory(const std::map<unsigned int, char> &masterBoard);
bool checkDraw(const std::map<unsigned int, char> &masterBoard);
auto randomize(const int &minVal, const int &maxVal);
void pickEmpty(std::map<unsigned int, char> &masterBoard, const int &turns);
void smartPickEmpty(std::map<unsigned int, char> &masterBoard, const int &turns);
void smartPickEmpty2(std::map<unsigned int, char> &masterBoard, const int &turns);
void pickSquare(std::map<unsigned int, char> &masterBoard, char turns, const std::string &playerName);
void pickSquare(std::map<unsigned int, char> &masterBoard, const int &turns, const std::string &playerName);
void mainMenu();
void ClearScreen();

