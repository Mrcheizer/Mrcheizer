#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char* argv[])
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat fileStat;

    mydir = opendir(argv[1]);
    while((myfile = readdir(mydir)) != NULL)
    {
      if (stat(myfile->d_name,&fileStat) == -1)
      {
          perror("myfile error");
          return -1;
      }


      if(S_ISDIR(fileStat.st_mode)){
        printf("d  ");
      }
      else if (S_ISREG(fileStat.st_mode)) {
        printf("-  ");
      }
      else printf("?  ");


      if(fileStat.st_mode & S_IRUSR){
        printf("r");
      }
      else printf("-");
      if(fileStat.st_mode & S_IWUSR){
        printf("w");
      }
      else printf("-");
      if(fileStat.st_mode & S_IXUSR){
        printf("x  ");
      }
      else printf("-  ");


      if(fileStat.st_mode & S_IRGRP){
        printf("r");
      }
      else printf("-");
      if(fileStat.st_mode & S_IWGRP){
        printf("w");
      }
      else printf("-");
      if(fileStat.st_mode & S_IXGRP){
        printf("x  ");
      }
      else printf("-  ");


      if(fileStat.st_mode & S_IROTH){
        printf("r");
      }
      else printf("-");
      if(fileStat.st_mode & S_IWOTH){
        printf("w");
      }
      else printf("-");
      if(fileStat.st_mode & S_IXOTH){
        printf("x  ");
      }
      else printf("-  ");


      printf(" %s",getpwuid(fileStat.st_uid)->pw_name);
      printf(" %s",getgrgid(fileStat.st_gid)->gr_name);


      if(S_ISREG(fileStat.st_mode)) 
          printf(" %d",fileStat.st_size);
      else
      {
          printf("          ");
      }


      char* time = ctime(&fileStat.st_mtim.tv_sec);
      printf(" %s",myfile->d_name);
      printf(" %s",time);
    }
    closedir(mydir);
}
