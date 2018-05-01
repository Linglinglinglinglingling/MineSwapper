#include <iostream> /* enable users to interact with the game*/
#include <ctime> /* reset the time everytime we run this program to generate random map */
#include <string.h> /* reset items in two mapping arrays to 0('0') to make sure users have a new map whenever they start a new game */
#include <fstream> /* enable users to save and load their procress */
#include <string> /* string is used in this program */

#define WIDTH 10 /* fixed map width */
#define HIGHT 10 /* fixed map hight */

/* declear the arrays used in the whole program */
char map[WIDTH][HIGHT] = { '0' }; /* the game map*/
int record[WIDTH][HIGHT] = { 0 }; /* the covering map */
int directions[16] = { -1, -1, -1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1 }; /* all of the changes of the locations' coordinaters */

/* declear the functions used in the program */
int initMap(int BOMB_NUM); /* initialize the gaming map */
void display(); /* display the gaming board */
void displayAll(); /* display the gaming map */
int bombAround(int x, int y); /* count the number of bombs around one cell */
int isSuccess(int BOMB_NUM); /* check if the user is winning the game */
void userPlay(int bombNum, std::string loadornot); /* playing choices */
int archive(); /* a function enable users to save their games */
int loadarchive(); /* a function enable users to load their saving games */
int checking(std::string x); /* check if the inputs of users is valid */
int converting(std::string x); /* convert string into integer */


/* declear important variables */
int bombNum = 0; /* bombs' number */
int locX = 0; /* the row */
int locY = 0; /* the coloum */
std::string slocX = "0"; /* the row inputed by users */
std::string slocY = "0"; /* the coloum inputed by users*/
std::string savetowhere = "0"; /* the saving point choosed by users */
std::string loadornot = "0"; /* decide if to load saving game */
int flag; /* if the users' input in valid, then it's 1, or will always be 0 */
int whichinput = 0; /* different input has different if statement in function checking(), this is deciding which if statement it going to use */

/* this function converts string into integer */
int converting(std::string x) {
	int y;
	y = stoi(x);
	return y;
}

/* this function checks every input of users is valid or not
   if the input is valid, return 1 to flag
   if it's not, return 0 to flag */
int checking(std::string x) {
	/* because all the input's length is 1, if the input is bigger than 1, then it's invalid */
	if (x.size() > 1) {
		return 0;
	}
	/* this else statement is checking if the input is correct */
	else {
		/* check input with 'y' or 'n' */
		if (whichinput == 1) {
			if ((x == "y") || (x == "n")) {
				return 1;
			}
			return 0;
		}
		/* check input with '1', '2', '3', '4' */
		if (whichinput == 2) {
			if ((x == "1") || (x == "2") || (x == "3") || (x == "4")) {
				return 1;
			}
			return 0;
		}
		/* check input with '1', '2', '3' */
		if (whichinput == 3) {
			if ((x == "1") || (x == "2") || (x == "3")) {
				return 1;
			}
			return 0;
		}
		/* check input with 's', 'e', 'g', 'r', 'm' */
		if (whichinput == 4) {
			if ((x == "s") || (x == "e") || (x == "g") || (x == "r") || (x == "m")) {
				return 1;
			}
			return 0;
		}
		/* check if the input of locations is valid */
		if (whichinput = 5) {
			if ((x == "0") || (x == "1") || (x == "2") || (x == "3") || (x == "4") || (x == "5") || (x == "6") || (x == "7") || (x == "8") || (x == "9")) {
				return 1;
			}
			return 0;
		}
	}
}

/* the main function
   display the initial interface of this program
   provide users a loading choice for previous games
   provide users four default levels and a customize level */
