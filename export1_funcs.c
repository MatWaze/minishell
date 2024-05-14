#include "incs/minishell.h"

t_content	*ft_content_new(char *key, char *val)
{
	t_content	*result;

	result = (t_content *) malloc(sizeof(t_content));
	if (result)
	{
		result->key = key;
		result->val = val;
		result->next = NULL;
	}
	return (result);
}

void	print_list(t_export **list)
{
	t_export	*temp;
	char		*val;
	
	temp = *list;
	while (temp != NULL)
	{
		val = temp->pair->val;
		if (val == NULL)
			printf("declare -x %s\n", temp->pair->key);
		else if (ft_strlen(val) == 0)
			printf("declare -x %s=\"\"\n", temp->pair->key);
		else
			printf("declare -x %s=\"%s\"\n", temp->pair->key, temp->pair->val);
		temp = temp->next;
	}
}

char	*get_val(char *s)
{
	int		i;
	int		size;
	char	*str;
	
	i = 0;
	size = 0;
	if (ft_strchr(s, '=') == NULL)
		str = NULL;
	else
	{
		while (s[i] != '=')
			i++;
		if (s[i] == '=')
			i++;
		if (s[i] == '\0')
			str = "";
		else
			str = &s[i];
	}
	return (str);
}

void	ft_swap(t_export **l1, t_export **l2)
{
	char	*temp;
	char	*temp2;

	temp = (*l2)->pair->key;
	temp2 = (*l2)->pair->val;
	(*l2)->pair->key = (*l1)->pair->key;
	(*l2)->pair->val = (*l1)->pair->val;
	(*l1)->pair->key = temp;
	(*l1)->pair->val = temp2;
}

void	sort_list(t_export **l)
{
	t_export	*l1;
	t_export	*l2;
	int			count;
	
	l1 = *l;
	while (l1)
	{
		l2 = l1->next;
		while (l2)
		{
			if (ft_strlen(l1->pair->key) > ft_strlen(l2->pair->key))
				count = ft_strlen(l1->pair->key);
			else
				count = ft_strlen(l2->pair->key);
			if (ft_strncmp(l1->pair->key, l2->pair->key, count) > 0)
				ft_swap(&l1, &l2);
			l2 = l2->next;
		}
		l1 = l1->next;
	}
}
// char	*add_brackets(char *env)
// {
// 	char	*s1;
	
// 	if (env != NULL)
// 	{
// 		s1 = ft_strjoin("=\"", env);
// 		env = ft_strjoin(s1, "\"");
// 		free(s1);
// 	}
// 	else
// 	{
// 		env = (char *) malloc(sizeof(char) * 3);
// 		if (!env)
// 			env = NULL;
// 		else
// 		{
// 			env[0] = '\"';
// 			env[1] = '\"';
// 			env[2] = '\0';
// 		}
// 	}
// 	return (env);
// }