/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorucu <mkorucu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:51:54 by btekinli          #+#    #+#             */
/*   Updated: 2023/02/07 14:20:16 by mkorucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_new_str(char **trimed, char *removed)
{
	char	*tmp;

	if (!(*trimed))
	{
		*trimed = ft_strdup(removed);
		free(removed);
		return ;
	}
	tmp = *trimed;
	*trimed = ft_strjoin(*trimed, removed);
	free(tmp);
	free(removed);
}

char	*clean_quotes(char *str, int *curr, char type)
{
	int		start;
	char	*new_str;

	++*curr;
	start = *curr;
	while (str[*curr] && str[*curr] != type)
		++*curr;
	new_str = ft_substr(str, start, *curr - start);
	if (str[*curr])
		++*curr;
	return (new_str);
}

char	*get_str(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != DOUBLE_QUOTE && str[*i] != SINGLE_QUOTE)
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*remove_quotes(char *str)
{
	int		curr;
	char	*removed;
	char	*trimed;

	curr = 0;
	trimed = NULL;
	str = dollar(str);
	while (str[curr])
	{
		if (str[curr] == DOUBLE_QUOTE || str[curr] == SINGLE_QUOTE)
			removed = clean_quotes(str, &curr, str[curr]);
		else
			removed = get_str(str, &curr);
		push_new_str(&trimed, removed);
	}
	free(str);
	return (trimed);
}
