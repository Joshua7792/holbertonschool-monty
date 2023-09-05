#include "monty.h"

/**
 * free_array - Frees an array of strings.
 * @tokens: The array of strings to free.
 */
void free_array(char **tokens)
{
	int i;

	if (tokens)
	{
		for (i = 0; tokens[i]; i++)
		{
			free(tokens[i]);
		}
		free(tokens);
	}
}

/**
 * free_stack - Frees a stack.
 * @stack: The stack to free.
 */
void free_stack(stack_t *stack)
{
	stack_t *current = stack;

	while (current)
	{
		stack_t *temp = current;

		current = current->next;

		free(temp);
	}
}
