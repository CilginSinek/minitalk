#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void string_handler(int sig, siginfo_t *info, void *context)
{
    static int bit_index;
    static char character;

    (void)context;
    character |= (sig == SIGUSR2);
    bit_index++;
    if (bit_index == 8)
    {
        bit_index = 0;
        if (character == '\0')
        {
            kill(info->si_pid, SIGUSR2);
            character = 0;
            return ;
        }
        else
            write(1, &character, 1);
        character = 0;
        kill(info->si_pid, SIGUSR2);
    }
    else
        character <<= 1;
}

int main(void)
{
    struct sigaction saction;

    pid_t pid;
    int i;

    pid = getpid();
    printf("%d\n", pid);
    saction.sa_flags = SA_SIGINFO;
    saction.sa_sigaction = string_handler;
    sigemptyset(&saction.sa_mask);
    sigaction(SIGUSR1, &saction, NULL);
    sigaction(SIGUSR2, &saction, NULL);
    while(1)
        pause();
    return 0;
}