/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:09:52 by mjoosten          #+#    #+#             */
/*   Updated: 2022/04/21 10:09:53 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	pwd(void)
{
	t_program_data	*pd;

	pd = pd_get();
	pd->last_exit_status = 0;
	ft_putendl_fd(pd->pwd, 1);
}
