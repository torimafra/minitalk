/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:19:48 by vimafra-          #+#    #+#             */
/*   Updated: 2025/05/23 17:37:17 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// int	g_server_response = 0;

// void	ack_server(int signal)
// {
// 	(void)signal;
// 	g_server_response = 0;
// }

// void	send_zero(int pid)
// {
// 	int	bit;

// 	bit = 8;
// 	while (bit--)
// 	{
// 		kill(pid, SIGUSR2);
// 		g_server_response = 1;
// 		while (g_server_response)
// 			pause();
// 	}
// }

// void	send_signal(int pid, char *str)
// {
// 	int	i;
// 	int	bit;

// 	i = 0;
// 	bit = 8;
// 	while (str[i] != '\0')
// 	{
// 		while (bit--)
// 		{
// 			if ((str[i] >> bit & 1) == 1)
// 				kill(pid, SIGUSR1);
// 			else
// 				kill(pid, SIGUSR2);
// 			g_server_response = 1;
// 			while (g_server_response)
// 				pause();
// 		}
// 		bit = 8;
// 		i++;
// 	}
// 	send_zero(pid);
// }

// int	error_handler(int argc, int pid)
// {
// 	if (argc != 3)
// 	{
// 		ft_putstr_fd("Input: PID, message\n", 1);
// 		return (-1);
// 	}
// 	if (pid <= 0)
// 	{
// 		ft_putstr_fd("Invalid PID\n", 1);
// 		return (-1);
// 	}
// 	if (kill(pid, 0) == -1)
// 	{
// 		ft_putstr_fd("Invalid process\n", 1);
// 		return (-1);
// 	}
// 	return (0);
// }

// int	main(int argc, char *argv[])
// {
// 	int	pid;

// 	pid = ft_atoi(argv[1]);
// 	if (error_handler(argc, pid) == -1)
// 		return (1);
// 	signal(SIGUSR1, ack_server);
// 	signal(SIGUSR2, ack_server);
// 	send_signal(pid, argv[2]);
// 	return (0);
// }

int g_server_response = 0;

void ack_server(int signal)
{
    (void)signal;
    g_server_response = 0;
}

void send_bit(int pid, int bit)
{
    g_server_response = 1;
    if (bit)
        kill(pid, SIGUSR1);
    else
        kill(pid, SIGUSR2);

    // Espera o ack do servidor
    while (g_server_response)
        pause();
}

void send_signal(int pid, char *str)
{
    int i = 0;
    int bit;

    while (str[i])
    {
        bit = 7;
        while (bit >= 0)
        {
            send_bit(pid, (str[i] >> bit) & 1);
            bit--;
        }
        i++;
    }

    // Envia o caractere nulo para sinalizar fim da mensagem
    bit = 7;
    while (bit >= 0)
    {
        send_bit(pid, 0);
        bit--;
    }
}

int main(int argc, char *argv[])
{
    int pid;

    if (argc != 3)
    {
        write(1, "Input: PID, message\n", 20);
        return (1);
    }

    pid = atoi(argv[1]);
    if (pid <= 0)
    {
        write(1, "Invalid PID\n", 12);
        return (1);
    }

    signal(SIGUSR1, ack_server);
    signal(SIGUSR2, ack_server);

    send_signal(pid, argv[2]);

    return (0);
}
