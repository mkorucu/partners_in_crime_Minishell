/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorucu <mkorucu@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:45:02 by mkorucu           #+#    #+#             */
/*   Updated: 2023/02/07 11:45:51 by mkorucu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	set_paths(void)
{
	char	*path;

	if (g_crime.paths)
		kill_him(g_crime.paths);
	path = get_env("PATH");
	if (!(*path))
		g_crime.paths = NULL;
	else
		g_crime.paths = ft_split(path, ':');
	free(path);
}