#pragma once
#include "stdafx.h"
#include "common.h"

extern void delay(clock_t sec);

void multiPlayer();

void gameLoop(std::pair < unsigned int, std::string> &result,
			  const std::string &playerOne,
			  const std::string &playerTwo,
			  unsigned int &playerOneScore,
			  unsigned int &playerTwoScore);