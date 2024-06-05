/*
	Kendric Agdaca
	05/14/24
 
	This is the main source file for the bank management system. This file houses the options menu for the system and the functions necessary to import and export accounts from a CSV file in order to maintain and keep the accounts even after the program has ended.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"
#include "merge.h"



/*Done
	Purpose: 
		-Reads each line from the Client Data Base CSV file and creates an account to add to the system.
	
	Inputs:
		-AVLNode *Root: Pointer to base tree root.
		-const char *FileName: Holds name of data base CSV file. 
		-int *AccNumCounter: Counts the number of accounts imported from the CSV file so that when a new account is added after the import, the new account will have the correct sequential account number.
	
	Outputs:
		-Returns the tree with all of the imported accounts loaded into it.
	
	Notes:
		-
*/
AVLNode *importAccounts(AVLNode *Root, FILE *File, int *AccNumCounter)
{
	char Line[500];
	Account NewAccount;

//skips reading column titles of CSV.
	if (fgets(Line, sizeof(Line), File) == NULL) 
	{
        	perror("Error reading file");
        	fclose(File);
    	}
    
    
//sscanf each line of the CSV, store the data into the corresponding struct member, then push it onto the tree. Increment AccNumCounter to keep track of the number of accounts imported.
	while (!feof(File) && !ferror(File))
	{
		while (fgets(Line, sizeof(Line), File))
		{
			NewAccount.AccNum = *AccNumCounter;

			sscanf(Line, "%d, %99[^,], %99[^,], %14[^,], %49[^,], %14[^,], %9[^,], %lf", 
               	&NewAccount.AccNum,      // Address of AccNum (int)
               	NewAccount.Name,         // Name is already a pointer (char array)
               	NewAccount.Address,      // Address is already a pointer (char array)
               	NewAccount.PhoneNum,     // PhoneNum is already a pointer (char array)
               	NewAccount.Email,        // Email is already a pointer (char array)
               	NewAccount.DoB,          // DoB is already a pointer (char array)
               	NewAccount.AccountType,  // AccountType is already a pointer (char array)
               	&NewAccount.Balance);    // Address of Balance (double)
		
			Root = addAccount(Root, NewAccount);
			(*AccNumCounter)++;	
		}
	}

	return Root;
}



/*Done
	Purpose:
		-Handles exporting accounts/nodes into CSV by fprinting each node's info one line at a time traversing the tree In Order
		-Main function for exporting accounts/nodes into CSV file. Opens the CSV for writing then calls on WriteInOrder aux function to perform this function.
	
	Input:
		-AVLNode *Root: Pointer to base tree root.
		-const char *FileName: Name of the CSV file "ClientDataBase.csv".
	
	Output:
		-N/A
	Note:
		-Similar to extractNodes function in merge.c.
*/
void exportAccounts(AVLNode *Root, FILE *File)
{
	if (Root != NULL)
	{
		exportAccounts(Root -> Left, File);
		
		fprintf(File, "%d,%s,%s,%s,%s,%s,%s,%.2f\n", Root -> Acc.AccNum, Root -> Acc.Name, Root -> Acc.Address, Root -> Acc.PhoneNum, Root -> Acc.Email, Root -> Acc.DoB, Root -> Acc.AccountType, Root -> Acc.Balance);
		
		exportAccounts(Root -> Right, File);
	}
}



//Done
int main(int argc, char *argv[])
{
	int choice;
	int AccNumCounter = 1;
	AVLNode *root = NULL;
	AVLNode *temp;
	Account NewAccount;
	const char *FileName = "ClientDataBase.csv";
	const char *columnTitles = "AccountNumber,Name,Address,PhoneNumber,Email,DoB,AccountType,Balance\n";


//see if ClientDataBase.CSV exists. If it doesn't exist, make one then print column titles on the first line. If failed, exit program. If created successfully or file exists, import the accounts and AccNumCounter.
	FILE *File = fopen(FileName, "r");
	
	if (File == NULL)
	{
		File = fopen(FileName, "w");
		
		if (File == NULL)
		{
			printf("Critical Error, failed to create database csv\n");
			exit(0);
		}
		
		fprintf(File, "Account Number,Name,Address,Phone Number,Email,Date of Birth,Account Type, Balance\n");	
	}
	
	else
	{
		root = importAccounts(root, File, &AccNumCounter);
		fclose(File);
	}




	printf("\nWelcome to the Bank Management System. Enter the number of the action you'd like to perform\n\n");
	do
	{
		
		printf("\nMenu:\n1) Print list\n2) Create account\n3) Deposit\n4) Withdraw\n5) Check balance\n6) Update account information\n7) Delete account\n8) Sort accounts\n9) Exit\n");
		printf(">>");
	        
	//ensures that user input is an int. If not, clear input buffer, error print, restart menu loop.
	        if (scanf("%d", &choice) != 1) 
	        {
            
            		while (getchar() != '\n');
            		printf("\nError. Invalid choice\n");
            		continue;
        	}



		switch(choice)
		{
			//print list
			case 1:
				printTree(root);
				break;
				
			//create account
			case 2:
				NewAccount = GatherUserInfo(AccNumCounter);
				root = addAccount(root, NewAccount);

				printf("\nAccount %05d added successfully\n\n", AccNumCounter);
				AccNumCounter++;
				break;
				
			//deposit
			case 3:
				Transaction(root, 1);
				break;

			//withdraw
			case 4:
				Transaction(root, 2);
				break;

			//check balance
			case 5:
				checkAccountBalance(root);
				break;
				
			//update account info
			case 6:
				root = updateAccountInfo(root);
				break;

			//delete account
			case 7:
				temp = findAccount(root);
				if (temp == NULL)
				{
					printf("Account doesn't exist\n\n");
					break;
				}
				else
				{
					printf("Account %05d successfully removed\n\n", temp -> Acc.AccNum);
					root = deleteAccount(root, temp -> Acc.AccNum);	
					break;
				}

			//sort accounts and print
			case 8:
				sortAccounts(root);
				break;

			//exit
			case 9:
				File = fopen(FileName, "w");
				
				if (File != NULL)
				{
					fprintf(File, "%s", columnTitles);
					exportAccounts(root, File);
				}
				else printf("Critical error, failed to export accounts\n");
					
				fclose(File);
				freeTree(root);
				printf("\nExiting Program\n");
				exit(0);

			default:
				printf("\nError. Invalid choice\n");
				break;
		}

	}while(1);
}
