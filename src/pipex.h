/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masolet- <masolet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:49:43 by masolet-          #+#    #+#             */
/*   Updated: 2026/04/09 14:36:55 by masolet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define ERR_USAGE "Usage: ./pipex file1 cmd1 cmd2 file2\n"
# define ERR_SPLIT "While splitting command\n"
# define ERR_COMMAND "command not found\n"
# define ERR_PERMISSION "Permission denied\n"
# define ERR_PIPE "pipe failed\n"
# define ERR_FORK1 "fork1 failed\n"
# define ERR_FORK2 "fork2 failed\n"
# define ERR_DUP2 "dup2 failed\n"

void	ft_printerror(char *str, int code);
int		open_file(char *file, int in_or_out);
void	ft_free_tab(char **tab);
char	**get_env_path(char **envp);
char	*get_path(char *cmd, char **env);
void	exec(char *cmd, char **env);
void	child(char **av, int *p_fd, char **env);
void	child2(char **av, int *p_fd, char **env);

#endif