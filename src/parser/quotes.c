/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenez <dximenez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:58:11 by bvelasco          #+#    #+#             */
/*   Updated: 2024/06/19 00:50:19 by dximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	get_singlequote_len(char *quote)
{
	int		i;
	size_t	len;

	len = 0;
	i = 1;
	while (quote[i] && quote[i] != '\'')
	{
		len++;
		i++;
	}
	return (len);
}

size_t	get_quotelen(t_list *env, char *raw_quote)
{
	size_t	len;
	size_t	i;
	char	*varname;

	i = 0;
	len = 0;
	if (raw_quote[i++] == '\'')
		return (get_singlequote_len(raw_quote));
	while (raw_quote[i] && raw_quote[i] != '"')
	{
		if (raw_quote[i] == '$')
		{
			varname = get_varname(raw_quote + i);
			if (!varname)
				return (0);
			len += get_env_var_len(env, varname);
			i += get_varname_len(raw_quote + i);
			free(varname);
			continue ;
		}
		i++;
		len++;
	}
	return (len);
}

int	get_unexpanded_quotelen(char *quote)
{
	int	i;

	i = 0;
	if (quote[i] == '\'')
	{
		i++;
		while (quote[i] && quote[i] != '\'')
			i++;
	}
	else if (quote[i] == '\"')
	{
		i++;
		while (quote[i] && quote[i] != '"')
			i++;
	}
	if (quote[i])
		i++;
	return (i);
}

static char	*expand_simple_quote(char *quote)
{
	char	*close_quote;

	close_quote = ft_strchr(quote + 1, '\'');
	if (!close_quote)
		return (ft_strdup(quote + 1));
	if (close_quote == quote + 1)
		return (NULL);
	return (ft_substr(quote, 1, close_quote - quote - 1));
}

char	*expand_quote(t_list *env, char *quote)
{
	const size_t	size = get_quotelen(env, quote) + 1;
	int				i;
	int				j;
	char			*result;
	char			*aux;

	i = 0;
	j = 0;
	if (quote[i] == '\'')
		return (expand_simple_quote(quote));
	i++;
	result = ft_calloc(size, 1);
	while (quote[i] && quote[i] != '"')
	{
		if (quote[i] == '$')
		{
			aux = expand_var(env, quote + i);
			j = ft_strlcat(result, aux, size);
			free(aux);
			i += get_varname_len(quote + i);
		}
		else
			result[j++] = quote[i++];
	}
	return (result);
}
