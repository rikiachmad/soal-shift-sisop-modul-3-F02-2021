# soal-shift-sisop-modul-3-F02-2021
# Nomor 1
Keverk adalah orang yang cukup ambisius dan terkenal di angkatannya. Sebelum dia menjadi ketua departemen di HMTC, dia pernah mengerjakan suatu proyek dimana keverk tersebut meminta untuk membuat server database buku. Proyek ini diminta agar dapat digunakan oleh pemilik aplikasi dan diharapkan bantuannya dari pengguna aplikasi ini. 

Di dalam proyek itu, Keverk diminta:
<ol type="a">
  <li>Pada saat client tersambung dengan server, terdapat dua pilihan pertama, yaitu register dan login. Jika memilih register, client akan diminta input id dan passwordnya untuk dikirimkan ke server. User juga dapat melakukan login. Login berhasil jika id dan password yang dikirim dari aplikasi client sesuai dengan list akun yang ada didalam aplikasi server. Sistem ini juga dapat menerima multi-connections. Koneksi terhitung ketika aplikasi client tersambung dengan server. Jika terdapat 2 koneksi atau lebih maka harus menunggu sampai client pertama keluar untuk bisa melakukan login dan mengakses aplikasinya. Keverk menginginkan lokasi penyimpanan id dan password pada file bernama akun.txt dengan format :<br><br>
    <b>akun.txt</b><br>
    id:password<br>
    id2:password2
  </li>
  <li>Sistem memiliki sebuah database yang bernama files.tsv. Isi dari files.tsv ini adalah path file saat berada di server, publisher, dan tahun publikasi. Setiap penambahan dan penghapusan file pada folder file yang bernama  FILES pada server akan memengaruhi isi dari files.tsv. Folder FILES otomatis dibuat saat server dijalankan. </li>
  <li>
    Tidak hanya itu, Keverk juga diminta membuat fitur agar client dapat menambah file baru ke dalam server. Direktori FILES memiliki struktur direktori di bawah ini : 
    <br><br>
    Direktori <b>FILES</b><br>
    File1.ekstensi<br>
    File2.ekstensi
    Kemudian, dari aplikasi client akan dimasukan data buku tersebut (perlu diingat bahwa Filepath ini merupakan path file yang akan dikirim ke server). Lalu client nanti akan       melakukan pengiriman file ke aplikasi server dengan menggunakan socket. Ketika file diterima di server, maka row dari files.tsv akan bertambah sesuai dengan data terbaru         yang ditambahkan.
  </li>
  <li>
    Dan client dapat mendownload file yang telah ada dalam folder FILES di server, sehingga sistem harus dapat mengirim file ke client. Server harus melihat dari files.tsv untuk     melakukan pengecekan apakah file tersebut valid. Jika tidak valid, maka mengirimkan pesan error balik ke client. Jika berhasil, file akan dikirim dan akan diterima ke client     di folder client tersebut.
  </li>
  <li>
    Setelah itu, client juga dapat menghapus file yang tersimpan di server. Akan tetapi, Keverk takut file yang dibuang adalah file yang penting, maka file hanya akan diganti       namanya menjadi ‘old-NamaFile.ekstensi’. Ketika file telah diubah namanya, maka row dari file tersebut di file.tsv akan terhapus.

  </li>
  <li>
    Client dapat melihat semua isi files.tsv dengan memanggil suatu perintah yang bernama see. Output dari perintah tersebut keluar dengan format. 
  </li>
  <li>
    Aplikasi client juga dapat melakukan pencarian dengan memberikan suatu string. Hasilnya adalah semua nama file yang mengandung string tersebut. Format output seperti format     output f.
  </li>
  <li>
    Dikarenakan Keverk waspada dengan pertambahan dan penghapusan file di server, maka Keverk membuat suatu log untuk server yang bernama running.log. Contoh isi dari log ini       adalah
  </li>
</ol>

