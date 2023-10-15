/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:31:25 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 18:28:40 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// TODO: free stuff when malloc fails
void	print_and_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	print_free_exit(char *str, t_philosopher **philosophers, t_fork **forks,
		t_philosopher_args **args)
{
	printf("Error: %s\n", str);
	if (*philosophers != NULL)
		free(*philosophers);
	if (*forks != NULL)
		free(*forks);
	if (*args != NULL)
		free(*args);
	exit(1);
}

void	print_state_core(t_philosopher *philosopher, t_sim_params *t_sim_params)
{
	printf("%lld %d ", current_timestamp(t_sim_params->start_time),
		philosopher->id);
	if (philosopher->state == EATING)
		printf("is eating\n");
	else if (philosopher->state == SLEEPING)
		printf("is sleeping\n");
	else if (philosopher->state == THINKING)
		printf("is thinking\n");
	else if (philosopher->state == DEAD)
	{
		t_sim_params->death_announced = YES;
		printf("died\n");
	}
	else if (philosopher->state == HAS_FORK)
		printf("has taken a fork\n");
	else if (philosopher->state == HAS_FORKS)
		printf("has taken a fork\n");
}

// void	print_state(t_philosopher *philosopher, t_sim_params *sim_params,
// 		t_hold_death_mutex hold_death_mutex)
// {
// 	pthread_mutex_lock(&sim_params->print_mutex);
// 	if (!hold_death_mutex)
// 		pthread_mutex_lock(&sim_params->death_mutex);
// 	if (sim_params->death_announced == YES)
// 	{
// 		if (!hold_death_mutex)
// 			pthread_mutex_unlock(&sim_params->death_mutex);
// 		pthread_mutex_unlock(&sim_params->print_mutex);
// 		return ;
// 	}
// 	print_state_core(philosopher, sim_params);
// 	if (!hold_death_mutex)
// 		pthread_mutex_unlock(&sim_params->death_mutex);
// 	pthread_mutex_unlock(&sim_params->print_mutex);
// }

void	print_state(t_philosopher *philosopher, t_sim_params *sim_params)
{
	pthread_mutex_lock(&sim_params->death_mutex);
	pthread_mutex_lock(&sim_params->print_mutex);
	if (sim_params->death_announced == YES)
	{
		pthread_mutex_unlock(&sim_params->print_mutex);
		pthread_mutex_unlock(&sim_params->death_mutex);
		return ;
	}
	print_state_core(philosopher, sim_params);
	pthread_mutex_unlock(&sim_params->print_mutex);
	pthread_mutex_unlock(&sim_params->death_mutex);
}

void	print_state_no_lock_death(t_philosopher *philosopher,
		t_sim_params *sim_params)
{
	pthread_mutex_lock(&sim_params->print_mutex);
	if (sim_params->death_announced == YES)
	{
		pthread_mutex_unlock(&sim_params->print_mutex);
		return ;
	}
	print_state_core(philosopher, sim_params);
	pthread_mutex_unlock(&sim_params->print_mutex);
}
