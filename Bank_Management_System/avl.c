/*
	Kendric Agdaca
	05/14/24
	
	Purpose: This is the main driver of the bank manangement system. Handles printing all accounts saved within the system, creating new accounts, depositing/withdrawing money into an account, checking account balance, update account info, deleting an account, and sorting accounts.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))//Used in addAccount, deleteAccount, and their aux functions.
#define MAX_ACCOUNTS 1000



/*Done
	Purpose:
		-Used to gather user input for account creation.
	
	Input:
		-int AccNumCounter: Counter variable for assigning the correct account number for the new account.
	
	Output:
		-Account NodeData: New account/node that'll be later passed to addAccount to be added into the system/tree.
	
	Notes:
		-
*/
Account GatherUserInfo(int AccNumCounter)
{
	int i;
	Account NodeData;

	NodeData.AccNum = AccNumCounter;

//take user input and remove newline
	printf("Enter full name: ");
	getchar();
	fgets(NodeData.Name, sizeof(NodeData.Name), stdin);
	NodeData.Name[strcspn(NodeData.Name, "\n")] = 0;

	printf("Enter home address: ");
	fgets(NodeData.Address, sizeof(NodeData.Address), stdin);
	NodeData.Address[strcspn(NodeData.Address, "\n")] = 0;

	printf("Enter phone number: ");
	fgets(NodeData.PhoneNum, sizeof(NodeData.PhoneNum), stdin);
	NodeData.PhoneNum[strcspn(NodeData.PhoneNum, "\n")] = 0;

	printf("Enter email address: ");
	fgets(NodeData.Email, sizeof(NodeData.Email), stdin);
	NodeData.Email[strcspn(NodeData.Email, "\n")] = 0;

	printf("Enter date of birth: ");
	fgets(NodeData.DoB, sizeof(NodeData.DoB), stdin);
	NodeData.DoB[strcspn(NodeData.DoB, "\n")] = 0;


	while (1)
	{
		printf("Enter account type (checking/savings): ");
		
	
		fgets(NodeData.AccountType, sizeof(NodeData.AccountType), stdin);
		NodeData.AccountType[strcspn(NodeData.AccountType, "\n")] = 0;
		for (i = 0; i < strlen(NodeData.AccountType); i++)//convert input to all lowercase
			NodeData.AccountType[i] = tolower(NodeData.AccountType[i]);
			
			
		if ((strcmp(NodeData.AccountType, "checking") == 0) || (strcmp(NodeData.AccountType, "savings") == 0))
			break;//valid input
		else
			printf("Error, invalid input. Try again.\n");
	}
	
	NodeData.Balance = 0;
	printf("\n");
	return NodeData;
}



/*Done
	Purpose:
		-Aux function to printTree function. Handles the actual printing of each account/node currently within the system.
	
	Input:
		-AVLNode *Root: AVL tree root.
	
	Output:
		-N/A. Only prints nodes on the tree.
	
	Notes:
		-Performs In Order traversal, recursively moves down the left, middle, then right branches.
*/
void printTreeAux(AVLNode *Root)
{
	if (Root != NULL)
	{
		printTreeAux(Root -> Left);
		
		printf("\n\n-----------------------------------------------------\n");
		printf("Account Number:%05d\n", Root -> Acc.AccNum);
		printf("Name: %s\n", Root -> Acc.Name);
		printf("Address: %s\n", Root -> Acc.Address);
		printf("Phone Number: %s\n", Root -> Acc.PhoneNum);
		printf("Email: %s\n", Root -> Acc.Email);
		printf("DoB: %s\n", Root -> Acc.DoB);
		printf("Account type: %s\n", Root -> Acc.AccountType);
		printf("Current Balance: %.2lf", Root -> Acc.Balance);
		printf("\n-----------------------------------------------------\n\n");
		
		printTreeAux(Root -> Right);
	}

	return;
}



/*Done
	Purpose:
		-Main function for printing out all the accounts/nodes in the system/tree. First checks if they're any accounts in the tree. If there are, print out.
	
	Input:
		-AVLNode *Root: AVL tree root.
	
	Output:
		-N/A
	
	Notes:
		-Aux function has to be separate from main since aux is recursive.
*/
void printTree(AVLNode *Root)
{
	if (Root == NULL)
	{
		printf("\nNo accounts to display\n\n");
		return;
	}
	
	else
	{
		printTreeAux(Root);
		return;
	}
}


