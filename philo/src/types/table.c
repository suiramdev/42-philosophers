/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:26:15 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/08 16:49:59 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Create a new table
/// @param n_philosophers The number of philosophers at the table
/// @param tt_die The time to die in milliseconds
/// @param tt_eat The time to eat in milliseconds
/// @param tt_sleep The time to sleep in milliseconds
/// @param must_eat The number of times each philosopher must eat
/// before the simulation ends
/// @return The table created, or NULL if an error occured
t_table	*setup_table(t_table_settings settings)
{
	t_table	*table;
	size_t	i;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->settings = settings;
	table->t_start = now() + (settings.n_philosophers / 2) * settings.tt_eat;
	i = 0;
	table->philosophers = NULL;
	while (i < settings.n_philosophers)
	{
		if (!add_philosopher(table, new_philosopher(i, table)))
		{
			destroy_table(table);
			return (NULL);
		}
		i++;
	}
	pthread_mutex_init(&table->mutex, NULL);
	return (table);
}

/// @brief Add a philosopher to the table
/// @param table The table to add the philosopher to
/// @param philosopher The philosopher to add
/// @return The philosopher added, or NULL if an error occured
/// @note The philosopher is added at the end of the list, to the left of the
/// last philosopher
t_philosopher	*add_philosopher(t_table *table, t_philosopher *philosopher)
{
	t_philosopher	*last;

	if (!philosopher)
		return (NULL);
	philosopher->table = table;
	if (!table->philosophers)
	{
		table->philosophers = philosopher;
		return (philosopher);
	}
	last = table->philosophers;
	while (last->next)
		last = last->next;
	last->next = philosopher;
	philosopher->neighbour_fork = &last->fork;
	table->philosophers->neighbour_fork = &philosopher->fork;
	return (philosopher);
}

/// @brief Destroy a table
/// @param table The table to destroy
/// @return void
void	destroy_table(t_table *table)
{
	t_philosopher	*tmp;

	while (table->philosophers)
	{
		tmp = table->philosophers;
		table->philosophers = table->philosophers->next;
		destroy_philosopher(tmp);
	}
	pthread_mutex_destroy(&table->mutex);
	free(table);
}
