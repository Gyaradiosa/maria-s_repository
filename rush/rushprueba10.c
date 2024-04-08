/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushprueba10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:26:04 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/17 23:26:13 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *trim(char *str) {
    while (*str && *str == ' ')
        str++;
    int len = strlen(str);
    while (len > 0 && str[len - 1] == ' ')
        str[--len] = '\0';
    return str;
}

char *my_strdup(const char *src) {
    size_t len = strlen(src) + 1;
    char *dest = malloc(len);
    if (dest == NULL) {
        write(STDERR_FILENO, "Memory allocation error\n", 24);
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < len; i++) {
        dest[i] = src[i];
    }
    return dest;
}

char *convert_to_written_form(unsigned long long int number, char *dict_path) {
    char buffer[BUFFER_SIZE];
    char *result = NULL;
    int fd = open(dict_path, O_RDONLY);
    if (fd == -1) {
        write(STDERR_FILENO, "Dict Error\n", 11);
        exit(EXIT_FAILURE);
    }

    while (read(fd, buffer, BUFFER_SIZE) > 0) {
        char *token = strtok(buffer, "\n");
        while (token != NULL) {
            char *delimiter = strchr(token, ':');
            if (delimiter != NULL) {
                *delimiter = '\0'; // Separar número y texto
                unsigned long long int current_number = strtoull(trim(token), NULL, 10);
                char *current_text = trim(delimiter + 1);
                if (number == current_number) {
                    result = my_strdup(current_text);
                    close(fd);
                    return result;
                }
            } else {
                write(STDERR_FILENO, "Dict Error\n", 11);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, "\n");
        }
    }
    close(fd);

    write(STDERR_FILENO, "Dict Error\n", 11);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        write(STDERR_FILENO, "Usage: ./rush-02 <number> <dictionary>\n", 40);
        return EXIT_FAILURE;
    }

    char *number_str = argv[1];
    char *dict_path = argv[2];

    // Convertir el número en una cadena a un número entero sin signo
    unsigned long long int number = strtoull(number_str, NULL, 10);

    if (number == 0) {
        char *result = convert_to_written_form(number, dict_path);
        write(STDOUT_FILENO, result, strlen(result));
        write(STDOUT_FILENO, "\n", 1);
        free(result);
        return EXIT_SUCCESS;
    }

    char *result = convert_to_written_form(number, dict_path);
    if (result != NULL) {
        write(STDOUT_FILENO, result, strlen(result));
        write(STDOUT_FILENO, "\n", 1);
        free(result);
        return EXIT_SUCCESS;
    } else {
        write(STDERR_FILENO, "Dict Error\n", 11);
        return EXIT_FAILURE;
    }
}

