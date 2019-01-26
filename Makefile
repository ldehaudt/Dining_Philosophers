NAME = philo
SRC = display.c philo.c setup.c

FRAMEWORKS = -framework OpenGl
BREW_INC = -I ~/.brew/include
SDL_LINK = -g  -L ~/.brew/lib -l SDL2
FLAGS = -w

GREEN = \033[1;38;2;0;175;117m
RED = \033[1;38;2;225;20;20m
WHITE = \033[1;38;2;255;251;214m
YELLO = \033[1;38;2;255;200;0m

all: $(NAME)

$(NAME): $(SRC) philo.h
	# @echo "${YELLO}Checking for graphics library ..."
	# @brew install sdl2
	@echo "${YELLO}Compiling ...${WHITE}"
	@gcc $(FLAGS) $(SRC) -o $(NAME) $(FRAMEWORKS) $(BREW_INC) $(SDL_LINK)
	@echo "${GREEN}Done!${WHITE}"

clean:
	@echo "${RED}Removing object files"	
	@rm -f *.o
	@rm -R $(NAME).dSYM

fclean: clean
	@echo "${RED}Removing Executable >.<"
	@rm -f $(NAME)

re: fclean all
