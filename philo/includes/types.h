/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:05:57 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/07 17:49:13 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_table
{
	long long				tt_die;
	long long				tt_eat;
	long long				tt_sleep;
	long long				must_eat;
	long long				t_start;
	size_t					n_philosophers;
	struct s_philosopher	*philosophers;
	pthread_mutex_t			mutex;
}	t_table;

typedef enum e_philosopher_state
{
	THINKING,
	EATING,
	SLEEPING
}	t_philosopher_state;

typedef struct s_philosopher
{
	size_t					id;
	t_philosopher_state		state;
	long long				t_meal;
	long long				meals;
	pthread_t				thread;
	pthread_mutex_t			fork;
	pthread_mutex_t			*neighbour_fork;
	struct s_table			*table;
	struct s_philosopher	*next;
}	t_philosopher;

t_table			*setup_table(size_t n_philosophers, long long tt_die,
					long long tt_eat, long long tt_sleep, long long must_eat);
t_philosopher	*add_philosopher(t_table *table, t_philosopher *philosopher);
void			pop_philosopher(t_table *table, t_philosopher *philosopher);
void			destroy_table(t_table *table);
t_philosopher	*new_philosopher(size_t id, t_table *table);
void			destroy_philosopher(t_philosopher *philosopher);

#endif
