/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamazari <mamazari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:17:45 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/05 17:46:18 by mamazari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "t_fd.h"

void	restore_in_out(t_fd *p)
{
	dup2(p->tempin, 0);
	dup2(p->tempout, 1);
	close(p->tempin);
	close(p->tempout);
}
