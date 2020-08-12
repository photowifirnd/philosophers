#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct			s_rules;

typedef struct		s_philo
{
	int		id;
	int		r_hand;
	int		l_hand;
	int		eat_flag;
	uint64_t	will_die;
	uint64_t	last_eat;
	int		cnt;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat;
	struct s_rules	*r;
}			t_philo;

typedef struct		s_rules
{
	unsigned int	n_philos;
	uint64_t	tt_die;
	uint64_t	tt_eat;
	uint64_t	tt_sleep;
	int		is_dead;
	size_t	n_times_to_eat;
	uint64_t	initial_time;
	t_philo		*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	philo_dead;
	pthread_mutex_t	message;
}			t_rules;

int			ft_set_philos(t_rules *r);
int			ft_set_forks(t_rules *r);
int			ft_set_general(int argc, char *argv[], t_rules *r);
void			ft_living(void *ph);
void			ft_eat_or_die(void *ph);
void			ft_count_eaters(void *rules);
void			ft_get_forks(t_philo *ph);
void			ft_get_lunch(t_philo *ph);
void			ft_leave_forks(t_philo *ph);
void			ft_messages(t_philo *ph, const char *str, int id_message);
void			ft_end_message(t_philo *ph, int id_message);
int			ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
int			ft_write_message(const char *str);
uint64_t			ft_time_in_ms(void);
void			ft_putchar(char c);
void			ft_putnbr(long long int num);
#endif
