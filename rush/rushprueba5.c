/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushprueba5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:19:36 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/17 23:19:52 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *trim(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;

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

char *my_strdup(const char *src) {
    size_t len = strlen(src) + 1;
    char *dest = malloc(len);
    if (dest == NULL) {
        // Manejo del error de asignación de memoria
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
            // Parse the line from the dictionary
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
                // Invalid line format in the dictionary
                write(STDERR_FILENO, "Dict Error\n", 11);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, "\n");
        }
    }
    close(fd);

    // No matching number found in the dictionary
    write(STDERR_FILENO, "Dict Error\n", 11);
    exit(EXIT_FAILURE);
}

// Función para obtener la cantidad de dígitos en un número
int count_digits(unsigned long long int number) {
    int count = 0;
    while (number != 0) {
        number /= 10;
        ++count;
    }
    return count;
}

// Función para obtener el dígito en una posición específica de un número
int get_digit_at(unsigned long long int number, int position) {
    while (position--) {
        number /= 10;
    }
    return number % 10;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(STDERR_FILENO, "Usage: ./rush-02 <number>\n", 27);
        return EXIT_FAILURE;
    }

    char *dict_path = "./dict_eng.txt"; // Cambia el nombre del archivo de diccionario
    unsigned long long int number;

    number = strtoull(argv[1], NULL, 10);

    if (number == 0) {
        char *result = convert_to_written_form(number, dict_path);
        write(STDOUT_FILENO, result, strlen(result));
        write(STDOUT_FILENO, "\n", 1);
        free(result);
        return EXIT_SUCCESS;
    }

    int digits = count_digits(number);
    char *composite_result = NULL;

    if (digits == 1) {
        composite_result = convert_to_written_form(number, dict_path);
    } else if (digits > 1) {
        unsigned long long int remaining = number;
        unsigned long long int divisor = 1;
        while (remaining >= 10) {
            remaining /= 10;
            divisor *= 10;
        }

        while (divisor > 0) {
            int digit = number / divisor;
            composite_result = realloc(composite_result, (strlen(composite_result) + 20) * sizeof(char));
            strcat(composite_result, convert_to_written_form(digit * divisor, dict_path));
            strcat(composite_result, " ");
            number %= divisor;
            divisor /= 10;
        }
    }

    if (composite_result != NULL) {
        write(STDOUT_FILENO, composite_result, strlen(composite_result));
        write(STDOUT_FILENO, "\n", 1);
        free(composite_result);
    } else {
        write(STDERR_FILENO, "Dict Error\n", 11);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
