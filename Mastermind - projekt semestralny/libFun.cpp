#include "libFun.hpp"
#include "libClass.hpp"
#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstdlib>

#pragma warning (disable: 4996)
#pragma warning (disable: 6031)
using namespace std;

//Funkcja czysci okno konsoli
void clearScreen(void) {
	//cout << "\x1B[2J\x1B[H";
	cout << endl;
}
//Funkcja wypisuje informacje dotyczaca gry
void gameInfo(void) {
	cout << "\t=========================================" << endl;
	cout << "\t|		MASTERMIND		|" << endl;
	cout << "\t=========================================\n" << endl;
	cout << "Witaj w grze 'Mastermind'." << endl;
	cout << "Celem gry jest odganiecie 4-kolorowego kodu, ulozonego przez drugiego gracza, maksymalnie w " << MOVES <<" ruchach." << endl;
	cout << "Za kazdy bledna probe odganiecia gracz dostaje 1 punkt."<< endl;
	cout << "Kazda gra sklada sie z " << ROUNDS << " rund." << endl;
	cout << "Wygrywa gracz z najmniejsza iloscia punktow." << endl;
	cout << "\nAby ustalic kod gracz zostanie poproszony o wpisanie ciagu 4 znakow, reprezentujacych kolory:" << endl;
	cout << "\t[R] - czerwony\n" << "\t[G] - zielony\n" << "\t[B] - niebieski\n" << "\t[O] - pomaranczowy\n" << "\t[P] - fioletowy\n" << "\t[Y] - zolty" << endl;
	cout << "UWAGA: Kolory moga sie powtarzac!" << endl;
	cout << "np.: RRBO oznacza kod czerwony, czerwony, niebieski, pomaranczowy" << endl;
	cout << "Rowniez w celu odganiecia kodu gracz zostanie poproszony o wpisanie ciagu 4 znakow." << endl;
	cout << "Po probie odganiecia, komputer dokona sprawdzenia i poda dwie cyfry:\n" << "Pierwsza oznacza ilosc odpowienich kolorow ustawionych na odpowiednim miejscu\n" << "Druga oznacza ilosc odpowienich kolorow ustawionych na niedopowiednich miejscach." << endl;
	cout << "np.: dla ustalonego kodu RRBO i odgadnietego ROPR zostanie wyswietlone [1][2] " << endl;
	cout << "\nDostepne sa dwa tryby rozgrywki:" << endl;
	cout << "\t1. GRACZ vs. GRACZ:\t";
	cout << "W rozgrywce bierze udzial dwoch graczy, ktorzy naprzemian ustalaja i probuja odgadnac kod." << endl;
	cout << "\t2. GRACZ vs. KOMPUTER:\t";
	cout << "W rozgrywce bierze udzial jeden gracz, ktory probuje odgadnac kod.\n" << endl;
	cout << "Po kazdej rundzie jest mozliwosc przerwania i zapisania gry.\n" << endl;
}
/*Funkcja zczytuje zapisany postep gry z pliku tekstowego do nowego obiektu klasy Game i zwraca ten obiekt, jezeli operacja odczytu sie powiedzie.
* W przeciwnym razie inicjalizuje nowy obiekt i rozpoczyna rozgrywke.*/
const Game loadSave(void) {
	FILE* stream;
	Game *gameplay = new Game();
	if ((stream = fopen(SAVE_NAME, "r")) == NULL) {
		cout << "\nBrak zapisanej gry.\n" << endl;
		cout << "Rozpocznij nowa gre:" << endl;
		initializeGameplay(*gameplay);
	}
	else {
		char nick[40] = { '\0' };
		unsigned int p, r;
		int i;
		fscanf(stream, "%s\t%d\t%d\n", nick, &p, &i);//zczytanie nicku i punktow 1. gracza
		if (!i)
			gameplay->playerOne = new Player(nick, p, i);
		else
			gameplay->playerOne = new Computer(nick, p, i);
		fscanf(stream, "%s\t%d\t%d\n", nick, &p, &i);//zczytanie nicku i punktow 2. gracza
		if (!i)
			gameplay->playerTwo = new Player(nick, p, i);
		else
			gameplay->playerTwo = new Computer(nick, p, i);
		fscanf(stream, "%d\n", &r);//zczytanie ilosci rozgranych rund
		gameplay->setRoundCounter(r);
		fclose(stream);
	}
	return *gameplay;
}
/*Funkcja wczytuje i kontynuuje zapisana wczesniej rozgrywke*/
void loadGameplay(Game&gameplay) {
	gameplay = loadSave();
	if (gameplay.getRoundCounter() == 0) {
		initializeGameplay(gameplay);
	}
	else if (gameplay.getRoundCounter() == 4)
		;
	else {
		cout << "Rozgrywka zostala wczytana." << endl;
		if (strcmp(gameplay.playerTwo->getNick(), PC)) {
			gameplay.gameStartPVP();
			gameplay.gameEndPvP();
		}
		else {
			gameplay.gameStartPVC();
			gameplay.gameEndPvC();
		}
	}
}
/*Funkcja rozpoczyna nowa rozgrywke*/
void initializeGameplay(Game& gameplay) {
	gameType temp;
	temp = gameplay.gameMode();
	switch (temp) {
	case PvP:
		gameplay.gameStartPVP();
		gameplay.gameEndPvP();
		break;
	case PvC:
		gameplay.gameStartPVC();
		gameplay.gameEndPvC();
		break;
	}
}
/*Funkcja wyswietla menu konca rozgrywki. Uzytkownik moze rozpoczac nowa gre, wyjsc z gry i wyswietlic historie rozgrywki.
* Funkcja zwraca wartosc true albo false*/
bool endMenu(void) {
	bool t;
	cout << "\nWybierz:" << endl;
	cout << "\t[1] - Nowa gra." << endl;
	cout << "\t[2] - Wyjdz z gry" << endl;
	cout << "\t[3] - Pokaz historie" << endl;
	cout << "\n>>>\t";
	int m = getThreeOptions<int>();
	switch (m) {
	case 1:
		t = true;
		break;
	case 2:
		t = false;
		break;
	case 3:
		showHisotry();
		endMenu();
		break;
	}
	return t;
}
/*Funkcja sprawdza aktualna date i zwraca cnapis w formacie DD.MM.RRRR*/
char* checkDate(void) {
	char buffer[80] = { '\0' };
	time_t rawdate;
	struct tm* newdate;
	time(&rawdate); //sprawdza aktualny czas
	newdate = localtime(&rawdate); //konwertuje na czas lokalny
	strftime(buffer, 80, "%d.%m.%Y", newdate);
	return buffer;
}
/*Funkcja sprawdza aktualna godzine i zwraca cnapis w formacie GG:MM*/
char* checkTime(void) {
	char buffer[80] = { '\0'};
	time_t rawtime;
	struct tm* newtime;
	time(&rawtime); //sprawdza aktualny czas
	newtime = localtime(&rawtime); //konwertuje na czas lokalny
	strftime(buffer, 80, "%H:%M", newtime);
	return buffer;
}
/*Funkcja zapisuje do pliku historie rozgrywek w kolejnosci od najnowszej do najstarszej*/
void saveHistory(Game& g) {
	gameHistory* head = NULL, * pointer = NULL;
	unsigned int p1, p2;
	char nick1[40] = { '\0' }, nick2[40] = { '\0' }, date[80] = { '\0' }, time[80] = { '\0' };
	strcpy(time, checkTime());
	strcpy(date, checkDate());
	FILE* stream;
	if ((stream = fopen(HISTORY_NAME, "r")) == NULL) {
		stream = fopen(HISTORY_NAME, "w");
		allocationCheck<FILE*>(stream);
		fprintf(stream, "%s\t%s\t%s\t%d\t%s\t%d\n", date, time, g.playerOne->getNick(), g.playerOne->getPoints(), g.playerTwo->getNick(), g.playerTwo->getPoints());
		fclose(stream);

	}
	else {
		//zczytanie dotyczasowego pliku
		head = pointer = new gameHistory;
		allocationCheck<gameHistory*>(head);
		fscanf(stream, "%s %s %s %d %s %d", pointer->date,pointer->time, nick1, &p1, nick2, &p2);
		pointer->playerOne = new Player(nick1, p1, 0);
		pointer->playerTwo = new Player(nick2, p2, 0);
;		pointer->next = NULL;
		while (!feof(stream)) {
			pointer->next = new gameHistory;
			pointer = pointer->next;
			pointer->next = NULL;
			fscanf(stream, "%s %s %s %d %s %d ", pointer->date, pointer->time, nick1, &p1, nick2, &p2);
			pointer->playerOne = new Player(nick1, p1, 0);
			pointer->playerTwo = new Player(nick2, p2, 0);
		}
		fclose(stream);
		stream = fopen(HISTORY_NAME, "w");
		allocationCheck<FILE*>(stream);
		pointer = head;
		fprintf(stream, "%s\t%s\t%s\t%d\t%s\t%d", date, time, g.playerOne->getNick(), g.playerOne->getPoints(), g.playerTwo->getNick(), g.playerTwo->getPoints());
		while (pointer != NULL) {
			fprintf(stream, "\n");
			fprintf(stream, "%s\t%s\t%s\t%d\t%s\t%d", pointer->date, pointer->time, pointer->playerOne->getNick(), pointer->playerOne->getPoints(), pointer->playerTwo->getNick(), pointer->playerTwo->getPoints());
			pointer = pointer->next;
		}
		fclose(stream);
	}
	delete head;
}
/*Funkcja zczytuje z pliku historie rozgrywek i wyswietla ja w konsoli
* W przypadku nieodnalezienia pliku z zapisem wyswietla stosowna informacje*/
void showHisotry(void) {
	FILE* stream;
	if ((stream = fopen(HISTORY_NAME, "r")) == NULL) {
		cout << "\nBrak historii rozgrywek" << endl;
	}
	else {
		int i = 1;
		unsigned int p1, p2;
		char nick1[40] = { '\0' }, nick2[40] = { '\0' }, date[80] = { '\0' }, time[80] = { '\0' };
		cout.put('\n');
		do{
			fscanf(stream, "%s %s %s %d %s %d", date, time, nick1, &p1, nick2, &p2);
			if (strcmp(nick2, PC)) {
				cout << i++ << ". " << date << "r. godz. " << time << endl;
				cout << nick1 << " - " << p1 << " pkt. VS. " << nick2 << " - " << p2 << " pkt." << endl;
				cout << "Zwyciezca tury: " << (p1 == p2 ? "REMIS" : (p1 < p2 ? nick1 : nick2)) << "\n" << endl;
			}
			else {
				cout << i++ << ". " << date << "r. godz. " << time << endl;
				cout << nick1 << " - " << p1 << " pkt.\n" << endl;
			}
		} while (!feof(stream));
		fclose(stream);
	}
}