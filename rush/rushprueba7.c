/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushprueba7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:22:44 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/17 23:22:49 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Función para eliminar los espacios en blanco al principio y al final de una cadena
char *trim(char *str) {
    while (*str && *str == ' ')
        str++;
    int len = strlen(str);
    while (len > 0 && str[len - 1] == ' ')
        str[--len] = '\0';
    return str;
}

// Función para asignar memoria y copiar una cadena
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

// Función para buscar y obtener la representación en palabras de un número en el diccionario
char *convert_to_written_form(unsigned long long int number, char *dict_path) {
    char buffer[BUFFER_SIZE];
    char *result = NULL;
    int fd = open(dict_path, O_RDONLY);
    if (fd == -1) {
        // Error al abrir el archivo de diccionario
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
                // Formato de línea inválido en el diccionario
                write(STDERR_FILENO, "Dict Error\n", 11);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, "\n");
        }
    }
    close(fd);

    // No se encontró el número en el diccionario
    write(STDERR_FILENO, "Dict Error\n", 11);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        // Se proporcionó un número incorrecto de argumentos
        write(STDERR_FILENO, "Usage: ./rush-02 <number>\n", 27);
        return EXIT_FAILURE;
    }

    char *dict_path = "./dict_eng.txt"; // Cambiar ruta según la ubicación del archivo de diccionario
    unsigned long long int number;

    number = strtoull(argv[1], NULL, 10);

    if (number == 0) {
        // Manejo del caso especial del número cero
        char *result = convert_to_written_form(number, dict_path);
        write(STDOUT_FILENO, result, strlen(result));
        write(STDOUT_FILENO, "\n", 1);
        free(result);
        return EXIT_SUCCESS;
    }

    // Buscar el número compuesto en el diccionario
    char *result = convert_to_written_form(number, dict_path);
    if (result != NULL) {
        // Imprimir la representación en palabras del número
        write(STDOUT_FILENO, result, strlen(result));
        write(STDOUT_FILENO, "\n", 1);
        free(result);
        return EXIT_SUCCESS;
    } else {
        // Error al encontrar el número en el diccionario
        write(STDERR_FILENO, "Dict Error\n", 11);
        return EXIT_FAILURE;
    }
}
