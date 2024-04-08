/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushprueba2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:29:57 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/03 21:14:18 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_square(int x, int y)
{
	int	x;
	x = 1;
	int	y;
	y = 1;
	if ((i == 1 & j == 1) || (i == 1 & j == y) || (i == x & j == 1 ) || (i == x & j == y))
	{
	write ('o');
 }
	if ((j == 1  || j == y) & (1 < i < x))
	{
	write ('-');
}
	if ((i == 1 || i == x ) & (1 < j < y))
	{
	write('|')
	}
	else
	{
	  write(' ')
		i++;
	}
	i = 1;
	j++;
}

void	rush(int i, int j)
{
}int main(void)
{
	rush (5,3);
	return (0);
}
