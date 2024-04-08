/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushprueba11.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:29:55 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/17 23:31:28 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to convert a number to its written form
char *convert_to_written_form(unsigned long long int number, char *dict_path) {
    char buffer[BUFFER_SIZE];
    char *result = NULL;
    char *line = NULL;
    unsigned long long int current_number;
    char current_text[BUFFER_SIZE];
    int fd = open(dict_path, O_RDONLY);
    if (fd == -1) {
        write(STDERR_FILENO, "Dict Error\n", 11);
        exit(EXIT_FAILURE);
    }
    while (read(fd, buffer, BUFFER_SIZE) > 0) {
        char *start = buffer;
        char *end = buffer;
        while (*end != '\0') {
            if (*end == '\n') {
                *end = '\0'; // Replace newline with null terminator
                // Parse the line from the dictionary
                char *token = strtok(start, ":");
                if (token != NULL) {
                    current_number = strtoull(token, NULL, 10);
                    token = strtok(NULL, ":");
                    if (token != NULL) {
                        strcpy(current_text, token);
                        if (number == current_number) {
                            result = strdup(current_text);
                            close(fd);
                            return result;
                        }
                    }
                }
                start = end + 1; // Move start pointer to the next line
            }
            end++;
        }
    }
    close(fd);
    write(STDERR_FILENO, "Dict Error\n", 11);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        write(STDERR_FILENO, "Error\n", 6);
        return EXIT_FAILURE;
    }
    unsigned long long int number;
    char *dict_path = "./dict_eng.txt";
    if (argc == 3) {
        dict_path = argv[1];
        number = strtoull(argv[2], NULL, 10);
    } else {
        number = strtoull(argv[1], NULL, 10);
    }
    char *result = convert_to_written_form(number, dict_path);
    write(STDOUT_FILENO, result, strlen(result));
    write(STDOUT_FILENO, "\n", 1);
    free(result);
    return EXIT_SUCCESS;
}
