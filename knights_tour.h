#ifndef KNIGHTS_TOUR_H
#define KNIGHTS_TOUR_H

typedef struct 
{
    int x;
    int y;
}index_t;


index_t *KnightsTour(index_t index, int size);

index_t *WarnsdorffTour(index_t index, int size);

#endif /* KNIGHTS_TOUR_H */