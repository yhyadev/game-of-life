OUT_DIR := out

CFLAGS = -Wall -Wextra -O3

all: $(OUT_DIR) $(OUT_DIR)/raylib $(OUT_DIR)/terminal

$(OUT_DIR):
	mkdir -p $@

$(OUT_DIR)/raylib: common.c raylib.c
	$(CC) $(CFLAGS) $? -o $@ -L./raylib/src -lraylib -lm 

$(OUT_DIR)/terminal: common.c terminal.c
	$(CC) $(CFLAGS) $? -o $@

clean: $(OUT_DIR)
	rm -rf $?
