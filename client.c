#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "minitalk.h"

void    signal_handler(int sig)
{
    static int i;
    printf("k");
    if(sig == SIGUSR1)
    {
        printf("%i\n", i);
        i = 0;
        exit(0);
    }
    else if(sig == SIGUSR2)
        i++;
}

void send_char(int pid, char c)
{
    int bit;
    int i;

    i = 0;
    while (i < 8) {
        bit = (c >> (7 - i)) & 1;
        if (bit == 0)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(300);
        i++;
    }
}

int main(int argc, char const *argv[])
{
    int pid;
    char *str;
    struct sigaction sa;

    if(argc == 3)
    {
        sa.sa_handler = signal_handler;
        sigemptyset(&sa.sa_mask);
        sigaction(SIGUSR1, &sa, NULL);
        sigaction(SIGUSR2, &sa, NULL);
        pid = ft_atoi(argv[1]);
        str = (char *)(argv[2]);
        while (*str)
        {
            send_char(pid, *str);
            str++;
        }
        while (1)
            pause();
    }
    return 0;
}
