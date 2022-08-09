/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvuorenl <rvuorenl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:34:44 by rvuorenl          #+#    #+#             */
/*   Updated: 2021/11/19 18:45:39 by rvuorenl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*zero_itoa(void)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * 2);
	if (!ptr)
		return (NULL);
	ptr[0] = '0';
	ptr[1] = '\0';
	return (ptr);
}

static char	*neg_itoa(int n, int size)
{
	char	*ptr;
	long	cpy;

	if (n == 0)
	{
		ptr = zero_itoa();
		return (ptr);
	}
	else
	{
		cpy = n;
		cpy *= -1;
		ptr = (char *)malloc(size + 1);
		if (!ptr)
			return (NULL);
		ptr[size--] = '\0';
		while (cpy > 0)
		{
			ptr[size--] = cpy % 10 + '0';
			cpy /= 10;
		}
	}
	ptr[size] = '-';
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	long	copy;

	copy = n;
	size = 0;
	while (copy != 0)
	{
		copy /= 10;
		size++;
	}
	if (n <= 0)
		return (neg_itoa(n, size + 1));
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (NULL);
	ptr[size] = '\0';
	while (n != 0)
	{
		ptr[--size] = n % 10 + '0';
		n /= 10;
	}
	return (ptr);
}
