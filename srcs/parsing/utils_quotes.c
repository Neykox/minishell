/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-masr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:49:44 by nel-masr          #+#    #+#             */
/*   Updated: 2022/01/11 12:20:05 by nel-masr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*verify_squote(char *line, int j, int k, char quote)
{
	int pre_quotes;
	int post_quotes;

	pre_quotes = 0;
	post_quotes = 0;
	while (line[++j] == quote)
	{
		pre_quotes++;
		if (line[j + 1] == '\0')
		{
			if (pre_quotes % 2 != 0)
				return (-1);
		}
	}
	while (line[++j] != quote)
		k++;
	while (line[++j] == quote)
		post_quotes++;
	if (post_quotes != pre_quotes)
		return (-1);
	return (k);
}