int main() {
	/* these lines are displaying the initial interface of this program */
	std::cout << "==============================================|" << std::endl;
	std::cout << "           WELCOME TO MINESWAPPER!            |" << std::endl;
	std::cout << "* * * * * * * * * * *RULE* * * * * * * * * * *|" << std::endl;
	std::cout << "  To win this game, you need to mark all the  |" << std::endl;
	std::cout << "     cells in the map that contain bombs!     |" << std::endl;
	std::cout << "==============================================|" << std::endl;
	std::string choice = "0"; /* level choice */
	std::string loadChoice = "0"; /* loading choice */
	/* these two while loops provide users loading options(and new games)
	  and stop the program from closing unless users close it manually */
	while (true) {
		while (true) {
			std::cout << "Do you wanna load your archives?(y/n) ";
			getline(std::cin, loadChoice); /* in case of the users enter space between strings */
			whichinput = 1; /* let the function checking() know what input it's valid(which if statement is suitable to check this input) */
			flag = checking(loadChoice);
			/* the users can leave this loop only when their input is valid */
			while (flag == 0) {
				std::cout << "ERROR: invalid input" << std::endl;
				std::cout << "Do you wanna load your archives?(y/n) ";
				getline(std::cin, loadChoice);
				flag = checking(loadChoice);
			}
			if (loadChoice == "y") {
				loadarchive();
			}
			loadornot = "0"; 
			/* the lines below enable users to choose from defult levels or customize level */
			std::cout << "==============================================" << std::endl;
			std::cout << "*You can quit by clicking the 'x' icon on the top right anytime :)" << std::endl;
			std::cout << "*To choose defaut levels: Enter 1(Simple/10x10, 10 bombs)" << std::endl;
			std::cout << "                          Enter 2(Medium/10x10, 20 bombs)" << std::endl;
			std::cout << "                          Enter 3(Difficult/10x10, 30 bombs)" << std::endl;
			std::cout << "*To create your own difficulty level!:" << std::endl;
			std::cout << "                          Enter 4(Customize/10x10) " << std::endl;
			slocX = "0";
			slocY = "0";
			choice = "0";
			std::cout << "Your choice: ";
			getline(std::cin, choice); // *****ERROR***** //
			whichinput = 2;
			flag = checking(choice);
			/* checking if the input is valid */
			while (flag == 0) {
				std::cout << "ERROR: invalid input" << std::endl;
				std::cout << "Your choice: ";
				getline(std::cin, choice);
				flag = checking(choice);
 			}
			/* choosing different defult levels */
			if ((choice == "1") || (choice == "2") || (choice == "3")) {
				if (choice == "1") {
					userPlay(10, "0");
				}
				if (choice == "2") {
					userPlay(20, "0");
				}
				if (choice == "3") {
					userPlay(30, "0");
				}
			}
			/* customize the bombs' amount */
			if (choice == "4") {
				while (true) {
					int choice2; /* the customized bomb number */
					std::cout << "*How many bombs do you want to play with?(please only enter number 1 - 100 or you may crush the game) ";
					std::cin >> choice2;
					/* check if the bomb number is suitable */
					userPlay(choice2, "0");
					break;
				}
			}
		}
	}
	return 0;
}

/* this function enable users to play the game
  provide users fives choices(reveal, mark, save, give up and restart */
