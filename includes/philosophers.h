/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:53:42 by slombard          #+#    #+#             */
/*   Updated: 2023/10/15 18:28:40 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>  // threads, mutex
# include <stdio.h>    // printf - substitute with putstr, to write again,
# include <stdlib.h>   // malloc, free
# include <sys/time.h> // gettimeftheday
# include <unistd.h>   // usleep and write

typedef enum e_philosopher_state
{
	HAS_FORK = 1,
	HAS_FORKS,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}						t_philosopher_state;

typedef enum e_death_state
{
	EVERYONE_ALIVE = 0,
	SOMEONE_DIED
}						t_death_state;

typedef enum e_hunger_state
{
	PHILOSOPHERS_NOT_FULL_YET = 0,
	PHILOSOPHERS_ARE_FULL
}						t_hunger_state;

// TODO: eventually change to meal check;
typedef enum e_hunger_check
{
	ON = 0,
	OFF
}						t_hunger_check;

typedef enum e_death_announced
{
	NO = 0,
	YES
}						t_death_announced;

/* The fork.id is just for debugging reason*/
typedef struct s_fork
{
	int					id;
	pthread_mutex_t		mutex_fork;
}						t_fork;

typedef struct s_philosopher
{
	int					id;
	pthread_t			p_thread;
	t_philosopher_state	state;
	t_fork				*fork_right;
	t_fork				*fork_left;
	long long			last_meal_ts;
	int					meals_eaten;
	int					meals_to_eat;

}						t_philosopher;

typedef struct s_simulation_parameters
{
	int					philos_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	struct timeval		start_time;
	t_death_state		death_state;
	t_death_announced	death_announced;
	int					nbr_of_times_each_philo_must_eat;
	int					total_meals_to_be_eaten;
	int					total_meals_eaten;
	t_hunger_check		hunger_check;
	t_hunger_state		hunger_state;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		death_mutex;

}						t_sim_params;

typedef struct s_philosopher_args
{
	t_philosopher		*philosopher;
	t_sim_params		*sim_params;
	pthread_mutex_t		*print_mutex;
	pthread_mutex_t		*meal_mutex;
	pthread_mutex_t		*death_mutex;
}						t_philosopher_args;

/* Single philosopher edge case*/

void					handle_single_philo(t_philosopher_args *args);

/* Init */
void					init_sim_params(t_sim_params *sim_params, int argc,
							char **argv);
void					allocate_memory(t_sim_params *sim_params,
							t_philosopher **philosophers, t_fork **forks,
							t_philosopher_args **args);
void					init_args(t_sim_params *sim_params,
							t_philosopher *philosophers,
							t_philosopher_args *args);
void					init_philos(t_sim_params *sim_params,
							t_philosopher *philosophers, t_fork *forks);
void					setup_env(t_sim_params *sim_params,
							t_philosopher *philosophers, t_fork *forks,
							t_philosopher_args *args);
void					init_forks(t_sim_params *sim_params, t_fork *forks);
void					start_simulation(t_philosopher *philosophers,
							t_philosopher_args *args, t_sim_params *sim_params);

/* Prints */
void					print_and_exit(char *str);
void					print_free_exit(char *str, t_philosopher **philosophers,
							t_fork **forks, t_philosopher_args **args);
// void					print_state(t_philosopher *philosopher,
// 							t_sim_params *sim_params,
// 							t_hold_death_mutex hold_death_mutex);
void					print_state(t_philosopher *philosopher,
							t_sim_params *sim_params);
void					print_state_no_lock_death(t_philosopher *philosopher,
							t_sim_params *sim_params);

/* Utils */
int						ft_isdigit(int c);
int						ft_atoi(const char *str);
long long				current_timestamp(struct timeval start_time);
void					destroy_and_free(t_sim_params *sim_params,
							t_philosopher *philosophers, t_fork *forks,
							t_philosopher_args *args);

/* Checks */
void					check_input(int argc, char **argv);
int						check_death_condition(t_philosopher *philosopher,
							t_sim_params *sim_params);
int						check_meal_condition(t_sim_params *sim_params);
int						check_death(t_philosopher *philosopher,
							t_sim_params *sim_params,
							struct timeval start_time);

/* Routines */
void					*eat_sleep_think(void *arg);
int						eat_routine(t_philosopher *philosopher,
							t_sim_params *sim_params);
int						sleep_routine(t_philosopher *philosopher,
							t_sim_params *sim_params);
void					think_routine(t_philosopher *philosopher,
							t_sim_params *sim_params);

int						is_about_to_die(t_philosopher *philosopher,
							t_sim_params *sim_params, int time_to_consider);
void					sleep_and_die(t_philosopher *philosopher,
							t_sim_params *sim_params);
void					increase_meals(t_philosopher *philosopher,
							t_sim_params *sim_params);

/* Forks */
void					pick_up_fork(t_fork *fork);
int						pick_up_forks(t_philosopher *philosopher,
							t_sim_params *sim_params);
void					drop_forks(t_fork *fork_right, t_fork *fork_left);

#endif
