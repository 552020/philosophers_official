/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:15:00 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 16:00:08 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pick_up_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex_fork);
}

int	pick_up_forks(t_philosopher *philosopher, t_sim_params *sim_params)
{
	if (philosopher->id % 2 == 0)
	{
		usleep(100);
		pick_up_fork(philosopher->fork_right);
		philosopher->state = HAS_FORK;
		print_state(philosopher, sim_params);
		pick_up_fork(philosopher->fork_left);
		philosopher->state = HAS_FORKS;
		print_state(philosopher, sim_params);
	}
	if (philosopher->id % 2 == 1)
	{
		pick_up_fork(philosopher->fork_left);
		philosopher->state = HAS_FORK;
		print_state(philosopher, sim_params);
		pick_up_fork(philosopher->fork_right);
		philosopher->state = HAS_FORKS;
		print_state(philosopher, sim_params);
	}
	return (1);
}

void	drop_forks(t_fork *fork_right, t_fork *fork_left)
{
	pthread_mutex_unlock(&fork_right->mutex_fork);
	pthread_mutex_unlock(&fork_left->mutex_fork);
}
