/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:15:25 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/21 19:15:02 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
		i++;
	}
	return (str);
}
/*void ft_putchar (char c)
{
	write(1, &c, 1);
}

int main(void)
{
	int i;
	char str [] = "PATATAAAA";
	
	i =0;
	ft_strlowcase(str);
	while(str[i] !='\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	return(0);
}*/
