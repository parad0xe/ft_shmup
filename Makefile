# build
NAME = ft_shmup

CC = cc
AR = ar rcs
BUILD = build

# flags
CFLAGS = -MMD -MP -Wall -Wextra -Werror

# files
MANDATORY_DIRECTORY = mandatory
SRCS=$(addprefix $(MANDATORY_DIRECTORY)/,\
	main.c \
)

BONUS_DIRECTORY = bonus
BONUS_SRCS = $(addprefix $(BONUS_DIRECTORY)/,\
	main.c\
)

OBJS = $(SRCS:%.c=$(BUILD)/%.o)
DEPS = $(OBJS:%.o=%.d)

# rules
all:
	@rm -rf $(BUILD)/$(BONUS_DIRECTORY)
	@mkdir -p $(BUILD)/$(MANDATORY_DIRECTORY)
	@$(MAKE) $(NAME) --no-print-directory

bonus:
	@rm -rf $(BUILD)/$(MANDATORY_DIRECTORY)
	@mkdir -p $(BUILD)/$(BONUS_DIRECTORY)
	@$(MAKE) $(NAME) SRCS="$(BONUS_SRCS)" --no-print-directory

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -Iincludes/ -o $@ $^

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iincludes/ -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
