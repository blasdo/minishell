/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvelasco <bvelasco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:53:06 by bvelasco          #+#    #+#             */
/*   Updated: 2024/05/29 19:05:56 by bvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*proc_arg_token(char *first_char, int *pos)
{
	int	i;

	i = 0;
	while (first_char[i] &&!ft_isspace(first_char[i]))
	{
		if (ft_isquote(first_char[i]))
		{
			i += get_quotelen(first_char + i);
			continue ;
		}
		if (first_char[i] == '$')
		{
			++i;
			i += get_varname_len(first_char + i);
			continue ;
		}
		if (ft_isredir(first_char[i]))
			break ;
		i++;
	}
	*pos += i;
	return (ft_substr(first_char, 0, i));
}

static char	*proc_redir_token(char *first_char, int *pos)
{
	int	i;

	i = 0;
	while (ft_isredir(first_char[i]) && i < 2)
		i++;
	while (first_char[i] && ft_isspace(first_char[i]))
		i++;
	if (!first_char[i] || ft_isredir(first_char[i]))
		return (NULL);
	while (first_char[i] && !ft_isspace(first_char[i]))
	{
		if (first_char[i] == '<' || first_char[i] == '>')
		{
			*pos += i;
			return (ft_substr(first_char, 0, i));
		}
		i++;
	}
	*pos += i;
	return (ft_substr(first_char, 0, i));
}

static int	process_token(t_list **tok_list, char *first_char, int *pos)
{
	int		i;
	char	*buffer;
	t_token	*tok;

	i = 0;
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (ERRMEM);
	tok->type = ARG;
	if (ft_isredir(first_char[i]))
	{
		buffer = proc_redir_token(first_char, pos);
		tok->type = RD;
	}
	else
		buffer = proc_arg_token(first_char, pos);
	if (!buffer)
		return (free(tok), ERRMEM);
	tok->value = buffer;
	ft_lstadd_back(tok_list, ft_lstnew_type(OTHER, (t_content)(void *) tok));
	return (0);
}

t_content	tokenize_command(t_content content, t_type type)
{
	int		i;
	t_list	*tok_list;
	char	*raw_cmd;

	(void) type;
	i = 0;
	tok_list = NULL;
	raw_cmd = content.str;
	while (raw_cmd[i])
	{
		if (!ft_isspace(raw_cmd[i]))
		{
			if (process_token(&tok_list, raw_cmd + i, &i))
				return ((t_content) NULL);
			continue ;
		}
		i++;
	}
	return ((t_content)(void *)tok_list);
}
