#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define M 20
#define N 6

long long matrix1[N][N], matrix2[N][N], (*hasil)[N];
pthread_t tid[N];

pid_t child;


void *multiply(void *arg){
  pthread_t id = pthread_self();
	long long res;

  for(long long x = 0; x < N; x++){
    if(pthread_equal(id,tid[x])){
      for (long long i = 0; i < 4; i++) {
        res = 0;
        for(long long j = 0; j < 3; j++)
          res += matrix1[i][j]*matrix2[j][x];

        hasil[i][x] = res;
      }
    }

  }
	// if(pthread_equal(id, tid[0])){
  //     for (int i=0; i<4; i++) {
  //       res = 0;
  //       for(int j=0; j<3; j++)
  //         res += matrix1[i][j]*matrix2[j][0];
  //
  //       hasil[i][0] = res;
  //     }
  //   }
  //   else if(pthread_equal(id, tid[1])){
  //     for (int i=0; i<4; i++) {
  //       res = 0;
  //       for(int j=0; j<3; j++)
  //         res += matrix1[i][j]*matrix2[j][1];
  //
  //       hasil[i][1] = res;
  //     }
  //   }
  //   else if(pthread_equal(id, tid[2])){
  //     for (int i=0; i<4; i++) {
  //       res = 0;
  //       for(int j=0; j<3; j++)
  //         res += matrix1[i][j]*matrix2[j][2];
  //
  //       hasil[i][2] = res;
  //     }
  //   }
  //   else if(pthread_equal(id, tid[3])){
  //     for (int i=0; i<4; i++) {
  //       res = 0;
  //       for(int j=0; j<3; j++)
  //         res += matrix1[i][j]*matrix2[j][3];
  //
  //       hasil[i][3] = res;
  //     }
  //   }
  //   else if(pthread_equal(id, tid[4])){
  //     for (int i=0; i<4; i++) {
  //       res = 0;
  //       for(int j=0; j<3; j++)
  //         res += matrix1[i][j]*matrix2[j][4];
  //
  //       hasil[i][4] = res;
  //     }
  //   }
  //   else{
  //     for (int i=0; i<4; i++) {
  //       res = 0;
  //       for(int j=0; j<3; j++)
  //         res += matrix1[i][j]*matrix2[j][5];
  //
  //       hasil[i][5] = res;
  //     }
  //   }
}

int main(){
	key_t key = 1234;

	long long shmid = shmget(key, sizeof(long long), IPC_CREAT | 0666);

  for(long long i=0; i<4; i++)
    for(long long j=0; j<3; j++)
      scanf("%lld", &matrix1[i][j]);

  for(long long i=0; i<3; i++)
    for(long long j=0; j<6; j++)
      scanf("%lld", &matrix2[i][j]);

	for(long long i=0; i<4; i++){
		for(long long j=0; j<3; j++){
			printf("%lld ", matrix1[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(long long i=0; i<3; i++){
		for(long long j=0; j<6; j++){
			printf("%lld ", matrix2[i][j]);
		}
		printf("\n");
	}
	printf("\n");

  // for(int i = 0; i<4; i++){
  //   for(int j = 0; j<6; j++){
  //     int res = 0;
  //     for(int k = 0; k<3; k++){
  //       res += matrix1[i][k]*matrix2[k][j];
  //     }
  //
  //     hasil[i][j] = res;
  //   }
  // }

  hasil =  shmat(shmid,NULL,0);
	for(long long i=0; i<N; i++){
        long long err=pthread_create(&(tid[i]), NULL, &multiply, NULL);

		if(err!=0)
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
	}

	for(long long i=0; i<N; i++){
		pthread_join(tid[i], NULL);
	}

    for(long long i=0; i<4; i++){
        for(long long j=0; j<6; j++)
        {
            printf("%lld ", hasil[i][j]);
        }
        printf("\n");
    }

 sleep(5);
 shmdt(hasil);
 shmctl(shmid, IPC_RMID, NULL);
}
