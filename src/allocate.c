/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:01:55 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 18:29:01 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	allocate_memory(t_sim_params *sim_params, t_philosopher **philosophers,
		t_fork **forks, t_philosopher_args **args)
{
	*philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
			* sim_params->philos_nbr);
	if (!*philosophers)
		print_free_exit("malloc philosophers failed", philosophers, forks,
			args);
	*forks = (t_fork *)malloc(sizeof(t_fork) * sim_params->philos_nbr);
	if (!*forks)
		print_free_exit("malloc forks failed", philosophers, forks, args);
	*args = (t_philosopher_args *)malloc(sizeof(t_philosopher_args)
			* sim_params->philos_nbr);
	if (!*args)
		print_free_exit("malloc args failed", philosophers, forks, args);
}
