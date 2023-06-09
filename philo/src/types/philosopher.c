/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:15:16 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/27 15:18:44 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Create a new philosopher
/// @param id The philosopher's id
/// @return The philosopher created, or NULL if an error occured
t_philosopher	*new_philosopher(size_t id, t_table *table)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (!philosopher)
		return (NULL);
	philosopher->id = id;
	philosopher->table = table;
	philosopher->t_meal = table->t_start;
	philosopher->meals = 0;
	philosopher->neighbour_fork = NULL;
	philosopher->next = NULL;
	if (pthread_mutex_init(&philosopher->mutex, NULL))
		return (destroy_philosopher(philosopher), NULL);
	if (pthread_mutex_init(&philosopher->fork, NULL))
		return (destroy_philosopher(philosopher), NULL);
	return (philosopher);
}

void	take_forks(t_philosopher *philosopher)
{
	if (philosopher->id % 2)
	{
		pthread_mutex_lock(&philosopher->fork);
		log_action(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->neighbour_fork);
		log_action(philosopher, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philosopher->neighbour_fork);
		log_action(philosopher, "has taken a fork");
		pthread_mutex_lock(&philosopher->fork);
		log_action(philosopher, "has taken a fork");
	}
}

void	leave_forks(t_philosopher *philosopher)
{
	if (philosopher->id % 2)
	{
		pthread_mutex_unlock(philosopher->neighbour_fork);
		pthread_mutex_unlock(&philosopher->fork);
	}
	else
	{
		pthread_mutex_unlock(&philosopher->fork);
		pthread_mutex_unlock(philosopher->neighbour_fork);
	}
}

/// @brief Destroy a philosopher
/// @param philosopher The philosopher to destroy
/// @return void
void	destroy_philosopher(t_philosopher *philosopher)
{
	pthread_mutex_destroy(&philosopher->mutex);
	pthread_mutex_destroy(&philosopher->fork);
	free(philosopher);
}
