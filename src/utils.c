/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:15:59 by slombard          #+#    #+#             */
/*   Updated: 2023/10/01 12:16:01 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc < 5 || argc > 6)
		print_and_exit("Usage: ./philo number_of_philosophers time_to_die time_to_eat "
						"time_to_sleep [number_of_times_each_philospher_must_eat]\n");
	// while (++i < argc)
	// {
	// 	if (argv[i][0] == '-')
	// 		print_and_exit("Error: arguments an only be positive integer\n");
	// 	while (argv[i][j])
	// 	{
	// 		while (argv[i][j] == '+')
	// 			j++;
	// 		if (argv[i][j] < '0' || argv[i][j] > '9')
	// 			print_and_exit("Error: arguments an only be positive integer\n");
	// 		j++;
	// 	}
	// 	j = 0;
	// }
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				print_and_exit("Error: Invalid input");
			j++;
		}
		i++;
	}
}

// long long	ft_atoi(const char *nptr)
// {
// 	long long	result;
// 	int			neg;

// 	result = 0;
// 	neg = 1;
// 	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
// 		nptr++;
// 	if (*nptr == '-' || *nptr == '+')
// 	{
// 		if (*nptr++ == '-')
// 			neg *= -1;
// 	}
// 	while (*nptr >= '0' && *nptr <= '9')
// 		result = result * 10 + neg * (*nptr++ - '0');
// 	return (result);
// }

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-')
	{
		sign = -1;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	destroy_free(t_simulation_parameters *sim_params)
{
	int	i;

	if (pthread_mutex_destroy(&sim_params->print_mutex))
		print_and_exit("Error: pthread_mutex_destroy failed\n ");
	if (pthread_mutex_destroy(&sim_params->finished_mutex))
		print_and_exit("Error: pthread_mutex_destroy failed\n ");
	if (pthread_mutex_destroy(&sim_params->death_mutex))
		print_and_exit("Error: pthread_mutex_destroy failed\n ");
	i = -1;
	while (++i < sim_params->number_of_philos)
	{
		if (pthread_mutex_destroy(&sim_params->forks[i]))
			print_and_exit("Error: pthread_mutex_destroy failed\n ");
		if (pthread_mutex_destroy(&sim_params->philos[i].meal_mutex))
			print_and_exit("Error: pthread_mutex_destroy failed\n ");
	}
	free(sim_params->philos);
	free(sim_params->forks);
	free(sim_params->args);
}

long long	current_timestamp(struct timeval start_time)
{
	struct timeval	now;
	long long		elapsed_time;

	gettimeofday(&now, NULL);
	elapsed_time = (now.tv_sec - start_time.tv_sec) * 1000;
	elapsed_time += (now.tv_usec - start_time.tv_usec) / 1000;
	return (elapsed_time);
}

void	handle_single_philosopher_case(t_philosopher_args *args)
{
	print_state(args, HAS_FORK);
	usleep(args->sim_params->time_to_die * 1000);
}
