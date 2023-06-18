/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:19:34 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/08 16:54:58 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	should_stop(t_table *table)
{
	bool	stop;

	pthread_mutex_lock(&table->mutex);
	stop = table->stop;
	pthread_mutex_unlock(&table->mutex);
	return (stop);
}

static bool	run_eat(t_philosopher *philosopher, t_table *table)
{
	if (should_stop(table))
		return (false);
	log_action(philosopher, "is thinking");
	pthread_mutex_lock(lower_fork(philosopher));
	log_action(philosopher, "has taken a fork");
	if (philosopher->neighbour_fork == NULL || should_stop(table))
	{
		pthread_mutex_unlock(lower_fork(philosopher));
		return (false);
	}
	pthread_mutex_lock(higher_fork(philosopher));
	log_action(philosopher, "has taken a fork");
	log_action(philosopher, "is eating");
	philosopher->t_meal = now();
	philosopher->state = EATING;
	philosopher->meals++;
	p_usleep(table->settings.tt_eat);
	pthread_mutex_unlock(higher_fork(philosopher));
	pthread_mutex_unlock(lower_fork(philosopher));
	return (true);
}

static bool	run_sleep(t_philosopher *philosopher, t_table *table)
{
	if (should_stop(table))
		return (false);
	log_action(philosopher, "is sleeping");
	philosopher->state = SLEEPING;
	p_usleep(table->settings.tt_sleep);
	philosopher->state = THINKING;
	return (true);
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
			if (!run_eat(philosopher, table))
				return (NULL);
		}
		if (!run_sleep(philosopher, table))
			return (NULL);
	}
	return (NULL);
}
