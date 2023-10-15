/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:15:20 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 00:05:00 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_simulation(t_philosopher *philosophers, t_philosopher_args *args,
		t_sim_params *sim_params)
{
	int	i;

	i = 0;
	while (i < sim_params->philos_nbr)
	{
		pthread_create(&philosophers[i].p_thread, NULL, eat_sleep_think,
			&args[i]);
		i++;
	}
}
