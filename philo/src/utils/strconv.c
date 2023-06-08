/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strconv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:19:25 by mnouchet          #+#    #+#             */
/*   Updated: 2023/06/07 17:54:25 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	p_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ');
}

static int	p_issign(int c)
{
	return (c == '+' || c == '-');
}

static int	p_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/// @brief Convert a string to an integer.
/// @param str The string to convert.
/// @return The integer.
long long	p_atoll(const char *str)
{
	long long	output;
	int			negative;
	size_t		i;

	output = 0;
	negative = 1;
	i = 0;
	while (p_isspace(str[i]))
		i++;
	if (p_issign(str[i]))
	{
		if (str[i] == '-')
			negative = -negative;
		i++;
	}
	while (p_isdigit(str[i]))
	{
		output *= 10;
		output += str[i] - '0';
		i++;
	}
	return (output * negative);
}
