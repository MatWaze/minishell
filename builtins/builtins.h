/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:29:25 by mamazari          #+#    #+#             */
/*   Updated: 2024/06/01 10:25:38 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "t_args.h"
# include "t_content.h"

t_content	*ft_content_new(char *key, char *val);
void		print_list(t_export **list, int i);
void		ft_swap(t_export **l1, t_export **l2);
void		append(char *s, char *key, t_export **l);
void		populate(t_export **l, char *key);
void		sort_list(t_export **l);
void		print_linked_list(t_list *l);
void		my_exit(char *num_str);
void		print_error_msg(char *msg, char *cmd);
void		my_unset(t_export **l, char *str);
char		*my_pwd(int i);
char		*get_val(char *s);
char		*my_strdup(char *src);
char		*tilde_exp(char *str, t_export **list);
char		*get_value_from_key(t_export **list, char *key);
int			my_strncpy(char *dest, char *src, int size);
int			ft_str_is_numeric(char *str);
int			my_cd(char *path);
int			my_export(t_args *args, char *s);
int			append_list(char *s, char *key, t_export *l1, t_export *l2);
int			append_last(char *s, char *key, t_export *last);
int			append_first(char *s, char *key, t_export **first);
int			is_inside(char *s, char *key, t_export **l);
int			is_builtin(char *str);
int			my_echo(char **strs);
int			check_key(char *key);

#endif
