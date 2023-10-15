/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:39:10 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 17:36:15 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_and_die(t_philosopher *philosopher, t_sim_params *sim_params)
{
	long long	remaining_time_to_die;

	usleep(50);
	remaining_time_to_die = (philosopher->last_meal_ts
			+ sim_params->time_to_die)
		- current_timestamp(sim_params->start_time);
	usleep(remaining_time_to_die * 1000);
	if (philosopher->state == EATING)
		drop_forks(philosopher->fork_right, philosopher->fork_left);
	philosopher->state = DEAD;
	pthread_mutex_lock(&sim_params->death_mutex);
	sim_params->death_state = SOMEONE_DIED;
	pthread_mutex_unlock(&sim_params->death_mutex);
	print_state(philosopher, sim_params);
}

int	is_about_to_die(t_philosopher *philosopher, t_sim_params *sim_params,
		int time_to_consider)
{
	(void)philosopher;
	if (time_to_consider > sim_params->time_to_die)
		return (1);
	return (0);
}

int	eat_routine(t_philosopher *philosopher, t_sim_params *sim_params)
{
	if (!pick_up_forks(philosopher, sim_params))
		return (0);
	philosopher->state = EATING;
	if (sim_params->hunger_check == ON)
		increase_meals(philosopher, sim_params);
	philosopher->last_meal_ts = current_timestamp(sim_params->start_time);
	print_state(philosopher, sim_params);
	if (is_about_to_die(philosopher, sim_params, sim_params->time_to_eat))
	{
		sleep_and_die(philosopher, sim_params);
		return (0);
	}
	else
		usleep(sim_params->time_to_eat * 1000);
	drop_forks(philosopher->fork_right, philosopher->fork_left);
	return (1);
}

int	sleep_routine(t_philosopher *philosopher, t_sim_params *sim_params)
{
	int	time_to_consider;

	time_to_consider = sim_params->time_to_sleep + sim_params->time_to_eat;
	philosopher->state = SLEEPING;
	print_state(philosopher, sim_params);
	if (is_about_to_die(philosopher, sim_params, time_to_consider))
	{
		sleep_and_die(philosopher, sim_params);
		return (0);
	}
	else
		usleep(sim_params->time_to_sleep * 1000);
	return (1);
}

void	think_routine(t_philosopher *philosopher, t_sim_params *sim_params)
{
	int	time_to_consider;

	time_to_consider = sim_params->time_to_sleep + sim_params->time_to_eat
		+ (sim_params->time_to_eat - sim_params->time_to_sleep);
	philosopher->state = THINKING;
	print_state(philosopher, sim_params);
	if (sim_params->time_to_sleep < sim_params->time_to_eat)
	{
		if (is_about_to_die(philosopher, sim_params, time_to_consider))
			sleep_and_die(philosopher, sim_params);
		else
			usleep((sim_params->time_to_eat - sim_params->time_to_sleep)
				* 1000);
	}
	else
		usleep(100);
}
