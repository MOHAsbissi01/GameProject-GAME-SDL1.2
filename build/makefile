CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image

SRCS = main.c enigme.c
OBJS = $(SRCS:.c=.o)

all: game

game: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) game

