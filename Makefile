name = minishell
cc = cc
build_dir = build
include_dir=incs

# MODULES
EXPANSION_DIR=expansion
EXPANSION_SRC=expansion expansion_counter digits_counter
EXPANSION_BUILD_DIR=$(build_dir)/$(EXPANSION_DIR)
EXPANSION_OBJ=$(addprefix $(EXPANSION_BUILD_DIR)/, $(addsuffix .o, $(EXPANSION_SRC)))

src = export1_funcs export2_funcs builtins pipex minishell quoted_split quotes helper_functions1 helper_functions2
obj = $(addprefix $(build_dir)/, $(addsuffix .o, $(src))) $(EXPANSION_OBJ)
readline_dir = readline-8.2
libft_dir = libft
lflags = -L$(libft_dir) -L$(readline_dir)/lib
iflags = -I. -I$(include_dir) -I$(libft_dir) -I$(readline_dir)/include
cflags = -Wall -Wextra -Werror -g3# -fsanitize=address

all : $(name)

$(name) : $(readline_dir)/lib/libreadline.a $(libft_dir)/libft.a $(obj)
	$(cc) $(lflags) -o $(name) $(obj) -lreadline -lft -lcurses

$(build_dir)/%.o: %.c Makefile $(include_dir)/minishell.h
	$(cc) $(cflags) $(iflags) -c $< -o $@

$(EXPANSION_BUILD_DIR)/%.o: $(EXPANSION_DIR)/%.c Makefile $(EXPANSION_DIR)/expansion.h | $(EXPANSION_BUILD_DIR)
	$(cc) $(cflags) $(iflags) -c $< -o $@

$(libft_dir)/libft.a:
	make -C $(libft_dir)

$(readline_dir)/lib/libreadline.a: $(readline_dir)/Makefile
	make -C $(readline_dir) install

$(EXPANSION_BUILD_DIR): | $(build_dir)
	mkdir $@

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
