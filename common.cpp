#include "stdafx.h"
#include "common.h"


//delay the screen output in milisecond
void delay(clock_t sec) { // clock_t is a like typedef unsigned int clock_t. Use clock_t instead of integer in this context
	clock_t start_time = clock();
	clock_t end_time = sec * 1000 + start_time;
	while ( clock() != end_time );
}

//Windows specific function - clear the screen
void ClearScreen() {
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if ( hStdOut == INVALID_HANDLE_VALUE ) return;

	/* Get the number of cells in the current buffer */
	if ( !GetConsoleScreenBufferInfo(hStdOut, &csbi) ) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if ( !FillConsoleOutputCharacter(
		hStdOut,
		( TCHAR ) ' ',
		cellCount,
		homeCoords,
		&count
		) ) return;

	/* Fill the entire buffer with the current colors and attributes */
	if ( !FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		) ) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

//initialize game board with ' ' (blanks)
std::map<unsigned int, char> initBoard() {
	std::map<unsigned int, char> masterBoard;
	for ( unsigned int i = 0; i < 9; i++ ) {
		masterBoard[ i ] = ' ';
	}
	return masterBoard;
}

//initialize player - prompt for their name
std::string initPlayer() {
	std::string playerName;
	std::cout << "Enter the player name : ";
	std::getline(std::cin, playerName);
	std::cin.clear();
	return playerName;
}

//show check mark whenever the player 1's turn
char p1BlipTurn(const char &turns) {
	char tick = static_cast<char>( 251 );
	char blank = ' ';
	if ( turns == '1' ) {
		return tick;
	} else {
		return blank;
	}
}
char p1BlipTurn(const int &turns) {
	char tick = static_cast<char>( 251 );
	char blank = ' ';
	if ( turns == 1 ) {
		return tick;
	} else {
		return blank;
	}
}

//show check mark whenever the player 2's turn
char p2BlipTurn(const char &turns) {
	char tick = static_cast<char>( 251 );
	char blank = ' ';
	if ( turns == '2' ) {
		return tick;
	} else {
		return blank;
	}

}
char p2BlipTurn(const int &turns) {
	char tick = static_cast<char>( 251 );
	char blank = ' ';
	if ( turns == 2 ) {
		return tick;
	} else {
		return blank;
	}

}

