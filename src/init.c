/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:16:04 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 18:29:18 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_sim_params(t_sim_params *sim_params, int argc, char **argv)
{
	if (argc == 5)
	{
		sim_params->hunger_check = OFF;
		sim_params->hunger_state = PHILOSOPHERS_NOT_FULL_YET;
		sim_params->nbr_of_times_each_philo_must_eat = 0;
	}
	if (argc == 6)
	{
		sim_params->hunger_check = ON;
		sim_params->hunger_state = PHILOSOPHERS_NOT_FULL_YET;
		sim_params->nbr_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	}
	sim_params->philos_nbr = ft_atoi(argv[1]);
	sim_params->time_to_die = ft_atoi(argv[2]);
	sim_params->time_to_eat = ft_atoi(argv[3]);
	sim_params->time_to_sleep = ft_atoi(argv[4]);
	sim_params->death_state = EVERYONE_ALIVE;
	sim_params->death_announced = NO;
	sim_params->total_meals_to_be_eaten = sim_params->philos_nbr
		* sim_params->nbr_of_times_each_philo_must_eat;
	if (gettimeofday(&sim_params->start_time, NULL) == -1)
		print_and_exit("Error: gettimeofday failed");
}

void	init_philos(t_sim_params *sim_params, t_philosopher *philos,
		t_fork *forks)
{
	int	i;

	i = 0;
	while (i < sim_params->philos_nbr)
	{
		philos[i].id = i + 1;
		philos[i].state = THINKING;
		if (i == 0)
		{
			philos[i].fork_left = &forks[i];
			philos[i].fork_right = &forks[sim_params->philos_nbr - 1];
		}
		else
		{
			philos[i].fork_left = &forks[i];
			philos[i].fork_right = &forks[i - 1];
		}
		philos[i].last_meal_ts = current_timestamp(sim_params->start_time);
		philos[i].meals_eaten = 0;
		philos[i].meals_to_eat = sim_params->nbr_of_times_each_philo_must_eat;
		i++;
	}
}

void	init_forks(t_sim_params *sim_params, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < sim_params->philos_nbr)
	{
		forks[i].id = i + 1;
		if (pthread_mutex_init(&forks[i].mutex_fork, NULL))
			printf("Error initializing mutex for fork %d\n", i);
		i++;
	}
}

void	init_args(t_sim_params *sim_params, t_philosopher *philosophers,
		t_philosopher_args *args)
{
	int	i;

	i = 0;
	while (i < sim_params->philos_nbr)
	{
		args[i].philosopher = &philosophers[i];
		args[i].sim_params = sim_params;
		args[i].print_mutex = &sim_params->print_mutex;
		args[i].meal_mutex = &sim_params->meal_mutex;
		args[i].death_mutex = &sim_params->death_mutex;
		i++;
	}
}

void	setup_env(t_sim_params *sim_params, t_philosopher *philosophers,
		t_fork *forks, t_philosopher_args *args)
{
	pthread_mutex_init(&sim_params->print_mutex, NULL);
	pthread_mutex_init(&sim_params->meal_mutex, NULL);
	pthread_mutex_init(&sim_params->death_mutex, NULL);
	init_philos(sim_params, philosophers, forks);
	init_forks(sim_params, forks);
	init_args(sim_params, philosophers, args);
}
