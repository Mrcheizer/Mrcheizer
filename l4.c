#include <sys/io.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>


FILE *fd;
sem_t semaphore;


void* square(void* args) {
    int i, res=0;
    for (i = 0; i < 100; i++) {
      sem_wait(&semaphore);
      res=i*i;
      fprintf(fd,"step %d: calculate %d*%d=%d \n", i, i, i, res);
      res=0;
      sem_post(&semaphore);
    }
}

void* cube(void* args) {
  int i, res=0;
  for (i = 0; i < 100; i++) {
    sem_wait(&semaphore);
    res=i*i*i;
    fprintf(fd,"step %d: calculate %d*%d*%d=%d \n", i, i, i, i, res);
    res=0;
    sem_post(&semaphore);
  }
}

int main(int argc, char const *argv[]) {
	  fd = fopen("log.txt", "w");
      pthread_t thread1;
      pthread_t thread2;

      sem_init(&semaphore, 0, 1);

      pthread_create(&thread1, NULL, square, NULL);
      pthread_create(&thread2, NULL, cube, NULL);

      pthread_join(thread1, NULL);
      pthread_join(thread2, NULL);
      printf("done \n");
      return 0;
}
