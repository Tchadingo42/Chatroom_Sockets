#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void            *function_one(void *argv);
void            *function_two(void *argv);

void            *function_one(void *arg)
{
    int         i;

    i = 0;
    while (i <= 10)
    {
        printf("thread 1: %d\n", i);
        i = i + 1;
    }
    pthread_exit(NULL);
}

void            *function_two(void *arg)
{
    int         i;

    i = 0;
    while (i <= 10)
    {
        printf("thread 2: %d\n", i);
        i = i + 1;
    }
    pthread_exit(NULL);
}

int             main(void)
{
    pthread_t   t1;
    pthread_t   t2;

    pthread_create(&t1, NULL, function_one, NULL);
    pthread_create(&t2, NULL, function_two, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return (0);
}
