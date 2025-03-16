/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolet-l <msolet-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:06:04 by msolet-l          #+#    #+#             */
/*   Updated: 2025/03/16 21:41:25 by msolet-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
	tab = NULL;
}

char	*ft_get_cmd_path(char **paths, char **cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	while (paths && paths[i] && (cmd[0][0] != '.' && cmd[0][0] != '/'))
	{
		tmp = ft_strjoin(paths[i], "/");
		if (tmp == NULL)
			return (NULL);
		res = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (res == NULL)
			return (NULL);
		if (access(res, F_OK | X_OK) == 0)
			return (free(cmd[0]), cmd[0] = res, res);
		free(res);
		i++;
	}
	if ((cmd[0][0] != '.' && cmd[0][0] != '/') && execve(cmd[0], cmd, envp) ==
		-1)
		return (ft_putstr_fd("Command not found\n", 2), NULL);
	return (cmd[0]);
}

char	*ft_find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i] && ft_strncmp(env[i], "PATH=", 5) == 0)
		return (env[i] + 5);
	return (NULL);
}

void	ft_err_exit(char *msg, char *arg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(arg, 2);
}
