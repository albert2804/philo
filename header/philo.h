/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aestraic <aestraic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:58:50 by aestraic          #+#    #+#             */
/*   Updated: 2023/02/06 19:11:12 by aestraic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <memory.h>
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

enum e_PHILO
{
	FORK = 0,
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	DEATH = 4,
	EATEN = 5,
};

//STRUCTS
/**
 * This philostruct stores all information about each philosphers.
 * @param n philospher number/ threadnumber
 * @param t2_die time to die
 * @param t2_eat time to eat
 * @param t2_sleep time to sleep
 * @param t_die deathtime
 * @param t_eat starttime eat
 * @param t_sleep starttime sleep
 * @param t_think endtime think
 * @param die boolean to check if philo died
 * @param eat boolean to check if philo is eating
 * @param sleep boolean to check if philo is sleeping
 * @param think boolean to check if philo is thinking
 * @param n_eat number of times eaten
 * @param table table_struct with all essential information
 */
typedef struct s_philo
{
	int				n;
	int				t2_die;
	int				t2_eat;
	int				t2_sleep;
	bool			eat;
	int				n_eat;
	int				eat_total;
	long long		t_eat;
	bool			die;
	struct s_table	*table;
}			t_philo;

/**
 * Malloc Struct used later for freeing
*/
typedef struct s_alloc
{
	pthread_t		*thread_array;
	t_philo			*philo_array;
	pthread_mutex_t	*forks;
}			t_alloc;
/**
 * Table has all philosophers, so it inherits the philo_struct
 * @param n_philos total count of philosophers
 * @param i universal count_varriable, used for eat state
 * @param j universal count_varriable, used for sleep state
 * @param k universal count_varriable, used for think state
 * @param eat flag if all philo on the table have eaten
 * @param n_eat number of meals, each philo ha to eat at least
 * @param die flag if one philo on the table died
 * @param philo_die tells which philosopher died, also printflag
 * @param starttime starttime
 * @param delta current timestamp - starttime
 * @param thread_array stores all philosphers(threads) in this array
 * @param forks forks are mutexes
 * @param allocations allocationsstruct for later cleanup function
 * @param philo_array stores all information of the philo_struct
 */
typedef struct s_table
{
	int				i;
	int				j;
	int				k;
	int				die_philo;
	int				n_philos;
	bool			eat;
	int				n_eat;
	bool			die;
	long long		die_time;
	long long		starttime;
	long long		delta;
	pthread_t		*thread_array;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_spawn;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_timestamp;
	pthread_mutex_t	mutex;
	t_alloc			allocations;
	t_philo			*philo_array;
}			t_table;

//INIT & UTILS
void		init_philo(int argc, char **argv, t_table *table);
void		ft_cleanup(t_table *table);
void		*advanced_calloc(size_t size, size_t times, void **malloc_struct);
void		init_allocs(char **argv, t_table *table);
void		init_table(char **argv, t_table *table);
void		print(int action, int philo, t_table *table);
void		print_die(long long delta, int philo, t_table *table);
void		set_eatingtime(t_table *table, t_philo *philo);
void		death_checker(t_table *table);
int			ft_atoi(const char *nptr);
int			ft_atoi(const char *nptr);
int			ft_isdigit(int c);
void		nos1(t_table *table);
void		nos2(t_table *table);

//TIME
long long	get_current(void);
long long	get_delta(long long starttime);
void		wait_func(long long time_in_ms);

//ROUTINE
void		*thread_function(void *arg);
void		*thread_obsrv(void *arg);
int			create_philosophers(int nbr, t_table *table);
void		routine(t_philo *philo, t_table *table);
void		eat(t_philo *philo, t_table *table);
void		sleeping(t_philo *philo, t_table *table);
void		think(t_philo *philo, t_table *table);
void		outset(t_philo *philo, t_table *table);
#endif