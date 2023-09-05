#include "monty.h"

/**
 * get_op_func - selects the correct function to perform an operation
 * @cmd: the opcode to be matched
 *
 * Return: a function pointer to the corresponding function,NULL if not found
 */
void (*get_op_func(char *cmd))(stack_t **, unsigned int, char *, FILE *)
{
	instruction_t opcodes[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"nop", nop},
		{"swap", swap},
		{"add", add},
		{"sub", sub},
		{"div", _div},
		{"mul", mul},
		{NULL, NULL}};

	int i = 0;

	while (opcodes[i].opcode)
	{
		if (strcmp(cmd, opcodes[i].opcode) == 0)
			return (opcodes[i].f);
		i++;
	}

	return (NULL); /* Return NULL if opcode is not found */
}

/**
 * reset_inside - resets the values inside the command and tokens
 * @cmd: the original command string
 * @tokens: the array of tokens
 */
void reset_inside(char *cmd, char **tokens)
{
	if (cmd)
	{
		free(cmd);
		cmd = NULL;
	}

	if (tokens)
	{
		free_array(tokens);
		tokens = NULL;
	}
}

/**
 * tokenization - tokenizes a string into an array of tokens
 * @ptr: the string to tokenize
 * @delim: the delimiter to split the string
 *
 * Return: an array of tokens, or NULL on failure
 */
char **tokenization(char *ptr, char *delim)
{
	char **tokens = NULL;
	char *token = NULL;
	int i = 0;

	tokens = malloc(sizeof(char *) * 128); /* Adjust the size as needed */

	if (tokens == NULL)
		return (NULL);

	token = strtok(ptr, delim);
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			free_array(tokens);
			return (NULL);
		}
		token = strtok(NULL, delim);
		i++;
	}
	tokens[i] = NULL;

	return (tokens);
}
