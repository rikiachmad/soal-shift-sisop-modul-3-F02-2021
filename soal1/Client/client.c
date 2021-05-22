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
char clientPath[] = "/home/riki/Praktikum3/Client/";

void trimTrailing(char * str)
{
    int index, i;

    /* Set default index */
    index = -1;

    /* Find last index of non-white space character */
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }

        i++;
    }

    /* Mark next character to last non-white space character as NULL */
    str[index + 1] = '\0';
}

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

char* secondWord(char str[], char inputCpy[]){
    const char del[10] = " ";
    strcpy(inputCpy, str);
    char * ptr = strtok(inputCpy, del);
    return strtok(NULL, del); 
}

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

void *delete(){
    read(sock, buffer, 1024);
    printf("%s", buffer);

}

void *see(){
    bzero(buffer, 1024) ;
    read(sock, buffer, 1024) ;
    printf("%s\n", buffer) ;
    bzero(buffer, 1024) ;
}

void *find(){
    bzero(buffer, 1024) ;
    read(sock, buffer, 1024) ;
    printf("%s\n", buffer) ;
    bzero(buffer, 1024) ;
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
    read(sock, buffer, 1024) ;
    printf("%s\n", buffer) ;
    bzero(buffer, 1024);
    printf("Main Menu\n1.SignUp\n2.Login\n");
    for(;;){
        scanf(" %[^\n]", query);
        trimTrailing(query);
        send(sock , query , strlen(query) , 0 );
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
                pthread_create(&(thread),NULL,&download,NULL);
            }else if(strncmp(query, "delete", 6)==0){
                pthread_create(&(thread),NULL,&delete,NULL);
            }else if(strcmp(query, "see")==0){
                pthread_create(&(thread),NULL,&see,NULL);
            }else if(strncmp(query, "find", 4)==0){
                pthread_create(&(thread),NULL,&find,NULL);
            }else{
                pthread_create(&(thread),NULL,&err,NULL);
            }
        }
        pthread_join(thread, NULL);
    }
    close(sock);
    return 0;
}
