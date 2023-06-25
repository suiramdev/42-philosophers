/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:41:47 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/08 21:32:12 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "types.h"

static t_table_settings	*table_settings(int argc, char **argv)
{
	t_table_settings	*settings;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, "Error: wrong number of arguments\n", 33);
		return (NULL);
	}
	settings = malloc(sizeof(t_table_settings));
	if (!settings)
		return (NULL);
	settings->n_philosophers = p_atoll(argv[1]);
	settings->tt_die = p_atoll(argv[2]);
	settings->tt_eat = p_atoll(argv[3]);
	settings->tt_sleep = p_atoll(argv[4]);
	settings->must_eat = 0;
	if (argc == 6)
		settings->must_eat = p_atoll(argv[5]);
	if (settings->n_philosophers < 1 || settings->tt_die < 1
		|| settings->tt_eat < 1 || settings->tt_sleep < 1
		|| (argc == 6 && settings->must_eat < 1))
	{
		write(STDERR_FILENO, "Error: wrong arguments\n", 23);
		return (free(settings), NULL);
	}
	return (settings);
}

static void	join_threads(t_table *table, pthread_t supervisor,
	t_philosopher *philosopher)
{
	pthread_join(supervisor, NULL);
	philosopher = table->philosophers;
	while (philosopher)
	{
		pthread_join(philosopher->thread, NULL);
		philosopher = philosopher->next;
	}
}

int	main(int argc, char **argv)
{
	t_table_settings	*settings;
	t_table				*table;
	t_philosopher		*philosopher;
	pthread_t			supervisor;

	settings = table_settings(argc, argv);
	if (!settings)
		return (EXIT_FAILURE);
	table = new_table(*settings);
	if (!table)
		return (free(settings), EXIT_FAILURE);
	philosopher = table->philosophers;
	while (philosopher)
	{
		pthread_create(&philosopher->thread, NULL, philosopher_routine,
			philosopher);
		philosopher = philosopher->next;
	}
	pthread_create(&supervisor, NULL, supervisor_routine, table);
	join_threads(table, supervisor, philosopher);
	destroy_table(table);
	free(settings);
	return (EXIT_SUCCESS);
}
