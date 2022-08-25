# Mastermind
![Mastermind](https://user-images.githubusercontent.com/90143413/186666518-438ce27d-6dce-42a1-bb0e-3f6d68bf74d4.png)

A simple logical console game, written in C++.
The purpose of writing this console game was to show my skills of objective programming in `c++` language. Thanks to this I could attempt to an end-of-term exam at my University.
## Source code files
- `main.cpp` - this file contains the main code of the game
- `libFun.cpp` - this file contains source code of all funcions used in main
- `libFun.hpp`  - this header file contains declarations of the funcions, that are definied in `libFun.cpp`
- `libClass.cpp`  - this cpp file contains source code of all classes used to run a game
- `libClass.hpp`  - this header file contanis declarations of the classes, that are defined in `libClass.cpp`
## Other files used by the program
- `mastermind-save.txt` - this text file is generated by the program to save current gameplay. Thanks to that user of the program can decide if he or she want to continue this gameplay or start a new one.
- `mastermind-history` - this text file is generated by the program to save hisotry of each ended gameplay. It contains date and time of each gameplay, nick-names and amount of points gained by the players. Thanks to this file program can show a history of previous gameplayes.
## Purpose of the program
Program has to run a *Mastermind* game in two diffrent gamemodes:
1. **PLAYER vs PLAYER** - two players are competing whith each other
2. **PLAYER vs COMPUTER** - player is trying to guess the code, that was randomly generated by the Computer.

This game is about guessing the code, that has been made up by another player. The winner is a player, who has the least amout of points. Each point is gained for wrong attempt of guessing the code.
