/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:03:10 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/08 21:32:32 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include <stddef.h>

void		log_action(t_philosopher *philosopher, char *action);
long long	p_atoll(const char *str);
long long	now(void);
void		p_usleep(long long ms);

#endif
