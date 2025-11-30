/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlallema <nlallema@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 00:45:38 by nlallema          #+#    #+#             */
/*   Updated: 2025/11/30 02:57:46 by nlallema         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.h"

int randint(int min, int max)
{
    return (int)(((double)rand() / RAND_MAX) * (max - min) + min);
}

double randfloat(int min, int max)
{
    return (((double)rand() / RAND_MAX) * (max - min) + min);
}