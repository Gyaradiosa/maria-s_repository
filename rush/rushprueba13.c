/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rushprueba13.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maduarte <maduarte@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:35:40 by maduarte          #+#    #+#             */
/*   Updated: 2024/03/17 23:35:48 by maduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to read a line from file descriptor
int read_line(int fd, char *buffer, int size) {
    int i = 0;
    char c;
    while (i < size - 1) {
        int n = read(fd, &c, 1);
        if (n <= 0) break;
        if (c == '\n') break;
        buffer[i++] = c;
    }
    buffer[i] = '\0';
    return i;
}

// Function to find the text corresponding to a number in the dictionary
char *find_text(unsigned long long int number, char *dict_path) {
    char buffer[BUFFER_SIZE];
    int fd = open(dict_path, O_RDONLY);
    if (fd == -1) {
        write(STDERR_FILENO, "Dict Error\n", 11);
        exit(EXIT_FAILURE);
    }

    while (read_line(fd, buffer, BUFFER_SIZE) > 0) {
        char *token = strtok(buffer, ":");
        if (token != NULL) {
            unsigned long long int current_number = strtoull(token, NULL, 10);
            token = strtok(NULL, ":");
            if (token != NULL && current_number == number) {
                close(fd);
                return strdup(token);
            }
        }
    }
    close(fd);
    return NULL;
}

// Function to convert a number to its written form recursively
char *convert_recursive(unsigned long long int number, char *dict_path) {
    if (number == 0) return strdup("zero");

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
        char *rest = find_text(number % 10, dict_path);
        char *concatenated = malloc(strlen(result) + strlen(rest) + 2);
        sprintf(concatenated, "%s-%s", result, rest);
        free(rest);
        free(result);
        return concatenated;
    } else {
        result = find_text(number, dict_path);
    }

    char *written_number = malloc(strlen(result) + strlen(suffix) + 1);
    sprintf(written_number, "%s%s", result, suffix);
    free(result);
    return written_number;
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
