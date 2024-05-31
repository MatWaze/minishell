/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:07:02 by zanikin           #+#    #+#             */
/*   Updated: 2024/05/31 15:53:18 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	pos(int n);
static int	neg(int n);
int			digits_count(int n);
void		insert_number(char *dst, int n);

void	insert_number(char *dst, int n)
{
	int	c;

	if (n == 0)
		dst[0] = '0';
	else
	{
		if (n < 0)
			dst++[0] = '-';
		c = digits_count(n);
		while (n)
		{
			c--;
			dst[c] = (n % 10) * (1 - 2 * (n < 0)) + '0';
			n /= 10;
		}
	}
}

int	digits_count(int n)
{
	int	c;

	if (n < 0)
		c = neg(n);
	else
		c = pos(n);
	return (c);
}

static int	neg(int n)
{
	int	c;

	if (n > -10)
		c = 2;
	else if (n > -100)
		c = 3;
	else if (n > -1000)
		c = 4;
	else if (n > -10000)
		c = 5;
	else if (n > -100000)
		c = 6;
	else if (n > -1000000)
		c = 7;
	else if (n > -10000000)
		c = 8;
	else if (n > -100000000)
		c = 9;
	else if (n > -1000000000)
		c = 10;
	else
		c = 11;
	return (c);
}

static int	pos(int n)
{
	int	c;

	if (n < 10)
		c = 1;
	else if (n < 100)
		c = 2;
	else if (n < 1000)
		c = 3;
	else if (n < 10000)
		c = 4;
	else if (n < 100000)
		c = 5;
	else if (n < 1000000)
		c = 6;
	else if (n < 10000000)
		c = 7;
	else if (n < 100000000)
		c = 8;
	else if (n < 1000000000)
		c = 9;
	else
		c = 10;
	return (c);
}
