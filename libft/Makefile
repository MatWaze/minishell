CFLAGS=-Wall -Wextra -Werror
BUILD_DIR=build
MODULES=ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset ft_strchr \
ft_strdup ft_strlcat ft_strlcpy ft_strlen ft_strncmp ft_strnstr ft_strrchr ft_tolower ft_toupper \
ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap \
get_next_line get_next_line_utils

OBJ=$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(MODULES)))

.PHONY: all clean fclean re

all: libft.a

libft.a: $(BUILD_DIR) $(OBJ)
	ar rcs libft.a $(OBJ)

$(BUILD_DIR)/%.o: %.c libft.h
	cc $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f libft.a

re: fclean all

$(BUILD_DIR):
	mkdir $(BUILD_DIR)
