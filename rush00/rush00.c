/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 21:35:12 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/03 22:20:06 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);

void	ft_square(int i, int j, int x, int y)
{
    if ((i == 1 && j == 1) || (i == 1 && j == y))
	{
		ft_putchar('o');		
	}		
	if ((i == x && j == 1 ) || (i == x && j == y))
    {
        ft_putchar('o');
    }
	if ((j == 1  || j == y) && (1 < i < x))
	{
		ft_putchar('-');
	}
	if ((i == 1 || i == x ) && (1 < j < y))
    {
		ft_putchar('|');
	}
	if ((i > 1 && i < x) && (j > 1 && j < y))
	{
		ft_putchar(' ');
	}
}

void	rush(int x, int y)
{
	int i;
	int j;

	i = 1;
	j = 1;
	while (j <= y)
	{
		while (i <= x)
		{
			ft_square(i, j, x, y);
			i++;
		}
		ft_putchar('\n');
		j++;
	}
}
