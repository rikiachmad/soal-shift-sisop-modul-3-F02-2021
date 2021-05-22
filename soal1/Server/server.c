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
#define PORT 8080
#define MAX 80
int server_fd, new_socket, valread, sdMax;
int master_socket , addrlen , new_socket , client_socket[30] , max_clients = 30 , activity, i , valread , sd;  
int max_sd;  
int someoneConnected, status;
char buffer[1024];
char user[50];
char serverPath[] = "/home/riki/Praktikum3/Server/";
void swapQueue() {
    int i ;
    for (i = 1 ; i < max_clients ; i++) {
        int temp = client_socket[i];
        client_socket[i] = client_socket[i-1];
        client_socket[i-1] = temp;
    }
}

int checkCreds(char cred[]){
    FILE* file = fopen("akun.txt", "r");
    char check[50];
    while(fgets(check, 50, file)) {
        if (!strcmp(check, cred)) {
            fclose(file) ;
            return 1 ;
        }
    }
    fclose(file) ;
    return 0 ;
}

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

void update(char msg[]) {
    FILE* file = fopen("akun.txt", "a") ;
    fputs(msg, file);
    fclose(file);
}

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

void* err(){
    strcpy(buffer, "Invalid Command\n") ;
    send(sd, buffer, strlen(buffer), 0) ;
    bzero(buffer, 1024);
}

void isSafe(){
     if ((valread = read( sd , buffer, 1024)) == 0)  
        {                  
            close( sd );
            someoneConnected = 0;
            status = 0;
            client_socket[i] = 0;
            swapQueue();
        }
}

void write_file(char path[]){
  int n;
  FILE *fp;

  fp = fopen(path, "w");
  while (1) {
    n = recv(sd, buffer, 1024, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, 1024);
  }
  return;
}

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

char* secondWord(char str[], char inputCpy[]){
    const char del[10] = " ";
    strcpy(inputCpy, str);
    char * ptr = strtok(inputCpy, del);    
    return strtok(NULL, del); 
}
char* firstWord(char str[], char inputCpy[]){
    char del[] = "\t";
    strcpy(inputCpy, str);
    return strtok(inputCpy, del);  
}

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

void *delete(){
    if(strcmp(buffer, "delete")==0){
        strcpy(buffer, "Enter file name!\n");
        send(sd, buffer, strlen(buffer), 0);
        bzero(buffer, 1024);
    }else{
        char *inputCopy = malloc(255 * sizeof(char));
        char *second = secondWord(buffer, inputCopy);
        int exist = 0;
        char path[400];
        strcpy(path, serverPath);
        strcat(path, "FILES/");
        strcat(path, second);
        char data[400];
        FILE *opfile = fopen("files.tsv", "rb");
        FILE* filee = fopen("tmp.tsv", "w");
        char temp[500];
        while(fgets(data, 400, opfile)) {
            char *input = malloc(255 * sizeof(char));
            char *first = firstWord(data, input);
            if(strcmp(first, path)) {
                fprintf(filee, "%s", data);
            }
            free(input);
            bzero(data, 200);
        }
        fclose(opfile);
        fclose(filee);
        remove("files.tsv");
        rename("tmp.tsv", "files.tsv");

        char new[100] ;
        strcpy(new, serverPath);
        strcat(new, "FILES/old-");
        strcat(new, second);

        rename(path, new);

        strcpy(buffer, "Delete Success\n");
        send(sd, buffer, strlen(buffer), 0);
        bzero(buffer, 1024);
        FILE* log = fopen("running.log", "a") ;
        fprintf(log, "Hapus : %s %s\n", second, user) ;
        fclose(log) ;
        free(inputCopy);
    }
}
void tab(char msg[], char a[], char b[], char c[]) {
    int i = 0 ;
    char* check ;
    while (check = strtok_r(msg, "\t", &msg)) {
        if (i == 0) strcpy(a, check) ;
        else if (i == 1) strcpy(b, check) ;
        else if (i == 2) strncpy(c, check, strlen(check) - 1) ;
        i++ ;
    }
}

void slash(char msg[], char a[]) {
    int i = 0 ;
    char* check ;
    while (check = strtok_r(msg, "/", &msg)) {
        strcpy(a, check) ;
        i++ ;
    }
}

void dot(char msg[], char a[], char b[]) {
    int i = 0 ;
    char* check ;
    if (strchr(msg, '.')) {
        char* ext = strchr(msg, '.') + 1 ;
        strcpy(b, ext) ;
    }
    while (check = strtok_r(msg, ".", &msg)) {
        if (i == 0) strcpy(a, check) ;
        
        i++ ;
    }
}

