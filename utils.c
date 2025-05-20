#include "minitalk.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s != '\0')
	{
		write(fd, &*s, 1);
		s++;
	}
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(str[i] != '\0')
        i++;
    return (i);
}

char	*ft_strdup(char *s)
{
	unsigned int	i;
	char			*dup;

	i = 0;
	dup = (char *)malloc(ft_strlen(s) * sizeof(char) + 1); // Malloca espaço para s + terminator na nova string
	if (!dup)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i]; // Cópia simples de s para dup
		i++;
	}
	dup[i] = '\0'; // Null terminates
	return (dup);
}

char	*ft_strjoin(char *s1, char c)
{
	char			*result;
	int	i;

	i = 0;
	if (!s1 || !c)
		return (NULL);
	result = (char *)malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while(*s1 != '\0')
	{
		result[i] = *s1;
		i++;
		s1++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	return (result);
}

int	ft_atoi(char *nptr)
{
	unsigned int	i;
	int				sign;
	int				result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] != '\0' && ((nptr[i] >= 9 && nptr[i] <= 13) \
			|| nptr[i] == 32))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9') // Encontrando um caractere de número, a função entra nesse loop para iniciar a conversão de char para int
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}