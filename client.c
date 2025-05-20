#include "minitalk.h"

int server_response = 0;

void ack_server(int signal)
{
    (void)signal;
    server_response = 0;
}

void send_zero(int pid)
{
    int bit;

    bit = 8;
    while(bit--)
    {
        kill(pid, SIGUSR2);
        server_response = 1;
        while (server_response)
            ;
    }
}

void send_signal(int pid, char *str)
{
    int i;
    int bit;

    i = 0;
    bit = 8;
    while (str[i] != '\0')
    {
        while (bit--)
        {
            if ((str[i] >> bit & 1) == 1)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            server_response = 1;
            while (server_response)
                ;
        }
        bit = 8;
        i++;
    }
    send_zero(pid);
}

int error_handler(int argc, int pid)
{
    if (argc != 3)
    {
        ft_putstr_fd("Input: PID, message\n", 1);
        return (-1);
    }
    if (pid <= 0)
    {
        ft_putstr_fd("Invalid PID\n", 1);
        return (-1);
    }
    if (kill(pid, 0) == -1)
    {
        ft_putstr_fd("Invalid process\n", 1);
        return (-1);
    }
    return (0);
}

int main(int argc, char *argv[])
{
    int pid;

    pid = ft_atoi(argv[1]);
    if (error_handler(argc, pid) == -1)
        return (1);
    signal(SIGUSR1, ack_server);
    signal(SIGUSR2, ack_server);
    send_signal(pid, argv[2]);
    return (0);
}