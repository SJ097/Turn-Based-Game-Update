/*This header file includes all constants, function prototypes and structure declarations
  used by the main function in the source file.*/

//Opponent's stats in demonstration
const int OPP_ATK = 5,
          OPP_DEF = 4,
		  OPP_MAG = 1,
		  OPP_SPD = 5,
          OPP_HP = 20;

//Function prototypes
void tryAgain(int * hero);
void statBoost(int * stat, char boost[10], char name[20]);
void damage(int * dmg, int stat, int adv_def, int * health, char mover[20]);
void Restore(int * hp, int * remaining, char eat[20]);

//Structure declaration
struct Character {
	//Character's statistical (stat) attributes
	int atk;
	int def;
	int mag;
	int spd;
	int hp;
	int ebar;
	//Character array set to 50 positions to avoid strings longer than 20 characters to use other variable's memory
	char name[50];
};

/*Function used if hero selected does not exist
Takes in hero integer's variable as a pointer for modification*/
void tryAgain(int * hero) {

	printf("\nOption not given. Please try again: ");
	scanf("%d", hero);
}

/*Stat boost calculation
Takes in stat boosted and user's name, as well as the modified stat as a pointer*/
void statBoost(int * stat, char boost[10], char name[20]) {
	*stat *= 2;
	//If stat wasn't 0, it was increased and outputs appropriate message
	if (*stat != 0)
		printf("\n%s's %s increased!\n", name, boost);
	//Otherwise, outputs opposite
	else printf("\n%s's %s could not be increased!\n", name, boost);
}

/*Calculates and prints damage dealt
Takes in stat used to attack, opponent's defense and the attacker's name
Also takes in modifiable damage and health variables as pointers*/
void damage(int * dmg, int stat, int adv_def, int * health, char mover[20]) {
	*dmg = (stat + rand() % 6) / adv_def + 1;
	*health -= *dmg;
	printf("\n%s dealt %d damage!\n", mover, *dmg);
}

/*Function restores 10 HP to either player or opponent, printing approrpiate message and remaining energy bars
Takes in consumer's name, as well as their HP and remaining energy bars as modifiable pointers*/
void Restore(int * hp, int * remaining, char eat[20]) {
	*hp += 10;
	*remaining -= 1;
	printf("\n%s ate an energy bar and restored 10 HP!\n%s has %d energy bars left!\n", eat, eat, *remaining);
}
