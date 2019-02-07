#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>
#include <stdlib.h>
#include <string.h>

#include "test_fibonakki.h"


const unsigned long long fiboSequence[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811};

/* Test functions */

void test_getFibonacciSeries(void){

	unsigned long long testSeries[255];

	/* Enough fibonacci numbers */
	CU_ASSERT_EQUAL(getFibonacciSeries(testSeries, 10, 20), 10);
	CU_ASSERT_EQUAL(getFibonacciSeries(testSeries, 10, 0), 10);
	CU_ASSERT_EQUAL(getFibonacciSeries(testSeries, 10, 1), 10);
	CU_ASSERT_EQUAL(getFibonacciSeries(testSeries, 10, 102), 10);

	/* Initial number is lower than the first fibonacci */

	long initN = 20;
	memset(testSeries,0,sizeof(testSeries));
	getFibonacciSeries(testSeries, 10, initN);
	CU_ASSERT(testSeries[0] >= initN);

	initN = 0;
	memset(testSeries,0,sizeof(testSeries));
	getFibonacciSeries(testSeries, 10, initN);
	CU_ASSERT(testSeries[0] >= initN);

	initN = 1;
	memset(testSeries,0,sizeof(testSeries));
	getFibonacciSeries(testSeries, 10, initN);
	CU_ASSERT(testSeries[0] >= initN);


	/* Test if numbers are real fibonaccis */
	memset(testSeries,0,sizeof(testSeries));
	getFibonacciSeries(testSeries, 28, 0);
	CU_ASSERT_EQUAL(memcmp(fiboSequence, testSeries, sizeof(fiboSequence)), 0);

	/* Test for integer overflow */
	CU_ASSERT_EQUAL(getFibonacciSeries(testSeries, 1000, 0), 6);
	
}

void test_saveFibonacciSeries(void){
	unsigned long long testSeries[]={1,2,3,4,5,6,7,8,9,10};
	unsigned long long savedSeries[10];
	
	/* Test if all numbers are looped */
	CU_ASSERT_EQUAL(saveFibonacciSeries(testSeries, 10, "testFileFibo.txt"), 10);

	/* Check that the numbers are correct */
	FILE *file;
	int i = 0;

	if((file = fopen("testFileFibo.txt", "r"))!=NULL){
		while(fscanf(file, "%llu", &savedSeries[i])==1){
			i++;
		}
	
		fclose(file);
	}

	CU_ASSERT_EQUAL(memcmp(testSeries, savedSeries, sizeof(testSeries)), 0);

	/* Test the case of invalid file */
	CU_ASSERT_EQUAL(saveFibonacciSeries(testSeries, 10, "P://testFileFibo.txt"), 0);
	CU_ASSERT_EQUAL(saveFibonacciSeries(testSeries, 10, "äööäöäöä&+/6‚‚‚‚&"), 0);
	CU_ASSERT_EQUAL(saveFibonacciSeries(testSeries, 10, ""), 0);
	CU_ASSERT_EQUAL(saveFibonacciSeries(testSeries, 10, "\0"), 0);
}

void test_main(void){
	char arg_c[] = "./testDriver",arg_n[] = "-n28",arg_m[] = "-nxd",arg_w[]="-x",
		 arg_o[] = "-otest_mainFileFibo.txt",arg_i[] = "-i0", arg_j[] = "-ikl";

	char *test_arg[] = {arg_c, arg_n, arg_o, arg_i};
	char *test_arg2[] = {arg_c};
	char *test_arg3[] = {arg_c, arg_m, arg_o, arg_j};
	char *test_arg4[] = {arg_c, arg_n, arg_o, arg_i, arg_w};
	  	
	char longFileName[] = "-oasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasd\
asdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasda\
sdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdas\
dasdasdasdasdasdasdasd.txt";
 
	unsigned long long savedSeries[28];

	/* Normal run */
	CU_ASSERT_EQUAL(main_(4, test_arg), 0);

	FILE *file;
	int i = 0;

	if((file = fopen("test_mainFileFibo.txt", "r"))!=NULL){
		while(fscanf(file, "%llu", &savedSeries[i])==1){
			i++;
		}
	
		fclose(file);
	}
	
	/* Check the numbers from the normal run */
	CU_ASSERT_EQUAL(memcmp(fiboSequence, savedSeries, sizeof(fiboSequence)), 0);
	
	/* No arguments */
	CU_ASSERT_EQUAL(main_(1, test_arg2), 0);

	/* Wrong arguments */
	CU_ASSERT_EQUAL(main_(5, test_arg4), 3);

	/*Wrong kind of values*/
	CU_ASSERT_EQUAL(main_(4, test_arg3), 1);
	
	/* Too long filename */
	test_arg[2] = longFileName;
	CU_ASSERT_EQUAL(main_(4, test_arg), 2);
		
}


int main(void){

	/*Init registry*/
	if(CU_initialize_registry()==CUE_SUCCESS){
		printf("\nRegistry initialization was successful.\n\n");	
	}else{
		printf("\nRegistry initialization failed.\n\n");
		exit(1);	
	}
	
	/*Add suites and tests*/
	
	CU_TestInfo tests_fibonacci[] = {
	{"testCalculating",test_getFibonacciSeries},
	{"testSaving",test_saveFibonacciSeries},
	{"testMain",test_main},
	CU_TEST_INFO_NULL,};
	
	CU_SuiteInfo fibonacciSuites[] = {
	{"Fibonacci_test_suite",NULL, NULL,NULL,NULL, tests_fibonacci},
	CU_SUITE_INFO_NULL,};

	if(CU_register_suites(fibonacciSuites)==CUE_SUCCESS){
		printf("Suite was created and tests were added successfully.\n");	
	}else{
		printf("Suite creation failed.\n'%s'\n",CU_get_error_msg());
		CU_cleanup_registry();
		exit(1);	
	}

	/* Run tests */
	CU_set_output_filename("FibonacciTest");
	CU_automated_run_tests();

	/* Summary */
	CU_pRunSummary summary = CU_get_run_summary();
		
	printf("\n\n--------Testing completed--------\n\nSuites ran\t%u\nSuites failed\t%u\n\
Tests ran\t%u\nTests failed\t%u\nAsserts ran\t%u\nAsserts failed\t%u\n",
			summary->nSuitesRun,summary->nSuitesFailed,summary->nTestsRun,
			summary->nTestsFailed,summary->nAsserts, summary->nAssertsFailed);

	/* Get failures */
	CU_pFailureRecord failureRecord = CU_get_failure_list();

	if(failureRecord != NULL){

		printf("\n--------Failure records--------\n\n");
		printf("CONDITION\t\tTEST\t\tSUITE\t\tLINE\n\n");

		while(failureRecord !=NULL){

			printf("%s\t%s\t%s\t%u\n",failureRecord->strCondition, failureRecord->pTest->pName, 					failureRecord->pSuite->pName, failureRecord->uiLineNumber);

			failureRecord = failureRecord->pNext;		
		}

		printf("\n");

	}else{
		printf("\nApplication PASSED all the tests.\n\n");
	}
	
	/* Cleanup */
	CU_cleanup_registry();

	return(0);
}
