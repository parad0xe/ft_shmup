# build
NAME = ft_shmup

CC = cc
BUILD = build

# flags
CFLAGS = -MMD -MP -Wall -Wextra -Werror -g

LIBS=-lncurses

# files
SRC_DIRECTORY = srcs
SRCS=$(addprefix $(SRC_DIRECTORY)/,\
	core/game.c \
	core/entity.c \
	entities/enemy.c \
	entities/player.c \
	entities/bullet.c \
	entities/background.c \
	renderer/ui_renderer.c \
	renderer/game_renderer.c \
	utils/time_utils.c \
	utils/rand_utils.c \
	input.c \
	main.c \
)

OBJS = $(SRCS:$(SRC_DIRECTORY)/%.c=$(BUILD)/%.o)
DEPS = $(OBJS:%.o=%.d)

# rules
all:
	@mkdir -p $(BUILD)
	@$(MAKE) $(NAME) --no-print-directory

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -Iincludes/ -o $@ $^ $(LIBS)

$(BUILD)/%.o: $(SRC_DIRECTORY)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iincludes/ -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