void userPlay(int bombNum, std::string loadornot) {
	/* this if statement stops the loading game map from being initialized */
	if (loadornot == "0") {
		initMap(bombNum);
	}
	/* this while loop enable users to leave the gaming process only when they require to */
	while (true) {
		display();
		std::string choicePlay = "0";
		int sumbombLeft = 0;
		/* this for loop counts the bomb number in the map and later to display it as a hint */
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (map[i][j] == 'B' && record[i][j] == 0) {
					sumbombLeft++;
				}
			}
		}
		std::cout << "**HINT! You have " << sumbombLeft << " bombs still to find" << std::endl;
		std::cout << "**What would you like to do?" << std::endl;
		std::cout << "(r)eveal, (m)ark, r(e)start, (s)ave, or (g)ive up? ";
		whichinput = 4;
		getline(std::cin, choicePlay);
		flag = checking(choicePlay);
		while (flag == 0) {
			std::cout << "ERROR: vaild input" << std::endl;
			std::cout << "(r)eveal, (m)ark, r(e)start, (s)ave, or (g)ive up? ";
			getline(std::cin, choicePlay);
			flag = checking(choicePlay);
		}
		/* save
		   enable users to save their game
		   THREE archives are offered */
		if (choicePlay == "s") {
			std::cout << "Choose an archive! (archive1(enter1), archive2(enter2), archive3(enter3) or back to game(4)) ";
			getline(std::cin, savetowhere);
			whichinput = 2;
			flag = checking(savetowhere);
			while (flag == 0) {
				std::cout << "ERROR: invalid input" << std::endl;
				std::cout << "Choose an archive! (archive1(enter1), archive2(enter2), archive3(enter3) or back to game(4)) ";
				getline(std::cin, savetowhere);
				flag = checking(savetowhere);
			}
			if (savetowhere == "1") {
				archive();
				continue;
			}
			if (savetowhere == "2") {
				archive();
				continue;
			}
			if (savetowhere == "3") {
				archive();
				continue;
			}
		}
		/* give up
		   show the game map to users when they don't want to play and are curious about the answers */
		if (choicePlay == "g") {
			std::cout << std::endl;
			displayAll();
			std::cout << "**You can click the 'x' icon on the top right to quit" << std::endl;
			std::string continuePlay;
			std::cout << "**Or enter 'c' to restart ";
			std::cin >> continuePlay;
			std::cout << "==============================================" << std::endl;
			break;
		}
		/* restart 
		   restart the whole game, users can choose to load archieves or start a new game */
		if (choicePlay == "e") {
			break;
		}
		/* reveal
		   that's how people play mineswapper */
		if (choicePlay == "r") {
			std::cout << "Which row? ";
			getline(std::cin, slocX);
			whichinput = 5;
			flag = checking(slocX);				
			while (flag == 0) {
				std::cout << "ERROR: invalid input" << std::endl;
				std::cout << "Which row? ";
				getline(std::cin, slocX);
				flag = checking(slocX);
			}
			std::cout << "Which column? ";
			getline(std::cin, slocY);
			whichinput = 5;
			flag = checking(slocY);
			while (flag == 0) {
				std::wcout << "ERROR: invalid input" << std::endl;
				std::cout << "Which column? ";
				getline(std::cin, slocY);
				flag = checking(slocY);
			}
			std::cout << std::endl;
			locX = converting(slocX);
			locY = converting(slocY);
			record[locX][locY] = 1;
			/* stop the game when users reveal a cell contains bomb */
			if (map[locX][locY] == 'B') {
				displayAll();
				std::cout << "BOOM! THIS IS A BOMB! YOU LOSE!" << std::endl;
				break;
			}
			if (map[locX][locY] != 'B') {
				continue;
			}
		}
		/* mark
		   this is also how people mineswapper, but they can only win the game by mrking all the bomb cells */
		if (choicePlay == "m") {
			std::cout << "Which row? ";
			getline(std::cin, slocX);
			whichinput = 5;
			flag = checking(slocX);
			while (flag == 0) {
				std::cout << "ERROR: invalid input" << std::endl;
				std::cout << "Which row? ";
				getline(std::cin, slocX);
				flag = checking(slocX);
			}
			std::cout << "Which column? ";
			getline(std::cin, slocY);
			whichinput = 5;
			flag = checking(slocY);
			while (flag == 0) {
				std::wcout << "ERROR: invalid input" << std::endl;
				std::cout << "Which column? ";
				getline(std::cin, slocY);
				flag = checking(slocY);
			}
			std::cout << std::endl;
			locX = converting(slocX);
			locY = converting(slocY);
			record[locX][locY] = 2;
			int flag = isSuccess(bombNum);
			if (flag == 1) {
				displayAll();
				std::cout << "CONGRATULATIONS! YOU WIN!" << std::endl;
				break;
			}
		}
	}
}

/* this function is used to generate random map in every new game */
int initMap(int BOMB_NUM) {
	memset(map, '0', sizeof(map));
	memset(record, 0, sizeof(record));
	int bombNum = BOMB_NUM;
	srand(time(NULL));
	/* this while loop randoms the index of bombs in the gaming map array */
	while (bombNum > 0) {
		int locX = rand() % (10);
		int locY = rand() % (10);
		/* don't do anything when a new random cell already has a bomb */
		if (map[locX][locY] == 'B') {
			continue;
		}
		else {
			bombNum--;
			map[locX][locY] = 'B';
		}
	}
	/* this for loop checks every sigle cell in the gaming map array
	  and counts the bomb number by using bombAround function */
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j] == 'B') {
				continue;
			}
			else {
				map[i][j] = '0' + bombAround(i, j);
			}
		}
	}
	return 0;
}

