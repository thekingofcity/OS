#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "sbuf.h"

int main() {
    key_t key;
    // 获取key值
    if ((key = ftok(".", 'z')) < 0) {
        perror("ftok error");
        exit(EXIT_FAILURE);
    }

    int shmid;
    // 创建共享内存
    size_t size = sizeof(sbuf_t) + N * sizeof(int);
    if ((shmid = shmget(key, size, IPC_CREAT | 0666)) == -1) {
        perror("Create Shared Memory Error");
        exit(EXIT_FAILURE);
    }

    char *shm;
    // 连接共享内存
    shm = (char *)shmat(shmid, 0, 0);
    if ((int)shm == -1) {
        perror("Attach Shared Memory Error");
        exit(EXIT_FAILURE);
    }

    printf("\nMemory attached at %X\n", (int)shm);

    // 设置共享内存
    struct sbuf_t *shared;  // 指向shm
    shared =
        (struct sbuf_t *)shm;  // 注意：shm有点类似通过 malloc()
                               // 获取到的内存，所以这里需要做个 类型强制转换

    sbuf_init(shared, N);

    printf("***************************************\n");
    printf("*     Hello commander, welcome to     *\n");
    printf("*  IPC(Inter Plantery Communication)  *\n");
    printf("*    Input 1 to send data to Mars.    *\n");
    printf("*    Input 2 to read data from Mars.  *\n");
    printf("*    Input 0 to quit.                 *\n");
    printf("***************************************\n");

    int op, item;
    printf("Waiting next operator: ");
    scanf("%d", &op);
    getchar();
    while (op)  // 读取共享内存中的数据
    {
        if (op == 1) {
            printf("What do you want to tell Mars?\n");
            scanf("%d", &item);
            getchar();
            sbuf_insert(shared, item);
            printf("Your message have been successfully sent to Mars.\n");
        } else if (op == 2) {
            item = sbuf_remove_noblock(shared);
            if (item == -1)
                printf("No more new message from Mars!\n");
            else
                printf("Mars said %d\n", item);
        }
        printf("Waiting next operator: ");
        scanf("%d", &op);
        getchar();
    }
    printf("Bye commander.\n");

    // 把共享内存从当前进程中分离
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    // 删除共享内存
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
}
