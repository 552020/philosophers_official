/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:14:29 by slombard          #+#    #+#             */
/*   Updated: 2023/10/14 23:00:32 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_and_free(t_sim_params *sim_params, t_philosopher *philosophers,
		t_fork *forks, t_philosopher_args *args)
{
	int	i;

	i = 0;
	while (i < sim_params->philos_nbr)
	{
		pthread_join(philosophers[i].p_thread, NULL);
		i++;
	}
	i = 0;
	while (i < sim_params->philos_nbr)
	{
		pthread_mutex_destroy(&forks[i].mutex_fork);
		i++;
	}
	pthread_mutex_destroy(&sim_params->print_mutex);
	pthread_mutex_destroy(&sim_params->meal_mutex);
	pthread_mutex_destroy(&sim_params->death_mutex);
	free(philosophers);
	free(forks);
	free(args);
}
