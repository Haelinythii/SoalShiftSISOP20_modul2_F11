# SoalShiftSISOP20_modul2_F11

## Soal 1

### 1.a
**Soal :**
```
Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh
```
**Jawaban :**
```c
int main(int argc, char** argv)
{
    ...
}
```
**Penjelasan :**

Semua argumen yang dituliskan di samping nama program akan disimpan di `char** argv`, termasuk nama programnya sendiri. Sedangkan `int argc` akan menyimpan jumlah argumen yang dimasukkan.

### 1.b
**Soal :**

```
Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai
```

**Jawaban :**
```c
//check Argument error
  if(argc != 5) //5 = program + 4 argumen lain
  {
    printf("salah woi kurang lol\n");
    return 0;
  }
```
Permisalan diatas melakukan checking apakah argumen yang dimasukkan adalah 5, sesuai dengan permintaan soal. Soal meminta 4 argumen, Karena nama program awal juga ikut masuk ke argv sebagai yang pertama, maka harus di tambahkan 1.

```c
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
```
Perulangan diatas digunakan untuk melakukan checking argumen detik, menit, dan jam. Perulangan bercabang diatas adalah untuk mengetahui apakah 3 argumen tersebut merupakan angka semua atau tidak, namun jika ketemu dengan "*", akan dilewati.
Lalu dibawahnya adalah pengecekan range, artinya jika tidak sesuai dengan range yang telah diberikan soal maka program akan berhenti. i==0 dan i==1 adalah untuk check detik dan menit 0-59, dan i==2 adalah check jam 0-23.

```c
  FILE *f;
  f = fopen(argv[4],"r+");
  if(f == NULL) //kalau null berarti belum ada file
  {
    printf("file tidak ada\n");
    return 0;
  }
  fclose(f);
```
Potongan program diatas adalah untuk mengetahui apakah file yang di maksud oleh argumen ke-4 itu ada. Akan dilakukan file open oleh program dan dicheck jika null maka file tersebut tidak ada dan program akan berhenti.

### 1.c
**Soal :**

```
Program hanya menerima 1 config cron
```

**Jawaban :**

### 1.d
**Soal :**

```
Program berjalan di background (daemon)
```

**Jawaban :**

```c
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
```
Potongan program diatas adalah cara untuk membuat daemon process.

```c
char jamWanted[5];
strcpy(jamWanted, argv[3]);
char menitWanted[5];
strcpy(menitWanted, argv[2]);
char detikWanted[5];
strcpy(detikWanted, argv[1]);
char pathFile[1000];
strcpy(pathFile, argv[4]);
```
Potongan diatas adalah untuk meng-copy argumen-argumen tersebut kedalam variabel char array / string dengan menggukan fungsi strcpy dengan header string.h.

```c
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
```
Potongan diatas adalah program yang akan dilooping. Pertama, program akan mendapatkan local time dari header time.h. Kemudian waktu2 itu akan dimasukkan kedalam variable string. Lalu akan dilakukan pengecekan, jika waktu yang diberikan oleh argumen dan waktu sekarang sama, atau argumen berupa "*", maka boolean akan diset menjadi true. Program bash hanya akan berjalan jika ke tiga boolean tersebut bernilai true. Jika semua boolean = true, maka program akan melakukan fork untuk spawn child yang kemudian mengeksekusi program bash dari argumen.

### 1.d
**Soal :**

```
Tidak boleh menggunakan fungsi system()
```

**Jawaban :**

Program diatas tidak menggunakan fungsi system(), hanya melakukan execv().
