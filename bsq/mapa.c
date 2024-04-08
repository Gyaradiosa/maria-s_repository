/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerome2 <alerome2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:50:02 by alerome2          #+#    #+#             */
/*   Updated: 2024/03/18 19:39:08 by alerome2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *mapa()
{
	char *mapa=	".o...o...o\n...o..oo..\n..........\n.oo...o...\n.....o....\n.......oo.";

	return mapa;
}

#include <unistd.h>
int main (void)
{
	int cont =0;
	char  *map = mapa();


	int range_columns=0;
	int up_to_x;
	while(map[cont] != '\0')
	{
		//Legamos a un obstaculo
		if(map[cont] == 'o')
		{
			write(1,"x",1);
			cont++;
		}
		else
		{
		write(1,&map[cont], 1);
		if(map[cont +1] == '\n')
		{
			write(1,"  ",2);
			char columnas = range_columns + '0';
			write(1, &columnas, 1);
			write(1, "\n", 1);
			range_columns = 0;
		}

		range_columns++;
		cont++;
		}
	}
	write(1, "\nPosiciones hasta o: ",21);
	write(1,&range_columns,2);
	write(1,"\n",1);


	return 0;
}
