
#include "../../includes/cub3d.h"

static char	**convert_list_to_array(t_stack *head)
{
	char	**array;
	t_stack	*current;
	int		size;
	int		i;

	size = ft_lstsize(head);
	array = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	current = head;
	while (current)
	{
		array[i] = (char *)current->content;
		current = current->next;
		i++;
	}
	while (head)
	{
		current = head->next;
		free(head);
		head = current;
	}
	return (array);
}

char	**read_file_to_array(int fd)
{
	t_stack *head;
	t_stack *new_node;
	char *line;

	head = NULL;
	line = get_next_line(fd);
	while (line)
	{
		new_node = ft_lstnew(line);
		if (!new_node)
		{
			free(line);
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, new_node);
		line = get_next_line(fd);
	}
	if (!head)
		return (NULL);
	return (convert_list_to_array(head));
}