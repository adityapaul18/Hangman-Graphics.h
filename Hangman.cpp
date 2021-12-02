#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>
#include <windows.h>

using namespace std;
void startGame();
void playGame();
char* getWord(int);	

HANDLE H_Console = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoXY(int X, int Y) {
	COORD position;
	position.X = X;
	position.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
void clearScreen() {
	for (int i = 0; i < 24; i++) {
		gotoXY(3, 3 + i);
		for (int j = 0; j < 74; j++)
			cout << " ";
	}
}
void hangmanGame() {
	clearScreen();
	char header[7][75];
	
	strcpy(header[0], "                    COMPUTER GRAPHICS LAB PROJECT ");
	strcpy(header[1], "                                      - ADITYA PAUL");
	strcpy(header[2], "                                        UI19CO04 CSE SEM 5");
	strcpy(header[3], "                                        IIIT SURAT ");
	strcpy(header[4], "                          ANIMAL HANGMAN GAME ");
	for (int i = 0; i <= 3; i++) {
		SetConsoleTextAttribute(H_Console, 10);
		gotoXY(3, 5 + i);	puts(header[i]);
	}
	gotoXY(3, 9);	puts("");
	gotoXY(3, 10);	puts("");
	gotoXY(3, 11);	puts("");
	SetConsoleTextAttribute(H_Console, 9);
		gotoXY(3, 12);	puts(header[4]);
	SetConsoleTextAttribute(H_Console, 6);
	gotoXY(26, 16);	cout << "Press (1) for  Play game ";
	gotoXY(26, 18);	cout << "Press (2) for  Exit    ";
//	system("color f5");	
	while (true) {
		gotoXY(0, 29);	char ch = getch();
		if (ch == '1')
			startGame();
		else if (ch == '2')
			exit(0);
		else
			continue;
	}
}
void startGame()
{
	//Starting game
	while (true) {
		playGame();
		//Waiting for 'y' or 'n'
		int again = 0;
		while (true) {
			gotoXY(15, 22);	cout << "Play again (y/n) :: ";
			char ch = getche();
			if (ch == 'y' || ch == 'Y') {
				again = 1;
				break;
			}
			if (ch == 'n' || ch == 'N')
				break;
		}
		if (again == 1)	
			continue;
		else	
			break;
	}
	hangmanGame();
}
char* getWord(int index) {
	static char words[][8] = {"CAT","DOG","TIGER","LION","HYENA","BOAR","LEOPARD","GIRAFFE","ZEBRA","BUFFALO"};
	return words[index];
}
void hash(char *word, char *guess) {
	int i = 1;
	guess[0] = word[0];
	while (word[i] != '\0') {
		guess[i] = '*';
		i++;
	}
	guess[i] = '\0';
}

void hanging(int wrong) {
	static char hang[12][20];
	if (wrong == 0) {
		strcpy(hang[0], " _____________    ");
		strcpy(hang[1], " |           |    ");
		strcpy(hang[2], " |           |    ");
		strcpy(hang[3], "             |    ");
		strcpy(hang[4], "             |   ");
		strcpy(hang[5], "             |    ");
		strcpy(hang[6], "             |   ");
		strcpy(hang[7], "             |    ");
		strcpy(hang[8], "             |    ");
		strcpy(hang[9], "             |    ");
		strcpy(hang[10], "             |    ");
		strcpy(hang[11], "         ---------");
	}
	else if (wrong == 1)
		strcpy(hang[3], " O           |    ");
	else if (wrong == 2)
		strcpy(hang[4], " |           |   ");
	else if (wrong == 3)
		strcpy(hang[4], "/|           |   ");
	else if (wrong == 4)
		strcpy(hang[4], "/|\\          |   ");
	else if (wrong == 5)
		strcpy(hang[5], " |           |    ");
	else if (wrong == 6)
		strcpy(hang[6], "/            |   ");
	else
		strcpy(hang[6], "/ \\          |   ");
	for (int i = 0; i < 12; i++) {
		if (wrong == 7)
			SetConsoleTextAttribute(H_Console, 12);
		gotoXY(49, 11 + i);	puts(hang[i]);
	}
	if (wrong == 7)
		SetConsoleTextAttribute(H_Console, 9);
}
bool checkGuess(char *word, char *guess, char ch) {
	bool check = false;	int i = 0;
	ch = toupper(ch);
	while (word[i] != '\0') {
		if (word[i] == ch) {	
			guess[i] = word[i];
			check = true;
		}
		i++;
	}
	return check;
}
bool checkWord(char *word, char *guess) {
	int i = 0;
	while (word[i] != '\0') {
		if (word[i] != guess[i])	//If any character didn't matched
			return false;
		i++;
	}
	return true;
}
void playGame()
{
	SetConsoleTextAttribute(H_Console, 3);
	clearScreen();
	int index, lifes = 0, check = 0;
	index = rand() % 10;
	char guess[8], input, *word;
	//Getting and storing word
	word = getWord(index);
	hash(word, guess);
	while (true) {
		gotoXY(12, 4); cout << "WORD :: ";
		puts(guess);
		gotoXY(58, 4); cout << "LIFES :: " << (7 - lifes);
		hanging(lifes);
		if (lifes == 7)	
			break;
		if (checkWord(word, guess)) {
			check = 1;
			break;
		}
		gotoXY(12, 11);	cout << "Enter your guess :: ";
		input = getche();
		gotoXY(14, 14);
		if (checkGuess(word, guess, input))	//If guessed character is found
			cout << "You saved a life!";
		else {	
			cout << "You loose a life!";
			lifes++;
		}
	}
	SetConsoleTextAttribute(H_Console, 12);
	gotoXY(18, 20);
	if (check == 1)
		cout << "!YOU WIN!";
	else
		cout << "!YOU LOSE!";
	SetConsoleTextAttribute(H_Console, 9);
}
int main()
{	
	system("mode 80,30");
	hangmanGame();						
	return 0;
}
