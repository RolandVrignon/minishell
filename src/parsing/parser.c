/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 15:31:37 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/09 19:56:19 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_parser(t_data **data)
{
	int	error;

	init_parsing(data);
	error = error_type_token(data);
	if (error != 0)
		return (-1);
	assign_file(data);
	convert_env(data);
	if (!parse_quotes(data))
		return (-1);
	return (0);
}
// FREE LE LEXER
//TEST
/*	int i = 0;
	while (token_type(data, i) != FINISH)
	{
		printf("CONTENT %s | TYPE %d | CMD %d\n", (*data)->parse[i].str,
		(*data)->parse[i].type, (*data)->parse[i].cmd);
		i++;
	}
		printf("CONTENT %s | TYPE %d | CMD %d\n", (*data)->parse[i].str,
		(*data)->parse[i].type, (*data)->parse[i].cmd);*/