#include <stdio.h>
#include "sbuf.h"
#include "shm.h"

int main() {
    int e2m_id = shm_id(60);
    int m2e_id = shm_id(120);
    struct sbuf_t *e2m = shm_new(e2m_id);
    struct sbuf_t *m2e = shm_new(m2e_id);

    printf("***************************************\n");
    printf("*     Hello commander, welcome to     *\n");
    printf("*  IPC(Inter Plantery Communication)  *\n");
    printf("*    Input 1 to send data to Earth.   *\n");
    printf("*    Input 2 to read data from Earth. *\n");
    printf("*    Input 0 to quit.                 *\n");
    printf("***************************************\n");

    int op, item;
    printf("Waiting next operator: ");
    scanf("%d", &op);
    getchar();
    while (op)  // 读取共享内存中的数据
    {
        if (op == 1) {
            printf("What do you want to tell Earth?\n");
            scanf("%d", &item);
            getchar();
            int status = sbuf_insert_noblock(m2e, item);
            if (status == -1)
                printf(
                    "Earth haven't read some messages. Failed to send "
                    "messages.\n");
            else
                printf("Your message have been successfully sent to Earth.\n");
        } else if (op == 2) {
            item = sbuf_remove_noblock(e2m);
            if (item == -1)
                printf("No more new message from Earth!\n");
            else
                printf("Earth said %d\n", item);
        }
        printf("Waiting next operator: ");
        scanf("%d", &op);
        getchar();
    }
    printf("Bye commander.\n");

    shm_unlink((char *)e2m);
    shm_unlink((char *)m2e);
}
