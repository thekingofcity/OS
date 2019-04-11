#ifndef __SHM_H__
#define __SHM_H__

#include <stdlib.h>
#include <sys/shm.h>

int shm_id();
char *shm_new(int shm_id);
void shm_unlink(char *shm);
void shm_delete(int shm_id);

#endif /* __SHM_H__ */