//display board using C cast of ASCII table
void displayBoard(const std::map<unsigned int, char> &masterBoard,
				  const unsigned int &playerOneScore,
				  const unsigned int &playerTwoScore,
				  const char &turns) {
	std::cout << "\tCurrent board\t\t" << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << "\tLegends" << "\n";
	std::cout << "\t\t\t\t" << (char)186 << " Legends:      " << " " << (char)186 << "\n";
	std::cout << "\t" << (char)201 << (char)205 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)205 << (char)187 << "\t\t" << (char)186 << " Player 1 : O " << p1BlipTurn(turns) << " " << (char)186 << "\t" << (char)201 << (char)205 << (char)203 << (char)205 << (char)203 << (char)205 << (char)187 << "\n";
	std::cout << "\t" << (char)186 << " " << masterBoard.at(0) << " " << (char)186 << " " << masterBoard.at(1) << " " << (char)186 << " " << masterBoard.at(2) << " " << (char)186 << "\t\t" << (char)186 << " Player 2 : X " << p2BlipTurn(turns) << " " << (char)186 << "\t" << (char)186 << '1' << (char)186 << '2' << (char)186 << '3' << (char)186 << "\n";
	std::cout << "\t" << (char)204 << (char)205 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)205 << (char)185 << "\t\t" << (char)204 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)185 << "\t" << (char)204 << (char)205 << (char)206 << (char)205 << (char)206 << (char)205 << (char)185 << "\n";
	std::cout << "\t" << (char)186 << " " << masterBoard.at(3) << " " << (char)186 << " " << masterBoard.at(4) << " " << (char)186 << " " << masterBoard.at(5) << " " << (char)186 << "\t\t" << (char)186 << " Current Score: " << (char)186 << "\t" << (char)186 << '4' << (char)186 << '5' << (char)186 << '6' << (char)186 << "\n";
	std::cout << "\t" << (char)204 << (char)205 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)205 << (char)185 << "\t\t" << (char)186 << " Player 1 : " << playerOneScore << "  " << " " << (char)186 << "\t" << (char)204  << (char)205 << (char)206  << (char)205 << (char)206  << (char)205 << (char)185 << "\n";
	std::cout << "\t" << (char)186 << " " << masterBoard.at(6) << " " << (char)186 << " " << masterBoard.at(7) << " " << (char)186 << " " << masterBoard.at(8) << " " << (char)186 << "\t\t" << (char)186 << " Player 2 : " << playerTwoScore << "  " << " " << (char)186 << "\t" << (char)186 << '7' << (char)186 << '8' << (char)186 << '9' << (char)186 << "\n";
	std::cout << "\t" << (char)200 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)188 << "\t\t" << (char)200 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)188 << "\t" << (char)200 << (char)205 << (char)202  << (char)205 << (char)202  << (char)205 << (char)188 << "\n" << std::endl;
}
void displayBoard(const std::map<unsigned int, char> &masterBoard,
				  const unsigned int &playerOneScore,
				  const unsigned int &playerTwoScore,
				  const int &turns) {
	std::cout << "\tCurrent board\t\t" << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << "\tLegends" << "\n";
	std::cout << "\t\t\t\t" << (char)186 << " Legends:      " << " " << (char)186 << "\n";
	std::cout << "\t" << (char)201 << (char)205 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)205 << (char)187 << "\t\t" << (char)186 << " Player 1 : O " << p1BlipTurn(turns) << " " << (char)186 << "\t" << (char)201 << (char)205 << (char)203 << (char)205 << (char)203 << (char)205 << (char)187 << "\n";
	std::cout << "\t" << (char)186 << " " << masterBoard.at(0) << " " << (char)186 << " " << masterBoard.at(1) << " " << (char)186 << " " << masterBoard.at(2) << " " << (char)186 << "\t\t" << (char)186 << " Player 2 : X " << p2BlipTurn(turns) << " " << (char)186 << "\t" << (char)186 << '1' << (char)186 << '2' << (char)186 << '3' << (char)186 << "\n";
	std::cout << "\t" << (char)204 << (char)205 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)205 << (char)185 << "\t\t" << (char)204 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)185 << "\t" << (char)204 << (char)205 << (char)206 << (char)205 << (char)206 << (char)205 << (char)185 << "\n";
	std::cout << "\t" << (char)186 << " " << masterBoard.at(3) << " " << (char)186 << " " << masterBoard.at(4) << " " << (char)186 << " " << masterBoard.at(5) << " " << (char)186 << "\t\t" << (char)186 << " Current Score: " << (char)186 << "\t" << (char)186 << '4' << (char)186 << '5' << (char)186 << '6' << (char)186 << "\n";
	std::cout << "\t" << (char)204 << (char)205 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)205 << (char)185 << "\t\t" << (char)186 << " Player 1 : " << playerOneScore << "  " << " " << (char)186 << "\t" << (char)204 << (char)205 << (char)206 << (char)205 << (char)206 << (char)205 << (char)185 << "\n";
	std::cout << "\t" << (char)186 << " " << masterBoard.at(6) << " " << (char)186 << " " << masterBoard.at(7) << " " << (char)186 << " " << masterBoard.at(8) << " " << (char)186 << "\t\t" << (char)186 << " Player 2 : " << playerTwoScore << "  " << " " << (char)186 << "\t" << (char)186 << '7' << (char)186 << '8' << (char)186 << '9' << (char)186 << "\n";
	std::cout << "\t" << (char)200 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)205 << (char)188 << "\t\t" << (char)200 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)188 << "\t" << (char)200 << (char)205 << (char)202 << (char)205 << (char)202 << (char)205 << (char)188 << "\n" << std::endl;
}

//ask user whether wants to play again or not.
bool playAgain() {
	std::cout << "Do you want to play again? (y/n) : ";
	char temp;
	bool valid = false;
	while ( !valid ) {
		std::string tempString;
		std::getline(std::cin, tempString);
		std::cin.clear();
		std::stringstream convert(tempString);
		if ( !( convert >> temp ) ) {
			std::cout << "That's not the answer. (y/n) only. Try again : ";
		} else if ( ( temp != 'y' ) && ( temp != 'n' ) ) {
			std::cout << "That's not the answer. (y/n) only. Try again : ";
		} else if ( ( temp == 'n' ) ) {
			valid = true;
			return false;
		} else if ( temp == 'y' ) {
			valid = true;
			return true;
		}
	}
	return false;
}

