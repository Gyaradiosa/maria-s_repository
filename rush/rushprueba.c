/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushprueba.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 22:46:21 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/17 22:59:37 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *custom_strcpy(char *dest, const char *src) {
    char *start = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return start;
}

int custom_strlen(const char *str) {
    int len = 0;
    while (*str++) {
        len++;
    }
    return len;
}

char *custom_strchr(const char *str, int c) {
    while (*str) {
        if (*str == c) {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}

char *custom_strtok(char *str, const char *delim) {
    static char *buffer = NULL;
    if (str != NULL) {
        buffer = str;
    }
    if (buffer == NULL || *buffer == '\0') {
        return NULL;
    }
    char *token = buffer;
    while (*buffer) {
        if (custom_strchr(delim, *buffer) != NULL) {
            *buffer++ = '\0';
            return token;
        }
        buffer++;
    }
    return token;
}

char *custom_trim(char *str) {
    char *start = str;
    char *end = str + custom_strlen(str) - 1;

    // Eliminar espacios en blanco al principio
    while (*start && *start == ' ')
        start++;

    // Eliminar espacios en blanco al final
    while (end > start && *end == ' ')
        end--;

    // Agregar terminador nulo al final
    *(end + 1) = '\0';

    return start;
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
        char *token = custom_strtok(buffer, "\n");
        while (token != NULL) {
            // Parse the line from the dictionary
            char *delimiter = custom_strchr(token, ':');
            if (delimiter != NULL) {
                *delimiter = '\0'; // Separar número y texto
                unsigned long long int current_number = strtoull(custom_trim(token), NULL, 10);
                char *current_text = custom_trim(delimiter + 1);
                if (number == current_number) {
                    result = strdup(current_text);
                    close(fd);
                    return result;
                }
            } else {
                // Invalid line format in the dictionary
                write(STDERR_FILENO, "Dict Error\n", 11);
                exit(EXIT_FAILURE);
            }
            token = custom_strtok(NULL, "\n");
        }
    }
    close(fd);

    // No matching number found in the dictionary
    write(STDERR_FILENO, "Dict Error\n", 11);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        write(STDERR_FILENO, "Usage: ./rush-02 <number>\n", 27);
        return EXIT_FAILURE;
    }
        
    char *dict_path ="./dict_eng.txt";
    unsigned long long int number;

    if (argc == 2) {
        number = strtoull(argv[1], NULL, 10);
    } else if (argc == 3) {
        dict_path = argv[1];
        number = strtoull(argv[2], NULL, 10);
    } else {
        write(STDERR_FILENO, "Error: Too many arguments\n", 26);
        return EXIT_FAILURE;
    }
    
    char *result = convert_to_written_form(number, dict_path);
    write(STDOUT_FILENO, result, strlen(result));
    write(STDOUT_FILENO, "\n", 1);
    free(result);
    return EXIT_SUCCESS;
}

