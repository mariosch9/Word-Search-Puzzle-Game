/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

/* Function Prototypes */
char **create2DArray(); //creates a 2D array of characters, returns pointer to array
void printArray(char** array); //prints out a 2D array on screen
void insertHorizontally(char* word, char** array);
void insertVertically(char* word, char** array);
void insertDiagonally(char* word, char** array);

/* Declarations */
char **myArray; //Global Array of the 2D Array
#define WIDTH 17
#define HEIGHT 17
char nameOfPlayer[15]; //This is the name of the player
int foundWordsArray[7] = {0};


/* 7 words for each game selection */
char *animals[7] = {"TIGER","BUTTERFLY","CHICKEN","KANGAROO","WHALE","ELEPHANT","CROCODILE"};
char *fruits[7] = {"WATERMELON","ORANGE","PINEAPPLE","CHERRY","BANANA","PEACH","BLUEBERRY"};
char *countries[7] = {"CANADA","THAILAND","NIGERIA","GERMANY","ROMANIA","AUSTRALIA","SWEEDEN"};
char *movies[7] = {"COMEDY","HORROR","FANTASY","THRILLER","HISTORY","DRAMATIC","ANIMATION"};
char *clothes[7] = {"SHORTS","JACKET","TRAINERS","UNDERWEAR","SANDALS","TROUSER","SWIMSUIT"};


/* MAIN METHOD */
wordSearchGame(){
	
	srand(time(NULL));//Random Number Generator
	
	menu();
	
}

void menu(){
	
	/* Declaration */
	int menuChoice;//Choice of the menu
	int i; //For Loop
	char** choosen;
	myTitle();
	printf("\nWhat is your name? ");
	scanf("%s", nameOfPlayer);
	printf("\nHi %s! What category would you like to play?\n\n", nameOfPlayer);
	
	printf("---------------\n");
	printf("1. Animals     \n");
	printf("2. Fruits      \n");
	printf("3. Countries   \n");
	printf("4. Movies      \n");
	printf("5. Clothes     \n");
	printf("---------------\n");
	
	myArray = create2DArray(); //Creates an empty 2D Array Table
	
	do{
		printf("\nPlease select option [1-5] :> ");
		scanf("%d", &menuChoice);
		choosen = malloc(sizeof(char*) * 7);
		switch(menuChoice){ 
			case 1:	
				//printf("hello mate");
				for(i=0; i<7; i++){
					choosen[i] = strdup(animals[i]);
				}
				break;
			case 2:
				for(i=0; i<7; i++){
					choosen[i] = strdup(fruits[i]);
				}   
				break;
			case 3:
				for(i=0; i<7; i++){
					choosen[i] = strdup(countries[i]);
				}
				break;
			case 4:
				for(i=0; i<7; i++){
					choosen[i] = strdup(movies[i]);
				}
				break;			
			case 5:
				for(i=0; i<7; i++){
					choosen[i] = strdup(clothes[i]);
				}
		} //End of switch statement
	}while(menuChoice>=6);
	for(i=0;i<7;i++)
	{
		int randomPlacement = rand()%100+1;
		if(randomPlacement>60)
			insertHorizontally(choosen[i], myArray);
		else if(randomPlacement>20)
			insertVertically(choosen[i], myArray);
		else
			insertDiagonally(choosen[i], myArray);
	}
	//fillArray();
	

	int choicesFound = 0;
	float playersTime = 180;
	while(choicesFound !=7 && playersTime>0)
	{
		
		myTitle();
	
		clock_t start = clock();//Start the clock
		
		printf("\nOK %s - There are 7 hidden words in this grid.\n",nameOfPlayer);
		printf("Can you find them all?\n");
		printf("You have 2 minutes!\n\n");
		
		printArray(myArray);
		
		
		
		
		printf("%d words left\n", (7-choicesFound));
		printf("You have %.0f seconds left\n",playersTime); //set time
		printf("PLEASE USE CAPITAL LETTERS\n");
		
		printf("Word : ");
		char inputWord[20];
		scanf("%s",inputWord);
		for(i=0; i<7; i++){
			if (!strcmp(choosen[i],inputWord) && foundWordsArray[i]!=1)
			{
				foundWordsArray[i] = 1;
				choicesFound++;
				break;
			}
		}
		clock_t end = clock();
		playersTime = playersTime - (float)(end-start)/CLOCKS_PER_SEC;
	}
	
	if(choicesFound==7){
		setColor(5);
		printf("\n\n**************************\n");
		printf("* Y O U   H A V E   W O N*\n");
		printf("**************************\n");
		winSound();
		winSound();
		winSound();
	}else{
		setColor(4);
		printf("\n\n**************************\n");
		printf("* Y O U   H A V E   L O S T  *\n");
		printf("******************************\n");
		invalidSound();
	}
	
}

