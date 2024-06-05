/*
	Kendric Agdaca
	05/14/24
	
	Purpose: This file was made to separate and isolate the merge sort functions in order to make implementation, testing, and debugging easier. Plus this is new content to me using a merge sort on an AVL Tree. Essentially you save each node in the tree into an array AND THEN perform the merge sort based on what you're sorting by. Once sorted, I can print the sorted list. 
	
	

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "merge.h"



/*Done
	Purpose:
		-Compare functions used to determine by which method and order to sort the AVL tree in. Can either sort by name, account type, balance and have the sorted in either ascending or descending order all based on user input.
		
	Inputs:
		-Account A: 1st node to compare
		-Account B: 2nd node to compare
		-int Order: Determines ascending or descending order. 
		
	Outputs:
		-Returns an int that determines the relative order of the two nodes passed in.
		-If Order = 1 (ascending) then return the following
			Negative if A.SortOrder < B.SortOrder
			Zero if A.SortOrder == B.SortOrder
			Positive if A.SortOrder > B.SortOrder
		
		-If Order = 0 (descending) then return the following
			Negative if A.SortOrder > B.SortOrder
			Zero if A.SortOrder == B.SortOrder
			Positive if A.SortOrder < B.SortOrder
	Notes:
		-int Order was included into the compare functions so that I can control ascending or descending sorting from within the merge sort itself as opposed to just sorting in ascending and then printing in ascending or descending order.
*/
int compareName(Account A, Account B, int Order)
{
	int Result = strcmp(A.Name, B.Name);
	return Order ? Result : -Result;
}

int compareAccType(Account A, Account B, int Order)
{
	int Result = strcmp(A.AccountType, B.AccountType);
	return Order ? Result : -Result;
}

int compareBalance(Account A, Account B, int Order)
{
	double Diff = A.Balance - B.Balance;
	
//return 1 if positive diff, -1 if negative diff	
	int result = (Diff > 0) - (Diff < 0);
	return Order ? result : -result;
}



/*Done
	Purpose:
		-Aux function to mergeSort function that handles determining the order of node pairs based on user input and then merging the tree back together accordingly.
		
	Inputs:
		-Account *SortedAccounts: Pointer array of the tree in the form of an array.
		-int Left: Left node.
		-int Mid: Middle node.
		-int Right: Right node.
		-int (*SortChoice)(Account, Account, int):
		-int Order: Determines ascending or descending order. 
		
	Outputs:
		-N/A. Performs sorting and merging in function then pointer stores it back into SortedAccounts without the need of a return.
		
	Notes:
		-When sorting by account type:
			Ascending = Checkings first.
			Descending = Savings first.
		-Check OneNote for more detailed notes on how Merge Sort works.
		
*/	
void Merge(Account *SortedAccounts, int Left, int Mid, int Right, int (*SortChoice)(Account, Account, int), int Order)
{
	int i, j, k;
//Calculate the size of the two sub arrays to be merged.
	int n1 = Mid - Left + 1;
	int n2 = Right - Mid;



//Create and initialize temp arrays and copy SortedAccounts into them.
	Account *LeftArray = (Account*)malloc(n1 * sizeof(Account));
	Account *RightArray = (Account*)malloc(n2 * sizeof(Account));
	
	for (i = 0; i < n1; i++)
		LeftArray[i] = SortedAccounts[Left + i];
	for (j = 0; j < n2; j++)
		RightArray[j] = SortedAccounts[Mid + 1 + j];
		
	i = 0;
	j = 0;
	k = Left;
	
	
//Perform merging based on user input using compare function passed in and store back into SortedAccounts.
	while (i < n1 && j < n2)
	{
		if (SortChoice(LeftArray[i], RightArray[j], Order) <= 0)
		{
			SortedAccounts[k] = LeftArray[i];
			i++;
		}
		else
		{
			SortedAccounts[k] = RightArray[j];
			j++;
		}
		k++;
	}
	
	
	
//If any, copy remaining nodes of Left and Right arrays
	while (i < n1)
	{
		SortedAccounts[k] = LeftArray[i];
		i++;
		k++;
	}
	
	while (j < n2)
	{
		SortedAccounts[k] = RightArray[j];
		j++;
		k++;
	}
	
//Cleanup.
	free(LeftArray);
	free(RightArray);
	
}
	
	
	
/*Done
	Purpose:
 		-Main Merge Sort function.
		
	Inputs:
		-Account *SortedAccounts: Pointer array of the tree in the form of an array.
		-int Left: Left node.
		-int Right: Right node.
		-int (*SortChoice)(Account, Account, int):
		-int Order: Determines ascending or descending order.
		
	Outputs:
		-N/A.
		
	Notes:
		-
		
*/	
void mergeSort(Account *SortedAccounts, int Left, int Right, int (*SortChoice)(Account, Account, int), int Order)
{
	int Mid;

	if (Left < Right)//Base case: If array has fewer than 2 nodes, already sorted.
	{
	//Find midpoint to determine where to split.
		Mid = Left + (Right - Left) / 2;
		
	//Recursively sort left and right halves
		mergeSort(SortedAccounts, Left, Mid, SortChoice, Order);
		mergeSort(SortedAccounts, Mid + 1, Right, SortChoice, Order);
		
	//Merge newly sorted halves.
		Merge(SortedAccounts, Left, Mid, Right, SortChoice, Order);
	}
}



