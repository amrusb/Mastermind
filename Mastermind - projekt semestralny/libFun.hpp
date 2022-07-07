#include <cstdio>
#include <iostream>
#include "libClass.hpp"

#ifndef libFun_hpp
#define libFun_hpp

//Funkcja wypisuje informacje dotyczaca poczatku gry
void gameInfo(void);
/*Szablon funkcji, sprawdzajacej alokacje zmiennej dynamicznej*/
template <typename type>
void allocationCheck(const type pointer) {
	if (pointer == NULL) {
		std::cout << "\nBlad alokacji obiektu lub otwarcia pliku.\n" << std::endl;
		exit(1);
	}
}
/*Szablon funkcji, pobierajacej od uzytkownika dwie wartosci 1, 2*/
template <typename type>
type getTwoOptions(void) {
	type m;
	while (scanf("%d", &m) != 1 || m < 1 || m > 2 || getchar() != '\n') {
		std::cout << "Podano bledne dane. Popraw: " << std::endl;
		std::cout << "\n>>>\t";
		while (getchar() != '\n')
			;
	}
	return m;
}
/*Szablon funkcji, pobierajacej od uzytkownika trzy wartosci 1, 2, 3*/
template <typename type>
type getThreeOptions(void) {
	type m;
	while (scanf("%d", &m) != 1 || m < 1 || m > 3 || getchar() != '\n') {
		std::cout << "Podano bledne dane. Popraw: " << std::endl;
		std::cout << "\n>>>\t";
		while (getchar() != '\n')
			;
	}
	return m;
}
/*Funkcja zczytuje zapisany postep gry z pliku tekstowego do nowego obiektu klasy Game i zwraca ten obiekt, jezeli operacja odczytu sie powiedzie.
* W przeciwnym razie inicjalizuje nowy obiekt i rozpoczyna rozgrywke.*/
const Game loadSave(void);
/*Funkcja wczytuje i kontynuuje zapisana wczesniej rozgrywke*/
void loadGameplay(Game&);
/*Funkcja rozpoczyna nowa rozgrywke*/
void initializeGameplay(Game&);
/*Funkcja wyswietla menu konca rozgrywki. Uzytkownik moze rozpoczac nowa gre, wyjsc z gry i wyswietlic historie rozgrywki.
* Funkcja zwraca wartosc true albo false*/
bool endMenu(void);
/*Funkcja sprawdza aktualna godzine i zwraca cnapis w formacie GG:MM*/
char* checkTime(void);
/*Funkcja sprawdza aktualna date i zwraca cnapis w formacie DD.MM.RRRR*/
char* checkDate(void);
/*Funkcja zapisuje do pliku historie rozgrywek w kolejnosci od najnowszej do najstarszej*/
void saveHistory(Game&);
/*Funkcja zczytuje z pliku historie rozgrywek i wyswietla ja w konsoli
* W przypadku nieodnalezienia pliku z zapisem wyswietla stosowna informacje*/
void showHisotry(void);
#endif // !libFun_hpp