## Sub Soal a
Pada sub soal a, diminta untuk membuat sebuah sistem untuk login dan registrasi bagi client. pada source code yang tertera, hal ini terdapat pada fungsi regist dan login dimana fungsi regist berfungsi untuk proses registrasi dan fungsi login berfungsi untuk proses login. 
Server:
```C
void* regist(){
    bzero(buffer, 1024);
    strcpy(buffer, "SignUp\nEnter New Id:\n");
    send(sd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sd, buffer, 1024);
    char id[50];
    strcpy(id, buffer);
    strcpy(buffer, "Enter Password:\n");
    send(sd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sd, buffer, 1024);
    char pass[50];
    strcpy(pass, buffer);

    char acc[50];
    sprintf(acc, "%s:%s\n",id, pass);
    update(acc);
    strcpy(buffer, "Registration Success. You may now login with your account.\n");
    send(sd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024) ;
}
```
```C
void* login(){
    bzero(buffer, 1024);
    strcpy(buffer, "Enter Id:\n");
    send(sd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sd, buffer, 1024);
    char id[50];
    strcpy(id, buffer);
    strcpy(buffer, "Enter Password:\n");
    send(sd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sd, buffer, 1024);
    char pass[50];
    strcpy(pass, buffer);
    char acc[50];
    sprintf(acc, "%s:%s\n",id, pass);
    if(checkCreds(acc)>0){
        strcpy(buffer, "Login Success\n");
        send(sd, buffer, strlen(buffer), 0);
        status = 1;
        sprintf(user, "(%s:%s)", id, pass);
    }else{
        strcpy(buffer, "Wrong Id or Password. Please Try Again.\n");
        send(sd, buffer, strlen(buffer), 0);
    }
    bzero(buffer, 1024);
}  
```
Client :
```C
void* regist(){
    read(sock, buffer, 1024);
    printf("%s", buffer);
    bzero(buffer, 1024);
    scanf(" %s", buffer) ;
    send(sock, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sock, buffer, 1024);
    printf("%s", buffer);
    memset(buffer, 0, 1024) ;
    scanf(" %s", buffer) ;
    send(sock, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sock, buffer, 1024);
    printf("%s", buffer);
    if(strcmp(buffer, "Login Success\n")==0){
        status=1;
    }
    bzero(buffer, 1024);
}
```
```C
// regist dan Login
void* regist(){
    read(sock, buffer, 1024);
    printf("%s", buffer);
    bzero(buffer, 1024);
    scanf(" %s", buffer) ;
    send(sock, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sock, buffer, 1024);
    printf("%s", buffer);
    memset(buffer, 0, 1024) ;
    scanf(" %s", buffer) ;
    send(sock, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sock, buffer, 1024);
    printf("%s", buffer);
    if(strcmp(buffer, "Login Success\n")==0){
        status=1;
    }
    bzero(buffer, 1024);
}
```
![image](https://user-images.githubusercontent.com/74702068/119250945-c738a480-bbcd-11eb-9590-b8de235c9dcf.png)

credential dari akun-akun yang telah tersimpan akan disimpan dalam file Akun.txt.
![image](https://user-images.githubusercontent.com/74702068/119250952-d61f5700-bbcd-11eb-916a-2008fe2611b7.png)


Sistem ini juga dapat menerima multi-connection, dimana jika terdapat lebih dari 1 koneksi client yang terhubung pada server maka client yang baru masuk harus menunggu hingga tidak ada client yang terhubung untuk bisa dapat mengakses command-command pada sistem.

## Sub Soal b
Sub soal b meminta untuk membuat sebuah file dengan nama "files.tsv" dimana files.tsv ini akan menampung file-file yang berada pada folder Server. ketika terdapat penambahan atau penghapusan file pada folder server, maka hal ini juga akan mempengaruhi files.tsv. Dan untuk file-file nya sendiri akan tersimpan pada folder FILES.
```C
FILE *fp = fopen("files.tsv", "ab+");
mkdir("FILES",0777);
fclose(fp);
```
![image](https://user-images.githubusercontent.com/74702068/119251037-6cec1380-bbce-11eb-85ee-f429054cc49f.png)
Gambar untuk files.tsv

![image](https://user-images.githubusercontent.com/74702068/119251047-842b0100-bbce-11eb-9f7f-479dc797c0d3.png)
Gambar untuk folder FILES.

## Sub Soal c
Pada sub soal c ini diminta untuk membuat sebuah command "Add" yang berfungsi untuk menambahkan sebuah file dari client ke server. Command Add hanya bisa digunakan pada client yang telah login. Pada saat client mengetikkan commmand add maka akan muncul sebuah input berdasarkan format yang diminta soal untuk menambahkan file dari client ke server. Apabila terdapat sebuah file baru yang ditambahkan ke dalam server, maka file "files.tsv" juga akan di update berdasarkan input client. Folder FILES pada server juga akan diupdate berdasarkan file yang dikirimkan dari client.
Server: 
```C
void* add(){
    char pathFile[200], publisher[100], year[100], fileName[100];
    strcpy(buffer, "Publisher: \n");
    send(sd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sd, buffer, 1024) ;
    strcpy(publisher, buffer);
 
    strcpy(buffer, "Tahun Publish: \n");
    send(sd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sd, buffer, 1024) ;
 
    strcpy(year, buffer);
 
    strcpy(buffer, "Filepath: \n");
    send(sd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sd, buffer, 1024);
    strcpy(pathFile, buffer);
    strcpy(fileName, buffer);
    char temp[400];
    strcpy(temp, pathFile);
    strcat(temp, "\t");
    strcat(temp, publisher);
    strcat(temp, "\t");
    strcat(temp, year);
    
    char temp2[400];
    strcpy(temp2, serverPath);
    strcat(temp2, "FILES/");
    strcat(temp2, temp);
    strcat(temp2, "\n");
 
    FILE* file = fopen("files.tsv", "a");
    fputs(temp2, file);
    fclose(file);
 
    char path[50];
    strcpy(path, serverPath); 
    strcat(path, "FILES/"); 
    strcat(path, buffer);
 
    FILE* filee = fopen(path, "w") ;

    bzero(buffer, 1024);
    read(sd, buffer, 1024);
    fprintf(filee, "%s", buffer);
    fclose(filee);
    printf("[+]Data written in the file successfully.\n");


    bzero(buffer, 1024) ;
 
    strcpy(buffer, "Add Success\n");
    send(sd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
 
    FILE* log = fopen("running.log", "a");
    fprintf(log, "Tambah : %s %s\n", fileName, user);
    fclose(log);
}
```

Client:
```C
void* add(){
    bzero(buffer, 1024);
    read(sock, buffer, 1024) ;
    printf("%s", buffer);
    bzero(buffer, 1024);
    scanf(" %s", buffer) ;
    send(sock, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sock, buffer, 1024) ;
    printf("%s", buffer);
    bzero(buffer, 1024);
    scanf(" %s", buffer) ;
    send(sock, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
    read(sock, buffer, 1024) ;
    printf("%s", buffer);
    bzero(buffer, 1024);
    scanf(" %s", buffer);
    while(access(buffer, F_OK ) != 0){
        printf("File doesn't exist! Please try again.\n");
        bzero(buffer, 1024);
        scanf(" %s", buffer);
    }
    send(sock, buffer, strlen(buffer), 0);
     
    FILE *fp = fopen(buffer, "rb");
    if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
  }

    send_file(fp);
    printf("[+]File data sent successfully.\n");
    
    read(sock, buffer, 1024);
    printf("%s\n", buffer);
    bzero(buffer, 1024);
}
```
![image](https://user-images.githubusercontent.com/74702068/119253557-00781100-bbdc-11eb-9bc8-4714c10a946f.png)
Contoh file tes.txt dari client yang akan dikirimkan menggunakan command add ke server.

![image](https://user-images.githubusercontent.com/74702068/119253590-269db100-bbdc-11eb-8bdd-b7d20560fc9a.png)
contoh penggunaan command Add.
![image](https://user-images.githubusercontent.com/74702068/119253609-3f0dcb80-bbdc-11eb-827f-b2c8ee4c22f1.png)
Folder FILES setelah client menggunakan comman add.

![image](https://user-images.githubusercontent.com/74702068/119253629-52209b80-bbdc-11eb-9ff6-c8690bb15a1b.png)
files.tsv setelah client menggunakan command add.

## Sub Soal d
Sub soal d meminta untuk menambahkan sebuah command baru ke dalam sistem yaitu command "download". Command donwload ini digunakan untuk mendownload sebuah file yang telah ada pada folder FILES dan files.tsv pada server. File yang telah di download dari folder server akan di copy ke dalam folder client.
Server:
```C
void *download(){
    if(strcmp(buffer, "download")==0){
        strcpy(buffer, "Enter file name!\n");
        send(sd, buffer, strlen(buffer), 0);
        bzero(buffer, 1024);
    }
    else{
        char *inputCopy = malloc(255 * sizeof(char));
        char *second = secondWord(buffer, inputCopy);

        int exist = 0;
        char path[400];
        strcpy(path, serverPath);
        strcat(path, "FILES/");
        strcat(path, second);
        char data[200];
        FILE *opfile = fopen("files.tsv", "rb");
        while(fgets(data, 200, opfile) != NULL) {
            char *input = malloc(255 * sizeof(char));
            char *first = firstWord(data, input);
            free(input);
            if(strcmp(first, path)==0) {
                exist = 1;
                break;
            }
            bzero(data, 200);
        }
        fclose(opfile);
        if(exist==0){
            strcpy(buffer, "File not found!\n");
            send(sd, buffer, strlen(buffer), 0);
            bzero(buffer, 1024);
        }
        else{
            char temp[200];
            strcpy(temp, "FILES/");
            strcat(temp, second);
            printf("%s\n", temp);
            int sz;
            FILE *fp = fopen(temp, "rb");
            if (fp == NULL) {
                perror("[-]Error in reading file.");
                exit(1);
            }
            
            while(fgets(data, 200, fp) != NULL) {
                if (send(sd, data, strlen(data), 0) == -1) {
                    perror("[-]Error in sending file.");
                    exit(1);
                }
                bzero(data, 200);
            }
            fclose(fp);
            printf("Filesent!\n");
        }
        free(inputCopy);
    }
}
```

Client:
```C
void *download(){
    char *inputCopy = malloc(255 * sizeof(char));
    char *second = secondWord(query, inputCopy);
    read(sock, buffer, 1024);
    if(strcmp(buffer, "Enter file name!\n")==0 || strcmp(buffer, "File not found!\n")==0){
        printf("%s", buffer);
    }
    else{
        char temp[300];
        strcpy(temp, clientPath);
        strcat(temp, second);
        FILE* filee = fopen(temp, "w");
        fprintf(filee, "%s", buffer);
        fclose(filee);
        printf("File Download Success!\n");
    }
    free(inputCopy);
}
```
Diatas merupakan sebuah fungsi untuk download pada server dan client.

![image](https://user-images.githubusercontent.com/74702068/119253899-7a5cca00-bbdd-11eb-9be7-2265d1318ba8.png)
Contoh penggunaan command download.

![image](https://user-images.githubusercontent.com/74702068/119253911-89437c80-bbdd-11eb-91f4-8cb8c0645f5a.png)
Hasil setelah download sebuah file dari server.

## Sub Soal e

## Sub Soal f

## Sub Soal g

## Sub Soal h

# Nomor 2
Crypto (kamu) adalah teman Loba. Suatu pagi, Crypto melihat Loba yang sedang kewalahan mengerjakan tugas dari bosnya. Karena Crypto adalah orang yang sangat menyukai tantangan, dia ingin membantu Loba mengerjakan tugasnya. Detil dari tugas tersebut adalah:
<ol type="a">
  <li>Membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).</li>
  <li>Membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c) (Catatan!: gunakan shared memory). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang a	da. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya matri(dari paling besar ke paling kecil) (Catatan!: gunakan thread untuk perhitungan di setiap cel). </li>
  <li>Karena takut lag dalam pengerjaannya membantu Loba, Crypto juga membuat program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command “ps aux | sort -nrk 3,3 | head -5” (Catatan!: Harus menggunakan IPC Pipes)</li>
</ol>

Note:
- Semua matriks berasal dari input ke program.
- Dilarang menggunakan system()

## Sub Soal a
Terdapat dua matrix yang dengan ordo 4x3 dan 3x6 yang mana perkalian keduanya akan menghasilkan matriks 4x6. Namun di sini hasil menggunakan array of pointer untuk shared memory.
```C
#define N 6

long long matrix1[N][N], matrix2[N][N], (*hasil)[N];
pthread_t tid[N];
```

Setelah itu dilakukan input biasa untuk matriks 1 dan 2 serta cetak tiap nilai matriks untuk memastikan nilaninya benar.
```C
for (long long i = 0; i < 4; i++)
    for (long long j = 0; j < 3; j++)
        scanf("%lld", &matrix1[i][j]);

for (long long i = 0; i < 3; i++)
    for (long long j = 0; j < 6; j++)
        scanf("%lld", &matrix2[i][j]);

for (long long i = 0; i < 4; i++)
{
    for (long long j = 0; j < 3; j++)
    {
        printf("%lld ", matrix1[i][j]);
    }
    printf("\n");
}
printf("\n");
for (long long i = 0; i < 3; i++)
{
    for (long long j = 0; j < 6; j++)
    {
        printf("%lld ", matrix2[i][j]);
    }
    printf("\n");
}
printf("\n");
```
Sebelum melakukan shared memory, perlu untuk mengatur key dan pipe agar dua program mengakses memory yang sama. Kemudian 
```C
key_t key = 1234;
long long shmid = shmget(key, sizeof(long long), IPC_CREAT | 0666);

hasil = shmat(shmid, NULL, 0);
```
Sebenarnya tidak ada instruksi untuk membuat thread, namun di sini ada 6 thread untuk melakukan perhitungan perkalian matriks. Sehingga perlu untuk membuat thread terlebih dahulu.
```C
for (long long i = 0; i < N; i++)
{
    long long err = pthread_create(&(tid[i]), NULL, &multiply, NULL);

    if (err != 0)
    {
        printf("\n can't create thread : [%s]", strerror(err));
    }
}
```
Saat thread dibuat, fungsi multiply juga dipanggil yang mana fungsi/prosedur ini akan menghitung perkaliannya.
```C
void *multiply(void *arg)
{
    pthread_t id = pthread_self();
    long long res;

    for (long long x = 0; x < N; x++)
    {
        if (pthread_equal(id, tid[x]))
        {
            for (long long i = 0; i < 4; i++)
            {
                res = 0;
                for (long long j = 0; j < 3; j++)
                    res += matrix1[i][j] * matrix2[j][x];

                hasil[i][x] = res;
            }
        }
    }
}
```
`id` merupakan id dari thread untuk menyaring agar thread bekerja pada tempat yang ditentukan. Di sini karena terdapat 6 thread, maka tiap thread akan mengisi kolom tiap baris i. Hasil perkalian matriks merupakan penjumlahan baris matriks1 x kolom matriks2. Dalam hal ini penjumlahan tersebut disimpan pada variabel res. Setelah itu hasil perkalian disimpan pada array `hasil`.

Setelah selesai, gabungkan kembali semua thread yang telah dibuat. Namun tunggu program selama beberapa saat sembari menjalankan program lain (yang ingin mengakses shared memory) serta cetak hasil perkaliannya.
```C
for (long long i = 0; i < N; i++)
{
    pthread_join(tid[i], NULL);
}

for (long long i = 0; i < 4; i++)
{
    for (long long j = 0; j < 6; j++)
    {
        printf("%lld ", hasil[i][j]);
    }
    printf("\n");
}

sleep(5);
shmdt(hasil);
shmctl(shmid, IPC_RMID, NULL);
```
![image](https://user-images.githubusercontent.com/45300477/119212449-916ac180-bae2-11eb-8290-5a161fc27cfb.png)

## Sub soal 2b
Sub soal ini diharuskan menggunakan hasil perkalian matriks sebelumnya, sehingga perlu membuat variabel dengan kriteria sama. Agar mudah akan sama persis.
```C
#define row 4
#define col 6

long long (*hasil)[col], faktorial[row][col], matrixB[row][col];

pthread_t tid[row * col];
```
Karena ingin mengakses memory yang sama, maka perlu konfigurasi yang sama dengan sebelumnya.
```C
key_t key = 1234;

long long shmid = shmget(key, sizeof(long long), IPC_CREAT | 0666);
hasil = shmat(shmid, NULL, 0);
```
Untuk memastikan bahwa akses berhasil, cetak semua nilai dari hasil.
```C
for (long long i = 0; i < row; i++)
{
    for (long long j = 0; j < col; j++)
    {
        printf("%lld ", hasil[i][j]);
    }
    printf("\n");
}
printf("\n");
```
Lalu input nilai sesuai soal.
```C
    for (long long i = 0; i < row; i++)
        for (long long j = 0; j < col; j++)
            scanf("%lld", &matrixB[i][j]);
```
Diperintahkan juga untuk menggunakan thread tiap sel, sehingga ada 24 thread yang akan dibuat.
```C
for (long long i = 0; i < row * col; i++)
{
    long long err = pthread_create(&(tid[i]), NULL, &fac, NULL);
    if (err != 0)
    {
        printf("\n can't create thread");
    }
}
```
`fac()` merupakan fungsi untuk menghitung faktorial sesuai perintah soal. Karena terdapat 24 thread, maka id akan diidentifikasi sebagai `col * i + j`:
 ```
1   2   3   4   5   6
7   8   9   10  11  12
13  14  15  16  17  18
19  20  21  22  23  24
```
Tiap sel akan dihitung dari `hasil[i][j]` sampai `min(hasil[i][j], matrixB[i][j]` sesuai soal.
```C
void *fac(void *p)
{
    pthread_t id = pthread_self();

    for (long long i = 0; i < row; i++)
    {
        for (long long j = 0; j < col; j++)
        {
            if (pthread_equal(id, tid[col * i + j]))
            {
                if (matrixB[i][j] == 0 || hasil[i][j] == 0)
                {
                    faktorial[i][j] = 0;
                }
                else
                {
                    faktorial[i][j] = 1;
                    for (long long k = 0; k < min(hasil[i][j], matrixB[i][j]); k++)
                    {
                        faktorial[i][j] *= (hasil[i][j] - k);
                    }
                }
            }
        }
    }
}
```
Setelah perhitungan faktorial selesai, gabungkan thread dan cetak nilai tiap sel untuk memastikan bahwa nilainya benar.
```C
for (long long i = 0; i < row * col; i++)
{
    pthread_join(tid[i], NULL);
}

for (long long i = 0; i < row; i++)
{
    for (long long j = 0; j < col; j++)
    {
        printf("%lld ", faktorial[i][j]);
    }
    printf("\n");
}
sleep(5);
shmctl(shmid, IPC_RMID, NULL);
```
![image](https://user-images.githubusercontent.com/45300477/119212475-c8d96e00-bae2-11eb-8562-8c7eaffcc9cf.png)

## Sub soal 2c
Terdapat 3 perintah dengan pipe, sehingga buat 2 pipe dan 3 fungsi untuk masing-masing perintah.
```C
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int pid;
int pipe1[2];
int pipe2[2];

void exec1();
void exec2();
void exec3();
```
Buat pipe terlebih dahulu, jika gagal, batalkan program dengan `exit(1)`. Kemudian buat proses baru dengan fork. Jika berhasil, panggil fungsi pertama yaitu untuk `ps aux`.
```C
if (pipe(pipe1) == -1)
{
    perror("bad pipe1");
    exit(1);
}

if ((pid = fork()) == -1)
{
    exit(1);
}
else if (pid == 0)
{
    exec1();
}
```
```C
void exec1()
{
    // output to pipe1
    dup2(pipe1[1], 1);

    close(pipe1[0]);
    close(pipe1[1]);
    // exec
    execlp("ps", "ps", "aux", NULL);
    _exit(1);
}
```
Kemudian buat juga pipe2 dan buat proses baru untuk perintah sort serta tutup pipe1 setelah digunakan untuk perintah kedua.
```C
if (pipe(pipe2) == -1)
{
    perror("bad pipe2");
    exit(1);
}

if ((pid = fork()) == -1)
{
    exit(1);
}
else if (pid == 0)
{
    exec2();
}
```
```C
void exec2()
{
    // input from pipe1
    dup2(pipe1[0], 0);
    // output to pipe2
    dup2(pipe2[1], 1);

    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    execlp("sort", "sort", "-nrk", "3,3", NULL);
    _exit(1);
}
```
Terakhir dapat dibuat langsung proses baru.
```C
if ((pid = fork()) == -1)
{
    exit(1);
}
else if (pid == 0)
{
    exec3();
}
```
```C
void exec3()
{
    // input from pipe2
    dup2(pipe2[0], 0);

    close(pipe2[0]);
    close(pipe2[1]);

    execlp("head", "head", "-5", NULL);

    _exit(1);
}
```
![image](https://user-images.githubusercontent.com/45300477/119212499-05a56500-bae3-11eb-93fa-29309195e327.png)

# Nomor 3
Seorang mahasiswa bernama Alex sedang mengalami masa gabut. Di saat masa gabutnya, ia memikirkan untuk merapikan sejumlah file yang ada di laptopnya. Karena jumlah filenya terlalu banyak, Alex meminta saran ke Ayub. Ayub menyarankan untuk membuat sebuah program C agar file-file dapat dikategorikan. Program ini akan memindahkan file sesuai ekstensinya ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.
Jika program dijalankan, program dapat:
1. Menerima argumen ``` -f ``` untuk mengkategorikan file. ``` cmd$ ./soal3 -f path/to/file1.jpg path/to/file2.zip path/to/file2/c```
2. Menerima argumen ``` -d ``` untuk mengakategorikan file yang terdapat dalam directory. ``` $ ./soal3 -d /path/to/directory/```
3. Menerima argumen ``` * ``` untuk mengkategorikan file yang berada pada working directory. ``` $ ./soal3 \* ```

```
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
```
- ```#include <sys/types.h>``` Library tipe data khusus (e.g. pid_t)
- ```#include <sys/stat.h>``` Library untuk pendeklarasian fungsi stat() dan semacamnya (e.g. fstat() dan lstat()).
- ```#include <errno.h>``` Library untuk error handling (e.g. errno).
- ```#include <stdio.h>``` Library untuk fungsi input-output (e.g. printf(), sprintf()).
- ```#include <stdlib.h>``` Library untuk fungsi umum (e.g. exit(), atoi()).
- ```#include <dirent.h>``` Library untuk merepresentasikan directory stream & struct dirent(e.g. struct dirent *entry).
- ```#include <string.h>``` Library untuk pendefinisian berbagai fungsi untuk manipulasi array karakter (e.g. strtok()).
- ```#include <ctype.h>``` Library untuk pendefinisian berbagai fungsi untuk karakter handling(e.g.tolower()).
- ```#include <unistd.h>``` Library untuk melakukan system call kepada kernel linux (e.g. fork()).
- ```#include <pthread.h>``` Library untuk operasi thread (e.g. pthread_create(), ptrhead_exit() ).

```
void getFileExtension(char *namaFile, char *returnExten) {
    char *ext = strchr(namaFile, '.');
    if (ext == NULL) {
        strcpy(returnExten, "Unknown");
    } else if (ext == namaFile) {
        strcpy(returnExten, "Hidden");
    } else {
        strcpy(returnExten, ext + 1);
    }
}
```
Fungsi tersebut bertujuan untuk mendapatkan extensi dari suatu file.

```
bool isExistAndRegFile(char *pathAwal) {
    struct stat bf;
    int exist = stat(pathAwal, &bf);
    if (exist == 0) {
        if (S_ISREG(bf.st_mode)) {
            return true;
        }
        else {
            return false;
        }
    } else {
        return false;
    }
}
```
Untuk mengecek apakah suatu file tersebut ada dan merupakan file reguler.
```

void *pindahFile(void *arg) {
    char pathAwal[PATH_MAX];
    strcpy(pathAwal, (char *)arg);

    if (isExistAndRegFile(pathAwal)) {

        const char *p = "/";
        char *a, *b;
        char full_path[PATH_MAX];
        strcpy(full_path, (char *)arg);

        char namaFile[100];

        for (a = strtok_r(full_path, p, &b); a != NULL; a = strtok_r(NULL, p, &b)) {
            memset(namaFile, 0, sizeof(namaFile));
            strcpy(namaFile, a);
        }
```
Fungsi diatas bertujuan untuk memindahkan file ke dalam folder sesuai dengan ekstensi file. Jika file tersebut ada dan merupakan reguler, maka proses pindah file akan dilanjutkan. Langkah pertama kita pisahkan dahulu pathnya menggunakan ```strtok``` berdasarkan tanda ```/``` pada path filenya. Kemudian ```memset``` 0 dan ```strcpy``` selama belum NULL. Karena nama file selalu ada di ujung path, maka kita ambil yang paling terakhir.
```
  char ext[PATH_MAX];
        getFileExtension(namaFile, ext);

        if (strcmp(ext, "Hidden") != 0 && strcmp(ext, "Unknown") != 0) {
            for (int i = 0; i < strlen(ext); i++) {
                ext[i] = tolower(ext[i]);
            }
        }
```
Mengambil ekstensi dari suatu file, kemudia di cek jika tidak hidden dan unknown maka ubah string ```ext``` menjadi lowercase agar tidak ada dua folder ekstensi yaitu uppercase dan lowercase.
```

        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd() error");
            return (void *)0;
        }

        char destinationDir[PATH_MAX];
        sprintf(destinationDir, "%s/%s", cwd, ext);
        mkdir(destinationDir, 0777);

        char destination[PATH_MAX];
        sprintf(destination, "%s/%s/%s", cwd, ext, namaFile);
        rename(pathAwal, destination);
        return (void *)1;
    }

    else {
        return (void *)0;
    }
}
```
Selanjutnya, kita buat direktori ekstensi tujuan dengan perintah ```mkdir``` dan menggabungkan ```cwd``` dan ```ext``` menggunakan sprintf. Kemudian renam nama path file dengan rename (sama seperti memindahkan file).
```
int listFilesFromDirectory(char *pathAwal, int *jumlahFile) {
    char path[PATH_MAX];
    struct dirent *dp;
    DIR *dir = opendir(pathAwal);

    if (!dir) {
        return 0;
    }

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            char full_path[PATH_MAX];
            sprintf(full_path, "%s/%s", pathAwal, dp->d_name);
            if (isExistAndRegFile(full_path)) {
                sprintf(listFile[*jumlahFile], "%s", full_path);
                *jumlahFile += 1;
            }

            strcpy(path, pathAwal);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesFromDirectory(path, jumlahFile);
        }
    }

    closedir(dir);
    return 1;
}
```
Fungsi diatas berfungsi untuk menglist nama path file-file dalam direktori secara rekursif. Pertama, mencoba membuka direktori dengan perindah ```opendir``` untuk mengecek apakah dia adalah direktori atau bukan. Jika iya, maka buka direktori dengan perintah ```readdir```. Selanjutnya, gunakan while untuk menglist file-file yang terdapat dalam direktori tersebut, menggunakan ```dp->d_name```. Kemudian panggil fungsi ```listFilesFromDirectory()``` lagi untuk menglist file-file secara rekursif, jika dia memang merupakan folder.
```
char listFile[2048][PATH_MAX];

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Butuh argumen.\n");
        exit(1);
        return 0;
    }
```
Agar program selalu menerima argumen.
```
char pathAwal[PATH_MAX];
```
```pathAwal``` merupakan working directory.
```
 if (strcmp(argv[1], "*") == 0) {
        if (getcwd(pathAwal, sizeof(pathAwal)) == NULL) {
            perror("getcwd() error");
            return 0;
        }
```
Jika argumen program adalah ```*```, cek apakah terdapat string path working directory.
```
    } else if (strcmp(argv[1], "-f") == 0) {
        if (argc < 3) {
            printf("Butuh argumen minimal 1 path menuju file.\n");
            return 0;
        }

        pthread_t tid[argc - 2];

        for (int i = 2; i < argc; i++) {
            pthread_create(&(tid[i - 2]), NULL, pindahFile, (void *)argv[i]);
        }

        for (int i = 0; i < argc - 2; i++) {
            int isBerhasilJoin;
            void *ptr;
            pthread_join(tid[i], &ptr);
            isBerhasilJoin = (int)ptr;

            if (isBerhasilJoin) {
                printf("File %d : Berhasil Dikategorikan\n", i + 1);
            } else {
                printf("File %d : Sad, gagal :(\n", i + 1);
            }
        }

        return 0;
```
Jika argumen yang diinput adalah ```-f```. Disini terdapat cegatan argumen. Selain itu juga membuat thread, 1 thread untuk 1 file. Kemudian thread dijoin agar thread main tidak selesai lebih dulu (karena jika main selesai, maka proses main akan selesai dan thread lain tidak akan berjalan).
```
    } else if (strcmp(argv[1], "-d") == 0) {
        if (argc == 3) {
            strcpy(pathAwal, argv[2]);           
        } else {
            printf("Argumen hanya 1 untuk direktori.\n");
            return 0;
        }
```
Cegatan argumen untuk argumen ```-d```.
```
    } else {
        printf("Argumen tidak valid.\n");
    }

    int jumlahFile = 0;
    if (!listFilesFromDirectory(pathAwal, &jumlahFile)) {
        printf("Yah, gagal disimpan :(\n");
        return 0;
    }

    pthread_t tid[jumlahFile];
    for (int i = 0; i < jumlahFile; i++) {
        pthread_create(&(tid[i]), NULL, pindahFile, (void *)listFile[i]);
    }

    for (int i = 0; i < jumlahFile; i++) {
        void *ptr;
        pthread_join(tid[i], &ptr);
    }

    if (strcmp(argv[1], "-d") == 0) {
        printf("Direktori sukses disimpan!\n");
    }

    return 0;
}
```
Untuk join thread argumen ```-d``` dan ```*```. Menggunakan fungsi ```listFilesFromDirectory()``` untuk mendapatkan list path file-file dalam direktory secara rekursif. List path file disimpan pada array global ```listFile[]```.
Screenshot saat program dijalankan:
- Kondisi awal folder
![kondisi folder awal](https://user-images.githubusercontent.com/67305615/119248595-63f24680-bbbc-11eb-97cc-a3faead663d7.JPG)
- Menjalankan program dengan perintah ```-f```
![-f](https://user-images.githubusercontent.com/67305615/119248606-7ec4bb00-bbbc-11eb-895a-1eaafb6693a8.JPG)
- Kondisi folder setelah perintah ```-f``` dijalankan
![kondisi folder setelah -f](https://user-images.githubusercontent.com/67305615/119248620-9603a880-bbbc-11eb-8322-14537bd3ff41.JPG)
- Merename folder txt menjadi fika, kemudian jalankan perintah ```-d```
![rename folder](https://user-images.githubusercontent.com/67305615/119248643-bb90b200-bbbc-11eb-8106-54161b33afa4.JPG)
![-d](https://user-images.githubusercontent.com/67305615/119248647-c21f2980-bbbc-11eb-91ec-6f99612ac5ce.JPG)
- Kondisi folder setelah perintah ```-d``` dijalankan
![kondisi folder setelah -d](https://user-images.githubusercontent.com/67305615/119248657-d4996300-bbbc-11eb-8872-9ee6bfad1087.JPG)
- Menjalankan program dengan perintah ```*```
![bintang](https://user-images.githubusercontent.com/67305615/119248666-ee3aaa80-bbbc-11eb-9515-b9c0df9b8a20.JPG)
- Kondisi folder setelah perintah ```*``` dijalankan
![kondisi folder setelah bintang](https://user-images.githubusercontent.com/67305615/119248681-fd215d00-bbbc-11eb-9cad-9b8d58354fe2.JPG)
![lanjutan](https://user-images.githubusercontent.com/67305615/119248688-05799800-bbbd-11eb-9180-aa4de713fb17.JPG)






