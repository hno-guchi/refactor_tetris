NAME = tetris

CFLAGS = -Wall -Wextra -MMD -MP 
LIBS = -lncurses

SRCS = tetris.c field.c game_loop.c print.c tetrimino.c timer.c
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

.PHONY: all clean fclean re

all: $(NAME)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: debug leaks

debug: CFLAGS += -g -fsanitize=address -fsanitize=undefined -fsanitize=integer
debug: re
d: debug

leaks: CFLAGS += -g -DLEAKS
leaks: re
l: leaks

-include $(DEPS)

