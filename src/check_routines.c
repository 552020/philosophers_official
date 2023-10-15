/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:15:44 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 18:28:40 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philosopher *philosopher, t_sim_params *sim_params,
		struct timeval start_time)
{
	if (current_timestamp(start_time)
		- philosopher->last_meal_ts >= sim_params->time_to_die)
	{
		philosopher->state = DEAD;
		sim_params->death_state = SOMEONE_DIED;
		print_state_no_lock_death(philosopher, sim_params);
		return (1);
	}
	return (0);
}

int	check_death_condition(t_philosopher *philosopher, t_sim_params *sim_params)
{
	int	death_occurred;

	death_occurred = 0;
	pthread_mutex_lock(&sim_params->death_mutex);
	if (check_death(philosopher, sim_params, sim_params->start_time)
		|| sim_params->death_state == SOMEONE_DIED)
	{
		death_occurred = 1;
	}
	pthread_mutex_unlock(&sim_params->death_mutex);
	return (death_occurred);
}

int	check_meal_condition(t_sim_params *sim_params)
{
	int	enough_meals;

	enough_meals = 0;
	pthread_mutex_lock(&sim_params->meal_mutex);
	if (sim_params->hunger_check == ON
		&& sim_params->hunger_state == PHILOSOPHERS_ARE_FULL)
	{
		enough_meals = 1;
	}
	pthread_mutex_unlock(&sim_params->meal_mutex);
	return (enough_meals);
}
