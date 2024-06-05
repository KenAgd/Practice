/*
 * 	Kendric Agdaca
 * 	05/14/24
 *
 * 	This file holds typedef struct for avl tree info, as well as,
 * function prototypes.
 */

#ifndef AVL_H
#define AVL_H

typedef struct Account //key data
{
	int AccNum;
	char Name[100];
	char Address[100];
	char PhoneNum[15];
	char Email[50];
	char DoB[15];
	char AccountType[10]; //checking or savings
	double Balance; //use %.2lf when printing
} Account;

typedef struct AVLNode
{
	Account Acc; //this is the "key" data thats stored within each node
	struct AVLNode *Left;
	struct AVLNode *Right;
	int Height;
} AVLNode;

Account GatherUserInfo(int AccNumCounter);
void printTreeAux(AVLNode *Root);
void printTree(AVLNode *Root);


int checkHeight(AVLNode *Root);
int checkTreeBalance(AVLNode *Root);
AVLNode *leftRotate(AVLNode *Root);
AVLNode *rightRotate(AVLNode *Root);
AVLNode *addAccount(AVLNode *Root, Account NewAccountData);

AVLNode *findAccount (AVLNode *Root);
void Transaction(AVLNode *Root, int Check);
void checkAccountBalance(AVLNode *Root);
AVLNode *updateAccountInfo(AVLNode *Root);
AVLNode *deleteAccount(AVLNode *Root, int AccountNumber);


void sortAccounts(AVLNode *Root);

void freeTree(AVLNode *Root);
#endif
