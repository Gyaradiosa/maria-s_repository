/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:24:48 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/14 16:40:57 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>//

void	ft_ultimate_div_mod(int	*a, int	*b)
{
	int	div;
	int	mod;

	div = *a / *b;
	mod = *a % *b;
	*a = div;
	*b = mod;
}

/*int	main(void)
{
	int x;
	int y;
	int a;
	int b;

	x = 10;
	y = 2;
	a = 0;
	b = 0;
	ft_ultimate_div_mod(&x, &y);
	printf("%i %i\n", x, y);
	return (0);
}*/
