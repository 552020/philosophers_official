/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:16:39 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 18:29:45 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eat_sleep_think_single(void *arg)
{
	t_philosopher_args	*args;

	args = (t_philosopher_args *)arg;
	print_state(args->philosopher, args->sim_params);
	printf("%lld %d has taken a fork\n",
		current_timestamp(args->sim_params->start_time), args->philosopher->id);
	usleep(args->sim_params->time_to_die * 1000);
	printf("%lld %d died\n", current_timestamp(args->sim_params->start_time),
		args->philosopher->id);
	args->sim_params->death_state = SOMEONE_DIED;
	return (NULL);
}

void	handle_single_philo(t_philosopher_args *args)
{
	t_philosopher	*philosopher;

	philosopher = args->philosopher;
	if (pthread_create(&philosopher->p_thread, NULL, eat_sleep_think_single,
			args) != 0)
	{
		fprintf(stderr, "Error creating thread for philosopher %d\n",
			philosopher->id);
		exit(EXIT_FAILURE);
	}
}
