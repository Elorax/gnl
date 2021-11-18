#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

typedef struct	s_count
{
	int		dest;
	int		buffer;
	char	end;
}	t_count;

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	*ft_strndup(char const *s, int n);
t_list	*ft_lstnnew(void *s, int n);
void	ft_lstadd_back(t_list **alst, t_list *new);
int	ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_char_swap(char *a, char *b);
void	clean_buffer(char *buffer, int nb, int size);
void	check_eol(int fd, t_count *count, char *buffer, t_list **lst);
char	*ft_makeline(t_list *lst, int n);
char	*get_next_line(int fd);

#endif
