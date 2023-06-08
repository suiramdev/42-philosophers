/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:18:34 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/07 17:54:39 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	event(t_philosopher *philosopher, char *action)
{
	printf("%lld %zu %s\n", now() - philosopher->table->t_start,
		philosopher->id, action);
}

/// @brief The supervisor's routine
/// @param arg The routine's parameters (t_table) @return void
void	*supervisor_routine(void *arg)
{
	t_table			*table;
	t_philosopher	*philosopher;
	size_t			finished;

	table = (t_table *)arg;
	p_usleep(table->t_start - now());
	while (1)
	{
		finished = 0;
		philosopher = table->philosophers;
		while (philosopher)
		{
			if (table->tt_die <= now() - philosopher->t_meal)
			{
				event(philosopher, "died");
				return (NULL);
			}
			if (table->must_eat > 0 && philosopher->meals >= table->must_eat)
				finished++;
			philosopher = philosopher->next;
		}
		if (finished == table->n_philosophers)
			return (NULL);
	}
	return (NULL);
}

/// @brief The philosopher's routine
/// @param arg The routine's parameters (t_routine_
/// @return void
void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;
	t_table			*table;

	philosopher = (t_philosopher *)arg;
	table = philosopher->table;
	p_usleep(table->t_start - now());
	while (1)
	{
		if (philosopher->state == THINKING)
		{
			event(philosopher, "is thinking");
			pthread_mutex_lock(&philosopher->fork);
			event(philosopher, "has taken a fork");
			if (philosopher->neighbour_fork == NULL)
			{
				event(philosopher, "error: no neighbour fork");
				return (NULL);
			}
			pthread_mutex_lock(philosopher->neighbour_fork);
			event(philosopher, "has taken a fork");
			event(philosopher, "is eating");
			philosopher->t_meal = now();
			philosopher->state = EATING;
			philosopher->meals++;
			p_usleep(table->tt_eat);
			pthread_mutex_unlock(&philosopher->fork);
			pthread_mutex_unlock(philosopher->neighbour_fork);
		}
		event(philosopher, "is sleeping");
		philosopher->state = SLEEPING;
		p_usleep(table->tt_sleep);
		philosopher->state = THINKING;
	}
	return (NULL);
}

