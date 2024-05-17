/*
 * Kendric Agdaca
 * Created 5/8/24
 * Rock Paper Scissors User vs Bot Game
 *
 * Compile Line: gcc -g -Wall -o RPS_Game RPS_Game.c
 * or make all
 *
 * Notes:
 * 	-Since this is a simple game, no need to pointer array. Only use pointer array if you dont know what the
 * 		size of the array will be. Since I do know (no more than 9 bytes), I can use a normal char array
 * 		BUT I have to set a guard cluase.
 *	-Memset if user input error to clear User_Input array and prevent stack smashing
 *
 *	-Could be improved by allowing user to restart while still executing instead of having to relaunch executable.
 	use "Handling String Input With Spaces | C Programming Tutorial" by Portfolio Courses as a ref
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>



/*
 * Input: User_Input
 * Output: None
 * Notes: 0 -> 32 = Rock    33->65 = Paper    66 -> 99 = Scissors
 * 	  % 100 in rand() makes random range 0->100
 *
 */
void Start_Game(char User_Input[])
{
	int Randomizer = rand() % 100;
	if (strcmp(User_Input, "rock") == 0)
	{
		if (Randomizer <= 32) printf("Computer played Rock. Tie\n");
		else if (Randomizer >= 33 && Randomizer <= 65) printf("Computer played Paper. You lose\n");
		else printf("Computer played Scissors. You win\n");
	}

	else if (strcmp(User_Input, "paper") == 0)
	{
		if (Randomizer <= 32) printf("Computer played Rock. You win\n");
		else if (Randomizer >= 33 && Randomizer <= 65) printf("Computer played Paper. Tie\n");
		else printf("Computer played Scissors. You lose\n");
	}

	else
	{
		if (Randomizer <= 32) printf("Computer played Rock. You lose\n");
		else if (Randomizer >= 33 && Randomizer <= 65) printf("Computer played Paper. You win\n");
		else printf("Computer played Scissors. Tie\n");
	}
}



int RestartGame()
{
	char Choice[10];


	do
	{
		printf("Would you like to play again? Yes/No\n");
		fgets(Choice, sizeof(Choice), stdin);

		if (strlen(Choice) > 9)
		{
			printf("Error. Invalid Choice\n");
			memset(Choice, 0, sizeof(Choice));
			continue;
		}
		Choice[strcspn(Choice, "\n")] = '\0';
		for (int i = 0; i < strlen(Choice); i++) Choice[i] = tolower(Choice[i]);


		if (strcmp(Choice, "yes")) return 0;
		else if (strcmp(Choice, "no")) return 1;
		else
		{
			printf("Error. Invalid choice\n");	
			memset(Choice, 0, sizeof(Choice));
			continue;
		}
	}while(1);
}



int main(int argc, char* argv[])
{
	char User_Input[100];
	srand(time(NULL));



	do
	{
		printf("Please select \"Rock\", \"Paper\", or \"Scissors\"\n");
		fgets(User_Input, sizeof(User_Input), stdin);

		if (strlen(User_Input) > 9)
		{
			printf("Error. Invalid Choice\n");
			memset(User_Input, 0, sizeof(User_Input));
			continue;
		}

		User_Input[strcspn(User_Input, "\n")] = 0;
		for (int i = 0; i < strlen(User_Input); i++) User_Input[i] = tolower(User_Input[i]);



		if ((strcmp(User_Input, "rock") == 0) || (strcmp(User_Input, "paper") == 0) || (strcmp(User_Input, "scissors") == 0))
		{
			Start_Game(User_Input);		
		}
		else
		{
			printf("Error. Invalid choice\n");
			memset(User_Input, 0, sizeof(User_Input));
			continue;
		}
	}while(RestartGame());
	return 0;
}
