NAME	=	ircserv

BUILD	=	build

INCLUDE	=	include

SUBDIRS =	network commands application

SRC		=	src

SRCS	=	$(patsubst %.cpp, $(SRC)/%.cpp, \
			main.cpp utils.cpp) \
			$(patsubst %.cpp, $(SRC)/network/%.cpp, \
			Server.cpp Connection.cpp) \
			$(patsubst %.cpp, $(SRC)/application/%.cpp, \
			Client.cpp Channel.cpp Application.cpp Parser.cpp) \
			$(patsubst %.cpp, $(SRC)/commands/%.cpp, \
			CommandHandler.cpp Cap.cpp Invite.cpp Join.cpp \
			Kick.cpp Mode.cpp Nick.cpp Notice.cpp \
			Part.cpp Pass.cpp Ping.cpp Pong.cpp \
			PrivMsg.cpp Quit.cpp Topic.cpp User.cpp \
			Who.cpp)

INC		=	$(patsubst %.hpp, $(INCLUDE)/%.hpp, \
			defines.hpp utils.hpp \
			Command.hpp CommandHandler.hpp Parser.hpp \
			IRCMessage.hpp) \
			$(patsubst %.hpp, $(INCLUDE)/network/%.hpp, \
			Connection.hpp Server.hpp) \
			$(patsubst %.hpp, $(INCLUDE)/application/%.hpp, \
			Application.hpp Channel.hpp Client.hpp)

OBJS	=	$(foreach dir, $(SUBDIRS), \
			$(patsubst $(SRC)/$(dir)/%.cpp, $(BUILD)/%.o, \
			$(filter $(SRC)/$(dir)/%.cpp, $(SRCS)))) \
			$(patsubst %.cpp, $(BUILD)/%.o, main.cpp utils.cpp)

DEP		=	$(INC) Makefile

# Compilation Options

CXX			=	c++

CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 #-g -fsanitize=address

INCFLAGS	=	-I $(INCLUDE) -I$(INCLUDE)/application -I$(INCLUDE)/network

# Colors

RESET	=	\033[0m
RED		=	\033[31m
GREEN	=	\033[32m
BLUE	=	\033[34m

# Rules

all:		$(BUILD) $(NAME)

$(BUILD):
			@mkdir -p $(BUILD)

$(BUILD)/%.o:	$(SRC)/%.cpp $(DEP)
			@echo "$(BLUE)Compiling: $<$(RESET)"
			@$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

$(BUILD)/%.o:	$(SRC)/*/%.cpp $(DEP)
			@echo "$(BLUE)Compiling: $<$(RESET)"
			@$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(OBJS)
			@$(CXX) $(CXXFLAGS) $(INCFLAGS) $(OBJS) -o $(NAME)
			@echo "$(GREEN)$(NAME) has been created.$(RESET)"

clean:
			@rm -rf $(BUILD)
			@echo "$(RED)Objects have been removed.$(RESET)"

fclean:	clean
			@rm -f $(NAME)
			@echo "$(RED)$(NAME) has been removed.$(RESET)"

re:		fclean all

.PHONY:	all clean fclean re
