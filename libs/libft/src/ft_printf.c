/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:43:56 by mjoosten          #+#    #+#             */
/*   Updated: 2022/02/24 15:26:54 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_percent(char c, va_list ap);

int	ft_printf(char *format, ...)
{
	int		len;
	va_list	ap;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format++ == '%')
			len += ft_percent(*format++, ap);
		else
			len += ft_putchar(*(format - 1));
	}
	va_end(ap);
	return (len);
}

static int	ft_percent(char c, va_list ap)
{
	if (c == 'c')
		return (ft_putchar(va_arg(ap, int)));
	if (c == 's')
		return (ft_putstr(va_arg(ap, char *)));
	if (c == 'p')
		return (ft_printf("0x%x", va_arg(ap, long)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	if (c == 'u')
		return (ft_putnbr(va_arg(ap, unsigned int)));
	if (c == 'x')
		return (ft_putnbr_base(va_arg(ap, int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_putnbr_base(va_arg(ap, int), "0123456789ABCDEF"));
	if (c == '%')
		return (ft_putchar('%'));
	return (-1);
}
