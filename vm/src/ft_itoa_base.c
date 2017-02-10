/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 19:55:22 by sjang             #+#    #+#             */
/*   Updated: 2017/02/09 19:55:23 by sjang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa_base(int value, int base)
{
	int result;
	int mod;
	int size;
	int i;
	int minusflag;
	char *str;

	if (value == 0)
	{
		str = (char*)malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	size = 0;
	result = value;
	while (result != 0)
	{
		result /= base;
		size++; 
	}
	minusflag = ((value < 0) && base == 10) ? 1 : 0;
	if (minusflag)
		size++;
	str = (char*)malloc(sizeof(char) * (size + 1));
	if (minusflag)
		str[0] = '-';
	str[size] = 0;
	result = value;
	i = 1;
	while (i <= size - minusflag)
	{
		mod = result % base;
		if (value < 0)
			mod *= -1;
		if (mod < 10)
			str[size - i] = '0' + mod;
		else
			str[size - i] = 'a' + mod - 10;
		result /= base;
		i++;
	}
	return (str);
}
