#include "TwoWayLinkedList.h"


int main(int argc, char *argv[]){
	int opt = 0;
	long long score;
	char sFilename[MAX], inputBuffer[MAX];
	char *scoreEndPtr = NULL, *username = NULL, *scoreBuffer = NULL;
	HighScoreNode *pFirst = NULL, *pLast = NULL;
	FILE *file;

	if(argc != 2){
		printf("Unknown amount of arguments\n");
		exit(1);
	}

	/* Get arguments */
	optind = 1;

	while((opt = getopt(argc, argv, "i:")) != -1){
		
		switch(opt){

			/* Input file */
			case 'i':
				if(strlen(optarg) < MAX){
					strcpy(sFilename, optarg);
				}else{
					printf("Too long filename.\n");
					exit(1);
				}
				break;

			case '?':
				printf("Unknown argument.\n");
				exit(1);
		}
	}
	
	/* Read the given file */
	if((file = fopen(sFilename, "r")) == NULL){
		perror("Couldn't open the given file");
		exit(1);	
	}

	while(fgets(inputBuffer, MAX, file) != NULL){
		if((username = strtok(inputBuffer,":")) == NULL){
			printf("The input file is malformed (username).\n");
			exit(1);
		}

		if((scoreBuffer = strtok(NULL,":")) == NULL){
			printf("The input file is malformed (score).\n");
			exit(1);
		}
		
		errno = 0;
		score = strtoll(scoreBuffer, &scoreEndPtr, 10);

		if(errno != 0 || scoreBuffer == scoreEndPtr){
			printf("The input file is malformed (score - strtoll).\n");
			exit(1);
		}
		
		pLast = setDataNode(pLast, username, score);

		/* Catch first node */
		if(pFirst == NULL){
			pFirst = pLast;
		}
	}

	fclose(file);

	sortHighScoreList(pFirst);

	displayListContents(pFirst);
	freeListMemory(pFirst);

	return(0);
}

