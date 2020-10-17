#include <sys/io.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>


int main(int argc, char const *argv[]) {
  int fd, ret;
  char ch;
  int i=1;
  int n=1;
  int sum=0;
  int strCount=0; int strlen=0;
  fd=open("text.txt", O_RDONLY);
  while ((ret=read(fd, &ch, 1))>0) {
      if(ch=='\n'){
        strCount++;
      }
  }
  close(fd);
  fd=open("text.txt", O_RDONLY);
  int arr[strCount];
  int brr[strCount];
  while ((ret=read(fd, &ch, 1))>0) {
      strlen++;
      if(ch=='\n'){
        arr[i]=strlen;
        i++;
        strlen=0;
      }
  }
  for(int j = 1; j<=strCount; j++){
    sum+=arr[j];
    brr[j+1]=sum;
  }
  close(fd);
  printf("Всего в файле %d строк\n", strCount);
  printf("Введите номер строки %d\n", strCount);
  while (n!=0) {
  scanf("%d", &n);
    fd=open("text.txt", O_RDONLY);
    lseek(fd, brr[n], SEEK_SET);
    for(int j = 1; j<arr[n]; j++){
      ret = read(fd, &ch, 1);
      printf("%c", ch);
    }
    printf("\n");
    close(fd);
  }
  printf("Программа завершила работу\n");
  return 0;
}
