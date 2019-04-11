#include <stdio.h>
#include <sys/shm.h>
#include "sbuf.h"
#include "shm.h"

int main() {
    int e2m_id = shm_id(60);
    int m2e_id = shm_id(120);
    struct sbuf_t *e2m = shm_new(e2m_id);
    struct sbuf_t *m2e = shm_new(m2e_id);

    sbuf_init(e2m, N);
    sbuf_init(m2e, N);

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
            int status = sbuf_insert_noblock(e2m, item);
            if (status == -1)
                printf(
                    "Mars haven't read some messages. Failed to send "
                    "messages.\n");
            else
                printf("Your message have been successfully sent to Mars.\n");
        } else if (op == 2) {
            item = sbuf_remove_noblock(m2e);
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

    shm_unlink((char *)e2m);
    shm_unlink((char *)m2e);
    shm_delete(e2m_id);
    shm_delete(m2e_id);
}