/*
	Purpose:
		-Checks the height of a node thats passed in.
	
	Input:
		-AVLNode *Root: Pointer of node to be checked.
	
	Output:
		-Node height.
	
	Notes:
		-Used by rotate, add, and delete functions.
*/
int checkHeight(AVLNode *Root)
{
	if (Root == NULL) return 0;
	return Root -> Height;
}



/*Done
	Purpose:
		-Calculates the balance of the AVL tree by subtracting the right side height from the left side height. 
	
	Input:
		-AVLNode *Root: AVL tree root.
		
	Output:
		-Returns int of tree balance. 
	
	Notes:
		-If it falls within the range of -1 -> 1 then tree is balanced. If outside that range, tree is unbalanced. Positive int mean right leaning, negative int means left leaning.
*/
int checkTreeBalance(AVLNode *Root)
{
	if (Root == NULL) return 0;
	return checkHeight(Root -> Left) - checkHeight(Root -> Right);
}



/*Done
	Purpose:
		-Rotates tree to the left for tree balancing.
	
	Input:
		-AVLNode *Root: Pointer to middle node.
	
	Output:
		-Returns new root of the new left rotated subtree.
	
	Notes:
		-Temp1 is right node and Temp2 is left node. Right node's child becomes middle node and middle node's right child becomes left node.
		-Update new heights of the swapped nodes and return new root.
*/
AVLNode *leftRotate(AVLNode *Root)
{
	AVLNode *Temp1 = Root -> Right;
	AVLNode *Temp2 = Temp1 -> Left;
	
	
	Temp1 -> Left = Root;
	Root -> Right = Temp2;
	
	
	Root -> Height = MAX(checkHeight(Root -> Left), checkHeight(Root -> Right)) + 1;
	Temp1 -> Height = MAX(checkHeight(Temp1 -> Left), checkHeight(Temp1 -> Right)) + 1;
	
	return Temp1;
}



/*Done
	Purpose:
		-Rotates tree to the right for tree balancing.
	
	Input:
		-AVLNode *Root: Pointer to middle node.
	
	Output:
		-Returns new root of the new right rotated subtree.
	
	Notes:
		-Temp1 is left node and Temp2 is right node. Left node's child becomes middle node and middle node's left child becomes right node.
		-Update new heights of the swapped nodes and return new root.
*/
AVLNode *rightRotate(AVLNode *Root)
{
	AVLNode *Temp1 = Root -> Left;
	AVLNode *Temp2 = Temp1 -> Right;
	
	
	Temp1 -> Right = Root;
	Root -> Left = Temp2;
	
	
	Root -> Height = MAX(checkHeight(Root -> Left), checkHeight(Root -> Right)) + 1;
	Temp1 -> Height = MAX(checkHeight(Temp1 -> Left), checkHeight(Temp1 -> Right)) + 1;
	
	return Temp1;
}



/*Done
	Purpose:
		-Performs new account/node insertion into the system/tree.
	
	Input:
		-AVLNode *Root: Pointer to base tree root.
		-Account NewAccount: Account struct member that holds all of the new account details.
	
	Output:
		-Returns updated entire tree with newly inserted node.
	
	Notes: 
		-Calls on addAccount, checkHeight ,checkTreeBalance, leftRotate, and rightRotate functions.
		-For further notes on rotation, check OneNote
*/
AVLNode *addAccount(AVLNode *Root, Account NewAccount)
{
	int Balance;
	AVLNode *Node;


//If tree is empty of the correct insertion spot is found, create, initialize, and insert new node.
	if (Root == NULL)
	{
		Node = (AVLNode*)malloc(sizeof(AVLNode));

		if (Node == NULL)
		{
			printf("Error. Malloc failure\n");
			exit(0);
		}
	
	
	
		Node -> Acc = NewAccount;
		if (NewAccount.Balance == 0) Node->Acc.Balance = 0;
		Node -> Left = NULL;
		Node -> Right = NULL;
		Node -> Height = 1;
		return Node;	
	}


//Recursively traverse the tree until correct insertion point is found. Once found, if statement above is triggered and insertion is performed.
	if (NewAccount.AccNum < Root -> Acc.AccNum)
	{
		Root -> Left = addAccount(Root -> Left, NewAccount);
	}
	else if (NewAccount.AccNum > Root -> Acc.AccNum)
	{
		Root -> Right = addAccount(Root -> Right, NewAccount);
	}
	else
	{
		return Root;//If reaches here, that means new node is a duplicate and will be cancelled.
	}


//Once inserted, update the height of the node previous to new node and check tree balance.
	Root -> Height = 1 + MAX(checkHeight(Root -> Left), (checkHeight(Root -> Right)));
	Balance = checkTreeBalance(Root);


//Left left rotation.
	if (Balance > 1 && (NewAccount.AccNum < Root -> Left -> Acc.AccNum))
	{
		return rightRotate(Root);
	}	
		
		
//Right right rotation.
	if (Balance < -1 && (NewAccount.AccNum > Root -> Right -> Acc.AccNum))
	{
		return leftRotate(Root);
	}	
	
	
//Left right rotation.
	if (Balance > 1 && (NewAccount.AccNum > Root -> Left -> Acc.AccNum))		
	{
		Root -> Left = leftRotate(Root -> Left);
		return rightRotate(Root);
	}
	

//Right left rotation.
	if (Balance < -1 && (NewAccount.AccNum < Root -> Right -> Acc.AccNum))
	{
		Root -> Right = rightRotate(Root -> Right);
		return leftRotate(Root);
	}
		

	return Root;
}



