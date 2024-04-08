/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:17:06 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/14 16:33:11 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>//

void	ft_swap(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

/*int main(void)
{
	int test1;
	int test2;

	test1 = 5;
	test2 = 15;
	ft_swap(&test1, &test2);
	printf("%d", test1, test2);
	return (0);
}*/
