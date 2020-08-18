#include "philo.h"

int	ft_set_forks(t_rules *r)
{
	size_t	i;

	i = 0;
	if (!(r->forks = (pthread_mutex_t *)malloc(sizeof(*(r->forks)) * r->n_philos)))
		return (1);
	while (i < r->n_philos)
		pthread_mutex_init(&r->forks[i++], NULL);
	return (0);
}

int	ft_set_philos(t_rules *r)
{
	size_t	i;

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
		pthread_mutex_init(&r->philo[i].mutex, NULL);
		pthread_mutex_init(&r->philo[i].eat, NULL);
		pthread_mutex_lock(&r->philo[i].eat);
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
	if (!(r->n_forks = (unsigned int *)malloc(r->n_philos)))
		return (1);
	i = 0;
	while (i < r->n_philos)
		r->n_forks[i++] = 0;
	r->tt_die = (uint64_t)ft_atoi(argv[2]) * 1000;
	r->tt_eat = (uint64_t)ft_atoi(argv[3]) * 1000;
	r->tt_sleep = (uint64_t)ft_atoi(argv[4]) * 1000;
	r->is_dead = 0;
	pthread_mutex_init(&r->message, NULL);
	pthread_mutex_init(&r->fork_state, NULL);
	pthread_mutex_init(&r->philo_dead, NULL);
	pthread_mutex_lock(&r->philo_dead);
	return (0);
}

int	ft_init(int argc, char *argv[], t_rules *r)
{
	return (ft_set_general(argc, argv, r) || ft_set_philos(r) || ft_set_forks(r));
}