/*Done
	Purpose:
		-Only handles finding finding a specific account/node within the tree based on account number.
	
	Input:
		-AVLNode *Root: Pointer to base tree root.
	
	Output:
		-If found, return pointer to found account/node.
		-Return NULL if user input isn't an int or if account isn't found.
	
	Notes:
		-Used by Transaction, checkAccountBalance, and updateAccountInfo functions.
		-If account isn't found, error printing is handled within the function that calls on findAccount.
		-Function asks for a 5 digit input but it only really matters if there's more than 9999 accounts.
			-EX: 00001 == 1
			     09999 == 9999
*/
AVLNode *findAccount(AVLNode *Root)
{
	int AccountLookup;
	AVLNode *Node = Root;
	
	printf("Enter 5 digit account number\n>>");
	if (scanf("%d", &AccountLookup) != 1) 
	{	
        	while (getchar() != '\n');// Clear the invalid input
        	return NULL;
    	}
	
	
	while (Node != NULL)
	{
		if (Node -> Acc.AccNum == AccountLookup) 
			return Node;
		else if (Node -> Acc.AccNum > AccountLookup)
			Node = Node -> Left;
		else 
			Node = Node -> Right;	
	}
	

	return NULL;
}



/*Done
	Purpose:
		-Handles depositing or withdrawing money from user selected accounts.
	
	Input:
		-AVLNode *Root: Pointer to base tree root.
		-int Check: int passed from menu in main.c. 1 = deposit    2 = withdraw.
	
	Output:
		-N/A. 
	
	Notes:
		-For the sake of clarity, used two separate if statements to check if user selected deposit or withdraw instead of just checking for deposit and if not deposit, assume withdraw.
*/
void Transaction(AVLNode *Root, int Check)
{
	double TransAmount;
	AVLNode *FoundAccount = findAccount(Root);
	
	if (FoundAccount != NULL)
	{
		if (Check == 1)
		{
			printf("\nEnter amount to deposit: ");
			
			if (scanf("%lf", &TransAmount) != 1) 
			{
        			// Clear the invalid input
        			while (getchar() != '\n');
        			printf("Error, invalid input. Returning to menu.\n");
        			return;
    			}
			
			FoundAccount -> Acc.Balance += TransAmount;
			printf("Deposit successful. Updated balance: $%.2lf\n\n", FoundAccount -> Acc.Balance);
			return;
		}
		
		if (Check == 2)
		{
			printf("\nEnter amount to withdraw: ");
			
			if (scanf("%lf", &TransAmount) != 1) 
			{
        			// Clear the invalid input
        			while (getchar() != '\n');
        			printf("Error, invalid input. Returning to menu.\n");
        		return;
    			}
			
			FoundAccount -> Acc.Balance -= TransAmount;
			printf("Withdrawal successful. Updated balance: $%.2lf\n\n", FoundAccount -> Acc.Balance);
			return;
		}
	}

	else
	{
		printf("\nError, account doesn't exist. Returning to menu.\n\n");
		return;
	}
}



/*Done
	Purpose:
		-Simply prints the balance of the user selected account.
	
	Input:
		-AVLNode *Root: Pointer to base tree root.
	
	Output:
		-N/A.
	
	Notes:
		-
*/
void checkAccountBalance(AVLNode *Root)
{
	AVLNode *FoundAccount = findAccount(Root);
	
	if (FoundAccount != NULL)
	{
		printf("Account number %05d current balance: $%.2lf\n\n", FoundAccount -> Acc.AccNum, FoundAccount -> Acc.Balance);
		return;
	}
	
	else
	{
		printf("\nError, account doesn't exist. Returning to menu.\n\n");
		return;
	}
}



