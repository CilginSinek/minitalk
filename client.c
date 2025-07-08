#include <unistd.h>

void send_char(pid_t pid, char c) {
    int bit;
    int i;

    i = 0;
    while (i < 8) {
        bit = (c >> i) & 1;
        if (bit == 0)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(10);
        i++;
    }
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    char *str;

    if(argc == 3)
    {
        pid = atoi(argv[1]);
        str = argv[2];
        while (*str)
        {
            send_char(pid, *str);
            str++;
        }
    }
    return 0;
}
