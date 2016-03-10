#include "stdafx.h"
#include "singlePlayer.h"

void singlePlayer() {
	bool valid = false;
	while ( valid == false ) {
		ClearScreen();
		std::cout << "Choose computer strength:\n1. Strong\n2. Weak\n3. Quit" << std::endl;
		int temp; std::string tempString;
		std::getline(std::cin, tempString);
		std::cin.clear();
		std::stringstream convert(tempString);
		if ( !( convert >> temp ) ) {
			cout << "That's not a number. Try again : ";
		} else if ( ( temp < 1 ) || ( temp>3 ) ) {
			cout << "That Menu is not valid. Try again : ";
		} else if ( temp == 1 ) {
			singlePlayerHard();
			valid = true;
		} else if ( temp == 2 ) {
			singlePlayerEasy();
			valid = true;
		} else if ( temp == 3 ) {
			valid = true;
		} 
	}
}

void singlePlayerHard() {
	std::pair < unsigned int, std::string> result;
	std::string playerOne = initPlayer();
	std::string playerTwo = "Computer";

	bool valid = false;
	while ( valid == false ) {
		ClearScreen();
		std::cout << "Do you want to start first?\n1. Yes (you will start first)\n2. No (Computer will moves first)" << std::endl;
		cout << ">>";
		int temp; std::string tempString;
		std::getline(std::cin, tempString);
		std::cin.clear();
		std::stringstream convert(tempString);
		if ( !( convert >> temp ) ) {
			cout << "That's not a number. Try again.";
			delay(1);
		} else if ( ( temp < 1 ) || ( temp>2 ) ) {
			cout << "That Menu is not valid. Try again.";
			delay(1);
		} else if ( temp == 1 || temp == 2) {
			int menuChoice = temp;
			hardMainGameLoop(menuChoice,playerOne,playerTwo);
			valid = true;
			delay(1);
		}
	}
}

void singlePlayerEasy() {
	std::pair < unsigned int, std::string> result;
	std::string playerOne = initPlayer();
	std::string playerTwo = "Computer";

	bool valid = false;
	while ( valid == false ) {
		ClearScreen();
		std::cout << "Do you want to start first?\n1. Yes (you will start first)\n2. No (Computer will moves first)" << std::endl;
		cout << ">>";
		int temp; std::string tempString;
		std::getline(std::cin, tempString);
		std::cin.clear();
		std::stringstream convert(tempString);
		if ( !( convert >> temp ) ) {
			cout << "That's not a number. Try again.";
			delay(1);
		} else if ( ( temp < 1 ) || ( temp>2 ) ) {
			cout << "That Menu is not valid. Try again.";
			delay(1);
		} else if ( temp == 1 || temp == 2 ) {
			int menuChoice = temp;
			easyMainGameLoop(menuChoice, playerOne, playerTwo);
			valid = true;
			delay(1);
		}
	}
}


/*
int checkvictory
if there was victory as ai player
	return 10
else if the was victory as human player
	return -10

loop through the board to find empty box
	place a move there
	imaginarily make a move on that blank box
	if player == computer
		getbestmove of the next move as human player to get the score
	else if player == human
		getbestmove of the next move as ai player to get the score
	reset the move back to empty
*/

void easyMainGameLoop(int &turn, const std::string &p1Name, const std::string &p2Name) {
	std::pair < unsigned int, std::string> result;
	unsigned int playerOneScore = 0;
	unsigned int playerTwoScore = 0;
	auto gameBoard = initBoard();
	bool playLoop = true;

	while ( playLoop ) {
		if ( turn == 1 ) {
			ClearScreen();
			displayBoard(gameBoard,playerOneScore,playerTwoScore,turn);
			pickSquare(gameBoard, turn, p1Name);
			if ( checkVictory(gameBoard) == true ) {
				playerOneScore++;
				ClearScreen();
				displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				std::cout << p1Name << " wins!" << std::endl;
				auto playAgainTemp = playAgain();			//use as temporary value to hold a boolean whether player wants to play again
				if ( playAgainTemp == true ) {
					std::cout << "Swapping turns..." << std::endl;

					delay(1);
					gameBoard = initBoard();				//create a new blank board
					ClearScreen();
					swapTurn(turn);							//the other player will start the new game
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				} else if ( playAgainTemp == false && playerTwoScore < playerOneScore ) {		//if the player decides not to continue game after winning,
					result.first = playerOneScore;			//the game will end by returning the current score at the end
					result.second = p1Name;					//of current game to result (pair) for further processing (see
					internalHallOfFame(result);
					playLoop = false;						//multiplayer() function above).
				} else {
					playLoop = false;
				}
			} else if ( checkVictory(gameBoard) == false ) {
				if ( checkDraw(gameBoard) == true ) {
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
					std::cout << "The game is drawn." << std::endl;
					auto playAgainTemp = playAgain();
					if ( playAgainTemp == true ) {
						std::cout << "Swapping turns..." << std::endl;
						delay(1);
						gameBoard = initBoard();
						ClearScreen();
						swapTurn(turn);
						displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
					} else if ( playAgainTemp == false ) {
						playLoop = false;	//when draw, no high score will be recorded
					}
				} else if ( checkDraw(gameBoard) == false ) {
					swapTurn(turn);
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn); // continue to player 2
				}
			}

		}
		if ( turn == 2 ) {
			ClearScreen();
			displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
			pickEmpty(gameBoard, turn);
			if ( checkVictory(gameBoard) == true ) {
				playerTwoScore++;
				ClearScreen();
				displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				std::cout << p2Name << " wins!" << std::endl;
				auto playAgainTemp = playAgain(); //use as temporary value to hold a boolean whether player wants to play again
				if ( playAgainTemp == true ) {
					std::cout << "Swapping turns..." << std::endl;
					delay(1);
					gameBoard = initBoard(); //create a new blank board
					ClearScreen();
					swapTurn(turn); //the other player will start the new game
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				} else if ( playAgainTemp == false ) {	//if the player decides not to continue game after winning,
					result.first = playerTwoScore;			//the game will end by returning the current score at the end
					result.second = p2Name;		//of current game to result (pair) for further processing (see
					playLoop = false;						//multiplayer() function above).
				}
			} else if ( checkVictory(gameBoard) == false ) {
				if ( checkDraw(gameBoard) == true ) {
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
					std::cout << "The game is drawn." << std::endl;
					auto playAgainTemp = playAgain();
					if ( playAgainTemp == true ) {
						std::cout << "Swapping turns..." << std::endl;
						delay(1);
						gameBoard = initBoard();
						ClearScreen();
						swapTurn(turn);
						displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
					} else if ( playAgainTemp == false ) {
						playLoop = false;	//when draw, no high score will be recorded
					}
				} else if ( checkDraw(gameBoard) == false ) {
					swapTurn(turn);
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn); // continue to player 2
				}
			}
		}
		
	}
}

