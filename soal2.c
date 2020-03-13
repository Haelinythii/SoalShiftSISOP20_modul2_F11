#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

void getTimestamp(char *path);
void writeKillerA();
void writeKillerB();

int main(int argc, char **argb){
  if(strcmp(argb[1], "-a") == 0){
    writeKillerA();
  }
  if(strcmp(argb[1], "-b") == 0){
    writeKillerB();
  }

  char buf[100];
  char *workingDir = getcwd(buf, 100);

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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1){
    chdir(workingDir);
    pid_t child_id1;
    int status1;
    
    child_id1 = fork();

    char namaFolder[1000];
    snprintf(namaFolder, 1000, "./");
    getTimestamp(namaFolder);

    if(child_id1 == 0){
      pid_t child_id2;
      int status2;
      
      child_id2 = fork();

      if(child_id2 == 0){
        char *argv[] = {"mkdir", namaFolder, NULL};
        execv("/bin/mkdir", argv);
      } else {
        while((wait(&status2)) > 0);
        pid_t child_id3;
        int status3, i;
        char curFolder[1000]; strcpy(curFolder, namaFolder);
        char namaFile[1000];
        char linkDownload[1000];

        for(i=0; i<20; i++){
          strcpy(namaFile, curFolder); strcat(namaFile, "/");
          getTimestamp(namaFile);
          long int sec = time(NULL)%1000 + 100;
          snprintf(linkDownload, 1000, "https://picsum.photos/%ld", sec);
          child_id3 = fork();
          if(child_id3 == 0){
            char *argv[] = {"wget", "-O", namaFile, linkDownload, NULL};
            execv("/usr/bin/wget", argv);
          } else {

          }
          sleep(5);
        }

        pid_t child_id4;
        int status4;

        child_id4 = fork();

        if(child_id4 == 0){
          char outputZip[1000];
          snprintf(outputZip, 1000, "%s.zip", curFolder);
          char *argv[] = {"zip", "-r", outputZip, curFolder, NULL};
          execv("/usr/bin/zip", argv);
        } else {
          while((wait(&status4)) > 0);
          char *argv[] = {"rm", "-r", curFolder, NULL};
          execv("/bin/rm", argv);
        }
      }
    } else {
      
    }
    sleep(30);
  }

  return 0;
}

void getTimestamp(char *path)
{
  char timeStr[10];

  time_t curtime;
  struct tm *loctime;    
  curtime = time (NULL);
  loctime = localtime (&curtime);
  
  snprintf(timeStr, 10, "%d-", loctime->tm_year+1900);
  strcat(path, timeStr);

  if ((loctime->tm_mon+1) < 10)
		snprintf(timeStr, 10, "0%d-", loctime->tm_mon+1);
	else
		snprintf(timeStr, 10, "%d-", loctime->tm_mon+1);
	strcat(path, timeStr);
	
	if (loctime->tm_mday < 10)
		snprintf(timeStr, 10, "0%d_", loctime->tm_mday);
	else
		snprintf(timeStr, 10, "%d_", loctime->tm_mday);
	strcat(path, timeStr);
	
	if (loctime->tm_hour < 10)
		snprintf(timeStr, 10, "0%d:", loctime->tm_hour);
	else
		snprintf(timeStr, 10, "%d:", loctime->tm_hour);
	strcat(path, timeStr);
	
	if (loctime->tm_min < 10)
		snprintf(timeStr, 10, "0%d:", loctime->tm_min);
	else
		snprintf(timeStr, 10, "%d:", loctime->tm_min);
	strcat(path, timeStr);
	
	if (loctime->tm_sec < 10)
		snprintf(timeStr, 10, "0%d", loctime->tm_sec);
	else
		snprintf(timeStr, 10, "%d", loctime->tm_sec);
	strcat(path, timeStr);
}

void writeKillerA()
{
  FILE *temp;
  temp = fopen("killer.sh", "w");
  fputs("#!/bin/bash\n", temp);
  fputs("killOrder=$(echo $(pidof soal2))\n", temp);
  fputs("kill -9 $killOrder\n", temp);
  fputs("rm $0\n", temp);
  fclose(temp);

  pid_t tempChild_id;
  int tempStatus;
  tempChild_id = fork();

  if(tempChild_id == 0){
    char *argv[]={"chmod", "+x", "killer.sh", NULL};
    execv("/bin/chmod", argv);
  } else {

  }
}

void writeKillerB()
{
  FILE *temp;
  temp = fopen("killer.sh", "w");
  fputs("#!/bin/bash\n", temp);
  fputs("killOrder=$(echo $(pidof soal2))\n", temp);
  fputs("killOrder=${killOrder##* }\n", temp);
  fputs("kill -9 $killOrder\n", temp);
  fputs("rm $0\n", temp);
  fclose(temp);

  pid_t tempChild_id;
  int tempStatus;
  tempChild_id = fork();

  if(tempChild_id == 0){
    char *argv[]={"chmod", "+x", "killer.sh", NULL};
    execv("/bin/chmod", argv);
  } else {

  }
}
