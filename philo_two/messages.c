#include "philo.h"

int	ft_error(const char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

void	ft_messages(t_philo *ph, const char *str, int id_message)
{
	size_t timestamp;

	sem_wait(ph->r->message);
	if (ph->r->is_dead == 0)
	{
		timestamp = ft_time_in_ms();
		ft_putnbr(timestamp);
		write(1, " ", 1);
		ft_putnbr(ph->id + 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		if (id_message == 1)
			ph->r->is_dead = 1;
	}
	sem_post(ph->r->message);
}
