/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_and_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabboudi <iabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:07:16 by iabboudi          #+#    #+#             */
/*   Updated: 2024/12/23 22:18:21 by iabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	close_to_die(t_philo *philo, bool usethemtx)
{
	int	time;

	if (usethemtx)
		pthread_mutex_lock(&philo->mutex);
	time = get_time() - philo->last_meal_time;
	if (usethemtx)
		pthread_mutex_unlock(&philo->mutex);
	if (time > philo->data->time_to_die)
		return (true);
	return (false);
}

void	death_check(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (close_to_die(&data->philo[i], true))
			{
				ft_write_message(&data->philo[i], true, "died");
				stop(data);
				return ;
			}
			i++;
		}
		if (!data->all_philos_ate && finised_eating(data))
		{
			stop(data);
			return ;
		}
	}
}

bool	stop(t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	data->stop = true;
	pthread_mutex_unlock(&data->mutex);
	return (true);
}

void	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}
