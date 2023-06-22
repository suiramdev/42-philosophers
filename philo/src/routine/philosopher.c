/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:19:34 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/22 16:51:09 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	run_eat(t_philosopher *philosopher, t_table *table)
{
	log_action(philosopher, "is thinking", BLUE);
	pthread_mutex_lock(lower_fork(philosopher));
	log_action(philosopher, "has taken a fork", WHITE);
	pthread_mutex_lock(higher_fork(philosopher));
	log_action(philosopher, "has taken a fork", WHITE);
	log_action(philosopher, "is eating", YELLOW);
	philosopher->state = EATING;
	pthread_mutex_lock(&philosopher->mutex);
	philosopher->t_meal = now();
	pthread_mutex_unlock(&philosopher->mutex);
	pthread_mutex_unlock(lower_fork(philosopher));
	p_usleep(table->settings.tt_eat);
	pthread_mutex_lock(&philosopher->mutex);
	philosopher->meals++;
	pthread_mutex_unlock(&philosopher->mutex);
	pthread_mutex_unlock(higher_fork(philosopher));
	return (true);
}

static bool	run_sleep(t_philosopher *philosopher, t_table *table)
{
	log_action(philosopher, "is sleeping", MAGENTA);
	philosopher->state = SLEEPING;
	p_usleep(table->settings.tt_sleep);
	philosopher->state = THINKING;
	return (true);
}

static void	die_lonely(t_philosopher *philosopher, t_table *table)
{
	log_action(philosopher, "is thinking", BLUE);
	log_action(philosopher, "has taken a fork", WHITE);
	log_action(philosopher, "died", RED);
	pthread_mutex_lock(&table->mutex);
	table->stop = true;
	pthread_mutex_unlock(&table->mutex);
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
	if (!philosopher->neighbour_fork)
		return (die_lonely(philosopher, table), NULL);
	while (!should_stop(table))
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
