#include "sbuf.h"
#include "shm.h"
#include <stdio.h>

int shm_id(int id) {
    key_t key;
    // 获取key值
    if ((key = ftok(".", id)) < 0) {
        perror("ftok error");
        exit(EXIT_FAILURE);
    }

    int shmid;
    // 创建共享内存
    size_t size = sizeof(sbuf_t);
    if ((shmid = shmget(key, size, IPC_CREAT | 0666)) == -1) {
        perror("Create Shared Memory Error");
        exit(EXIT_FAILURE);
    }

    return shmid;
}

char *shm_new(int shmid) {
    char *shm;
    // 连接共享内存
    shm = (char *)shmat(shmid, 0, 0);
    if ((int)shm == -1) {
        perror("Attach Shared Memory Error");
        exit(EXIT_FAILURE);
    }

    // printf("\nMemory attached at %X\n", (int)shm);

    // 设置共享内存
    struct sbuf_t *shared;  // 指向shm
    shared =
        (struct sbuf_t *)shm;  // 注意：shm有点类似通过 malloc()
                               // 获取到的内存，所以这里需要做个 类型强制转换

    return shared;
}

void shm_unlink(char *shm) {
    // 把共享内存从当前进程中分离
    if (shmdt(shm) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
}

void shm_delete(int shmid) {
    // 删除共享内存
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
}