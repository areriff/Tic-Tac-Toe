#include "stdafx.h"
#include "multiPlayer.h"


//initialize paramaters that will be passed into the main game loop
void multiPlayer() {
	std::pair < unsigned int,std::string> result;
	std::string playerOne = initPlayer();
	std::string playerTwo = initPlayer();
	unsigned int playerOneScore = 0;
	unsigned int playerTwoScore = 0;
	gameLoop(result,playerOne,playerTwo,playerOneScore,playerTwoScore);
	internalHallOfFame(result);
}

//main game loop that get the parameter from multiplayer() above.
void gameLoop(std::pair < unsigned int, std::string> &result,
			  const std::string &playerOne, 
			  const std::string &playerTwo,
			  unsigned int &playerOneScore,
			  unsigned int &playerTwoScore) {
	bool play = true;
	auto gameBoard = initBoard();
	char turn = '1';
	while ( play ) {
		ClearScreen();
		displayBoard(gameBoard,playerOneScore,playerTwoScore,turn);
		if ( turn == '1' ) {
			pickSquare(gameBoard, '1', playerOne);	//user enter move and modify the current gameBoard.
			if ( checkVictory(gameBoard) == true ) {
				playerOneScore++;	
				ClearScreen();
				displayBoard(gameBoard, playerOneScore, playerTwoScore, turn); //display current gameBoard
				std::cout << playerOne << " wins!" << std::endl;
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
					result.second = playerOne;		//of current game to result (pair) for further processing (see
					play = false;						//multiplayer() function above).
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
						play = false;	//when draw, no high score will be recorded
					}
				} else if ( checkDraw(gameBoard) == false ) {
					swapTurn(turn);
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn); // continue to player 2
				}
			}
		}
		if ( turn == '2' ) {							//player 2 loop are exactly the same as player 1(except 
			pickSquare(gameBoard, '2', playerTwo);		//for the parameters that are being passed, which are
			if ( checkVictory(gameBoard) == true ) {	//unique for player 2 for identification purposes
				playerTwoScore++;
				ClearScreen();
				displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				std::cout << playerTwo << " wins!" << std::endl;
				auto playAgainTemp = playAgain();
				if (playAgainTemp == true ) {
					std::cout << "Swapping turns..." << std::endl;
					delay(1);
					gameBoard = initBoard();
					ClearScreen();
					swapTurn(turn);
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				} else if (playAgainTemp == false ) {
					result.first = playerTwoScore;
					result.second = playerTwo;
					play = false;
				}

			} else if ( checkVictory(gameBoard) == false ) {
				if ( checkDraw(gameBoard) == true ) {
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
					std::cout << "The game is drawn." << std::endl;
					auto playAgainTemp = playAgain();
					if (playAgainTemp == true ) {
						std::cout << "Swapping turns..." << std::endl;
						delay(1);
						gameBoard = initBoard();
						ClearScreen();
						swapTurn(turn);
						displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
					} else if (playAgainTemp == false ) {
						play = false;
					}
				} else if ( checkDraw(gameBoard) == false ) {
					swapTurn(turn);
					ClearScreen();
					displayBoard(gameBoard, playerOneScore, playerTwoScore, turn);
				}
			}
		}
	}
}