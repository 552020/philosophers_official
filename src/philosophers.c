/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:09:40 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 16:01:34 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eat_sleep_think(void *arg)
{
	t_philosopher_args	*args;

	args = (t_philosopher_args *)arg;
	print_state(args->philosopher, args->sim_params);
	while (1)
	{
		if (check_death_condition(args->philosopher, args->sim_params))
			break ;
		if (check_meal_condition(args->sim_params))
			break ;
		if (!eat_routine(args->philosopher, args->sim_params))
			break ;
		if (check_death_condition(args->philosopher, args->sim_params))
			break ;
		if (check_meal_condition(args->sim_params))
			break ;
		if (!sleep_routine(args->philosopher, args->sim_params))
			break ;
		if (check_death_condition(args->philosopher, args->sim_params))
			break ;
		think_routine(args->philosopher, args->sim_params);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_sim_params		sim_params;
	t_philosopher		*philosophers;
	t_fork				*forks;
	t_philosopher_args	*args;

	check_input(argc, argv);
	init_sim_params(&sim_params, argc, argv);
	allocate_memory(&sim_params, &philosophers, &forks, &args);
	setup_env(&sim_params, philosophers, forks, args);
	if (sim_params.philos_nbr == 1)
		handle_single_philo(args);
	else
		start_simulation(philosophers, args, &sim_params);
	destroy_and_free(&sim_params, philosophers, forks, args);
	if (sim_params.death_state != SOMEONE_DIED && sim_params.hunger_check == ON
		&& sim_params.hunger_state == PHILOSOPHERS_ARE_FULL)
		printf("%lld Everyone ate enough\n",
			current_timestamp(sim_params.start_time));
	printf("%lld Exiting program\n", current_timestamp(sim_params.start_time));
	return (0);
}
