#include "philo.h"

sem_t	*ft_sem_open(char const *str, int val)
{
	sem_unlink(str);
	return (sem_open(str, O_CREAT | O_EXCL, 0644, val));
}

char	*ft_sem_name(char const *str, char *buff, int pos)
{
	int	i;

	i = ft_strcpy(buff, str);
	while (pos > 0)
	{
		buff[i++] = (pos % 10) + '0';
		pos /= 10;
	}
	buff[i] = 0;
	return (buff);
}
