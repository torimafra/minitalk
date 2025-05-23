/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:20:05 by vimafra-          #+#    #+#             */
/*   Updated: 2025/05/23 17:37:59 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	string_builder(char **str, char c, int client_pid)
{
	char	*temp;

	if (c == 0)
	{
		ft_putstr_fd(*str, 1);
		ft_putstr_fd("\n", 1);
		free(*str);
		*str = NULL;
		kill(client_pid, SIGUSR2);
		return ;
	}
	temp = ft_strjoin(*str, c);
	free(*str);
	*str = temp;
}

// void	server_handler(int signal, siginfo_t *info, void *context)
// {
// 	static char	c = 0;
// 	static char	*str = NULL;
// 	static int	bit_counter = 0;

// 	(void)context;
// 	if (!str)
// 		str = ft_strdup("");
// 	c = c << 1;
// 	if (signal == SIGUSR1)
// 		c = c | 1;
// 	bit_counter++;
// 	if (bit_counter == 8)
// 	{
// 		string_builder(&str, c, info->si_pid);
// 		kill(info->si_pid, SIGUSR1);
// 		c = 0;
// 		bit_counter = 0;
// 		if (!str)
// 			return ;
// 	}
// }

void server_handler(int signal, siginfo_t *info, void *context)
{
    static char c = 0;
    static char *str = NULL;
    static int bit_counter = 0;

    (void)context;

    if (!str)
        str = ft_strdup("");

    c = c << 1;
    if (signal == SIGUSR1)
        c = c | 1;

    bit_counter++;

    if (bit_counter == 8)
    {
        string_builder(&str, c, info->si_pid);
        c = 0;
        bit_counter = 0;

        // Se a string foi finalizada (string_builder setou str para NULL)
        if (!str)
            return ;
    }

    // ACK para o cliente a cada bit recebido
    kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	char				*pid;

	ft_putstr_fd("Server initialized in ", 1);
	pid = ft_itoa(getpid());
	ft_putstr_fd(pid, 1);
	free(pid);
	ft_putstr_fd("\n", 1);
	sa.sa_sigaction = server_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
