/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:44:02 by bvelasco          #+#    #+#             */
/*   Updated: 2024/06/02 15:37:40 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	tokeniced_to_args(t_list *token_list, char ***args)
{
	int			noa;
	int			i;
	t_token		*tok;
	char		**result;

	i = 0;
	noa = ft_lstsize(token_list);
	if (noa == 0)
		return (*args = NULL, 0);
	result = malloc((noa + 1) * sizeof(void *));
	result[noa] = NULL;
	while (i < noa)
	{
		tok = token_list->content.oth;
		result[i] = ft_strdup(tok->value);
		token_list = token_list->next;
		i++;
	}
	*args = result;
	return (noa);
}

int	identify_redir_type(char *redir)
{
	if (*redir == '<')
	{
		if (*(++redir) == '<')
			return (0);
		return (1);
	}
	if (*redir == '>')
	{
		if (*(++redir) == '>')
			return (2);
		return (3);
	}
	return (-1);
}

void	open_redirs(t_list *env, t_command *command, t_list *token_list)
{
	t_token	*tok;
	int		redir_type;
	int		i;

	while (token_list)
	{
		i = 0;
		tok = token_list->content.oth;
		redir_type = identify_redir_type(tok->value);
		while (tok->value[i] && ft_isredir(tok->value[i]))
			i++;
		while (tok->value[i] && ft_isspace(tok->value[i]))
			i++;
		if (redir_type == 0)
			command->fds[0] = creat_heredoc(env, tok->value + i);
		else if (redir_type == 1)
			command->fds[0] = open(tok->value + i, O_RDONLY);
		else if (redir_type == 2)
			command->fds[1] = open(tok->value + i, O_CREAT | O_RDWR
					| O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (redir_type == 3)
			command->fds[1] = open(tok->value + i, O_CREAT | O_RDWR | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		token_list = token_list->next;
	}
}

static __int8_t	get_type(char **args)
{
	int			i;
	const char	*redir[] = {"echo", "pwd", "env", NULL};
	const char	*noredir[] = {"cd", "export", "unset", "exit", NULL};

	i = -1;
	if (args == NULL)
		return (-1);
	while (redir[++i])
		if (!ft_strncmp(args[0], redir[i], ft_strlen(redir[i]) + 1))
			return (0);
	i = -1;
	while (noredir[++i])
		if (!ft_strncmp(args[0], noredir[i], ft_strlen(noredir[i]) + 1))
			return (1);
	if (args[0][0] == '.' || args[0][0] == '/')
		return (2);
	return (3);
}

t_command	*create_command(t_list *env, t_list *token_list)
{
	t_command	*result;
	t_list		**token_lists;

	result = ft_calloc(1, sizeof(t_command));
	result->fds[1] = 1;
	result->fds[2] = 2;
	token_lists = separe_tokens(token_list);
	result->argc = tokeniced_to_args(token_lists[0], &result->args);
	open_redirs(env, result, token_lists[1]);
	result->info = get_type(result->args);
	ft_lstclear_type(&token_lists[0], del_token);
	ft_lstclear_type(&token_lists[1], del_token);
	free(token_lists);
	return (result);
}
