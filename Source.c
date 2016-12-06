/*Game Battle System Trial Update. Created by Sathya Jayakumar.
  This program would be implemented as several functions in a fully-fledged game.
  The updated program has a header file (Header.h) containing important declarations.*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include "Header.h"

int main(void) {
	//Different integer variables used in battle system
	int hero;
	int command;
	int value;
	int dmg = 0;
	int index = 0;

	// Type of hero selected in demo
	char type[7];

	//Structures for player and trial opponent
	struct Character user;
	struct Character enemy = {OPP_ATK,OPP_DEF,OPP_MAG,OPP_SPD,OPP_HP,1,"The Evil Overlord"};

	//Time-based randomizer used in certain calculations
	time_t t;
	srand((unsigned)time(&t));

	//Program introduction
	printf("TURN-BASED GAME: Battle System Trial\nProgrammed by Sathya Jayakumar, UBC Engineering Student\n\n");
	system("PAUSE");

	// Prompt to enter name
	printf("\nChoose a name! (Maximum 20 characters)\n\n");
	scanf("%s", &user.name);

	// If/While name too long, enter one of appropriate length
	while (strlen(user.name) > 20) {
		printf("\nName too long. Please enter one that is 20 characters at most: ");
		scanf("%s", &user.name);
	}

	//Selecting between 3 distinct types of heroes
	printf("\nSelect a hero class!\n\n	1. Knight\n	2. Mage\n	3. Thief\n\n");
	scanf("%d", &hero);

	//User prompted to enter valid integer if they entered an invalid one
	while (!(hero <= 3 && hero >= 1))
		tryAgain(&hero);

	//Declaring different hero classes' stat attributes
	if (hero == 1) {
		user.atk = 7;
		user.def = 6;
		user.mag = 0;
		user.spd = 2;
		strcpy(type, "Knight");
	}
	else if (hero == 2) {
		user.atk = 1;
		user.def = 3;
		user.mag = 7;
		user.spd = 4;
		strcpy(type, "Mage");
	}
	else if (hero == 3) {
		user.atk = 4;
		user.def = 3;
		user.mag = 2;
		user.spd = 6;
		strcpy(type, "Thief");
	}

	// Initializing HP and Energy Bars in user's struct and displaying name + hero type
	user.hp = 20;
	user.ebar = 1;
	printf("\n%s is a %s!\n\n", user.name, type);

	system("PAUSE");

	//Challenge from opponent
	printf("\n%s challenges %s!\n", enemy.name, user.name);

	//Battle system loop
	while (user.hp > 0 && enemy.hp > 0) {
		//Index counting # of turns
		index++;

		//Main menu; Indicates remaining HP and energy bars (to restore HP), as well as different commands possible
		printf("\nHP remaining: %d\nEnergy bars remaining: %d\nWhat will you do?\n\n	1. Attack\n	2. Magic\n	3. Flex\n	4. Focus\n	5. Defend\n	6. Energy bar\n	7. Run\n\n", user.hp, user.ebar);
		scanf("%d", &command);

		//If no energy bars remain and its command is selected, loop will force user to select another command
		while (command == 6 && user.ebar == 0) {
			printf("\nYou have no more energy bars! Do something else! ");
			scanf("%d", &command);
		}

		//If user's speed is greater than opponent's, former will make move first
		if (user.spd > enemy.spd) {

			//Damage calculator if physical attack command is selected
	USER:	if (command == 1)
				damage(&dmg, user.atk, enemy.def, &enemy.hp, user.name);

			//Damage calculator if magic attack command is selected
			else if (command == 2)
				damage(&dmg, user.mag, enemy.def, &enemy.hp, user.name);

			//Attack calculator if player chose to flex
			else if (command == 3)
				statBoost(&user.atk, "attack", user.name);

			//Magic calculator if player chose to focus
			else if (command == 4)
				statBoost(&user.mag, "magic", user.name);

			//Defense calculator if player chose to defend
			else if (command == 5)
				statBoost(&user.def, "defense", user.name);

			//Health restore calculator
			else if (command == 6)
				Restore(&user.hp, &user.ebar, user.name);

			//Can't escape message if player tries to run
			else if (command == 7)
				printf("\n%s can't escape!\n", user.name);

			//Turn wasted message if player chooses otherwise
			else printf("\nYou wasted your turn! Don't do that!\n");

			//If user's speed is lower, return to appropriate position in code
			if (user.spd < enemy.spd)
				goto BACK;
		}

		/*If opponent's HP goes to or below 0 immediately after player's move, will break out of current "if" loop
		  and encompassing "while" loop, and the player wins*/
		if (enemy.hp <= 0)
			break;

		//Randomizer to determine if opponent will restore HP or attack
		value = rand() % 10;

		//If randomizer returns certain value and energy bar counter is above 0, opponent can restore HP
		if (value > 7 && enemy.ebar != 0) 
			Restore(&enemy.hp,&enemy.ebar,enemy.name);

		//Otherwise opponent will attack player...
		else if (value > 3)
			damage(&dmg, enemy.atk, user.def, &user.hp, enemy.name);

		//...possibly with magic
		else damage(&dmg, enemy.mag, user.def, &user.hp, enemy.name);

		//Same as previous break loop except in terms of user's HP
		if (user.hp <= 0)
			break;

		//If opponent made move first...
		if (user.spd < enemy.spd) {
			//Go to user's move code for execution and return from there afterwards
			goto USER;
			BACK:;
		}
	}

	//Win statement if player wins
	if (enemy.hp <= 0)
		printf("\n\n%s won!\nThe game was %d turns long.\n\n", user.name, index);

	//Lose statement if opponent wins
	else if (user.hp <= 0)
		printf("\n\n%s lost... :(\nThe game was %d turns long.\n\n", user.name, index);

	system("PAUSE");

	//Thank you statement
	printf("\n\nThank you for playing! See you in the final version!\n\n");

	//End game
	system("PAUSE");
	return 0;
}