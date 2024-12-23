/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabboudi <iabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:42:26 by iabboudi          #+#    #+#             */
/*   Updated: 2024/12/20 22:42:27 by iabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parse_args(t_data *data, int argc, char **argv)
{
	if (input_is_valid(argc, argv))
        return (1);
    data->nb_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
    {
        data->nb_must_eat = ft_atoi(argv[5]);
        data->all_philos_ate = false;
    }
    else
        {
            data->nb_must_eat = 0;
            data->all_philos_ate = true;
        }
    if (data->nb_philo <= 0 || data->time_to_die <= 0 
    || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
    {
        printf("Invalid arguments\n");
        exit(4);
    }
    return (0);
}

int assign_philos(t_data *data)
{
    int i;
    data->philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
    if(!data->philo)
        return (0);
    i = 0;
    while (i < data->nb_philo)
    {
        data->philo[i].id = i + 1;
        data->philo[i].data = data;
        data->philo[i].last_meal_time = get_time();
        if(pthread_mutex_init(&data->philo[i].mutex, NULL) != 0)
            return (0);
        i++;
    }
    return (1);
    }

int assign_mutex(t_data *data)
{
    int i;
    data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->nb_philo);
    if(!data->forks)
        return (0);
    i = 0;
    while (i < data->nb_philo)
    {
        if(pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (0);
        i++;
    }
    if(pthread_mutex_init(&data->print, NULL) != 0)
        return (0);
    if(pthread_mutex_init(&data->mutex, NULL) != 0)
        return (0);

    return (1);

}

int assign_thread(t_data *data)
{
    int i;

    i = 0;
    data->stop = false;
    data->start_time = get_time();
    while (i < data->nb_philo)
    {
        if(pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]) != 0)
            return (0);
        i++;
    }
    return (1);
}
int input_is_valid(int ac, char **av)
{
    if(ac < 5 || ac > 6)
    {
        printf("Invalid number of arguments\n");
        return (1);
    }
    is_valid(av);
    return (0);
}

long long get_time(void)
{
    struct timeval time_val;
    long   time_ms;
    gettimeofday(&time_val, NULL);
    time_ms = (time_val.tv_sec * 1000) + (time_val.tv_usec / 1000);
    return (time_ms);
}
void is_valid(char **av)
{
    int i = 1;
    while (av[i])
    {
        if (!is_number(av[i]))
        {
            printf("Invalid arguments\n");
            exit(1);
        }
        if (!is_empty(av[i]))
        {
            printf("Invalid arguments\n");
            exit(2);
        }
        i++;
    }
}
int is_number(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int is_empty(char *str)
{
    int i = 0;
    while (str[i] && str[i] == ' ')
        i++;
    if (str[i] == '\0')
        return (0);
    return (1);
} 

int ft_atoi(char *str)
{
    int res = 0;
    int sign = 1;
    int i = 0;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res * sign);
}