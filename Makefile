name = minishell
cc = cc
src = minishell.c my_split.c helper_functions1.c helper_functions2.c
obj = $(src:.c=.o)
dir = /Users/mamazari/Desktop/42-cursus/minishell/local
libft_dir = /Users/mamazari/Desktop/42-cursus/minishell/libft
libft = -L libft -lft
flags = -Iincs -I $(libft_dir)/libft.h#-g3 -fsanitize=address

all : $(name)

$(name) : $(obj) Makefile
	make -C $(libft_dir)
	$(cc) $(flags) -o $(name) $(obj) $(libft) -L$(dir)/lib/ -lreadline -lcurses
%.o: %.c
	$(cc) $(flags) -c $< -o $@

clean :
	make -C $(libft_dir) clean
	rm -f $(obj)

fclean : clean
	rm -f $(name)
	rm -f libft/libft.a

re : fclean all

.PHONY: all clean fclean re