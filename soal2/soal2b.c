#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define row 4
#define col 6

int (*hasil)[col],faktorial[row][col], matrixB[row][col];

pthread_t tid[row*col];
int min(int a, int b){
  return a<b?a:b;
}
void* fac(void* p) {
   pthread_t id = pthread_self();

   for(int i=0; i<row; i++){
     for(int j=0; j<col; j++){
       if(pthread_equal(id, tid[col*i + j])){
         if(matrixB[i][j] == 0 || hasil[i][j]==0){
           faktorial[i][j] = 0;
         }
         else{
           faktorial[i][j] = 1;
           for(int k = 0; k<min(hasil[i][j], matrixB[i][j]); k++){
             faktorial[i][j] *= (hasil[i][j]-k);
           }
         }
       }
     }
   }
	// for(int i=0; i<col; i++)
	// 	if(pthread_equal(id, tid[i])){
  //           for(int j=0 ; j < 4;j++)
  //               for(int k=(int)hasil[j][4-i] ; k>0 ; k--){
  //                   faktorial[j][4-i]+=k;
  //               }
  //       }
}

int main(){
    key_t key = 1234;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    hasil = shmat(shmid, NULL, 0);

    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++)
        {
            printf("%3d ", hasil[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(int i=0; i<row; i++)
      for(int j=0; j<col; j++)
        scanf("%d", &matrixB[i][j]);

   	for(int i=0; i<row*col; i++){
        int err=pthread_create(&(tid[i]), NULL, &fac, NULL);
		if(err!=0)
		{
			printf("\n can't create thread");
		}
	}

    for(int i=0; i<row*col; i++){
        pthread_join(tid[i], NULL);
    }

    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++)
        {
            printf("%3d ", faktorial[i][j]);
        }
        printf("\n");
    }
    sleep(5);
        shmctl(shmid, IPC_RMID, NULL);
}
