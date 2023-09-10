#include "monty.h"

char **tokens = NULL;

/**
 * main - Monty bytecode interpreter.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Description: This program reads and interprets Monty bytecode files
 * to perform various stack operations.
 *
 * Return: 0 on success, EXIT_FAILURE on failure.
 */
int main(int ac, char **av)
{
	int input_verification, line_number = 0;
	char *cmd = NULL;
	size_t buffer = 0;
	FILE *fd;
	void (*valid_fun)(stack_t **, unsigned int, char *, FILE *) = NULL;
	stack_t *stack = NULL;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fd = fopen(av[1], "r");
	if (fd == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	while ((input_verification = getline(&cmd, &buffer, fd)) > -1)
	{
		line_number++;
		if (strcmp(cmd, "\n") == 0 || *cmd == '#')
			continue;

		tokens = tokenization(cmd, " \n");
		if (tokens == NULL)
			continue;

		valid_fun = get_op_func(tokens[0]);
		valid_fun(&stack, line_number, cmd, fd);
		buffer = 0;
		reset_inside(cmd, tokens);
		cmd = NULL;
		tokens = NULL;
	}

	free(cmd);
	free_stack(stack);
	fclose(fd);
	exit(EXIT_SUCCESS);
}
