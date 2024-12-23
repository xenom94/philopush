/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabboudi <iabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 04:27:18 by iabboudi          #+#    #+#             */
/*   Updated: 2024/12/21 07:13:18 by iabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool close_to_die(t_philo *philo, bool usethemtx)
{   
    int time;
    if(usethemtx)
        pthread_mutex_lock(&philo->mutex);
    time = get_time() - philo->last_meal_time;
    if (usethemtx)
        pthread_mutex_unlock(&philo->mutex);
    if(time > philo->data->time_to_die)
        return (true);
    return (false);
        
}
bool check_stop(t_data *data)
{
    bool stop;
    pthread_mutex_lock(&data->mutex);
    stop = data->stop;
    pthread_mutex_unlock(&data->mutex);
    return (stop);
}

void	wait_ms(int ms)
{
	long long	start_time;

	start_time = get_time();
	usleep(ms * 1000 * 0.9);
	while (get_time() - start_time < ms)
		usleep(30);
}

int ft_modulo(int a, int b)
{
    while(a < 0)
        a = a + b;
    return (a % b);
}

void ft_write_message(t_philo *philo, bool status, char *str)
{   
    long long time;
    
    if(!status && close_to_die(philo, false))
        return;
    pthread_mutex_lock(&philo->data->print);
    time = get_time() - philo->data->start_time;
    if (!check_stop(philo->data))
        printf("%lld %d %s\n", time, philo->id, str);
    pthread_mutex_unlock(&philo->data->print);
}

void ft_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[ft_modulo((philo->id - 1), philo->data->nb_philo)]);
    ft_write_message(philo, false ,"took the fork at the right");
    pthread_mutex_lock(&philo->data->forks[ft_modulo(philo->id - 2, philo->data->nb_philo)]);
    ft_write_message(philo, false, "took the fork at the left");
    ft_write_message(philo, false, "is eating");
    pthread_mutex_lock(&philo->mutex);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->mutex);
    wait_ms(philo->data->time_to_eat);
    pthread_mutex_unlock(&philo->data->forks[ft_modulo((philo->id - 2) , philo->data->nb_philo)]);
    pthread_mutex_unlock(&philo->data->forks[ft_modulo((philo->id - 1) , philo->data->nb_philo)]); 
}

void *routine(void *arg)
{
    t_philo *philo;
    int eat_count;

    philo = (t_philo*)arg;
    eat_count = 0;
    
    if (philo->id % 2 == 0)
    usleep((philo->data->time_to_eat / 2) * 1000);

    while(!check_stop(philo->data))
    {
        ft_eat(philo);
        eat_count++;
        if (!philo->data->all_philos_ate && eat_count >= philo->data->nb_must_eat)
        {
            pthread_mutex_lock(&philo->data->mutex);
            philo->done_eating = true;
            pthread_mutex_unlock(&philo->data->mutex);
            return (NULL);
        }
        ft_write_message(philo, false, "is sleeping");
        wait_ms(philo->data->time_to_sleep);
        ft_write_message(philo, false, "is thinking");
    }
    return (NULL);
}
void death_check(t_data *data)
{   
    int i ;
  while(1)
    {
    i = 0;
        while(i < data->nb_philo)
        {
            if(close_to_die(&data->philo[i], true))
            {
            ft_write_message(&data->philo[i], true, "died");
            stop(data);
            return ;
            }
            i++;
        }
        if(!data->all_philos_ate && finised_eating(data))
        {
            stop(data);
            return ;
        }
    }
}

bool stop(t_data *data)
{
    pthread_mutex_lock(&data->mutex);
    data->stop = true;
    pthread_mutex_unlock(&data->mutex);
    return (true);
}

bool finised_eating(t_data *data)
{
    int i;
    bool done_eating;
    i = 0;
    while (i < data->nb_philo)
    {
        pthread_mutex_lock(&data->mutex);
        done_eating = data->philo[i].done_eating;
        pthread_mutex_unlock(&data->mutex);
        if (!done_eating)
            return (false);
        i++;
    }
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
