
#include "TwoWayLinkedList.h"

void *allocateMemory(size_t nodeSize){
	void *ptr = NULL;

	if((ptr = malloc(nodeSize))==NULL){
		perror("Node memory allocation failed");
		exit(1);
	}

	return(ptr);
}

HighScoreNode *setDataNode(HighScoreNode *pLast, char *username, long long score){
	HighScoreNode *ptr = NULL;
	
	ptr = (HighScoreNode *)allocateMemory(sizeof(HighScoreNode));
	
	strcpy(ptr->sUsername, username);
	ptr->llScore = score;	
	ptr->pNextNode = NULL;

	if(pLast == NULL){
		ptr->pLastNode = NULL;
	}else{
		pLast->pNextNode = ptr;
		ptr->pLastNode = pLast;
	}

	return(ptr);
}

void displayListContents(HighScoreNode *pFirst){
	HighScoreNode *ptr = pFirst;
	HighScoreNode *pLast = pFirst;

	printf("Players in ascending order.\n");

	while(ptr != NULL){
		printf("%s\t-\t%lld\n", ptr->sUsername, ptr->llScore);
		pLast = ptr;
		ptr = ptr->pNextNode;
	}

	printf("\n\n");
	ptr = pLast;

	printf("Players in descending order.\n");

	while(ptr != NULL){
		printf("%s\t-\t%lld\n", ptr->sUsername, ptr->llScore);
		pLast = ptr;
		ptr = ptr->pLastNode;
	}

}

void switchNodePlaces(HighScoreNode *ptr1, HighScoreNode *ptr2){
	HighScoreNode pTemp;
	
	strcpy(pTemp.sUsername, ptr1->sUsername);
	strcpy(ptr1->sUsername, ptr2->sUsername);
	strcpy(ptr2->sUsername, pTemp.sUsername);

	pTemp.llScore = ptr1->llScore;

	ptr1->llScore = ptr2->llScore;
	ptr2->llScore = pTemp.llScore;
}

void sortHighScoreList(HighScoreNode *pFirst){
	HighScoreNode *ptrR = pFirst;
	
	while(TRUE){
		
		if(ptrR->pNextNode == NULL)
			break;

		/* Compare current and next value in the list */
		if(ptrR->llScore > (ptrR->pNextNode)->llScore){
			switchNodePlaces(ptrR, ptrR->pNextNode);

			/* Backtrack and check if the value is in the right place */
			if(ptrR->pLastNode != NULL){
				if(ptrR->pLastNode->llScore > ptrR->llScore){				
					ptrR = ptrR->pLastNode;
				}
			}

		}else{
			ptrR = ptrR->pNextNode;

		}
		
	}

}

void freeListMemory(HighScoreNode *pFirst){
	HighScoreNode *ptr = NULL;

	while(pFirst != NULL){
		ptr = pFirst->pNextNode;
		free(pFirst);
		pFirst = ptr;
	}

}
