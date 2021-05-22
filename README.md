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

## Sub Soal b

## Sub Soal c

## Sub Soal d

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
