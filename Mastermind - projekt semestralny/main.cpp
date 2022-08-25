#include "libFun.hpp"
#include "libClass.hpp"
#include <cstdio>
#include <time.h>
#include <cstdlib>
#include <iostream>

#pragma warning (disable: 4996)

using namespace std;

int main(int argc, char *argv[]) {
	Game* gameplay = new Game();
	allocationCheck<Game*>(gameplay);
	bool next;
	int m;
	srand((unsigned)time(NULL));
	gameInfo();
	do {
		cout << "\nChoose:\n" << endl;
		cout << "\t[1] - start a game" << endl;
		cout << "\t[2] - show history" << endl;
		cout << "\t[3] - quit" << endl;
		cout << "\n>>>\t";
		m = getThreeOptions<int>();
		switch (m) {
		case 1:
			cout.put('\n');
			break;
		case 2:
			cout.put('\n');
			showHisotry();
			break;
		case 3:
			return 0;
		}
	} while (m != 1);
	cout << "\nChoose:\n" << endl;
	cout << "\t[1] - load the game" << endl;
	cout << "\t[2] - new game" << endl;
	cout << "\n>>>\t";
	m = getTwoOptions<int>();
	switch (m) {
	case 1:
		cout.put('\n');
		loadGameplay(*gameplay);
		break;
	case 2:
		cout.put('\n');
		initializeGameplay(*gameplay);
		break;
	}
	delete gameplay;
	next = endMenu();
	while (next) {
		cout.put('\n');
		Game* gameplay = new Game();
		allocationCheck<Game*>(gameplay);
		initializeGameplay(*gameplay);
		next = endMenu();
		delete gameplay;
	}
	return 0;
}