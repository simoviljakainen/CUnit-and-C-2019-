
/* THIS PROGRAM IS THE VERSION THAT IS TESTED */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAXLENGTH 255
#define MAXSIZE 18446744073709551615U

int getFibonacciSeries(unsigned long long *series, long n, long initN){
	unsigned long long f1 = 0, f2 = 1, tmp;
	int i;


 	/* Calculate fibonacci numbers to starting number */

	while(1){
		tmp = f1;

		if(f1 > (MAXSIZE-f2)){
			return(6);		
		}
		
		f1 = f1 + f2;
		f2 = tmp;
		
		if(f1 > initN){
			f2 = f1 - tmp;			
			f1 = tmp;
			break;		
		}
	}

	/* Calculate fibonacci series */

	for(i = 0; i<n; i++){

		if(f1 > (MAXSIZE-f2)){
			return(6);		
		}	

		series[i] = f2 + f1;
		f2 = f1;		
		f1 = series[i];
	}
	
	return(i);

}

int saveFibonacciSeries(unsigned long long *series, long n, char *filename){
	FILE *file;
	int i;
	
	if((file = fopen(filename, "w"))!=NULL){
		for(i = 0; i < n; i++){
			fprintf(file, "%llu\n", series[i]);
		}

		fclose(file);

		return(i);

	}else{

		return(0);	
	}
	
}

int main_(int argc, char *argv[]){
	int opt = 0;
	long initN = 0, n = 10;
	char outputFile[MAXLENGTH] = "fibonakkiNumbers.txt"; 
	char *strtolEndPtr;

	/* get arguments */

	optind = 1;
	while((opt = getopt(argc, argv, "o:i:n:")) != -1){
		
		switch(opt){

			/* Output */
			case 'o':
				
				if(strlen(optarg) < MAXLENGTH){
					strcpy(outputFile, optarg);
				}else{
					return(2);
				}
				break;

			/* Starting number */
			case 'i':
				errno = 0;
				initN = strtol(optarg, &strtolEndPtr, 10);

				if((optarg == strtolEndPtr) || (errno != 0 && initN == 0) || initN < 0){
					return(1);				
				}

				break;

			/* Length of the series */
			case 'n':
				errno = 0;
				n = strtol(optarg, NULL, 10);

				if((errno != 0) || n < 1){
					return(1);				
				}
				break;

			case '?':
				return(3);	
		}

	}
	
	unsigned long long series[n];
	
	getFibonacciSeries(series, n, initN);
	
	saveFibonacciSeries(series, n, outputFile);

	return(0);
}
