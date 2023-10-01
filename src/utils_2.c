/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:16:16 by slombard          #+#    #+#             */
/*   Updated: 2023/10/01 12:16:19 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	death_and_finished_lock(t_philosopher_args *args)
{
	pthread_mutex_lock(&args->sim_params->death_mutex);
	pthread_mutex_lock(&args->sim_params->finished_mutex);
}

void	death_and_finished_unlock(t_philosopher_args *args)
{
	pthread_mutex_unlock(&args->sim_params->finished_mutex);
	pthread_mutex_unlock(&args->sim_params->death_mutex);
}
