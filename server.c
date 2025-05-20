#include "minitalk.h"

void string_builder(char **str, char c, int client_pid)
{
	char *temp;

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

// Função que recebe os sinais SIGUSR1 e SIGUSR2, e converte eles em 0 ou 1
void server_handler(int signal, siginfo_t *info, void *context)
{
    static char	c = 0;
	static char *str = NULL;
	static int	bit_counter = 0;

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
		if (!str)
			return ;
	}
	kill(info->si_pid, SIGUSR1);
}

int main()
{
    struct sigaction sa;

    // Imprime o PID, para poder ser usado como input pelo cliente
    printf("Servidor iniciado em %i\n", getpid());
    // Configura como lidar com um sinal recebido
    // Indica que funçao executar quando receber um sinal
    sa.sa_sigaction = server_handler;
    // Inicializa sa_mask como um conjunto vazio, para evitar lixo de memória (boa prática)
    sigemptyset(&sa.sa_mask);
    // A flag SA_SIGINFO deve ser usada em conjunto com a função complexa sa_sigaction
    // Guarda as informações extras do sinal que serão usadas por sa_sigaction
    sa.sa_flags = SA_SIGINFO;
    // Essa função indica qual sinal responder com a função definida acima
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    // Loop que faz o programa esperar um sinal
    // A função pause() espera por QUALQUER sinal
    // Se o sinal for algum SIGUSR, lida com ele do modo configurado
    while (1)
        pause();
    return (0);
}