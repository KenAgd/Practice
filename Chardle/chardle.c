/*
 * Kendric Agdaca
 * Chardle C practice
 *
 * Input: letter, word
 * Output: N/A
 *
 * Description: Basic function is to user input a word and a letter and to parse the word for the amount of times the user input letter is found.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char letter[5];
	char word[10];
	int i, CharCount;

	printf("Enter a 5 letter word: ");
	scanf("%s", word);

	if(strlen(word) != 5)
	{
		printf("Word is not 5 letters\n");
		exit(0);
	}

	printf("Enter a single character: ");
	scanf("%s", letter);

	if(strlen(letter) != 1)
	{
		printf("Invalid input, not a single character\n");
		exit(0);
	}

	printf("Searching for %s in %s\n", letter, word);
	for (i = 0; i < 5; i++)
	{
		if(letter[0] == word[i])
		{
			printf("%s found at index %d\n", letter, i);
			CharCount++;
		}
	}

	printf("%d instances of %s found in %s\n", CharCount, letter, word);
}
