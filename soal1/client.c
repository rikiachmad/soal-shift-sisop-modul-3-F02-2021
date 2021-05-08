#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <sys/stat.h>
#include <netinet/in.h> 
#include <sys/time.h>
#include <string.h>
#define PORT 8080
int sock = 0, valread;
int status;
char query[80] = {0};
pthread_t thread;
char buffer[1024];
struct sockaddr_in serv_addr;
int wait=0;


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

void* err(){
    bzero(buffer, 1024);
    read(sock, buffer, 1024);
    printf("%s\n", buffer);
    bzero(buffer, 1024);
}

void send_file(FILE *fp){
  int n;
  char data[200] = {0};

  while(fgets(data, 200, fp) != NULL) {
    if (send(sock, data, strlen(data), 0) == -1) {
      perror("[-]Error in sending file.");
      exit(1);
    }
    bzero(data, 200);
  }
  fclose(fp) ;
}

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

void *download(){

}

void *delete(){

}

void *see(){

}

void *find(){
    
}

int main(int argc, char const *argv[]) {
   if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
 
    read(sock, buffer, 1024);
    printf("%s\n", buffer);
    bzero(buffer, 1024);
    printf("Main Menu\n1.SignUp\n2.Login\n");
    for(;;){
        scanf(" %s", query);
        send(sock , query , strlen(query) , 0 );\
        if(strcmp(query, "1")==0){
            pthread_create(&(thread),NULL,&regist,NULL);
        }else if(strcmp(query, "2")==0){
            pthread_create(&(thread),NULL,&regist,NULL);
        }else if(status==0){
            pthread_create(&(thread),NULL,&err,NULL);
        }else{
            if(strcmp(query, "add")==0){
                pthread_create(&(thread),NULL,&add,NULL);
            }else if(strncmp(query, "download", 8)==0){
                pthread_create(&(thread),NULL,&add,NULL);
            }else if(strncmp(query, "delete", 6)==0){
                pthread_create(&(thread),NULL,&add,NULL);
            }else if(strcmp(query, "see")==0){
                pthread_create(&(thread),NULL,&add,NULL);
            }else if(strncmp(query, "find", 4)==0){

            }
            }
        pthread_join(thread, NULL);
    }
    close(sock);
    return 0;
}