/* Welcome User to the program */
void myTitle(){ 
	printf("   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("  |                                                                  |\n");
	printf("  |                    WELCOME TO WORD SEARCH 3000                   |\n");
	printf("  |                                                                  |\n");
	printf("   - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n\n");
	
}

/* Create a 2D array of WIDTH * HEIGHT and return a pointer to it */
char **create2DArray(){ 
	
	int i,j; //For Loops
	char **array2D = (char **) malloc(sizeof(char*) * WIDTH);
	
	for(i=0; i<WIDTH; i++){
		array2D[i] = (char *) malloc(sizeof(char) * HEIGHT);
	}

	for(i=0; i<WIDTH; i++){
		for(j=0; j<HEIGHT; j++){
			
			//char randomLetter = 'A' + (rand() % 26); //ASCII TABLE from 65 to 90 (A-Z)
			char dot = '.';
			array2D[i][j] = dot;
		}
	}
	return array2D;
}

/* Prints the Array Table in the console screen */
void printArray(char** array){
	
	int i,j; //For Loops
	
	for(i=0; i<WIDTH; i++){
		for(j=0; j<HEIGHT; j++){
			printf("   %c",array[i][j]);
		}
		printf("\n\n");
	}
	printf("\n");
}


/* Inserting words to the Array Table Horizontally */
void insertHorizontally(char* word, char** array){
	
	
	/* Declaration */
	int pos=0;
	int i,j; //For Loop
	int x,y; //Create a random location in the 2D array grid
	int wordLength = strlen(word);
	
	while(pos!=1){
		
		pos = 1;
    x = rand() % (WIDTH - wordLength);
    y = rand() %  HEIGHT;
    
		for(i=0; i< strlen(word); i++){
			
			if( !(array[y][x+i] == '.' || array[y][x+i] == word[i]) ){
				pos = 0;
				break;
			}
		}
	}
	
	//After checking, set the words in main array
  for(j=0; j< strlen(word); j++){
  	array[y][x+j] = word[j];  
	}
	
}

/* Inserting words to the Array Table Vertically */
void insertVertically(char*word, char**array){
	
	/* Declaration */
	int pos=0;
	int i,j; //For Loop
	int x,y; //Create a random location in the 2D array grid
	int wordLength = strlen(word);
	
	while(pos!=1){
		pos = 1;
    x = rand() % WIDTH;
    y = rand() % (HEIGHT- wordLength);
    
		for(i=0; i< strlen(word); i++){
			
			/* Checks if the grid is empty or if its filled with another word*/
			if( !(array[y+i][x] == '.' || array[y+i][x] == word[i]) ){
				pos = 0;
				break;
			}
		}
	}
	
	
	//After checking, set the words in main array
  for(j=0; j< strlen(word); j++){
  	array[y+j][x] = word[j];  
	}
}


/* Inserting word to the Array Table Diagonally */
void insertDiagonally(char* word, char** array){
	
	/* Declaration */
	int pos=0;
	int i,j; //For Loop
	int x,y; //Create a random location in the 2D array grid
	int wordLength = strlen(word);
	
	while(pos!=1){
		pos = 1;
    x = rand() % (WIDTH- wordLength);
    y = rand() % (HEIGHT- wordLength);
    
		for(i=0; i<strlen(word); i++){
			
			/* Checks if the grid is empty or if its filled with another word*/
			if( !(array[y+i][x+i] == '.' || array[y+i][x+i] == word[i]) ){
				pos = 0;
				break;
			}
		}
	}
	
	//After checking, set the word in main array
  for(j=0; j< strlen(word); j++){
  	array[y+j][x+j] = word[j];  
	}
	
}


/* Fill the 2D array grid with random Letters */
void fillArray(){
	
	int i , j;//For Loops
	
	for(i = 0; i < WIDTH; i++){
		for(j = 0; j < HEIGHT; j++){
			if(myArray[i][j] == '.')
				myArray[i][j] = 65 + rand() % 25;
		}
	}
}


/* Setting Color to the text*/
void setColor(int num){

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,num);
}


void splitter(){
	
	int i;
	for(i=0; i<2; i++){
		insertHorizontally(animals[i],myArray);
	}
	
	for(i=0; i<2; i++){
		insertVertically(animals[i], myArray);
	}
	for(i=0; i<3; i++){
		insertDiagonally(animals[i], myArray);
	}
	
}

void winSound(){
	
	// Winning message
	Beep(1500,150);
	Beep(2000,150);
	Beep(2500,150);
	Beep(3000,150);
}

void invalidSound(){
	// Word not found 
	Beep(200,200);
	Beep(200,200);
}


void findWord(char* word){
	int i,j;//For Loops
	int foundWord=0;
	int cl; //Copy the location of the word
	int z;
	
	/* Check the Array Grid Horizontally*/
	//For every Width and every Height
	for(i=0; i<WIDTH; i++){
		for(j=0; j<HEIGHT; j++){
		
			/* For every word in the array selection */
			for(z=0; z<7; z++){
				/* Checks if the word is in the 2D array */
				if(myArray[i][j] == word[z]){
					foundWord=0;
					break;
				}
			}
		}
	}
}




