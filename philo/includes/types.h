/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:05:57 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/08 16:50:56 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_table_settings
{
	size_t		n_philosophers;
	long long	tt_die;
	long long	tt_eat;
	long long	tt_sleep;
	long long	must_eat;
}	t_table_settings;

typedef struct s_table
{
	t_table_settings		settings;
	long long				t_start;
	bool					stop;
	struct s_philosopher	*philosophers;
	pthread_mutex_t			mutex;
}	t_table;

typedef struct s_philosopher
{
	size_t					id;
	long long				t_meal;
	long long				meals;
	pthread_t				thread;
	pthread_mutex_t			mutex;
	pthread_mutex_t			fork;
	pthread_mutex_t			*neighbour_fork;
	struct s_table			*table;
	struct s_philosopher	*next;
}	t_philosopher;

t_table			*new_table(t_table_settings settings);
t_philosopher	*add_philosopher(t_table *table, t_philosopher *philosopher);
void			pop_philosopher(t_table *table, t_philosopher *philosopher);
void			destroy_table(t_table *table);
t_philosopher	*new_philosopher(size_t id, t_table *table);
void			take_forks(t_philosopher *philosopher);
void			leave_forks(t_philosopher *philosopher);
void			destroy_philosopher(t_philosopher *philosopher);

#endif