void hardMainGameLoop(int &turn, const std::string &p1Name, const std::string &p2Name) {
	std::pair < unsigned int, std::string> result;
	unsigned int playerOneScore = 0;
	unsigned int playerTwoScore = 0;
	auto gameBoard = initBoard();
	bool playLoop = true;

	while ( playLoop ) {
		if ( turn == 1 ) {
			ClearScreen();
			displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
			pickSquare(gameBoard, turn, p1Name);
			if ( checkVictory(gameBoard) == true ) {
				playerOneScore++;
				ClearScreen();
				displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				std::cout << p1Name << " wins!" << std::endl;
				auto playAgainTemp = playAgain(); //use as temporary value to hold a boolean whether player wants to play again
				if ( playAgainTemp == true ) {
					std::cout << "Swapping turns..." << std::endl;
					delay(1);
					gameBoard = initBoard(); //create a new blank board
					ClearScreen();
					swapTurn(turn); //the other player will start the new game
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				} else if ( playAgainTemp == false ) {	//if the player decides not to continue game after winning,
					result.first = playerOneScore;			//the game will end by returning the current score at the end
					result.second = p1Name;		//of current game to result (pair) for further processing (see
					playLoop = false;						//multiplayer() function above).
				}
			} else if ( checkVictory(gameBoard) == false ) {
				if ( checkDraw(gameBoard) == true ) {
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
					std::cout << "The game is drawn." << std::endl;
					auto playAgainTemp = playAgain();
					if ( playAgainTemp == true ) {
						std::cout << "Swapping turns..." << std::endl;
						delay(1);
						gameBoard = initBoard();
						ClearScreen();
						swapTurn(turn);
						displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
					} else if ( playAgainTemp == false ) {
						playLoop = false;	//when draw, no high score will be recorded
					}
				} else if ( checkDraw(gameBoard) == false ) {
					swapTurn(turn);
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn); // continue to player 2
				}
			}

		}
		if ( turn == 2 ) {
			ClearScreen();
			displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
			smartPickEmpty(gameBoard, turn);
			if ( checkVictory(gameBoard) == true ) {
				playerTwoScore++;
				ClearScreen();
				displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				std::cout << p2Name << " wins!" << std::endl;
				auto playAgainTemp = playAgain(); //use as temporary value to hold a boolean whether player wants to play again
				if ( playAgainTemp == true ) {
					std::cout << "Swapping turns..." << std::endl;
					delay(1);
					gameBoard = initBoard(); //create a new blank board
					ClearScreen();
					swapTurn(turn); //the other player will start the new game
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				} else if ( playAgainTemp == false ) {	//if the player decides not to continue game after winning,
					result.first = playerTwoScore;			//the game will end by returning the current score at the end
					result.second = p2Name;		//of current game to result (pair) for further processing (see
					playLoop = false;						//multiplayer() function above).
				}
			} else if ( checkVictory(gameBoard) == false ) {
				if ( checkDraw(gameBoard) == true ) {
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
					std::cout << "The game is drawn." << std::endl;
					auto playAgainTemp = playAgain();
					if ( playAgainTemp == true ) {
						std::cout << "Swapping turns..." << std::endl;
						delay(1);
						gameBoard = initBoard();
						ClearScreen();
						swapTurn(turn);
						displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
					} else if ( playAgainTemp == false ) {
						playLoop = false;	//when draw, no high score will be recorded
					}
				} else if ( checkDraw(gameBoard) == false ) {
					swapTurn(turn);
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn); // continue to player 2
				}
			}
		}

	}
}

