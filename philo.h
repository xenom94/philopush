/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabboudi <iabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:42:37 by iabboudi          #+#    #+#             */
/*   Updated: 2024/12/20 22:42:38 by iabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_philo
{
    int id;
    unsigned long last_meal_time;
    bool done_eating;
    pthread_t thread;
    pthread_mutex_t mutex;
    struct s_data   *data;
}   t_philo;

typedef struct s_data
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_must_eat;
    bool all_philos_ate;
    bool stop;
    long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t mutex;
    t_philo *philo;
}   t_data;

void is_valid(char **av);
int parse_args(t_data *data, int argc, char **argv);
int assign_philos(t_data *data);
int is_number(char *str);
int input_is_valid(int ac, char **av);
int is_empty(char *str);
int ft_atoi(char *str);
bool close_to_die(t_philo *philo, bool usethemtx);
bool check_stop(t_data *data);
void	wait_ms(int ms);
int ft_modulo(int a, int b);
void ft_write_message(t_philo *philo, bool status, char *str);
void ft_eat(t_philo *philo);
void *routine(void *arg);
void	join_thread(t_data *data);
bool finised_eating(t_data *data);
bool stop(t_data *data);
void death_check(t_data *data);
int assign_thread(t_data *data);
int assign_mutex(t_data *data);
long long get_time(void);

# endif