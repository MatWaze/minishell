name = minishell
build_dir = build
include_dir=incs
readline_dir = readline-8.2
libft_dir = libft
lflags = -L$(libft_dir) -L$(readline_dir)/lib
iflags = -I. -I$(include_dir) -I$(libft_dir) -I$(readline_dir)/include
cflags = -Wall -Wextra -Werror -g

all : dirs $(name)

sanitize : cflags += -g3 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
sanitize : lflags += -g3 -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG
sanitize : all

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

EXPANSION_BUILD_DIR=$(build_dir)/expansion
EXPORT_BUILD_DIR=$(build_dir)/export
CD_BUILD_DIR=$(build_dir)/cd
COMMON_BUILD_DIR=$(build_dir)/common
ECHO_BUILD_DIR=$(build_dir)/echo
EXIT_BUILD_DIR=$(build_dir)/exit
PIPEX_BUILD_DIR=$(build_dir)/pipex
PWD_BUILD_DIR=$(build_dir)/pwd
UNSET_BUILD_DIR=$(build_dir)/unset
QUOTES_BUILD_DIR=$(build_dir)/quotes
REDIRECTION_BUILD_DIR=$(build_dir)/redirection
SIGNALS_BUILD_DIR=$(build_dir)/signals

#         ___ __ __ _ __  __ _  _ _   ___(_) ___  _ _     #
#        / -_)\ \ /| '_ \/ _` || ' \ (_-<| |/ _ \| ' \    #
#        \___|/_\_\| .__/\__,_||_||_|/__/|_|\___/|_||_|   #
#                  |_|                                    #

EXPANSION_MODULES=digits_counter expansion_counter expansion
EXPANSION_OBJ=$(addprefix $(EXPANSION_BUILD_DIR)/, $(addsuffix .o, $(EXPANSION_MODULES)))
$(EXPANSION_BUILD_DIR): | $(build_dir)
	mkdir $@

#                _                                         #
#         __  __| |                                        #
#        / _|/ _` |                                        #
#        \__|\__,_|                                        #

CD_MODULES=cd
CD_OBJ=$(addprefix $(CD_BUILD_DIR)/, $(addsuffix .o, $(CD_MODULES)))
$(CD_BUILD_DIR): | $(build_dir)
	mkdir $@

#         __  ___  _ __   _ __   ___  _ _                  #
#        / _|/ _ \| '  \ | '  \ / _ \| ' \                 #
#        \__|\___/|_|_|_||_|_|_|\___/|_||_|                #
#                                                          #

COMMON_MODULES=common
COMMON_OBJ=$(addprefix $(COMMON_BUILD_DIR)/, $(addsuffix .o, $(COMMON_MODULES)))
$(COMMON_BUILD_DIR): | $(build_dir)
	mkdir $@

#                  _                                       #
#         ___  __ | |_   ___                               #
#        / -_)/ _|| ' \ / _ \                              #
#        \___|\__||_||_|\___/                              #

ECHO_MODULES=echo
ECHO_OBJ=$(addprefix $(ECHO_BUILD_DIR)/, $(addsuffix .o, $(ECHO_MODULES)))
$(ECHO_BUILD_DIR): | $(build_dir)
	mkdir $@

#                  _  _                                    #
#        ___ __ __(_)| |_                                  #
#       / -_)\ \ /| ||  _|                                 #
#       \___|/_\_\|_| \__|                                 #

EXIT_MODULES=exit
EXIT_OBJ=$(addprefix $(EXIT_BUILD_DIR)/, $(addsuffix .o, $(EXIT_MODULES)))
$(EXIT_BUILD_DIR): | $(build_dir)
	mkdir $@

#                                   _                      #
#         ___ __ __ _ __  ___  _ _ | |_                    #
#        / -_)\ \ /| '_ \/ _ \| '_||  _|                   #
#        \___|/_\_\| .__/\___/|_|   \__|                   #
#                  |_|                                     #

EXPORT_MODULES=append bypass create_destroy export sort
EXPORT_OBJ=$(addprefix $(EXPORT_BUILD_DIR)/, $(addsuffix .o, $(EXPORT_MODULES)))
$(EXPORT_BUILD_DIR): | $(build_dir)
	mkdir $@

#               _                                           #
#         _ __ (_) _ __  ___ __ __                          #
#        | '_ \| || '_ \/ -_)\ \ /                          #
#        | .__/|_|| .__/\___|/_\_\                          #
#        |_|      |_|                                       #

