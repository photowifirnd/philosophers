#include "philo.h"

int	ft_set_forks(t_rules *r)
{
	r->forks = ft_sem_open("SemForks", r->n_philos);
	return (0);
}

int	ft_set_philos(t_rules *r)
{
	size_t	i;
	char 	str[250];

	if (!(r->philo = (t_philo *)malloc(sizeof(t_philo) * r->n_philos)))
		return (1);
	i = 0;
	while (i < r->n_philos)
	{
		r->philo[i].id = i;
		r->philo[i].r_hand = (i + 1) % r->n_philos;
		r->philo[i].l_hand = i;
		r->philo[i].eat_flag = 0;
		r->philo[i].last_eat = 0;
		r->philo[i].will_die = 0;
		r->philo[i].cnt = 0;
		r->philo[i].r = r;
		ft_sem_name("pSemaphorePhilo", (char *)str, i);
		r->philo[i].mutex = ft_sem_open(str, 1);
		ft_sem_name("pSemaphorePhiloEat", (char *)str, i);
		r->philo[i].eat = ft_sem_open(str, 0);
		i++;
	}
	return (0);
}

int	ft_set_general(int argc, char *argv[], t_rules *r)
{
	unsigned int i;

	r->n_times_to_eat = ((argc == 6) ? ft_atoi(argv[5]) : 0);
	r->philo = NULL;
	r->forks = NULL;
	r->n_philos = ft_atoi(argv[1]);
	if (r->n_philos < 2)
		return (1);
	if (!(r->n_forks = (int *)malloc(r->n_philos)))
		return (1);
	i = 0;
	while (i < r->n_philos)
		r->n_forks[i++] = -1;
	r->tt_die = (uint64_t)ft_atoi(argv[2]) * 1000;
	r->tt_eat = (uint64_t)ft_atoi(argv[3]) * 1000;
	r->tt_sleep = (uint64_t)ft_atoi(argv[4]) * 1000;
	r->is_dead = 0;
	r->message = ft_sem_open("WriteMessagge", 1);
	r->philo_dead = ft_sem_open("PhiloDead", 0);
	return (0);
}