/*Done
	Purpose:
		-Simply recursively finds the total number of accounts within the system.
		
	Inputs:
		-AVLNode *Root: Pointer to base tree root.
		
	Outputs:
		-Returns an int of the total height of the AVL Tree.
		
	Notes:
		-Used by sortAccounts function.
		-+1 accounts for the root.
		
*/
int getTotalAcc(AVLNode *Root)
{
	if (Root == NULL) return 0;

	//else root + nodes on left + nodes on right
	return 1 + getTotalAcc(Root -> Left) + getTotalAcc(Root -> Right);

}
	
	
	
/*
	Purpose:
		-Handles making copies of each node on the AVL Tree and storing them into a pointer array.
		
	Inputs:
		-AVLNode *Root: Pointer to base tree root.
		-Account *SortedAccounts: Pointer array that will hold the nodes.
		-int *Index: Int pointer used to maintain indice position without the need of a global counter variable.
		
	Outputs:
		-N/A.
		
	Notes:
		-Copies nodes in In Order Traversal.
		
*/
void extractNodes(AVLNode *Root, Account *SortedAccounts, int *Index)
{
	if (Root != NULL)
	{
		extractNodes(Root -> Left, SortedAccounts, Index);
		SortedAccounts[(*Index)++] = Root -> Acc;
		extractNodes(Root -> Right, SortedAccounts, Index);
	}
}
	


/*
	Purpose:
		-Simply prints out the array of sorted accounts.
		
	Inputs:
		-Account *SortedAccounts: Pointer array of the tree in the form of an array.
		-int NumOfAcc: Number of accounts.
		
	Outputs:
		-N/A
		
	Notes:
		-Cant use printTree function in avl.c because that relies on having an access pointer to the tree root. Had to alter and make this since merge sort works best with arrays and linked lists.
		
*/	
void printSortedAccounts(Account *SortedAccounts, int NumOfAcc)
{
	int i;

	for (i = 0; i < NumOfAcc; i++)
	{
		printf("\n------------------------------------\n");
		printf("Account Number:%05d\n", SortedAccounts[i].AccNum);
		printf("Name: %s\n", SortedAccounts[i].Name);
		printf("Address: %s\n", SortedAccounts[i].Address);
		printf("Phone Number: %s\n", SortedAccounts[i].PhoneNum);
		printf("Email: %s\n", SortedAccounts[i].Email);
		printf("DoB: %s\n", SortedAccounts[i].DoB);
		printf("Account type: %s\n", SortedAccounts[i].AccountType);
		printf("Current Balance: %.2lf\n", SortedAccounts[i].Balance);
		printf("\n------------------------------------\n");
	}
	printf("\n");
	return;
}





/*
	Purpose:
		-Main function of the source file. First gathers sorting choice and sorting order from user input and then passes all necessary data to perform Merge Sort Algo.
		
	Inputs:
		-AVLNode *Root: Pointer to base tree root.
		
	Outputs:
		-N/A
		
	Notes:
		-
		
*/
void sortAccounts(AVLNode *Root)
{

	char SortChoice[20];
	char SortOrder[20];
	int Index = 0;
	int Order;
	
	printf("\nHow would you like to sort the accounts by?:\nName\nAccount Type\nBalance\n>>");
	getchar();
	fgets(SortChoice, sizeof(SortChoice), stdin);
	SortChoice[strcspn(SortChoice, "\n")] = 0;
	for (int j = 0; j < strlen(SortChoice); j++)
		SortChoice[j] = tolower(SortChoice[j]);
	

	if ((strcmp(SortChoice, "name") != 0) && (strcmp(SortChoice, "account type") != 0) && (strcmp(SortChoice, "balance") != 0))
	{
		printf("Error, invalid choice. Returning to menu.\n\n");
		return;
	}
	
	
	printf("\nSort in Ascending or Descending order?\n>>");
	fgets(SortOrder, sizeof(SortOrder), stdin);
	SortOrder[strcspn(SortOrder, "\n")] = 0;
	for (int j = 0; j < strlen(SortOrder); j++)
		SortOrder[j] = tolower(SortOrder[j]);
	
	
	if ((strcmp(SortOrder, "ascending") != 0) && (strcmp(SortOrder, "descending") != 0))
	{
		printf("Error, invalid choice. Returning to menu\n\n");
		return;
	}
	
	else
	{
		Order = (strcmp(SortOrder, "ascending") == 0);
	}
	
	
	
	
	
			//Start of merge sort
	
//Initialize a copy of the AVL tree in the form of an array.
	int NumOfAcc = getTotalAcc(Root);
	Account *SortedAccounts = (Account*)malloc(NumOfAcc * sizeof(Account));
	
	if (SortedAccounts == NULL)
	{
		printf("Error allocating sortedAccounts\n");

		return;
	}

	extractNodes(Root, SortedAccounts, &Index);
	
	

	


//Perform merge sort based on what user chooses to sort by.
	if (strcmp(SortChoice, "name") == 0)
		mergeSort(SortedAccounts, 0, NumOfAcc - 1, compareName, Order);
	if (strcmp(SortChoice, "account type") == 0)
		mergeSort(SortedAccounts, 0, NumOfAcc - 1, compareAccType, Order);
	else
		mergeSort(SortedAccounts, 0, NumOfAcc - 1, compareBalance, Order);	
	
	
	

//Print the list then cleanup.	
	printSortedAccounts(SortedAccounts, NumOfAcc);
	free(SortedAccounts);
	return;
}
