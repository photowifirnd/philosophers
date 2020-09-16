/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheras-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 08:29:45 by jheras-f          #+#    #+#             */
/*   Updated: 2020/09/16 08:37:19 by jheras-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				ft_write_message(const char *str)
{
	if (str != NULL)
		write(1, str, ft_strlen(str));
	return (-1);
}

size_t			ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int				ft_strcpy(char *dst, const char *src)
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
