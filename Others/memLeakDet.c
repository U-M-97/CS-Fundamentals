#include <stdio.h>
#include <stdlib.h>

struct Memory {
    int* ptr;
    int size;
};

void allocMem(int size, struct Memory* mptr){
    int totalSize = sizeof(int) * size;
    mptr->ptr = (int*)malloc(totalSize);
    mptr->size = totalSize;
}

void freeMem(struct Memory* mptr){
    free(mptr->ptr);
    mptr->ptr = NULL;
    mptr->size = 0;
}

void displayLeaks(struct Memory* hptr, int* filledMemArray){
    int totalMemoryLeak = 0;
    for(int i = 0; i < *filledMemArray; i++){
        if(hptr->ptr != NULL && hptr->size != 0){
            printf("%d, bytes of memory leak detected\n", hptr->size);
            totalMemoryLeak += hptr->size;
        }
        hptr++;
    }
    printf("total leaked memory = %d bytes", totalMemoryLeak);
}

int main(){
    struct Memory m[100];
    int filledMemArray = 0;

    struct Memory* hptr = m;
    struct Memory* mptr = m;

    allocMem(10, mptr);
    mptr++;
    filledMemArray++;

    allocMem(20, mptr);
    freeMem(mptr);
    mptr++;
    filledMemArray++;

    allocMem(30, mptr);
    mptr++;
    filledMemArray++;

    allocMem(40, mptr);
    filledMemArray++;
    freeMem(mptr);

    displayLeaks(hptr, &filledMemArray);
    return 0;
}