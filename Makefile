name = minishell
build_dir = build
include_dir=incs
readline_dir = readline-8.2
libft_dir = libft
lflags = -L$(libft_dir) -L$(readline_dir)/lib #-fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
iflags = -I. -I$(include_dir) -I$(libft_dir) -I$(readline_dir)/include
cflags = -Wall -Wextra -Werror #-fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

# sanitize : cflags += -g3 -fsanitize=address -fsanitize=undefined
# sanitize : lflags += -g3 -fsanitize=address -fsanitize=undefined
# sanitize : all

all : dirs $(name)

$(libft_dir)/libft.a:
	make -C $(libft_dir)

$(readline_dir)/lib/libreadline.a: $(readline_dir)/Makefile
	make -C $(readline_dir) install

$(readline_dir)/Makefile:
	cd $(readline_dir); ./configure --prefix=$(shell pwd)/$(readline_dir) --enable-shared=no

configure:
	cd $(readline_dir); ./configure --prefix=$(shell pwd)/$(readline_dir) --enable-shared=no


#                             _       _                   #
#         _ __ ___   ___   __| |_   _| | ___  ___         #
#        | '_ ` _ \ / _ \ / _` | | | | |/ _ \/ __|        #
#        | | | | | | (_) | (_| | |_| | |  __/\__ \        #
#        |_| |_| |_|\___/ \__,_|\__,_|_|\___||___/        #
#                                                         #

EXPANSION_DIR=expansion
EXPORT_DIR=export
CD_DIR=cd
COMMON_DIR=common
ECHO_DIR=echo
EXIT_DIR=exit
PIPEX_DIR=pipex
PWD_DIR=pwd
UNSET_DIR=unset
QUOTES_DIR=quotes

#         ___ __ __ _ __  __ _  _ _   ___(_) ___  _ _     #
#        / -_)\ \ /| '_ \/ _` || ' \ (_-<| |/ _ \| ' \    #
#        \___|/_\_\| .__/\__,_||_||_|/__/|_|\___/|_||_|   #
#                  |_|                                    #

EXPANSION_SRC=expansion expansion_counter digits_counter
EXPANSION_BUILD_DIR=$(build_dir)/$(EXPANSION_DIR)
EXPANSION_OBJ=$(addprefix $(EXPANSION_BUILD_DIR)/, $(addsuffix .o, $(EXPANSION_SRC)))
obj+=$(EXPANSION_OBJ)

$(EXPANSION_BUILD_DIR)/expansion.o: $(EXPANSION_DIR)/expansion.c Makefile $(libft_dir)/libft.h $(EXPORT_DIR)/export.h $(EXPORT_DIR)/t_export.h $(include_dir)/t_args.h $(EXPORT_DIR)/t_keyval.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(EXPANSION_BUILD_DIR)/expansion_counter.o: $(EXPANSION_DIR)/expansion_counter.c Makefile $(libft_dir)/libft.h $(EXPORT_DIR)/export.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h $(include_dir)/t_args.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(EXPANSION_BUILD_DIR)/digits_counter.o: $(EXPANSION_DIR)/digits_counter.c Makefile
	cc $(cflags) $(iflags) -o $@ -c $<

$(EXPANSION_BUILD_DIR): | $(build_dir)
	mkdir $@


#                _                                         #
#         __  __| |                                        #
#        / _|/ _` |                                        #
#        \__|\__,_|                                        #

CD_SRC=cd
CD_BUILD_DIR=$(build_dir)/$(CD_DIR)
CD_OBJ=$(addprefix $(CD_BUILD_DIR)/, $(addsuffix .o, $(CD_SRC)))
obj+=$(CD_OBJ)

$(CD_BUILD_DIR)/cd.o: $(CD_DIR)/cd.c Makefile $(COMMON_DIR)/common.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(CD_BUILD_DIR): | $(build_dir)
	mkdir $@

#         __  ___  _ __   _ __   ___  _ _                  #
#        / _|/ _ \| '  \ | '  \ / _ \| ' \                 #
#        \__|\___/|_|_|_||_|_|_|\___/|_||_|                #
#                                                          #

COMMON_SRC=common
COMMON_BUILD_DIR=$(build_dir)/$(COMMON_DIR)
COMMON_OBJ=$(addprefix $(COMMON_BUILD_DIR)/, $(addsuffix .o, $(COMMON_SRC)))
obj+=$(COMMON_OBJ)

$(COMMON_BUILD_DIR)/common.o: $(COMMON_DIR)/common.c Makefile $(libft_dir)/libft.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(COMMON_BUILD_DIR): | $(build_dir)
	mkdir $@