//swap turn after each move
void swapTurn(char &turn) {
	if ( turn == '1' ) {
		turn = '2';
	} else if ( turn == '2' ) {
		turn = '1';
	}
}

void swapTurn(int &turn) {
	if ( turn == 1 ) {
		turn = 2;
	} else if ( turn == 2 ) {
		turn = 1;
	}
}

//check for victory
bool checkVictory(const std::map<unsigned int, char> &masterBoard) {
	if ( ( masterBoard.at(0) != ' ' ) && ( masterBoard.at(0) == masterBoard.at(1) && ( masterBoard.at(1) ) == masterBoard.at(2) ) ) {
		return true;
	} else if ( ( masterBoard.at(3) != ' ' ) && ( masterBoard.at(3) == masterBoard.at(4) && ( masterBoard.at(4) ) == masterBoard.at(5) ) ) {
		return true;
	} else if ( ( masterBoard.at(6) != ' ' ) && ( masterBoard.at(6) == masterBoard.at(7) && ( masterBoard.at(7) ) == masterBoard.at(8) ) ) {
		return true;
	} else if ( ( masterBoard.at(0) != ' ' ) && ( masterBoard.at(0) == masterBoard.at(3) && ( masterBoard.at(3) ) == masterBoard.at(6) ) ) {
		return true;
	} else if ( ( masterBoard.at(1) != ' ' ) && ( masterBoard.at(1) == masterBoard.at(4) && ( masterBoard.at(4) ) == masterBoard.at(7) ) ) {
		return true;
	} else if ( ( masterBoard.at(2) != ' ' ) && ( masterBoard.at(2) == masterBoard.at(5) && ( masterBoard.at(5) ) == masterBoard.at(8) ) ) {
		return true;
	} else if ( ( masterBoard.at(0) != ' ' ) && ( masterBoard.at(0) == masterBoard.at(4) && ( masterBoard.at(4) ) == masterBoard.at(8) ) ) {
		return true;
	} else if ( ( masterBoard.at(2) != ' ' ) && ( masterBoard.at(2) == masterBoard.at(4) && ( masterBoard.at(4) ) == masterBoard.at(6) ) ) {
		return true;
	} else {
		return false;
	}
	return false;
}

//check for the draw
bool checkDraw(const std::map<unsigned int, char> &masterBoard) {
	std::vector<unsigned int> tempVec;
	for ( auto a : masterBoard ) {
		if ( a.second == ' ' ) {
			tempVec.push_back(a.second);
		}
	}
	if ( tempVec.empty() ) {
		return true;
	} else if ( !( tempVec.empty() ) ) {
		return false;
	}
	return false;
}

//use with pickEmpty() to choose random value
auto randomize(const int &minVal, const int &maxVal) {
	std::random_device rd;
	std::mt19937 genEngine(rd());
	std::uniform_int_distribution<int> distrib(minVal, maxVal);
	return distrib(genEngine);
}

// return a gamestate score from current position
int gameState(std::map<unsigned int, char> &masterBoard, int turn) {
	int state = 0;	// initialized it to value of a draw
	if ( turn == 1 ) {
		if ( checkVictory(masterBoard) == true ) {
			state = -10;
		} else if ( checkDraw(masterBoard) == true ) {
			state = 0;
		} else {	// game not finish
			state = -1;
		}
	}
	if ( turn == 2 ) {
		if ( checkVictory(masterBoard) == true ) {
			state = 10;
		} else if (checkDraw(masterBoard) == true) {
			state = 0;
		} else {	// game not finish
			state = -1;
		}
	}
	return state;
}

int miniMax(std::map<unsigned int, char> &masterBoard, int turn) {
	/*
	function minimax(node, depth, maximizingPlayer)
	if depth = 0 or node is a terminal node
		return the heuristic value of node

	if maximizingPlayer
		bestValue : = −∞
		for each child of node
			v : = minimax(child, depth − 1, FALSE)
			bestValue : = max(bestValue, v)
		return bestValue

	else    ( *minimizing player * )
		bestValue : = +∞
		for each child of node
			v : = minimax(child, depth − 1, TRUE)
			bestValue : = min(bestValue, v)
	return bestValue */
	return 0;
}

