#include "monty.h"
/**
 * push - Pushes an element onto the stack.
 * @stack: A pointer to a pointer to the stack.
 * @line_number: The line number in the Monty bytecode file.
 * @cmd: The original command from the file.
 * @fd: A file pointer for error handling.
 *
 */
void push(stack_t **stack, unsigned int line_number, char *cmd, FILE *fd)
{
	char *endptr;
	long int num;

	num = strtol(tokens[1], &endptr, 10);

	if (*endptr != '\0' || num < INT_MIN || num > INT_MAX)
	{
		dprintf(STDERR_FILENO, "L%d: usage: push integer\n", line_number);
		free(cmd);
		free_array(tokens);
		free_stack(*stack);
		fclose(fd);
		exit(EXIT_FAILURE);
	}

	stack_t *new_node = malloc(sizeof(stack_t));

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free(cmd);
		free_array(tokens);
		free_stack(*stack);
		fclose(fd);
		exit(EXIT_FAILURE);
	}

	new_node->n = (int)num;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack)
		(*stack)->prev = new_node;

	*stack = new_node;
}

#include "monty.h"
/**
 * pall - prints all the values on the stack.
 * @stack: pointer to the stack.
 * @line_number: line number in the Monty bytecode file.
 * @cmd: original command from the file.
 * @fd: file pointer for error handling.
 */
void pall(stack_t **stack, unsigned int line_number, char *cmd, FILE *fd)
{
	stack_t *current = *stack;
	(void)line_number; /* Unused, but required to match the function signature */
	(void)cmd;
	(void)fd;

	while (current)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

#include "monty.h"

/**
 * pint - prints the value at the top of the stack, followed by a new line.
 * @stack: pointer to the stack.
 * @line_number: line number in the Monty bytecode file.
 * @cmd: original command from the file.
 * @fd: file pointer for error handling.
 */
void pint(stack_t **stack, unsigned int line_number, char *cmd, FILE *fd)
{
	if (!stack || !*stack)
	{
		dprintf(STDERR_FILENO, "L%d: can't pint, stack empty\n", line_number);
		free(cmd);
		free_array(tokens);
		fclose(fd);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

#include "monty.h"
/**
 * pop - removes the top element of the stack.
 * @stack: pointer to the stack.
 * @line_number: line number in the Monty bytecode file.
 * @cmd: original command from the file.
 * @fd: file pointer for error handling.
 */
void pop(stack_t **stack, unsigned int line_number, char *cmd, FILE *fd)
{
	if (!*stack)
	{
		dprintf(STDERR_FILENO, "L%d: can't pop an empty stack\n", line_number);
		free(cmd);
		free_array(tokens);
		free_stack(*stack);
		fclose(fd);
		exit(EXIT_FAILURE);
	}

	stack_t *tmp = *stack;
	*stack = (*stack)->next;

	if (*stack)
		(*stack)->prev = NULL;

	free(tmp);
}

#include "monty.h"
/**
 * nop - doesn't do anything.
 * @stack: pointer to the stack.
 * @line_number: line number in the Monty bytecode file.
 * @cmd: original command from the file.
 * @fd: file pointer for error handling.
 */
void nop(stack_t **stack, unsigned int line_number, char *cmd, FILE *fd)
{
	(void)stack;
	(void)line_number;
	(void)cmd;
	(void)fd;
}