/*
	Purpose:
		-Handles updating ALL account properties (except balance) of user selected account.
	
	Input:
		-AVLNode *Root: Pointer to base tree root.
	
	Output:
		-Returns tree with the updated account.
	
	Notes:
		-
*/
AVLNode *updateAccountInfo (AVLNode *Root)
{
	Account NewAccount;
	AVLNode *FoundAccount = findAccount(Root);
	double PreservedBalance;


	if (FoundAccount != NULL)
	{
		PreservedBalance = FoundAccount -> Acc.Balance;
		NewAccount = GatherUserInfo(FoundAccount -> Acc.AccNum);
		FoundAccount -> Acc = NewAccount;
		FoundAccount -> Acc.Balance = PreservedBalance;
		printf("Account %d successfully updated\n\n", FoundAccount -> Acc.AccNum);
		
	}
	
	
	return Root;
}



/*Done
	Purpose:
		-Handles deleting user selected account from system.
	
	Input:
		-AVLNode *Root: Pointer to base tree root.
		-int AccountNumber: Account number of account to be deleted.
	
	Output:
		-Returns updated tree with the removed account.
	
	Notes:
		-Cant use findAccount function because deleteAccount recursively calls itself so its gonna keep asking for account number to delete. 
		-Mental note of understanding: I dont have to worry about shifting accounts up the tree when a preceding node is removed because the remaining nodes need to be shifted up anyways in order for the tree to remain balanced.
*/
AVLNode *deleteAccount(AVLNode *Root, int AccountNumber)
{
	AVLNode *Temp;
	int Balance;


	if (Root == NULL)
	{
		printf("There are no accounts saved\n\n");
		return Root;
	}
	

//Recursively find account in the system.
	if (Root -> Acc.AccNum > AccountNumber)
	{
		Root -> Left = deleteAccount(Root -> Left, AccountNumber);
	}
	else if (Root -> Acc.AccNum < AccountNumber)
	{
		Root -> Right = deleteAccount(Root -> Right, AccountNumber);
	}

//Once found, check how many children .
	else
	{
	//Node with only one or no child.
		if ((Root -> Left == NULL) || (Root -> Right == NULL))
		{
		//assign Temp to non NULL child, or NULL if both children are NULL.
			Temp = Root -> Left ? Root -> Left : Root -> Right;
			
			if (Temp == NULL)//no children case.
			{
				Temp = Root;
				Root = NULL;
			}
			
			else *Root = *Temp;
			free(Temp);
		}	
		
		else//one child case.
		{
			Temp = Root -> Right;
			
			while (Temp -> Left != NULL)
				Temp = Temp -> Left;
				
			Root -> Acc = Temp -> Acc;
			Root -> Right = deleteAccount(Root -> Right, Temp -> Acc.AccNum);
		}
	}
	if (Root == NULL) return Root;//If only one node in tree case.





//After removal, update tree height and check balance.
	Root -> Height = 1 + MAX(checkHeight(Root -> Left), checkHeight(Root -> Right));
	Balance = checkTreeBalance(Root);
	
//Left left rotation.
	if ((Balance > 1) && (checkTreeBalance(Root -> Left)) >= 0)
		return rightRotate(Root);

//Right right rotation.
	if ((Balance > 1) && (checkTreeBalance(Root -> Left)) < 0)
	{
		Root -> Left = leftRotate(Root -> Left);
		return rightRotate(Root);
	}
	
//Left right rotation.
	if ((Balance < -1) && (checkTreeBalance(Root -> Right)) <= 0)
		return leftRotate(Root);

//Right left rotation.	
	if ((Balance < -1) && (checkTreeBalance(Root -> Right)) > 0)
	{
		Root -> Right = rightRotate(Root -> Right);
		return leftRotate(Root);
	}


	return Root;	
}
	
	

/*Done
	Purpose:
		-Frees nodes then frees tree.
	
	Input:
		-AVLNode *Root: Pointer to base tree root.
	
	Output:
		-N/A
	
	Notes:
		-
*/	
void freeTree(AVLNode *Root)
{
	if (Root == NULL)
	{
		return;
	}


	freeTree(Root -> Left);
	freeTree(Root -> Right);
	free(Root);

	
}