//allow computer randomly pick from empty box to make moves
void pickEmpty(std::map<unsigned int, char> &masterBoard, const int &turns) {
	bool valid = false;
	while ( !valid ) {
		std::vector<unsigned int> tempVec;
		for ( auto a : masterBoard ) {
			if ( a.second == ' ' ) {
				tempVec.push_back(a.first);
			}
		}
		auto temp = randomize(0, tempVec.size() - 1);
		unsigned int tempBox = tempVec.at(temp);
		if ( turns == 1 && masterBoard.at(tempBox) == ' ' ) {
			masterBoard[ tempBox ] = 'O';
			valid = true;
		} else if ( turns == 2 && masterBoard.at(tempBox) == ' ' ) {
			masterBoard[ tempBox ] = 'X';
			valid = true;
		} else {
			continue;
		}
	}
}
void smartPickEmpty(std::map<unsigned int, char> &masterBoard, const int &turns) {
	auto tempBoard = masterBoard;	// copy the gameboard so that changes don't applied while trying moves
	std::vector<unsigned int> tempVec; //vector to hold the value to apply to the masterBoard
	int tempTurn = turns;	//same purpose as tempBoard
	int score = 0;
	bool valid = true;
	while ( score < 10 || valid ) {
		if ( tempTurn == 2 ) {
			auto iter = tempBoard.begin();
			while ( score < 10 || iter != tempBoard.end() ) {
				if ( iter->second == ' ' ) {	// find a blank then make a move
					iter->second = 'X';
					if ( checkVictory(tempBoard) == true ) { 
						score += 100;
						tempVec.push_back(iter->first);
						valid = false;
						break;
					} else if ( checkDraw(tempBoard) == true ) {
						score++;
						tempBoard = masterBoard;
						break;
					} else {	// the game not draw, next player turn to move
						score--;
						swapTurn(tempTurn);
						iter++;
						break;
					}
				}
				iter++;
			}
		}
		if ( tempTurn == 1 ) {
			auto iter2 = tempBoard.begin();
			while ( score < 10 || iter2 != tempBoard.end() ) {
				if ( iter2->second == ' ' ) {
					iter2->second = 'O';
					if ( checkVictory(tempBoard) == true ) {
						score -= 100;
						break;
					} else if ( checkDraw(tempBoard) == true ) {
						score--;
						tempBoard = masterBoard;
						break;
					} else {
						score++;
						swapTurn(tempTurn);
						iter2++;
						break;
					}
				}
				//i++;
				/*if ( checkDraw(tempBoard) == false || score > 10 ) {
				break;
				}*/
				iter2++;
			}
		}
		displayBoard(tempBoard,1,1,1);
	}
	//store real value
	if ( !tempVec.empty() ) {
	masterBoard[ tempVec.at(0) ] = 'X';
	}
}
void smartPickEmpty2(std::map<unsigned int, char> &masterBoard, const int &turns) {
	auto tempBoard = masterBoard;	// copy the gameboard so that changes don't applied while trying moves
	std::vector<unsigned int> tempVec; //vector to hold the value to apply to the masterBoard
	int tempTurn = turns;	//same purpose as tempBoard
	int score = 0;
	bool valid = true;
	while ( score < 10 || valid ) {
		if ( tempTurn == 2 ) {
			auto iter = tempBoard.begin();
			while ( score < 10 || iter != tempBoard.end() ) {
				if ( iter->second == ' ' ) {	// find a blank then make a move
					iter->second = 'X';
					if ( checkVictory(tempBoard) == true ) {
						score += 100;
						tempVec.push_back(iter->first);
						valid = false;
						break;
					} else if ( checkDraw(tempBoard) == true ) {
						score++;
						tempBoard = masterBoard;
						break;
					} else {	// the game not draw, next player turn to move
						score--;
						swapTurn(tempTurn);
						iter++;
						break;
					}
				}
				iter++;
			}
		}
		if ( tempTurn == 1 ) {
			auto iter2 = tempBoard.begin();
			while ( score < 10 || iter2 != tempBoard.end() ) {
				if ( iter2->second == ' ' ) {
					iter2->second = 'O';
					if ( checkVictory(tempBoard) == true ) {
						score -= 100;
						break;
					} else if ( checkDraw(tempBoard) == true ) {
						score--;
						tempBoard = masterBoard;
						break;
					} else {
						score++;
						swapTurn(tempTurn);
						iter2++;
						break;
					}
				}
				//i++;
				/*if ( checkDraw(tempBoard) == false || score > 10 ) {
				break;
				}*/
				iter2++;
			}
		}
		displayBoard(tempBoard, 1, 1, 1);
	}
	//store real value
	if ( !tempVec.empty() ) {
		masterBoard[ tempVec.at(0) ] = 'X';
	}
}

