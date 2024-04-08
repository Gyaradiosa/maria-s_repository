/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerome2 <alerome2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:39:50 by alerome2          #+#    #+#             */
/*   Updated: 2024/03/18 18:40:50 by alerome2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
	//size_t buffer_size = 10;
	//char buffer [];

	int fd = open("example_file",O_RDONLY);

	if(fd == -1)
		printf("No se ha abierto el archivo");
	else
		printf("El archivo se ha abierto correctamente\n");

	size_t buffer_size = 1024;
	char buffer[50];
	int bytes_leidos;



	printf("File descriptor: %d\n",fd);
	bytes_leidos = read(fd, buffer, buffer_size);
	printf("Se han leido %d bytes\n", bytes_leidos);
	buffer[buffer_size] = '\0';
	printf("Los bytes leidos son: %s<-\n", buffer);
	
	return (0);
}

