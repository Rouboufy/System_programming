#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int main(int ac, char *const *av){

 
    int wstatus;
    int i = 1;
    pid_t cpid, w;

    if (ac == 1){
        printf("%s","You need to enter at least one argument");
        return(EXIT_FAILURE);
    }
    if (ac > 2) {
        printf("%s", "This program take only one argument either '--help' or 'lsblk'");
        return(EXIT_FAILURE);
    }


    while(av[i] != NULL){
        int helper = strcmp(av[i], "--help");
        if (helper == 0){
            printf("%s", "./program 'lsblk'");
            _exit(EXIT_SUCCESS);
        }
        i++;
    }
    cpid = fork();
    if (cpid == -1){
        perror("fork");
        _exit(EXIT_FAILURE);
    }

    if (cpid == 0){
        printf("Child PID is %jd\n", (intmax_t) getpid());
        if (ac == 2){
            int command = strcmp(av[1], "lsblk");
            if (command == 0){
                execvp("lsblk", &av[1]);
                perror("execvp");
                _exit(EXIT_FAILURE);
            }
            else{
                fprintf(stderr, "Unexpected input: %s\n", av[1]);
                _exit(EXIT_FAILURE);
            }
        }
    }
    else {

        w = waitpid(cpid, &wstatus, 0);
        if (w == -1){
            perror("Child waiting failed");
            return WEXITSTATUS(wstatus);
        }
        if (WIFEXITED(wstatus))
            return WEXITSTATUS(wstatus);
        else if (WIFSIGNALED(wstatus))
            return WTERMSIG(wstatus);
    }
}
