/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkromer <jkromer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:45:36 by jkromer           #+#    #+#             */
/*   Updated: 2021/11/05 12:46:21 by jkromer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	abs(int val)
{
	if (val >= 0)
		return (val);
	return (-val);
}