//allow user to choose box to enter their move
void pickSquare(std::map<unsigned int, char> &masterBoard, char turns, const std::string &playerName) {
	std::vector<unsigned int> tempVec;
	for ( auto a : masterBoard ) {
		if ( a.second == ' ' ) {
			tempVec.push_back(a.first);
		}
	}
	std::cout << "Player " << turns << "'s turn" << std::endl;
	std::cout << playerName << " choose from the empty square to enter an ";
	if ( turns == '1' ) {
		std::cout << "O";
	} else {
		std::cout << "X";
	}
	std::cout << " : ";
	bool valid = false;
	unsigned int temp;
	while ( !valid ) {
		std::string tempString;
		std::getline(std::cin, tempString);
		std::cin.clear();
		std::stringstream convert(tempString);
		if ( !( convert >> temp ) ) {
			std::cout << "That's not a number. Try again : ";
		} else if ( ( temp < 1 ) || ( temp>9 ) ) {
			std::cout << "Only enter number 1 through 9. Try again : ";
		} else if ( masterBoard.at(temp - 1) == 'X' || masterBoard.at(temp - 1) == 'O' ) {
			std::cout << "Box is occupied, choose another box: ";
		} else {
			valid = true;
		}
	}
	if ( turns == '1' ) {
		masterBoard[ temp - 1 ] = 'O';
	} else {
		masterBoard[ temp - 1 ] = 'X';
	}
}
void pickSquare(std::map<unsigned int, char> &masterBoard, const int &turns, const std::string &playerName) {
	std::vector<unsigned int> tempVec;
	for ( auto a : masterBoard ) {
		if ( a.second == ' ' ) {
			tempVec.push_back(a.first);
		}
	}
	std::cout << "Player " << turns << "'s turn" << std::endl;
	std::cout << playerName << " choose from the empty square to enter an ";
	if ( turns == 1 ) {
		std::cout << "O";
	} else {
		std::cout << "X";
	}
	std::cout << " : ";
	bool valid = false;
	unsigned int temp;
	while ( !valid ) {
		std::string tempString;
		std::getline(std::cin, tempString);
		std::cin.clear();
		std::stringstream convert(tempString);
		if ( !( convert >> temp ) ) {
			std::cout << "That's not a number. Try again : ";
		} else if ( ( temp < 1 ) || ( temp>9 ) ) {
			std::cout << "Only enter number 1 through 9. Try again : ";
		} else if ( masterBoard.at(temp - 1) == 'X' || masterBoard.at(temp - 1) == 'O' ) {
			std::cout << "Box is occupied, choose another box: ";
		} else {
			valid = true;
		}
	}
	if ( turns == 1 ) {
		masterBoard[ temp - 1 ] = 'O';
	} else {
		masterBoard[ temp - 1 ] = 'X';
	}
}

void mainMenu() {
	using std::cout;
	using std::endl;
	auto menuLoop = true;

	while ( menuLoop ) {
		ClearScreen();
		cout << "\tMain Menu" << endl;
		cout << "1. Single Player" << endl;
		cout << "2. Multi Player" << endl;
		cout << "3. High Score" << endl;
		cout << "4. Exit Game" << endl;
		int temp; std::string tempString;
		std::getline(std::cin, tempString);
		std::cin.clear();
		std::stringstream convert(tempString);
		if ( !( convert >> temp ) ) {
			cout << "That's not a number. Try again : ";
		} else if ( ( temp < 1 ) || ( temp>4 ) ) {
			cout << "That Menu is not valid. Try again : ";
		} else if ( temp == 1 ) {
			singlePlayer();
		} else if ( temp == 2 ) {
			multiPlayer();
		} else if ( temp == 3 ) {
			hallOfFame();
		} else if ( temp == 4 ) {
			menuLoop = false;
			exit(0);
		}
	}
}

