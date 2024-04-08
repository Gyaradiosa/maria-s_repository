# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rush                                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/17 18:32:00 by maduarte          #+#    #+#              #
#    Updated: 2024/03/17 19:54:55 by maduarte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#include <unistd.h>
#include <fcntl.h>
#include <stdLib.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int open(const char *pathname, int flags)
{

}
ssize_t read(int fd, void *buf, size_t count)
{

}

int close(int fd)
{

}

void *malloc(size_t size)
{
	return malloc(size);
}
void free(void *ptr)
{
	int n;

	n = //n//;
	ptr = (int*)malloc(n * sizeof(int));
	if (ptr == '\0')
	{
		write(1, //"error"/, 5);
		exit(0);
	}
	else
	{
		write(1, // //, 1);
	}
	free(ptr);
}	

char *itoa (int value, char *res, int base) //o Itoa(long)//
{

}


int	main(void)
{
	int *ptr;
	ptr = (int*)malloc(n * sizeof(int));
    if (ptr == '\0')
    {
        write(1, //"error"/, 5);
        exit(0);
    }

	free(ptr);
	return(0);
}
