/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushprueba4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:15:17 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/17 23:16:43 by maduarte         ###   ########.fr       */
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

// Función para convertir un entero en una cadena de caracteres
char *int_to_string(unsigned long long int number) {
    // Calcula la cantidad de dígitos en el número
    unsigned long long int temp = number;
    int num_digits = 0;
    while (temp != 0) {
        temp /= 10;
        num_digits++;
    }

    // Crea una cadena con suficiente espacio para los dígitos y el terminador nulo
    char *str = (char *)malloc((num_digits + 1) * sizeof(char));
    if (str == NULL) {
        // Manejo del error de asignación de memoria
        write(STDERR_FILENO, "Memory allocation error\n", 24);
        exit(EXIT_FAILURE);
    }

    // Rellena la cadena con los dígitos del número
    for (int i = num_digits - 1; i >= 0; i--) {
        str[i] = (number % 10) + '0';
        number /= 10;
    }
    str[num_digits] = '\0'; // Agrega el terminador nulo al final
    return str;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        write(STDERR_FILENO, "Usage: ./rush-02 <number>\n", 27);
        return EXIT_FAILURE;
    }

    char *dict_path = "./dict_eng.txt"; // Cambia el nombre del archivo de diccionario
    unsigned long long int number;

    number = strtoull(argv[1], NULL, 10);

    // Maneja el caso especial de 0
    if (number == 0) {
        char *result = convert_to_written_form(number, dict_path);
        write(STDOUT_FILENO, result, strlen(result));
        write(STDOUT_FILENO, "\n", 1);
        free(result);
        return EXIT_SUCCESS;
    }

    // Convierte el número en una cadena de caracteres
    char *number_str = int_to_string(number);
    int num_digits = strlen(number_str);

    // Crea un buffer para almacenar la representación en palabras
    char *composite_result = (char *)malloc((num_digits * 20) * sizeof(char));
    if (composite_result == NULL) {
        // Manejo del error de asignación de memoria
        write(STDERR_FILENO, "Memory allocation error\n", 24);
        free(number_str);
        exit(EXIT_FAILURE);
    }
    composite_result[0] = '\0'; // Inicializa el buffer

    // Itera sobre cada dígito del número
    for (int i = 0; i < num_digits; i++) {
        // Obtiene el dígito en la posición actual
        int digit = number_str[i] - '0';
        if (digit != 0) { // Ignora los ceros
            // Obtiene la potencia de 10 correspondiente al dígito
            int power = num_digits - i - 1;
            if (power > 0) {
                // Añade la representación en palabras del dígito multiplicado por 10^power
                char *digit_str = int_to_string(digit);
                char *power_str = int_to_string(1);
                for (int j = 0; j < power; j++) {
                    power_str = realloc(power_str, (strlen(power_str) + 1) * sizeof(char));
                    strcat(power_str, "0");
                }
                char *temp_result = convert_to_written_form(atoll(power_str), dict_path);
                strcat(composite_result, temp_result);
                strcat(composite_result, " ");
                free(temp_result);
                free(power_str);
                free(digit_str);
            } else {
                // Añade la representación en palabras del dígito
                char *temp_result = convert_to_written_form(digit, dict_path);
                strcat(composite_result, temp_result);
                strcat(composite_result, " ");
                free(temp_result);
            }
        }
    }
}
