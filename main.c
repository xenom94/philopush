/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabboudi <iabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:42:29 by iabboudi          #+#    #+#             */
/*   Updated: 2024/12/20 22:42:30 by iabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (parse_args(&data, ac, av))
		return (2);
	if (!assign_philos(&data))
		return (1);
	if (!assign_mutex(&data))
		return (1);
	if (!assign_thread(&data))
		return (1);
	death_check(&data);
	join_thread(&data);
	return (0);
}