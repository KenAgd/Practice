/*
 * Kendric Agdaca
 * 5/10/24
 * Simple Calculator
 *
 * Description: Per the name of this source file, this is a simple calculator application where the user inputs 
 * 	the entire mathmatical calculation all in one input as opposed to other simple calculators where you 
 * 	input the first number, then the operator, then the second number. This is made possible by using strtok
 * 	and parsing the user input into separate parts. Yes its lengthy and more work but visually to me is more
 * 	appealing in user experience
 * 	EX: instead of 1 \n + \n 1 you would input 1 + 1 on a single input with a space in between each character
 *
 * Notes:
 * 	-UserInput[strcspn(UserInput, "\n")] = 0 removes the newline character from fgets input and can also
 * 	be used in scanf input. Look at man strcspn for inputs and return value info
 * 	
 * 	-double variable type is used for higher precision for calculation. If user expected input is very 
 * 	large or small, switch to long double for higher precision.
 *
 * 	-do while loop is used in main to allow for user to either choose to do another calculation or end the
 * 	program
 *
 * 	-strtok_r is used instead of standard strtok to allow for reentry into the Expression and allow for
 * 	multiple tokens to be used to parse separate within the same UserInput string.
 * 		-EX (list of IPV4 addresses): 127.0.0.1, 192.0.2.1    where first strtok_r uses 
 * 		token: 127.0.0.1
 * 		sub token: 127
 * 		sub token: 0
 * 		sub token: 0
 * 		sub token: 1
 * 		token: 192.0.2.1
 * 		sub token: 192
 * 		sub token: 0
 * 		sub token: 2
 * 		sub token: 1
 * 		-This is a list of IPV4 addresses. The first strtok_r call uses "," to separate the two addresses
 * 		and the second uses "." to separate each part of the address. 
 * 		(refer to https://systems-encyclopedia.cs.illinois.edu/articles/c-strok/)
 *
 * 	-atof converts a number string into into a double data type.
 * 		-EX: 12345 -> 12345.0000
 * 		     asdf -> 0000.0000
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
 *Purpose: Parses math expression inputted by user into 3 separate variables: operand1, operator, and
 *	operand2. Once parsed, perform math calculation.
 *Input: char UserInput[]
 *Output: double "inputted math expression answer"
 */
double Calculate(char UserInput[])
{
	double operand1;
	char operator;
	double operand2;

	
	char *Token;
	char *Expression = UserInput;



	Token = strtok_r(Expression, " ", &Expression);
	operand1 = atof(Token);


	Token = strtok_r(NULL, " ", &Expression);
	if (Token == NULL)
	{
		printf("Error. Operator not detected.\n");
		exit(0);
	}
	operator = Token[0];


	Token = strtok_r(NULL, " ", &Expression);
	operand2 = atof(Token);


	switch(operator)
	{
		case '+':
			return operand1 + operand2;
			break;

		case '-':
			return  operand1 - operand2;
			break;

		case '*':
			return  operand1 * operand2;
			break;
	
		case '/':
			if (operand2 != 0)
			{
				return operand1 / operand2;
				break;
			}
			else
			{
				printf("Error. Division by zero\n");
				exit(0);
			}

		default:
			printf("Error. Invalid operator.\n");
			exit(0);
	}
}



/*
 *Purpose: Simply prompts user if they'd like to do another calculation. This function was made to prevent 
 	having and extreme amount of nested do while loops and if else statements within the main function
 *Input: None
 *Output: 
 *	-return 1 = restart
 *	-return 0 = end program
 */
int Restart()
{
	char RestartChoice[10];

	do
	{
		printf("Would you like to perform another calculation? Yes/No: ");
		fgets(RestartChoice, sizeof(RestartChoice), stdin);

		if (strlen(RestartChoice) > 4)
		{
			printf("Error. Invalid choice FLAG\n");
			memset(RestartChoice, 0, sizeof(RestartChoice));
			continue;
		}
		RestartChoice[strcspn(RestartChoice, "\n")] = '\0';
		
		for (int i = 0; i< strlen(RestartChoice); i++) RestartChoice[i] = tolower(RestartChoice[i]);


		if (strcmp(RestartChoice, "yes") == 0) return 1;
		else if (strcmp(RestartChoice, "no") == 0) return 0;
		else printf("Error. Invalid choice\n");
	}while (1);
}





int main(int argc, char* argv[])
{
	char UserInput[100];


	do
	{
		printf("Enter a math expression (100 characters max):");
		fgets(UserInput, sizeof(UserInput), stdin);
		

		//guard clause to ensure user input is less than 100 characters. If triggered, reset UserInput[] and restart do while loop.
		if (sizeof(UserInput) > 100)
		{
			printf("Error, input greater than 100 characters. Try again\n");
			while (getchar() != '\n');
			continue;
		}
		
		UserInput[strcspn(UserInput, "\n")] = 0;


		printf("Answer: %.2f\n", Calculate(UserInput));	
	

		
	}while (Restart());
	printf("end of program\n");
}
