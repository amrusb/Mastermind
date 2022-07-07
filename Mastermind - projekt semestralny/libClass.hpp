#include <cstdio>
#ifndef libClass_hpp
#define libClass_hpp

//nazwa pliku sluzacego do zapsisu gry
#define SAVE_NAME "mastermind-save.txt"
//nazwa pliku zawierajacego historie
#define HISTORY_NAME "mastermind-history.txt"
//nazwa sluzaca do oznaczenia komputera
#define PC "Komputer"
//dlugosc kodu
#define CODE_L 4
//ilosc rozgrywanych rund
#define ROUNDS 4
//maksymalna ilosc odganiec podczas jednej rund
#define MOVES 10
//typ kolorow
enum availableColors { red = 'R', green = 'G', blue = 'B', orange = 'O', purple = 'P', yellow = 'Y' };

class Player;
class Game;
///////////////////////////
//		class Move		 //
///////////////////////////
/*Klasa przechowuje zapis jednego ruchu, wykonywanego przez gracza w danej rundzie*/
class Move {
	friend class Round;
	char guess[CODE_L];			//proba odganiecia
	unsigned int correctPlace;	//ilosc kolorow ustawiona w odpowiednim miejscu
	unsigned int correctColour;	//ilosc poprawnych kolorow na nieodpowiednim miejscu
public:
	Move* next;					//wskaznik do obiektu klasy Move
	Move();
	Move(char*, unsigned int, unsigned int);
	Move(Move&);
	~Move();
	void setGuess(char*);
	char* getGuess(void);
	void setCorrectPlace(unsigned int);
	unsigned int getCorrectPlace(void);
	void setCorrectColour(unsigned int);
	unsigned int getCorrectColour(void);
	void checkCorrectPlace(char*);
	void checkCorrectColour(char*);
};
///////////////////////////
//		class Round		 //
///////////////////////////
/*Klasa przechowuje zapis jednej rundy  rozgrywki, skladajacej sie z kolejnych ruchow*/
class Round {
	char code[CODE_L];				//tablica zawierajaca ustalony przez gracza kod
	unsigned int moveCounter;		//ilosc wykonanych ruchow w aktualnej rundzie
public:	
	bool win;						//zmienna przechowujaca informacje o wygranej rozgrywce
	Round* next;					//wskaznik do obiektu klasy Round
	Move* firstMove;				//wskaznik do obiektu klasy Move oznaczajacego pierwszy ruch
	Move* pointMove;				//wskaznik do obiektu klasy Move oznaczajacego kolejne ruchy
	Round();
	Round(char*, unsigned int);
	Round(Round&);
	~Round();
	void setCode(char*);
	char* getCode(void);
	void setMove(unsigned int);
	unsigned int getMove(void);
	void nextMove(Player*);
};
//////////////////////////////
//		class Player		//
//////////////////////////////
/*Klasa przechowuje informacje o jednym graczu*/
class Player {
	char nick[40];			//tablica zawierajaca nick gracza
	unsigned int points;	//ilosc punktow zromadzona przez gracza
	int isComputer;			//przechowuje informacje czy jest komputerem
public:
	Player();
	Player(const char*, unsigned int, int);
	Player(Player&);
	void setNick(char*);
	char* getNick(void);
	void setPoints(unsigned int);
	unsigned int getPoints(void);
	void guessCode(char*);
	void setIsComputer(int);
	int getIsComputer(void);
	virtual void setCode(char*);
	virtual void nextRound(Game*, Player*);
	const Player& operator++(void);	
};
//////////////////////////////
//		class Computer		//
//////////////////////////////
/*Klasa stosowana podczas rozgrywki gracz kontra komputer, oznaczajaca komputer*/
class Computer : public Player {
public:
	Computer();
	Computer(char*, unsigned int, int);
	Computer(Player&);
	void setCode(char*);
	void nextRound(Game* g, Player*);
};
//////////////////////////
//		class Game		//
//////////////////////////
/*Klasa przechowywuje zapis gry, skladajacej sie z rund*/
class Game {
	unsigned int roundCounter;		//ilosc rozegranych rund
public:
	Round* firstRound;				//wskaznik do obiektu klasy Round oznaczajacego pierwsza runde
	Round* pointRound;				//wskaznik do obiektu klasy Round oznaczajacego kolejne rundy
	Player* playerOne;				//wskazik do obiektu klasy Player oznaczajacego gracza pierwszego
	Player* playerTwo;				//wskazik do obiektu klasy Player oznaczajacego gracza drugiego
	Game();
	Game(unsigned int, Player*, Player*, Round*);
	Game(const Game&);
	~Game();
	void setRoundCounter(unsigned int);
	unsigned int getRoundCounter(void);
	int gameMode(void);
	void gameStartPVP(void);
	void gameStartPVC(void);
	void gameEndPvP(void);
	void gameEndPvC(void);
	void game2file(void);
	const Game& operator=(const Game&);
};
//Szablon klasy sluzaca do utworzenia listy dynamicznej, zawierajacej historie rozgrywki
template <typename type, int size>
class gameHistory: public Game {
public:
	type date[size];			//tablica sluzaca do przechowywania daty
	type time[size];			//tablica sluzaca do przechowywania godziny
	gameHistory<type, size>* next;		//wskazik do nastepnego obiektu klasy gameHistory
	~gameHistory();
	gameHistory();
	gameHistory(char* ,char*, unsigned int, Player*, Player*, Round*);
	gameHistory(gameHistory&);
};
template <typename type, int size>
gameHistory<type, size>::gameHistory() : Game() {
	next = NULL;
	date[0] = { '\0' };
	time[0] = { '\0' };
}
/*Konsturtor argumentowy, przekazujacy wartosci z przekazanych argumentow do pol nowego obiektu*/
template <typename type, int size>
gameHistory<type, size>::gameHistory(char* d, char* t, unsigned int c, Player* p1, Player* p2, Round* r) : Game(c, p1, p2, r) {
	strcpy(date, d);
	strcpy(time, t);
	next = NULL;
}
/*Konsturtor kopiujacy, przekazujacy wartosci z pol z obiektu gh do pol nowego obiektu*/
template <typename type, int size>
gameHistory<type, size>::gameHistory(gameHistory& gh) : Game(gh.getRoundCounter(), gh.playerOne, gh.playerTwo, gh.firstRound) {
	strcpy(date, gh.date);
	strcpy(time, gh.time);
	next = NULL;
}
/*Destruktor usuwajacy obiekty dynamiczne*/
template <typename type, int size>
gameHistory<type, size>::~gameHistory() {
	delete next;
}
#endif // !libClass_hpp
