/*
 * 	Kendric Agdaca
 * 	05/14/24
 *
 * 	Just holds function prototypes for merge.c.
 */

#ifndef MERGE_H
#define MERGE_H

#include "avl.h" //this gives the Merge Sort functions access to the tree and nodes

int compareName(Account A, Account B, int Order);
int compareAccType(Account A, Account B, int Order);
int compareBalance(Account A, Account B, int Order);


void Merge(Account *SortedAccounts, int Left, int Mid, int Right, int (*SortChoice)(Account, Account, int), int Order);
void mergeSort(Account *SortedAccounts, int Left, int Right, int (*SortChoice)(Account, Account, int), int Order);


int getTotalAcc(AVLNode *Root);
void extractNodes(AVLNode *Root, Account *SortedAccounts, int *Index);
void sortAccounts(AVLNode *Root);
#endif
