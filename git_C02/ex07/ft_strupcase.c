/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:55:18 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/21 19:12:00 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

char	*ft_strupcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] -= 32;
		}
		i++;
	}
	return (str);
}
/*
void    ft_putchar(char c)
{
	 write(1, &c, 1);
}

int main (void)
{
	char str[] = "patata";
	int i;
	
	i = 0;
	ft_strupcase(str);
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	return(0);
}*/
