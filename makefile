C_SRC := ./src
C_INC := ./include
BUILD_DIR := ./build

SRCS_SERVER =  $(C_SRC)/src_cli_fifo.c \
			  $(C_SRC)/Handlers_Serv.c \
              $(C_SRC)/utils.c \
			  $(C_SRC)/server.c

SRCS_CLIENT = $(C_SRC)/client.c \
              $(C_SRC)/src_cli_fifo.c \
              $(C_SRC)/utils.c 

OBJS_SERVER = $(patsubst $(C_SRC)/%.c, $(BUILD_DIR)/%.o, $(SRCS_SERVER))
OBJS_CLIENT = $(patsubst $(C_SRC)/%.c, $(BUILD_DIR)/%.o, $(SRCS_CLIENT))

CC := gcc
CFLAGS := -I$(C_INC)
LDFLAGS := -o

Server: $(BUILD_DIR) $(OBJS_SERVER)
	$(CC) -g $(OBJS_SERVER) -o server $(CFLAGS)

Client: $(BUILD_DIR) $(OBJS_CLIENT)
	$(CC) $(OBJS_CLIENT) -o client $(CFLAGS)

$(BUILD_DIR)/%.o: $(C_SRC)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o server client