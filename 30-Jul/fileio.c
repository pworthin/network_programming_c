#include "helper.h"

void directoryTrav(int cliSock, char *buffer){

    char *home;
    home = getenv("HOME");
    struct dirent **directory;
    int n = scandir(home, &directory, NULL, alphasort);
    if(n < 0){

        perror("Scandir");
        //exit(EXIT_FAILURE);
        stackTrace();
    }

    while(n--){
        snprintf(buffer, BUFFER_SIZE,"%s\n", directory[n]->d_name);
        send(cliSock, buffer, strlen(buffer),0);
        send(cliSock, "\n", 1, 0);
        free(directory[n]);
    }
    free(directory);
}