#                  _                                       #
#         ___  __ | |_   ___                               #
#        / -_)/ _|| ' \ / _ \                              #
#        \___|\__||_||_|\___/                              #

ECHO_SRC=echo
ECHO_BUILD_DIR=$(build_dir)/$(ECHO_DIR)
ECHO_OBJ=$(addprefix $(ECHO_BUILD_DIR)/, $(addsuffix .o, $(ECHO_SRC)))
obj+=$(ECHO_OBJ)

$(ECHO_BUILD_DIR)/echo.o: $(ECHO_DIR)/echo.c Makefile $(libft_dir)/libft.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(ECHO_BUILD_DIR): | $(build_dir)
	mkdir $@

#                  _  _                                    #
#        ___ __ __(_)| |_                                  #
#       / -_)\ \ /| ||  _|                                 #
#       \___|/_\_\|_| \__|                                 #

EXIT_SRC=exit
EXIT_BUILD_DIR=$(build_dir)/$(EXIT_DIR)
EXIT_OBJ=$(addprefix $(EXIT_BUILD_DIR)/, $(addsuffix .o, $(EXIT_SRC)))
obj+=$(EXIT_OBJ)

$(EXIT_BUILD_DIR)/exit.o: $(EXIT_DIR)/exit.c Makefile $(libft_dir)/libft.h $(COMMON_DIR)/common.h $(include_dir)/t_args.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(EXIT_BUILD_DIR): | $(build_dir)
	mkdir $@

#                                   _                      #
#         ___ __ __ _ __  ___  _ _ | |_                    #
#        / -_)\ \ /| '_ \/ _ \| '_||  _|                   #
#        \___|/_\_\| .__/\___/|_|   \__|                   #
#                  |_|                                     #

EXPORT_SRC=append bypass create_destroy export sort
EXPORT_BUILD_DIR=$(build_dir)/$(EXPORT_DIR)
EXPORT_OBJ=$(addprefix $(EXPORT_BUILD_DIR)/, $(addsuffix .o, $(EXPORT_SRC)))
obj+=$(EXPORT_OBJ)

$(EXPORT_BUILD_DIR)/append.o: $(EXPORT_DIR)/append.c Makefile $(libft_dir)/libft.h $(EXPORT_DIR)/export.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h $(include_dir)/t_args.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(EXPORT_BUILD_DIR)/bypass.o: $(EXPORT_DIR)/bypass.c Makefile $(libft_dir)/libft.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(EXPORT_BUILD_DIR)/create_destroy.o: $(EXPORT_DIR)/create_destroy.c Makefile $(libft_dir)/libft.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(EXPORT_BUILD_DIR)/export.o: $(EXPORT_DIR)/export.c Makefile $(libft_dir)/libft.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h $(include_dir)/t_args.h $(COMMON_DIR)/common.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(EXPORT_BUILD_DIR)/sort.o: $(EXPORT_DIR)/sort.c Makefile $(libft_dir)/libft.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(EXPORT_BUILD_DIR): | $(build_dir)
	mkdir $@

#               _                                           #
#         _ __ (_) _ __  ___ __ __                          #
#        | '_ \| || '_ \/ -_)\ \ /                          #
#        | .__/|_|| .__/\___|/_\_\                          #
#        |_|      |_|                                       #

PIPEX_SRC=handlers path_extruder pid pipex fd new_envp
PIPEX_BUILD_DIR=$(build_dir)/$(PIPEX_DIR)
PIPEX_OBJ=$(addprefix $(PIPEX_BUILD_DIR)/, $(addsuffix .o, $(PIPEX_SRC)))
obj+=$(PIPEX_OBJ)

$(PIPEX_BUILD_DIR)/handlers.o: $(PIPEX_DIR)/handlers.c Makefile $(COMMON_DIR)/common.h $(EXPORT_DIR)/export.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h $(include_dir)/t_args.h $(UNSET_DIR)/unset.h $(CD_DIR)/cd.h $(PWD_DIR)/pwd.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(PIPEX_BUILD_DIR)/path_extruder.o: $(PIPEX_DIR)/path_extruder.c Makefile $(libft_dir)/libft.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h $(COMMON_DIR)/common.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(PIPEX_BUILD_DIR)/fd.o: $(PIPEX_DIR)/fd.c Makefile $(include_dir)/t_fd.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(PIPEX_BUILD_DIR)/new_envp.o: $(PIPEX_DIR)/new_envp.c Makefile $(libft_dir)/libft.h $(EXPORT_DIR)/t_export.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(PIPEX_BUILD_DIR)/pid.o: $(PIPEX_DIR)/pid.c Makefile $(include_dir)/t_args.h $(libft_dir)/libft.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(PIPEX_BUILD_DIR)/pipex.o: $(PIPEX_DIR)/pipex.c Makefile $(PWD_DIR)/pwd.h $(include_dir)/t_args.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h $(libft_dir)/libft.h $(ECHO_DIR)/echo.h $(EXIT_DIR)/exit.h $(EXPANSION_DIR)/expansion.h $(COMMON_DIR)/common.h $(EXPORT_DIR)/export.h $(include_dir)/t_fd.h $(QUOTES_DIR)/quotes.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(PIPEX_BUILD_DIR): | $(PIPEX_DIR)
	mkdir $@

