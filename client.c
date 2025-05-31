/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:19:48 by vimafra-          #+#    #+#             */
/*   Updated: 2025/05/24 14:29:22 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_server_response = 0;

void	ack_server(int signal)
{
	(void)signal;
	g_server_response = 0;
}

void	send_bit(int pid, int bit)
{
	g_server_response = 1;
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	while (g_server_response)
		pause();
}

void	send_signal(int pid, char *str)
{
	int	i;
	int	bit;

	i = 0;
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
	bit = 7;
	while (bit >= 0)
	{
		send_bit(pid, 0);
		bit--;
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		ft_putstr_fd("Input: PID, message\n", 1);
		return (1);
	}
	pid = atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("Invalid PID\n", 1);
		return (1);
	}
	if (kill(pid, 0) == -1)
	{
		ft_putstr_fd("Invalid process\n", 1);
		return (-1);
	}
	signal(SIGUSR1, ack_server);
	signal(SIGUSR2, ack_server);
	send_signal(pid, argv[2]);
	return (0);
}
