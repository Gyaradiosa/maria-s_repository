/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushprueba12.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:33:52 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/17 23:33:59 by maduarte         ###   ########.fr       */
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
    int fd = open(dict_path, O_RDONLY);
    if (fd == -1) {
        write(STDERR_FILENO, "Dict Error\n", 11);
        exit(EXIT_FAILURE);
    }

    // Read the dictionary file
    while (read(fd, buffer, BUFFER_SIZE) > 0) {
        char *start = buffer;
        char *end = buffer;
        while (*end != '\0') {
            if (*end == '\n') {
                *end = '\0'; // Replace newline with null terminator
                // Parse the line from the dictionary
                char *token = strtok(start, ":");
                if (token != NULL) {
                    unsigned long long int current_number = strtoull(token, NULL, 10);
                    token = strtok(NULL, ":");
                    if (token != NULL) {
                        char current_text[BUFFER_SIZE];
                        strcpy(current_text, token);

                        // If the current number matches, assign the corresponding text
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

// Function to convert a number to written form recursively
char *convert_recursive(unsigned long long int number, char *dict_path) {
    if (number == 0) {
        return strdup("zero");
    } else {
        char *result = NULL;
        char *suffix = "";
        if (number >= 1000000000000000000) {
            result = convert_recursive(number / 1000000000000000000, dict_path);
            suffix = " quintillion";
        } else if (number >= 1000000000000000) {
            result = convert_recursive(number / 1000000000000000, dict_path);
            suffix = " quadrillion";
        } else if (number >= 1000000000000) {
            result = convert_recursive(number / 1000000000000, dict_path);
            suffix = " trillion";
        } else if (number >= 1000000000) {
            result = convert_recursive(number / 1000000000, dict_path);
            suffix = " billion";
        } else if (number >= 1000000) {
            result = convert_recursive(number / 1000000, dict_path);
            suffix = " million";
        } else if (number >= 1000) {
            result = convert_recursive(number / 1000, dict_path);
            suffix = " thousand";
        } else if (number >= 100) {
            result = convert_recursive(number / 100, dict_path);
            suffix = " hundred";
        } else if (number >= 20) {
            result = convert_recursive((number / 10) * 10, dict_path);
            char *rest = convert_to_written_form(number % 10, dict_path);
            asprintf(&result, "%s-%s", result, rest);
            free(rest);
        } else {
            result = convert_to_written_form(number, dict_path);
        }
        char *written_number = NULL;
        asprintf(&written_number, "%s%s", result, suffix);
        free(result);
        return written_number;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        write(STDERR_FILENO, "Error\n", 6);
        return EXIT_FAILURE;
    }

    unsigned long long int number;
    char *dict_path = "numbers.dict";

    if (argc == 3) {
        dict_path = argv[1];
        number = strtoull(argv[2], NULL, 10);
    } else {
        number = strtoull(argv[1], NULL, 10);
    }

    char *result = convert_recursive(number, dict_path);
    write(STDOUT_FILENO, result, strlen(result));
    write(STDOUT_FILENO, "\n", 1);
    free(result);

    return EXIT_SUCCESS;
}
