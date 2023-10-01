/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:14:38 by slombard          #+#    #+#             */
/*   Updated: 2023/10/01 12:14:48 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pick_up_forks(t_philosopher_args *args)
{
	if (current_timestamp(args->sim_params->start_time) 
		- args->philo->last_meal_timestamp 
		< args->sim_params->time_to_eat + args->sim_params->time_to_sleep + 10)
		usleep(500);
	if (args->philo->id % 2 == 0)
	{
		pthread_mutex_lock(args->philo->fork_right);
		print_state(args, HAS_FORK);
		pthread_mutex_lock(args->philo->fork_left);
		print_state(args, HAS_FORKS);
	}
	if (args->philo->id % 2 == 1)
	{
		pthread_mutex_lock(args->philo->fork_left);
		print_state(args, HAS_FORK);
		pthread_mutex_lock(args->philo->fork_right);
		print_state(args, HAS_FORKS);
	}
}

void	drop_forks(t_philosopher_args *args)
{
	if (args->philo->id % 2 == 1)
		if (pthread_mutex_unlock(args->philo->fork_right) 
			|| pthread_mutex_unlock(args->philo->fork_left))
			print_exit("Error: could not unlock fork mutex\n");
	if (args->philo->id % 2 == 0)
		if (pthread_mutex_unlock(args->philo->fork_left) 
			|| pthread_mutex_unlock(args->philo->fork_right))
			print_exit("Error: could not unlock fork mutex\n");
}