/* this function counts the number of bombs around every sigle empty cell */
int bombAround(int x, int y) {
	int sum = 0;
	int locX = x;
	int locY = y;
	for (int i = 0; i < 8; i++) {
		int directions[16] = { -1, -1, -1, 0, -1, 1, 0, 1, 1, 1, 1, 0, 1, -1, 0, -1 }; /* this array stores the changes of the loctions of all the eight cells around one cell */
		locX = x + directions[i * 2 + 0];
		locY = y + directions[i * 2 + 1];
		/* this if statement checks the cells with less than eight cells surrounding them and adds up the number of bombs for every sigle cell */
		if (locX >= 0 && locX < 10 && locY >= 0 && locY < 10) {
			if (map[locX][locY] == 'B') {
				sum++;
			}
		}
	}
	return sum;
}

/* this function displays the gaming board on the screen 
   most of the ouput is using to make the game board clean and in clear format */
void display() {
	std::cout << "   ";
	for (int i = 0; i < 10; i++) { /*coordinates for each coloum*/
		std::cout << "   " << i;
	}
	std::cout << std::endl;
	std::cout << "    ";
	for (int i = 0; i < 10; i++) {
		std::cout << " " << "---";
	}
	std::cout << std::endl;
	/* the gaming board is printing from here */
	for (int i = 0; i < 10; i++) { 
		std::cout << " " << i << "  "; /* coordinates for each row */
		for (int j = 0; j < 10; j++) {
			if (record[i][j] == 1) {
				std::cout << "|" << " " << map[i][j] << " ";
			}
			if (record[i][j] == 2) {
				std::cout << "|" << " " << "X" << " ";
			}
			if (record[i][j] == 0) {
				std::cout << "|" << " " << " " << " ";
			}
		}
		std::cout << "|";
		std::cout << std::endl;
		std::cout << "    ";
		for (int i = 0; i < 10; i++) {
			std::cout << " " << "---";
		}
		std::cout << std::endl;
	}
} 

/* this fuction is used to display the game map when users don't want to continue but want to know the answer
   it's nearly the same as display() fuction except it only output the game map array to let users see the game map */
void displayAll() {
	std::cout << "   ";
	for (int i = 0; i < 10; i++) {
		std::cout << "   " << i;
	}
	std::cout << std::endl;
	std::cout << "    ";
	for (int i = 0; i < 10; i++) {
		std::cout << " " << "---";
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << " " << i << "  ";
		for (int j = 0; j < 10; j++) {
			std::cout << "|" << " " << map[i][j] << " ";
		}
		std::cout << "|";
		std::cout << std::endl;
		std::cout << "    ";
		for (int i = 0; i < 10; i++) {
			std::cout << " " << "---";
		}
		std::cout << std::endl;
	}
}

/* this function is ran to check if the bombs are all marked
   (the users are assumed to play the game, not to mark every cells to win) */
int isSuccess(int BOMB_NUM) {
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j] == 'B' && record[i][j] == 2) {
				sum++;
			}
		}
	}
	if (sum == BOMB_NUM) {
		return 1;
	}
	return 0;
}

/* this is the saving function for archive1-3
   it write the game map and covering map users want to store into certain files */
