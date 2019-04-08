#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "sbuf.h"


#define N 10
#define N_thread 2

void *receive(void *vargp);

sbuf_t sp;

int main()
{
    printf("%d\n", sizeof(sbuf_t));

    sbuf_init(&sp, N);
    pthread_t tid[N_thread];

    for (int i = 0; i < N_thread; i++)
    {
        int argv = i;
        tid[i] = pthread_create(&tid, NULL, receive, (void *)argv);
    }

    for (int i = 0; i < N_thread; i++)
        pthread_join(tid[i], NULL);

    sbuf_deinit(&sp);
}

void *receive(void *vargp)
{
    int argv = (int *)vargp;
    if (argv == 0)
    {
        int item = 999;
        sbuf_insert(&sp, item);
    }
    else if (argv == 1)
    {
        int item = sbuf_remove(&sp);
        printf("%d\n", item);
    }
    return;
}