#include "ipc.h"

void send_message(int pid, char *message)
{
    int letter;
    int i;

    letter = 0;
    while (message[letter])
    {
        i = -1;
        while (++i < 8)
        {
            if (((unsigned char)(message[letter] >> (7 - i)) & 1) == 0)
                kill(pid, SIGUSR1);
            else if (((unsigned char)(message[letter] >> (7 - i)) & 1) == 1)
                kill(pid, SIGUSR2);
            usleep(50);
        }
        letter++;
    }
    i = 0;
    while (i++ < 8)
    {
        kill(pid, SIGUSR1);
        usleep(50);
    }
}


int main(int argc, char **argv)
{
    int pid;
    char *message;

    if (argc == 3)
    {
        pid = atoi(argv[1]);
        message = argv[2];
        printf("PID: %d\n", pid);
        printf("Message: %s", message);
        send_message(pid, message);
    }
    else
    {
        printf("Error: Merci d'entrer un PID et un Message");
    }

    return 0;
}