#                          _                                #
#         _ __ __ __ __ __| |                               #
#        | '_ \\ V  V // _` |                               #
#        | .__/ \_/\_/ \__,_|                               #
#        |_|                                                #

PWD_SRC=pwd
PWD_BUILD_DIR=$(build_dir)/$(PWD_DIR)
PWD_OBJ=$(addprefix $(PWD_BUILD_DIR)/, $(addsuffix .o, $(PWD_SRC)))
obj+=$(PWD_OBJ)

$(PWD_BUILD_DIR)/pwd.o: $(PWD_DIR)/pwd.c Makefile $(include_dir)/t_args.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h $(libft_dir)/libft.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(PWD_BUILD_DIR): | $(build_dir)
	mkdir $@

#                          _                                #
#         __ _  _  _  ___ | |_  ___  ___                    #
#        / _` || || |/ _ \|  _|/ -_)(_-<                    #
#        \__, | \_,_|\___/ \__|\___|/__/                    #
#           |_|                                             #

QUOTES_SRC=quoted_split quotes
QUOTES_BUILD_DIR=$(build_dir)/$(QUOTES_DIR)
QUOTES_OBJ=$(addprefix $(QUOTES_BUILD_DIR)/, $(addsuffix .o, $(QUOTES_SRC)))
obj+=$(QUOTES_OBJ)

$(QUOTES_BUILD_DIR)/quoted_split.o: $(QUOTES_DIR)/quoted_split.c Makefile
	cc $(cflags) $(iflags) -o $@ -c $<

$(QUOTES_BUILD_DIR)/quotes.o: $(QUOTES_DIR)/quotes.c Makefile
	cc $(cflags) $(iflags) -o $@ -c $<

$(QUOTES_BUILD_DIR): | $(build_dir)
	mkdir $@

#                              _                            #
#         _  _  _ _   ___ ___ | |_                          #
#        | || || ' \ (_-</ -_)|  _|                         #
#         \_,_||_||_|/__/\___| \__|                         #

UNSET_SRC=unset
UNSET_BUILD_DIR=$(build_dir)/$(UNSET_DIR)
UNSET_OBJ=$(addprefix $(UNSET_BUILD_DIR)/, $(addsuffix .o, $(UNSET_SRC)))
obj+=$(UNSET_OBJ)

$(UNSET_BUILD_DIR)/unset.o: $(UNSET_DIR)/unset.c Makefile $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h $(libft_dir)/libft.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(UNSET_BUILD_DIR): | $(build_dir)
	mkdir $@

#                      _                                    #
#         _ __   __ _ (_) _ _                               #
#        | '  \ / _` || || ' \                              #
#        |_|_|_|\__,_||_||_||_|                             #

src = minishell
obj+=$(addprefix $(build_dir)/, $(addsuffix .o, $(src)))

$(build_dir)/minishell.o: minishell.c Makefile $(include_dir)/t_args.h $(EXPORT_DIR)/t_export.h $(EXPORT_DIR)/t_keyval.h $(libft_dir)/libft.h $(EXPORT_DIR)/export.h $(PIPEX_DIR)/pipex.h $(COMMON_DIR)/common.h
	cc $(cflags) $(iflags) -o $@ -c $<

$(name) : $(readline_dir)/lib/libreadline.a $(libft_dir)/libft.a $(obj)
	cc $(lflags) -o $@ $(obj) -lreadline -lft -lcurses

dirs: $(CD_BUILD_DIR) $(COMMON_BUILD_DIR) $(ECHO_BUILD_DIR) $(EXIT_BUILD_DIR) $(EXPANSION_BUILD_DIR) $(EXPORT_BUILD_DIR) $(PIPEX_BUILD_DIR) $(PWD_BUILD_DIR) $(QUOTES_BUILD_DIR) $(UNSET_BUILD_DIR)

$(build_dir):
	mkdir $@

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

.PHONY: all clean fclean re configure dirs
