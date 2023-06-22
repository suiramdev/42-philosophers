/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:03:10 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/22 16:41:20 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include <stddef.h>

# define RED "\x1B[31m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define WHITE "\x1B[37m"
# define RESET "\x1B[0m"

void		log_action(t_philosopher *philosopher, char *action, char *color);
bool		should_stop(t_table *table);
void		stop(t_table *table);
long long	p_atoll(const char *str);
long long	now(void);
void		p_usleep(long long ms);

#endif
