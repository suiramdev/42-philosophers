/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 16:19:34 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/27 15:19:10 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	die_lonely(t_philosopher *philosopher, t_table *table)
{
	log_action(philosopher, "has taken a fork");
	log_action(philosopher, "died");
	pthread_mutex_lock(&table->mutex);
	table->stop = true;
	pthread_mutex_unlock(&table->mutex);
}

static bool	run_eat(t_philosopher *philosopher, t_table *table)
{
	take_forks(philosopher);
	log_action(philosopher, "is eating");
	pthread_mutex_lock(&philosopher->mutex);
	philosopher->t_meal = now();
	pthread_mutex_unlock(&philosopher->mutex);
	p_usleep(table->settings.tt_eat);
	pthread_mutex_lock(&philosopher->mutex);
	philosopher->meals++;
	pthread_mutex_unlock(&philosopher->mutex);
	leave_forks(philosopher);
	return (true);
}

static bool	run_sleep(t_philosopher *philosopher, t_table *table)
{
	log_action(philosopher, "is sleeping");
	p_usleep(table->settings.tt_sleep);
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
	log_action(philosopher, "is thinking");
	if (!philosopher->neighbour_fork)
		return (die_lonely(philosopher, table), NULL);
	if (philosopher->id % 2)
		p_usleep(table->settings.tt_eat / 50);
	while (!should_stop(table))
	{
		if (!run_eat(philosopher, table))
			return (NULL);
		if (!run_sleep(philosopher, table))
			return (NULL);
		log_action(philosopher, "is thinking");
		p_usleep(table->settings.tt_eat / 50);
	}
	return (NULL);
}
