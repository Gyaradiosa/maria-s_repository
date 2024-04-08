/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerome2 <alerome2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:56:13 by alerome2          #+#    #+#             */
/*   Updated: 2024/03/18 16:38:09 by alerome2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
void map (int x, int y)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < x)
	{
		while (j < y)
		{
			write(1,".",1);
			j++;
		}
		j=0;
		write(1,"\n",1);
		i++;
	}
}

#include <stdio.h>
int main(int argc, char *argv[])
{
	char *temp_argument;

	temp_argument = argv[1];
	printf("Hola %s",argv[1]);
	if(argc == 0)
	{
		write(3, "Error: Map Expected",19);
		return 0;
	}
	map(4, 5);
	//Leer un archivo
	return (0);
}
