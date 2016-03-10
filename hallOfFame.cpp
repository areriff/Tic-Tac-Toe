#include "stdafx.h"
#include "hallOfFame.h"

//global hall of fame
static std::map<std::string, unsigned int> masterHall;
static std::set<std::pair<unsigned int,std::string>> masterHallSet;

//function use by user - pick from main menu
void hallOfFame() {
	using std::cout;
	using std::endl;
	ClearScreen();
	cout << "Hall of Fame" << endl;
	//read from the end of the set (largest at the bottom)
	for ( auto a = masterHallSet.rbegin(); a != masterHallSet.rend(); a++ ) {
		cout << a->first << "\t" << a->second << endl;
	}
	cout << "End of the hall" << endl;
	delay(2);
}

//function use internally by game loop to enter score into hall of fame
void internalHallOfFame(std::pair <unsigned int, std::string> &winner) {
	masterHallSet.insert(winner);
}