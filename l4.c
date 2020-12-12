#include <sys/io.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h> 
#include <sys/stat.h>


FILE *fd;
sem_t *semaphore1;
sem_t *semaphore2;


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
    fclose(fd);
    sem_post(&semaphore);
  }
}

int main(int argc, char const *argv[]) {
      pthread_t thread1;
      pthread_t thread2;

      semaphore1 = sem_open("/my_named_semaphore1", O_CREAT, S_IRUSR | S_IWUSR, 0);
      semaphore2 = sem_open("/my_named_semaphore2", O_CREAT, S_IRUSR | S_IWUSR, 1);

      pthread_create(&thread1, NULL, square, NULL);
      pthread_create(&thread2, NULL, cube, NULL);

      pthread_join(thread1, NULL);
      pthread_join(thread2, NULL);
      
      
      sem_unlink("/my_named_semaphore1");
      sem_unlink("/my_named_semaphore2");
      printf("done \n");
      return 0;
}
