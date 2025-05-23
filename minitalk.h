/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimafra- <vimafra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:19:56 by vimafra-          #+#    #+#             */
/*   Updated: 2025/05/22 17:28:39 by vimafra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>

void	ft_putstr_fd(char *s, int fd);
void	string_builder(char **str, char c, int client_pid);
void	server_handler(int signal, siginfo_t *info, void *context);
void	ack_server(int signal);
void	send_zero(int pid);
void	send_signal(int pid, char *str);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char c);
char	*write_number(int n, char *s);
char	*ft_swap(char *s, int n);
char	*is_int_min(int n);
char	*ft_itoa(int n);
int		ft_atoi(char *nptr);
int		ft_strlen(char *str);
int		digit_counter(int n);

#endif
