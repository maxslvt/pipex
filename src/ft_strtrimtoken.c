/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimtoken.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolet-l <msolet-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:05:59 by msolet-l          #+#    #+#             */
/*   Updated: 2025/03/10 12:17:46 by msolet-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*			ft_strtrimtoken
basiquement un melange de strdup et strtrim :
on parcoure str si on tombe sur un guillemet:
une autre boucle check si il y a un espace si oui
alors tu copie normalement sinon tu copie sans les guillemets,
	tout ca en enlevant les espaces et
les guillemets au debut et a la fin de str
*/

void	ft_isinquotes(char **start, char **end, int *in_quote)
{
	*in_quote = 0;
	if ((**start == '"' && **end == '"') || (**start == '\'' && **end == '\''))
	{
		*in_quote = 1;
		(*start)++;
		(*end)--;
	}
}

char	*ft_strtrimtoken(char *str)
{
	char	*start;
	char	*end;
	int		enclosed_in_quotes;
	char	*result;
	char	*dest;

	start = str;
	end = str + ft_strlen(str) - 1;
	while (*str && *str == ' ')
		str++;
	while (end > start && *str == ' ')
		end--;
	ft_isinquotes(&start, &end, &enclosed_in_quotes);
	result = malloc(end - start + 1 + 1);
	if (!result)
		return (NULL);
	dest = result;
	while (start <= end)
	{
		if (enclosed_in_quotes || *str != ' ')
			*dest++ = *start;
		start++;
	}
	*dest = '\0';
	return (result);
}
