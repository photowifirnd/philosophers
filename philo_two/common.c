#include "philo.h"

int	ft_write_message(const char *str)
{
	if (str != NULL)
		write (1, str, ft_strlen(str));
	return (-1);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}

static size_t	ft_l(void)
{
	size_t	lmts;

	lmts = (size_t)(9223372036854775807 / 10);
	return (lmts);
}

int				ft_atoi(const char *s)
{
	int				sign;
	unsigned long	r;

	r = 0;
	sign = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		if ((r > ft_l() || (r == ft_l() && (*s - '0') > 7)) && sign == 1)
			return (-1);
		else if ((r > ft_l() || (r == ft_l() && (*s - '0') > 8)) && sign == -1)
			return (0);
		r = r * 10 + *s - '0';
		s++;
	}
	return (sign * (int)r);
}

uint64_t	ft_time_in_ms(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (uint64_t)1000) + (t.tv_usec / 1000));
}

uint64_t	ft_time_in_micro_s(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * (uint64_t)1000 * (uint64_t)1000) + (t.tv_usec));
}

void	ft_putchar(char c)
{
	write(1, &c ,1);
}

void	ft_putnbr(long long int n)
{
	unsigned long long int	num;

	if (n < 0)
	{
		num = n * -1;
		ft_putchar('-');
	}
	else
		num = n;
	if (num >= 10)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	else
		ft_putchar((num + '0'));
}
