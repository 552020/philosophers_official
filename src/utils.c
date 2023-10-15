/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 00:31:46 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 00:57:19 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

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
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
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

// TODO: we don't need the global variable total_meals_eaten I guess. Remove it.
void	increase_meals(t_philosopher *philosopher, t_sim_params *sim_params)
{
	philosopher->meals_eaten++;
	pthread_mutex_lock(&sim_params->meal_mutex);
	sim_params->total_meals_eaten++;
	if (sim_params->total_meals_eaten >= sim_params->total_meals_to_be_eaten)
		sim_params->hunger_state = PHILOSOPHERS_ARE_FULL;
	pthread_mutex_unlock(&sim_params->meal_mutex);
}
