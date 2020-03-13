#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char** argv) {
  //check Argument error
  if(argc != 5) //5 = program + 4 argumen lain
  {
    printf("salah woi kurang lol\n");
    return 0;
  }
  for (int i = 0; i < 3; i++) //check jam
  {
    //check alpha?
    for (int j = 0; j < strlen(argv[i+1]); j++)
    {
      if(strcmp(argv[i+1], "*") == 0)
      {
        continue;
      }
      else if(isdigit(argv[i+1][j]) == 0) //isdigit return 0 kalau bukan angka
      {
        //salah
        printf("arg ke %d salah alphabet\n", i+1);
        return 0;
      }
    }
    printf("arg ke %d bener angka semua\n", i+1);
    //check range
    int check = atoi(argv[i+1]); //convert ke integer
    if((i == 0 || i == 1) && (check > 59 || check < 0)) //check detik & menit
    {
      printf("arg ke %d salah range\n", i+1);
      return 0;
    }
    if(i == 2 && (check > 23 || check < 0)) //check jam
    {
      printf("arg ke %d salah range\n", i+1);
      return 0;
    } 
  }
  FILE *f;
  f = fopen(argv[4],"r+");
  if(f == NULL) //kalau null berarti belum ada file
  {
    printf("file tidak ada\n");
    return 0;
  }
  fclose(f);
  
  
  

  pid_t pid, sid;
  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);


    char jamWanted[5];
    strcpy(jamWanted, argv[3]);
    char menitWanted[5];
    strcpy(menitWanted, argv[2]);
    char detikWanted[5];
    strcpy(detikWanted, argv[1]);
    char pathFile[1000];
    strcpy(pathFile, argv[4]);


  while (1) {
    bool checkJam = false, checkMenit= false, checkDetik= false;
    time_t curtime;
    struct tm *loctime;
    curtime = time (NULL);
    loctime = localtime (&curtime);

    
    char detikNow[5], menitNow[5], jamNow[5];
    sprintf(jamNow,"%d",loctime->tm_hour);
    sprintf(menitNow,"%d",loctime->tm_min);
    sprintf(detikNow,"%d", loctime->tm_sec);

    //check waktunya bener ato ga
    if(strcmp(jamWanted, "*") == 0 || strcmp(jamNow, jamWanted) == 0)
    {
        checkJam = true;
    }
    if(strcmp(menitWanted, "*") == 0 || strcmp(menitNow, menitWanted) == 0)
    {
        checkMenit = true;
    }
    if(strcmp(detikWanted, "*") == 0 || strcmp(detikNow,detikWanted) == 0)
    {
        checkDetik = true;
    }
    

    if(checkJam && checkMenit && checkDetik)
    {
      pid_t pid;
      pid = fork();
        if(pid == 0)
        {
          char *argv[] = {"bash", pathFile, NULL};
          execv("/bin/bash", argv);
        }
    }
    sleep(1);
  }
}
