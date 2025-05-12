#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "treasure_hub.h"

void calculate_scores_with_pipe(){
    const char *hunts[] = { "game1", "game2", "game3" };
    int num_hunts = sizeof(hunts) / sizeof(hunts[0]);

    for (int i = 0; i < num_hunts; i++) {
        printf("\n--- Scoruri pentru %s ---\n", hunts[i]);
        
        if(pipe(pipe_fd) < 0){
            perror("Eroare la crearea pipe-ului\n");
            exit(-1);
        }

        pid_t pid = fork();

        if(pid < 0){
            perror("Eroare creeare proces fiu!\n");
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            exit(-1);
        }

        if(pid == 0){
            close(pipe_fd[0]);
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
            execl("./calculate_scores", "calculate_scores", hunts[i], NULL);
            perror("Eroare la execl monitor!\n");
            exit(1);
        }

        close(pipe_fd[1]);
        char buf[256];
        ssize_t n;
        while ((n = read(pipe_fd[0], buf, sizeof(buf) - 1)) > 0) {
            buf[n] = '\0';
            fputs(buf, stdout);
        }
        close(pipe_fd[0]);
        waitpid(pid, NULL, 0);
    }   

}