void *see(){
    FILE* file = fopen("files.tsv", "r");
    char line[1024];
    char publisher[255] = {0};
    char year[10] = {0};
    char path[511] = {0};
    char fileName[63] = {0};
    char name[50] = {0};
    char extension[10] = {0};
    char savePath[511] = {0};
    bzero(buffer, 1024);
    int i = 0;
    while(fgets(line, 1024, file)) {
        if (i) strcat(buffer, "\n\n");
        tab(line, path, publisher, year);
        strcpy(savePath, path);
        slash(path, fileName);
        dot(fileName, name, extension);
        strcat(buffer, "Nama: ");
        strcat(buffer, name);
        strcat(buffer, "\nPublisher: ");
        strcat(buffer, publisher);
        strcat(buffer, "\nTahun publishing: ");
        strcat(buffer, year);
        strcat(buffer, "\nEkstensi file: "); 
        strcat(buffer, extension) ;
        strcat(buffer, "\nFile path: ");
        strcat(buffer, savePath);
        i++;
    }
    send(sd, buffer, strlen(buffer), 0);
    bzero(buffer, 1024);
}
void *find(){
    if(strcmp(buffer, "find")==0) {
        strcpy(buffer, "Enter file name!\n");
        send(sd, buffer, strlen(buffer), 0);
        bzero(buffer, 1024);
    }
    else {
        char *inputCopy = malloc(255 * sizeof(char));
        char *second = secondWord(buffer, inputCopy);
        FILE* file = fopen("files.tsv", "r");
        char line[1024];
        char publisher[255] = {0};
        char year[10] = {0};
        char path[511] = {0};
        char fileName[63] = {0};
        char name[50] = {0};
        char extension[10] = {0};
        char savePath[511] = {0};
        bzero(buffer, 1024);
        
        int i = 0;
        while(fgets(line, 1024, file)) {
                
            tab(line, path, publisher, year);
            strcpy(savePath, path);
            slash(path, fileName);
            dot(fileName, name, extension);

            char searchName[63], searchExt[10];
            dot(second, searchName, searchExt);
            if (!strstr(name, searchName)) continue;

            if (i) 
                strcat(buffer, "\n\n");

            strcat(buffer, "Nama: ");
            strcat(buffer, name);
            strcat(buffer, "\nPublisher: "); 
            strcat(buffer, publisher);
            strcat(buffer, "\nTahun publishing: ");
            strcat(buffer, year);
            strcat(buffer, "\nEkstensi file: ");
            strcat(buffer, extension);
            strcat(buffer, "\nFile path: ");
            strcat(buffer, savePath);
            i++;
        }

        if (!i) {
            strcpy(buffer, "File not found\n");
        }
        send(sd, buffer, strlen(buffer), 0);
        bzero(buffer, 1024);
        free(inputCopy);
    }
}

int main(int argc, char const *argv[]) {

    // Credit to Akshat Sinha From Geeks For Geeks :)
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    fd_set readfds;
    //initialise all client_socket[] to 0 so not checked 
    for (i = 0; i < max_clients; i++)  
    {  
        client_socket[i] = 0;  
    }  
      
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
     
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  
         
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection 
    addrlen = sizeof(address);  
    puts("Waiting for connections ...");  
         
    FILE *outfile = fopen("akun.txt", "ab+");
    FILE *fp = fopen("files.tsv", "ab+");
    mkdir("FILES",0777);
    fclose(outfile);
    for(;;){

        FD_ZERO(&readfds);  
     

        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
             

        for ( i = 0 ; i < max_clients ; i++)  
        {  
            sd = client_socket[i];  
                 

            if(sd > 0)  
                FD_SET( sd , &readfds);  
            if(sd > max_sd)  
                max_sd = sd;  
        }  
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, 
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }
            
            char *message = "Connected..\n";

            //send new connection greeting message 
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )  
            {  
                perror("Error Sending Message\n");  
            }
                 
            //add new socket to array of sockets 
            for (i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket;  
                    break;  
                }  
            }  
        }
             
        sd = client_socket[i];
        someoneConnected = 1;
        while(someoneConnected>0){
            isSafe();
            pthread_t thread;
            if(strcmp(buffer, "1")==0){
                pthread_create(&(thread),NULL,&regist,NULL);
            }else if(strcmp(buffer, "2")==0){
                pthread_create(&(thread),NULL,&login,NULL);
            }else if(status==0){
                pthread_create(&(thread),NULL,&err,NULL);
            }else{
                if(strcmp(buffer, "add")==0){
                    pthread_create(&(thread),NULL,&add,NULL);
                }else if(strncmp(buffer, "download", 8)==0){
                    pthread_create(&(thread),NULL,&download,NULL);
                }else if(strncmp(buffer, "delete", 6)==0){
                    pthread_create(&(thread),NULL,&delete,NULL);
                }else if(strcmp(buffer, "see")==0){
                    pthread_create(&(thread),NULL,&see,NULL);
                }else if(strncmp(buffer, "find", 4)==0){
                    pthread_create(&(thread),NULL,&find,NULL);
                }else{
                    pthread_create(&(thread),NULL,&err,NULL);
                }
            }
            pthread_join(thread, NULL);
        }
    }

    close(server_fd);
    return 0;
}



