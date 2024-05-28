name = minishell
cc = cc
build_dir = build

# MODULES
EXPANSION_DIR=expansion
EXPANSION_SRC=expansion expansion_counter
EXPANSION_BUILD_DIR=$(build_dir)/$(EXPANSION_DIR)

src = my_split export1_funcs export2_funcs builtins pipex minishell quoted_split quotes helper_functions1 helper_functions2
obj = $(addprefix $(build_dir)/, $(addsuffix .o, $(src)))
readline_dir = readline-8.2
libft_dir = libft
lflags = -Llibft -L$(readline_dir)/lib
iflags = -Iincs -I$(libft_dir) -I$(readline_dir)/include
cflags = -Wall -Wextra -Werror#-g3 -fsanitize=address

all : $(name)

$(name) : $(readline_dir)/lib/libreadline.a $(libft_dir)/libft.a $(obj)
	$(cc) $(lflags) -o $(name) $(obj) -lreadline -lft -lcurses

dirs: $(build_dir)

$(build_dir)/%.o: %.c Makefile incs/minishell.h
	$(cc) $(cflags) $(iflags) -c $< -o $@

$(libft_dir)/libft.a:
	make -C $(libft_dir)

$(readline_dir)/lib/libreadline.a: $(readline_dir)/Makefile
	make -C $(readline_dir) install

$(build_dir):
	mkdir $@

$(readline_dir)/Makefile:
	cd $(readline_dir); ./configure --prefix=$(shell pwd)/$(readline_dir) --enable-shared=no

clean : $(readline_dir)/Makefile
	rm -rf $(build_dir)
	make -C $(libft_dir) clean
	make -C $(readline_dir) clean

fclean : clean
	make -C $(libft_dir) fclean
	rm -f $(name)
	make -C $(readline_dir) uninstall
	make -C $(readline_dir) distclean

re : fclean configure all

configure:
	cd $(readline_dir); ./configure --prefix=$(shell pwd)/$(readline_dir) --enable-shared=no

.PHONY: all clean fclean re configure dirs
