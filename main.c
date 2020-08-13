#include "philo.h"

int	ft_finish(t_rules *r)
{
	size_t i;

	i = 0;
	if (r->philo != NULL)
	{
		while (i < r->n_philos)
		{
			if (r->forks != NULL)
				pthread_mutex_destroy(&r->forks[i]);
			pthread_mutex_destroy(&r->philo[i].mutex);
			pthread_mutex_destroy(&r->philo[i++].eat);
		}
		free(r->philo);
		(r->forks != NULL) ? free(r->forks): NULL;
	}
	pthread_mutex_destroy(&r->philo_dead);
	pthread_mutex_destroy(&r->message);
	return (0);
}

void	ft_messages(t_philo *ph, const char *str, int id_message)
{
	size_t timestamp;

	pthread_mutex_lock(&ph->r->message);
	if (ph->r->is_dead == 0)
	{
		timestamp = ft_time_in_ms();
		ft_putnbr(timestamp);
		write(1, " ", 1);
		ft_putnbr(ph->id + 1);
		write(1, " ", 1);
		write(1, str, ft_strlen(str));
		if (id_message == 1)
		{
			ph->r->is_dead = 1;
			write(1, "philosopher's dead at: ", 23);
			ft_putnbr(ph->will_die);
			ft_putchar('\n');
		}
	}
	pthread_mutex_unlock(&ph->r->message);
}

void	ft_get_sleep(t_philo *ph)
{
	ft_messages(ph, "philosopher is sleeping\n", 0);
	usleep(ph->r->tt_sleep * 1000);
}

void	ft_get_lunch(t_philo *ph)
{
	pthread_mutex_lock(&ph->mutex);
	ph->cnt++;
	ph->eat_flag = 1;
	ph->last_eat = ft_time_in_ms();
	ph->will_die = ph->last_eat + ph->r->tt_die;
	usleep(ph->r->tt_eat * 1000);
	pthread_mutex_unlock(&ph->r->forks[ph->r_hand]);
	pthread_mutex_unlock(&ph->r->forks[ph->l_hand]);
	ft_messages(ph, "philosopher has eaten\n", 0);
	ph->eat_flag = 0;
	pthread_mutex_unlock(&ph->mutex);
	pthread_mutex_unlock(&ph->eat);
}

void	ft_get_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->r->forks[ph->r_hand]);
	ft_messages(ph, "philosopher has taken a right fork\n", 0);
	pthread_mutex_lock(&ph->r->forks[ph->l_hand]);
	ft_messages(ph, "philosopher has taken a left fork\n", 0);
}

void	ft_eat_or_die(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	while(1)
	{
		if (philo->r->is_dead)
			return ;
		pthread_mutex_lock(&philo->mutex);
		if (!philo->eat_flag && ft_time_in_ms() > philo->will_die)
		{
			ft_messages(philo, "philosofer died\n", 1);
			pthread_mutex_lock(&philo->r->message);
			printf("Finalizando\n");
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->r->philo_dead);
			return ;
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(100);
	}
}

void	ft_living(void *ph)
{
	t_philo		*philo;
	pthread_t	pthread_id;
	int		must_continue;

	must_continue = 1;
	philo = (t_philo *)ph;
	philo->last_eat = ft_time_in_ms();
	philo->will_die = philo->last_eat + philo->r->tt_die;
	if (pthread_create(&pthread_id, NULL, (void *)ft_eat_or_die, philo) != 0)
		must_continue = 0;
	pthread_detach(pthread_id);
	while (must_continue && !philo->r->is_dead)
	{
		ft_get_forks(philo);
		ft_get_lunch(philo);
		//ft_leave_forks(philo);
		ft_get_sleep(philo);
		ft_messages(philo, "philosopher is thinking\n", 0);
	}
}

void	ft_count_eaters(void *rules)
{
	t_rules	*r;
	size_t	i;
	size_t	j;

	r = (t_rules *)rules;
	i = 0;
	while (i < r->n_times_to_eat)
	{
		j = 0;
		while (j < r->n_philos)
			pthread_mutex_lock(&r->philo[j++].eat);
		i++;
	}
	if (r->n_times_to_eat > 0)
		r->is_dead = 1;
	pthread_mutex_unlock(&r->philo_dead);
}

int	ft_init_threads(t_rules *r)
{
	void		*philo;
	size_t		i;
	pthread_t	thread_id;

	if (r->n_times_to_eat > 0)
	{
		if (pthread_create(&thread_id, NULL, (void *)ft_count_eaters, (void *)r) != 0)
			return (1);
		pthread_detach(thread_id);
	}
	i = 0;
	while (i < r->n_philos)
	{
		if (i % 2 == 0)
		{
		philo = (void *)(&r->philo[i]);
		if (pthread_create(&thread_id, NULL, (void *)ft_living, philo) != 0)
			return (1);
		pthread_detach(thread_id);
		}
		i++;
	}
	usleep(1000);
	i = 0;
	while (i < r->n_philos)
	{
		if (i % 2 == 1)
		{
			philo = (void *)(&r->philo[i]);
			if (pthread_create(&thread_id, NULL, (void *)ft_living, philo) != 0)
				return (1);
			pthread_detach(thread_id);
		}
		i++;
	}
	return (0);
}

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
	r->n_times_to_eat = ((argc == 6) ? ft_atoi(argv[5]) : 0);
	r->philo = NULL;
	r->forks = NULL;
	r->n_philos = ft_atoi(argv[1]);
	r->tt_die = (uint64_t)ft_atoi(argv[2]);
	r->tt_eat = (uint64_t)ft_atoi(argv[3]);
	r->tt_sleep = (uint64_t)ft_atoi(argv[4]);
	r->is_dead = 0;
	pthread_mutex_init(&r->philo_dead, NULL);
	pthread_mutex_lock(&r->philo_dead);
	pthread_mutex_init(&r->message, NULL);
	return (0);
}

int	ft_init(int argc, char *argv[], t_rules *r)
{
	return (ft_set_general(argc, argv, r) || ft_set_philos(r) || ft_set_forks(r));
}

int	ft_error(const char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	main(int argc, char *argv[])
{
	t_rules	r;

	if (argc < 5 || argc > 6)
		return (ft_error("Error: Argument\n"));
	if (ft_init(argc, argv, &r))
		return (1);
	if (ft_init_threads(&r))
		return (1);
	pthread_mutex_lock(&r.philo_dead);
	pthread_mutex_unlock(&r.philo_dead);
	ft_finish(&r);
	return (0);
}
