#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>

void	ft_putstr_fd(char *s, int fd);
int ft_strlen(char *str);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char c);
int	ft_atoi(char *nptr);
void string_builder(char **str, char c, int client_pid);
void server_handler(int signal, siginfo_t *info, void *context);
void ack_server(int signal);
void send_zero(int pid);
void send_signal(int pid, char *str);

#endif