/**********************************************************************
* File Name: knights_tour.c   					    				  *
* Name: Uriel Naiman								    			  *
* Topic: knights tour C file      									  *
**********************************************************************/
#include <stdlib.h>     /* malloc, free */
#include <stdio.h>

#include "knights_tour.h"
#include "bit_array.h"

#define MAX_NUM_OF_TRIES 8
#define BITS_IN_SIZE_T 64

/* util functions */
static int KnightsTourRec(index_t index, index_t* array_of_moves, 
bit_array_t *is_full, index_t *possibility, int size, int depth);
static int WarnsdorffTourRec(index_t index, index_t* array_of_moves, 
bit_array_t *is_full, index_t *possibility, int size, int depth);
static int OnBoardAndOpen(index_t next, bit_array_t is_full, int size);
static size_t GetIndex(index_t index, int size);

/* special for warnsdorff algorithm */
static int NumOfMoves(index_t index, index_t *possibility, int size, 
bit_array_t is_full);
static index_t FindNextMove(index_t index, index_t *possibility, 
        bit_array_t *bit_arr, int size, bit_array_t is_full);

/*---------------------------------------------------------------------*/

index_t *KnightsTour(index_t index, int size)
{
    int depth = 0;
    bit_array_t *is_full = NULL;
    int game_size = size *size;
    index_t possibility[8] ={{2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, 
                                                    {-1,-2}, {1,-2}, {2,-1}};
    
    index_t *array_of_moves = (index_t*) malloc(size * size * sizeof(index_t));
    if (NULL == array_of_moves)
    {
        return (NULL);
    }
    is_full = (bit_array_t *) malloc(sizeof(bit_array_t));
    if (NULL == is_full)
    {
        free(array_of_moves);
        return (NULL);
    }
    
    *is_full = BitArrSetAll(*is_full);
    array_of_moves[depth] = index;
    *is_full =  BitArrSetOff(*is_full, GetIndex(index, size));
    
    while(BITS_IN_SIZE_T > game_size)
    {
        *is_full =  BitArrSetOff(*is_full, game_size++);
    }

    if (KnightsTourRec(index, array_of_moves, is_full, possibility, size, depth + 1))
    {
        return (NULL);
    }
    free(is_full);

    return (array_of_moves);
}

/*---------------------------------------------------------------------*/

static int KnightsTourRec(index_t index, index_t* array_of_moves, 
bit_array_t *is_full, index_t *possibility, int size, int depth)
{
    index_t next = {0, 0};

    int i = 0;

    if (!(*is_full))
    {
        return (EXIT_SUCCESS);
    }

    for (i = 0; i < MAX_NUM_OF_TRIES; ++i)
    {
        next.x = index.x + possibility[i].x;
        next.y = index.y + possibility[i].y;

        if (OnBoardAndOpen(next, *is_full, size))
        {
            *is_full =  BitArrSetOff(*is_full, GetIndex(next, size));
            array_of_moves[depth] = next;
            
            if(!KnightsTourRec(next, array_of_moves, is_full, possibility, size, depth + 1))
            {
                return (EXIT_SUCCESS);
            }
            else
            {
                *is_full =  BitArrSetOn(*is_full, GetIndex(next, size));
            }
            
        }
        
    }
    
    return (EXIT_FAILURE);
}
/*---------------------------------------------------------------------*/

index_t *WarnsdorffTour(index_t index, int size)
{
    int depth = 0;
    bit_array_t *is_full = NULL;
    int game_size = size *size;
    index_t possibility[8] ={{2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, 
                                                    {-1,-2}, {1,-2}, {2,-1}};
    
    index_t *array_of_moves = (index_t*) malloc(size * size * sizeof(index_t));
    if (NULL == array_of_moves)
    {
        return (NULL);
    }
    is_full = (bit_array_t *) malloc(sizeof(bit_array_t));
    if (NULL == is_full)
    {
        free(array_of_moves);
        return (NULL);
    }
    
    *is_full = BitArrSetAll(*is_full);
    array_of_moves[depth] = index;
    *is_full =  BitArrSetOff(*is_full, GetIndex(index, size));
    
    /*while(BITS_IN_SIZE_T > game_size)
    {
        *is_full =  BitArrSetOff(*is_full, game_size++);
    }*/

    if (WarnsdorffTourRec(index, array_of_moves, is_full, possibility, size, depth + 1))
    {
        return (NULL);
    }
    free(is_full);

    return (array_of_moves);
}

/*---------------------------------------------------------------------*/

static int WarnsdorffTourRec(index_t index, index_t* array_of_moves, 
bit_array_t *is_full, index_t *possibility, int size, int depth)
{
    index_t next = {0, 0};
    bit_array_t bit_arr = 0;
    int i = 0;

    bit_arr = BitArrResetAll(bit_arr);
    
    if (!(*is_full))
    {
        return (EXIT_SUCCESS);
    }
    /*printf("%d%d ", next.x, next.y);*/

    for (i = 0; i < MAX_NUM_OF_TRIES; ++i)
    {
        next = FindNextMove(index, possibility, &bit_arr, size, *is_full);
        
        *is_full =  BitArrSetOff(*is_full, GetIndex(next, size));
        array_of_moves[depth] = next;
            
        if(!WarnsdorffTourRec(next, array_of_moves, is_full, possibility, size, depth + 1))
        {
            return (EXIT_SUCCESS);
        }
        else
        {
            *is_full =  BitArrSetOn(*is_full, GetIndex(next, size));
        }
            
    }
    
    return (EXIT_FAILURE);
}
/*---------------------------------------------------------------------*/

static int OnBoardAndOpen(index_t next, bit_array_t is_full, int size)
{
    return ((0 <= next.x) && (0 <= next.y) && (next.x < size)
                && (next.y < size) && (BitArrIsOn(is_full, GetIndex(next, size))));
}

/*---------------------------------------------------------------------*/

static size_t GetIndex(index_t index, int size)
{
    if (0 == index.x) 
    {
        return ((size_t)index.y);
    }

    return ((size_t)(index.x * size + index.y));
}

/*---------------------------------------------------------------------*/

static int NumOfMoves(index_t index, index_t *possibility, int size, 
bit_array_t is_full)
{
    int count = 0;
    int i = 0;
    index_t temp = {0};

    for (i = 0; i < size; ++i)
    {
        temp.x = index.x + possibility[i].x;
        temp.y = index.y + possibility[i].y;

        if (OnBoardAndOpen(temp, is_full, size))
        {
            ++count;
        }
    }
    return(count);
}

/*---------------------------------------------------------------------*/

static index_t FindNextMove(index_t index, index_t *possibility, 
        bit_array_t *bit_arr, int size, bit_array_t is_full)
{
    index_t temp = {0};
    int i = 0;
    int count = MAX_NUM_OF_TRIES + 1;
    int place = 0;
    int curr_num = 0;

    for (i = 0; i < size; ++i)
    {
        temp.x = index.x + possibility[i].x;
        temp.y = index.y + possibility[i].y;

        curr_num = NumOfMoves(temp, possibility, size, is_full);

        if(OnBoardAndOpen(temp, is_full, size) && 
        curr_num < count && BitArrIsOff(*bit_arr, i))
        {
            place = i;
            count = curr_num;
        }     
        
    }
   
    BitArrSetOn(*bit_arr, place);   
    temp.x = index.x + possibility[place].x;
    temp.y = index.y + possibility[place].y;
    
    return (temp);
}