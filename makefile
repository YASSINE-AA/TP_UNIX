C_SRC := ./src
C_INC := ./include
C_TEST := ./test
BUILD_DIR := ./build

SRCS_SERVER = $(C_SRC)/src_cli_fifo.c \
              $(C_SRC)/Handlers_Serv.c \
              $(C_SRC)/utils.c \
              $(C_SRC)/server.c

SRCS_CLIENT = $(C_SRC)/client.c \
              $(C_SRC)/src_cli_fifo.c \
              $(C_SRC)/utils.c

SRCS_TEST = $(C_TEST)/unity.c \
            $(C_TEST)/tests.c \
			$(C_SRC)/src_cli_fifo.c \
			$(C_SRC)/utils.c

OBJS_SERVER = $(patsubst $(C_SRC)/%.c, $(BUILD_DIR)/%.o, $(SRCS_SERVER))
OBJS_CLIENT = $(patsubst $(C_SRC)/%.c, $(BUILD_DIR)/%.o, $(SRCS_CLIENT))
OBJS_TEST = $(patsubst $(C_SRC)/%.c, $(BUILD_DIR)/%.o, $(SRCS_TEST))
OBJS_TEST_INC = $(patsubst $(C_TEST)/%.c, $(BUILD_DIR)/%.o, $(SRCS_TEST))

CC := gcc
CFLAGS := -I$(C_INC) -I$(C_INC)/unity -g

Server: $(BUILD_DIR) $(OBJS_SERVER)
	$(CC) $(OBJS_SERVER) -o $(BUILD_DIR)/server

Client: $(BUILD_DIR) $(OBJS_CLIENT)
	$(CC) $(OBJS_CLIENT) -o $(BUILD_DIR)/client

Test: $(BUILD_DIR) $(OBJS_TEST)
	$(CC) $(OBJS_TEST_INC) -o $(BUILD_DIR)/test $(CFLAGS)



$(BUILD_DIR)/%.o: $(C_SRC)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(C_TEST)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/server $(BUILD_DIR)/client $(BUILD_DIR)/test
