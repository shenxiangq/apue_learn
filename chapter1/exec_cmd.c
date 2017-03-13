#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);

#define MSG "OMG , I catch the signal SIGINT\n"
#define MSG_END "OK,finished process signal SIGINT\n"
int do_heavy_work()
{
        int i ; 
            int k;
                srand(time(NULL));

                    for(i = 0 ; i < 100000000;i++)
                            {
                                        k = rand()%1234589;
                                            }

}

void signal_handler(int signo)
{
        write(2,MSG,strlen(MSG));
            do_heavy_work();
                write(2,MSG_END,strlen(MSG_END));
}

int main(void) {
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("sig:%d", SIGINT);
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;
        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) {
            execlp(buf, buf, (char *)0);
            printf("%s\n", buf);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");
    }
    fgets(buf, MAXLINE, stdin);
    printf("finished\n");
    exit(0);
}


void sig_int(int signo) {
    printf("interrupt %d\n%% ", signo);
}

