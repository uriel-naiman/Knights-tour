/**********************************************************************
* File Name: knights_tour_test.c 				    				  *
* Name: Uriel Naiman								    			  *
* Topic: knights tour Test file    									  *
**********************************************************************/
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* free */
#include <time.h>

#include "knights_tour.h"

static void TestKnightsTour(index_t index, int size);
static void TestWarnsdorffTour(index_t index, int size);
static void TestTimeCaseOne(void);
static void TestTimeCaseTwo(void);

int main()
{
    
    TestTimeCaseOne();
    TestTimeCaseTwo();
    return(0);
}


static void TestKnightsTour(index_t index, int size)
{
    short i = 0;

    index_t *array_of_moves = KnightsTour(index, size);


    for (i = 0; i < size *size; ++i)
    {
        printf("%d,%d ",array_of_moves[i].x, array_of_moves[i].y);
    }

    printf("\n");

    free(array_of_moves);
}

static void TestWarnsdorffTour(index_t index, int size)
{
    short i = 0;

    index_t *array_of_moves = WarnsdorffTour(index, size);


    for (i = 0; i < size *size; ++i)
    {
        printf("%d,%d ",array_of_moves[i].x, array_of_moves[i].y);
    }

    printf("\n");

    free(array_of_moves);
}

static void TestTimeCaseOne(void)
{
    clock_t t = 0;
	double time_taken = 0;
    index_t index = {0,7};
    int size = 8;

    printf("----comparing run time random vs warnsdorff------\n");
    printf("----------case----{0,7}----------\n");
    printf(" ****** random--case ******\n");
	
    t = clock();
    TestKnightsTour(index, size);
    t = clock() - t;
    time_taken = (double)t/CLOCKS_PER_SEC;
    printf("random case took %f seconds\n", time_taken);
    
    printf(" ****** warnsdorff--case ******\n");
    
    t = clock();
	TestWarnsdorffTour(index, size);
    t = clock() - t;
    time_taken = (double)t/CLOCKS_PER_SEC;
    printf("warnsdorff case took %f seconds\n", time_taken);
}

static void TestTimeCaseTwo(void)
{
    clock_t t = 0;
	double time_taken = 0;
    index_t index = {5,5};
    int size = 8;

    printf("----comparing run time random vs warnsdorff------\n");
    printf("----------case----{2,3}----------\n");
        
    printf(" ****** warnsdorff--case ******\n");
    
    t = clock();
	TestWarnsdorffTour(index, size);
    t = clock() - t;
    time_taken = (double)t/CLOCKS_PER_SEC;
    printf("warnsdorff case took %f seconds\n", time_taken);

    printf(" ****** random--case ******\n");
	
    t = clock();
    TestKnightsTour(index, size);
    t = clock() - t;
    time_taken = (double)t/CLOCKS_PER_SEC;
    printf("random case took %f seconds\n", time_taken);

}