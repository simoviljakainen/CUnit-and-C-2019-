#ifndef TWOWAYLINKEDLIST_H
#define TWOWAYLINKEDLIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>

#define MAX 255
#define TRUE 1

typedef struct dataNode{
	
	char sUsername[MAX];
	long long llScore;	
		
	struct dataNode *pLastNode;
	struct dataNode *pNextNode;

}HighScoreNode;


void *allocateMemory(size_t);
HighScoreNode *setDataNode(HighScoreNode *, char *, long long);
void freeListMemory(HighScoreNode *);
void displayListContents(HighScoreNode *);
void switchNodePlaces(HighScoreNode *, HighScoreNode *);
void sortHighScoreList(HighScoreNode *);


#endif
