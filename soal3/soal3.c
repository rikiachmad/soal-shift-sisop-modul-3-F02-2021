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

char *getExtensionFile(char *FileName, char buff[]) {
  	char buffFileName[1339];
  	char *token = strtok(FileName, "/");
  	
 	while (token != NULL) {
    	sprintf(buffFileName, "%s", token);
    	token = strtok(NULL, "/");
  	}
  
  	token = strtok(buffFileName, ".");
  	int sum = 0;
  	while(token != NULL) {
    	sum++;
    	sprintf(buff, "%s", token);
    	token = strtok(NULL, ".");
  	}
  	
  	if (sum < 2) {
    	strcpy(buff, "unknown");
	}

  	return buff;
}

char *getNameFile(char *FileName, char buff[]) {
  	char *token = strtok(FileName, "/");
  	
	while (token != NULL) {
    	sprintf(buff, "%s", token);
    	token = strtok(NULL, "/");
  	}
}


void dirCheck(char buff[]) {
  	DIR *dr = opendir(buff);
  	if (ENOENT == errno) {
    	mkdir(buff, 0775);
    	closedir(dr);
  	}
}

struct args {
  	char *buffer;
};

void *routine(void* arg) {
  	char buffExt[100];
  	char buffFileName[1339];
  	char buffFrom[1339];
  	char buffTo[1339];
  	char cwd[1339];
  	getcwd(cwd, sizeof(cwd));
  	strcpy(buffFrom, (char *) arg);

  	if (access(buffFrom, F_OK) == -1) {
    	printf("File %s tidak ada\n", buffFrom);
    	pthread_exit(0);
  	}
  	
	DIR* dir = opendir(buffFrom);
  	if (dir) {
    	printf("file %s berupa folder\n", buffFrom);
    	pthread_exit(0);
  	}
  	closedir(dir);

  	getNameFile(buffFrom, buffFileName);
  	strcpy(buffFrom, (char *) arg);

  	getExtensionFile(buffFrom, buffExt);
  	
  	for (int i = 0; i < sizeof(buffExt); i++) {
    	buffExt[i] = tolower(buffExt[i]);
  	}
  	
  	strcpy(buffFrom, (char *) arg);

  	dirCheck(buffExt);

  	sprintf(buffTo, "%s/%s/%s", cwd, buffExt, buffFileName);
  	rename(buffFrom, buffTo);

  	pthread_exit(0);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("Argumen kurang\n");
    exit(1);
  }
  
  if (strcmp(argv[1], "-f") != 0 && strcmp(argv[1], "*") != 0 && strcmp(argv[1], "-d")) {
    printf("Argumen tidak ada\n");
    exit(1);
  }

  if (strcmp(argv[1], "-f") == 0) {
  	if (argc <= 2) {
      printf("Argumen salah\n");
      exit(1);
    }

    pthread_t tid[argc-2];
    int m=2;
    while(m < argc) {
      	pthread_create(&tid[m-2], NULL, &routine, (void *)argv[m]);
      	m++;
    }
    
    int n=2;
    while(n < argc) {
    	pthread_join(tid[n-2], NULL);
    	n++;
    }
    exit(0);
  }

  char *directory;
  if (strcmp(argv[1], "*") == 0) {
    if (argc != 2) {
      printf("Argument salah\n");
      exit(1);
    }
    char buff[1339];
    getcwd(buff, sizeof(buff));
    directory = buff;
  }

  if (strcmp(argv[1], "-d") == 0) {
    if (argc != 3) {
      printf("Argument salah\n");
      exit(1);
    }
    DIR* dir = opendir(argv[2]);
    if (dir) {
      directory = argv[2];
    } else if (ENOENT == errno) {
      printf("Directory tidak ada\n");
      exit(1);
    }
    closedir(dir);
  }

  int file_sum = 0;
  DIR* dir = opendir(directory);
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) {
      file_sum++;
    }
  }
  closedir(dir);

  pthread_t tid[file_sum];
  char buff[file_sum][1339];
  int iterasi = 0;

  dir = opendir(directory);
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) {
      sprintf(buff[iterasi], "%s/%s", directory, entry->d_name);
      iterasi++;
    }
  }
  closedir(dir);
  
  int i=0;
  while(i < file_sum) {
    char  *test = (char*)buff[i];
    printf("%s\n", test);
    pthread_create(&tid[i], NULL, &routine, (void *)test);
    i++;
  }
	
  int j=0;
  while(j < file_sum) {
    pthread_join(tid[j], NULL);
    j++;
  }

}
