# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
/*   openreadclose.c                                    :+:      :+:    :+:   */
#                                                     +:+ +:+         +:+      #
#    By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/17 19:29:08 by maduarte          #+#    #+#              #
/*   Updated: 2024/03/17 20:19:13 by maduarte         ###   ########.fr       */
#                                                                              #
# **************************************************************************** #

#include <unistd.h>
#include <fcntl.h>
#include <stdLib.h>

int open(const char *dict) 
{
    int fd;

	fd = open(dict, O_RDWR);
    return fd;
}

ssize_t read(int fd, char *buffer, size_t lon)
{
    ssize_t byread; //bytes read//
	byread = read(fd, buffer, long);
    
	if(fd == -1) 
	{
        write(1, "Dict Error \n", 12);
        exit(0);
	}
	else
	{
		return(byread);
	}
}

int close(int fd) 
{
	int res;
    res = close(fd);
	return(res);
}

int main(void)
{
	int fd; //filedescriptor//
	ssize_t
	char buffer
}
