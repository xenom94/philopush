/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabboudi <iabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:09:49 by iabboudi          #+#    #+#             */
/*   Updated: 2024/12/23 22:20:12 by iabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_ms(int ms)
{
	long long	start_time;

	start_time = get_time();
	usleep(ms * 1000 * 0.9);
	while (get_time() - start_time < ms)
		usleep(30);
}

int	ft_modulo(int a, int b)
{
	while (a < 0)
		a = a + b;
	return (a % b);
}

int	input_is_valid(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Invalid number of arguments\n");
		return (1);
	}
	is_valid(av);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time_val;
	long			time_ms;

	gettimeofday(&time_val, NULL);
	time_ms = (time_val.tv_sec * 1000) + (time_val.tv_usec / 1000);
	return (time_ms);
}