int archive() {
	std::string archive;
	std::string archivetxtName1, archivetxtName2;
	/* these if statements is used to mention users which saving point they are useing in later code */
	if (savetowhere == "1") {
		archive = "archive1";
		archivetxtName1 = "archive1map.txt";
		archivetxtName2 = "archive1record.txt";
	}
	if (savetowhere == "2") {
		archive = "archive2";
		archivetxtName1 = "archive2map.txt";
		archivetxtName2 = "archive2record.txt";
	}
	if (savetowhere == "3") {
		archive = "archive3";
		archivetxtName1 = "archive3map.txt";
		archivetxtName2 = "archive3record.txt";
	}
	/* the lines below is to mention users they might accidently overwrite the old archieve they want to store */
	std::cout << "********************************!ATTENTION!********************************" << std::endl;
	std::cout << "Before you save, think carefully if you have ever saved in " << archive << " before" << std::endl;
	std::cout << "If you continue, your old archieve1 will be covered" << std::endl;
	std::cout << "Do you still wanna save your game in this saving point?(y/n) ";
	std::string choice = "0";
	getline(std::cin, choice);
	whichinput = 1;
	flag = checking(choice);
	while (flag == 0) {
		std::cout << "ERROR: invalid input" << std::endl;
		std::cout << "Do you still wanna save your game in this saving point?(y/n) ";
		getline(std::cin, choice);
		flag = checking(choice);
	}
	/* if users are sure that they want to store the current process, they will get into this if statement
	   and their process will be wrote into certain files */
	if (choice == "y") {
		/* this writes the current gaming map into file */
		std::ofstream archieveMap;
		archieveMap.open(archivetxtName1);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				archieveMap << map[i][j] << std::endl;
			}
		}
		archieveMap.close();
		/* this writes the current covering map into file */
		std::ofstream archieveRecord;
		archieveRecord.open(archivetxtName2);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				archieveRecord << record[i][j] << std::endl;
			}
		}
		archieveRecord.close();
		/* these lines below is to remind users that their game are stored successfully */
		std::cout << "------------------------------------------------" << std::endl;
		std::cout << "Progress has been saved SUCCESSFULLY in " << archive << " " << std::endl;
		std::cout << "------------------------------------------------" << std::endl;
		std::cout << "**You can click the 'x' icon on the top right to quit" << std::endl;
		return 1;
	}
	return 0;
}

/* this is the loading function for archive1-3
   it loads the game board stored in archive1-3 to the global and functions with other functions to let users contiune this stored game
   if there's no gaming process stored in archive1-3, the users are forced to start a new game */
int loadarchive() {
	/* line 420-440 offers users a choice to choose which archive to load */
	std::string archive;
	std::string fileName1, fileName2; /*flieName1 for gaming maps, fileName2 for covering maps */
	std::string loadwhichone = "0";
	std::cout << "Which archieve do you wanna load? (archive1(enter1), archive2(enter2), or archive3(enter3)) ";
	getline(std::cin, loadwhichone);
	whichinput = 3;
	flag = checking(loadwhichone);
	while (flag == 0) {
		std::cout << "ERROR: valid input" << std::endl;
		std::cout << "Which archieve do you wanna load? (archive1(enter1), archive2(enter2), or archive3(enter3)) ";
		getline(std::cin, loadwhichone);
		flag = checking(loadwhichone);
	}
	if (loadwhichone == "1") {
		archive = "archive1";
		fileName1 = "archive1map.txt";
		fileName2 = "archive1record.txt";
	}
	if (loadwhichone == "2") {
		archive = "archive2";
		fileName1 = "archive2map.txt";
		fileName2 = "archive2record.txt";
	}
	if (loadwhichone == "3") {
		archive = "archive3";
		fileName1 = "archive3map.txt";
		fileName2 = "archive3record.txt";
	}
	/* the lines of codes below are used to remind users there are no stored games in archive1-3 and send them to start a new game */
	std::ifstream fin(fileName1);
	if (!fin) {
		std::cout << "******************!ERROR!********************" << std::endl;
		std::cout << "        You don't have " << archive <<" yet!        " << std::endl;
		std::string goback = "0";
		std::cout << "        Enter 'c' to start new games!        ";
		getline(std::cin, goback);
		std::cout << "=============================================" << std::endl;
		loadornot = "0";
		return 0;
	}
	/* this else statement works when there is a stored game in archive1-3 */
	else {
		loadornot = '1'; /* this stops the maps from being initalized when users gets back to function userPlay() */
		/* the stored game is loaded to global to function with other functions */
		/* read the gaming map */
		std::ifstream readarchiveMap;
		readarchiveMap.open(fileName1);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				readarchiveMap >> map[i][j];
			}
		}
		readarchiveMap.close();
		/* read the covering map */
		std::ifstream readarchiveRecord;
		readarchiveRecord.open(fileName2);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				readarchiveRecord >> record[i][j];
			}
		}
		readarchiveRecord.close();
	}
	/* this for loop is used to count the bomb numbers in the loaded game map */
	int sumb = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j] == 'B') {
				sumb++;
			}
		}
	}
	/* users will continue their stored game from here */
	userPlay(sumb, loadornot);
}

/* this is the end of Ling's mineswapper game code, thank you for reading */