PIPEX_MODULES=fd handlers heredoc new_envp path_extruder pid pipex
PIPEX_OBJ=$(addprefix $(PIPEX_BUILD_DIR)/, $(addsuffix .o, $(PIPEX_MODULES)))
$(PIPEX_BUILD_DIR): | $(build_dir)
	mkdir $@

#                          _                                #
#         _ __ __ __ __ __| |                               #
#        | '_ \\ V  V // _` |                               #
#        | .__/ \_/\_/ \__,_|                               #
#        |_|                                                #

PWD_MODULES=pwd
PWD_OBJ=$(addprefix $(PWD_BUILD_DIR)/, $(addsuffix .o, $(PWD_MODULES)))
$(PWD_BUILD_DIR): | $(build_dir)
	mkdir $@

#                          _                                #
#         __ _  _  _  ___ | |_  ___  ___                    #
#        / _` || || |/ _ \|  _|/ -_)(_-<                    #
#        \__, | \_,_|\___/ \__|\___|/__/                    #
#           |_|                                             #

QUOTES_MODULES=quoted_split quotes
QUOTES_OBJ=$(addprefix $(QUOTES_BUILD_DIR)/, $(addsuffix .o, $(QUOTES_MODULES)))
$(QUOTES_BUILD_DIR): | $(build_dir)
	mkdir $@

#                              _                            #
#         _  _  _ _   ___ ___ | |_                          #
#        | || || ' \ (_-</ -_)|  _|                         #
#         \_,_||_||_|/__/\___| \__|                         #

UNSET_MODULES=unset
UNSET_OBJ=$(addprefix $(UNSET_BUILD_DIR)/, $(addsuffix .o, $(UNSET_MODULES)))
$(UNSET_BUILD_DIR): | $(build_dir)
	mkdir $@

#                   _ _             _   _                   #
#         ___ ___ _| |_|___ ___ ___| |_|_|___ ___           #
#        |  _| -_| . | |  _| -_|  _|  _| | . |   |          #
#        |_| |___|___|_|_| |___|___|_| |_|___|_|_|          #

REDIRECTION_MODULES=counter heredoc redirections remove_redirections
REDIRECTION_OBJ=$(addprefix $(REDIRECTION_BUILD_DIR)/, $(addsuffix .o, $(REDIRECTION_MODULES)))
$(REDIRECTION_BUILD_DIR): | $(build_dir)
	mkdir $@

DEPFLAGS = -MT $@ -MMD -MP -MF $(build_dir)/$*.d

#       .__                     .__
#  _____|__| ____   ____ _____  |  |   ______
# /  ___/  |/ ___\ /    \\__  \ |  |  /  ___/
# \___ \|  / /_/  >   |  \/ __ \|  |__\____ 
#/____  >__\___  /|___|  (____  /____/____  >
#     \/  /_____/      \/     \/          \/


SIGNALS_MODULES=signals
SIGNALS_OBJ=$(addprefix $(SIGNALS_BUILD_DIR)/, $(addsuffix .o, $(SIGNALS_MODULES)))
$(SIGNALS_BUILD_DIR): | $(build_dir)
	mkdir $@

#                      _                                    #
#         _ __   __ _ (_) _ _                               #
#        | '  \ / _` || || ' \                              #
#        |_|_|_|\__,_||_||_||_|                             #

obj=$(build_dir)/minishell.o $(EXPANSION_OBJ) $(CD_OBJ) $(COMMON_OBJ) \
$(ECHO_OBJ) $(EXIT_OBJ) $(EXPORT_OBJ) $(PIPEX_OBJ) $(PWD_OBJ) $(QUOTES_OBJ) \
$(REDIRECTION_OBJ) $(UNSET_OBJ) $(SIGNALS_OBJ)

$(build_dir)/%.o: %.c $(build_dir)/%.d Makefile
	cc $(cflags) $(iflags) $(DEPFLAGS) -c $< -o $@

$(name) : $(readline_dir)/lib/libreadline.a $(libft_dir)/libft.a $(obj)
	cc $(lflags) -o $@ $(obj) -lreadline -lft -lcurses

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

dirs: $(CD_BUILD_DIR)/ $(COMMON_BUILD_DIR)/ $(ECHO_BUILD_DIR)/ $(EXIT_BUILD_DIR)/ \
$(EXPANSION_BUILD_DIR)/ $(EXPORT_BUILD_DIR)/ $(PIPEX_BUILD_DIR)/ $(PWD_BUILD_DIR)/ \
$(QUOTES_BUILD_DIR)/ $(UNSET_BUILD_DIR)/ $(REDIRECTION_BUILD_DIR)/ $(SIGNALS_BUILD_DIR)

$(build_dir):
	mkdir $@

$(obj:.o=.d):
include $(obj:.o=.d)
