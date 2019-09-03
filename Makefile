CC = gcc 
CFLAGS =-I. --std=c11 -pedantic -Wall -Wuninitialized -O3
SRC = src
BUILD = build
LIBRARIES = -lm
TESTBINARIES = four_game_test four_opt_test four_ai_test test_helper_test four_io_test
BINARIES = $(TESTBINARIES) connect4
HEADERS = $(wildcard $(SRC)/*/*.h)

.PHONY: all clean compile test checkstyle

all: compile test checkstyle

clean:
	rm -f -r $(BINARIES) build/*

compile: $(BINARIES)

%.o: $(SRC)/ai/%.c $(HEADERS)
	$(CC)$(CFLAGS) -c $< -o $(BUILD)/$@

%.o: $(SRC)/main/%.c $(HEADERS)
	$(CC)$(CFLAGS) -c $< -o $(BUILD)/$@

%.o: $(SRC)/game/%.c $(HEADERS)
	$(CC)$(CFLAGS) -c $< -o $(BUILD)/$@

%.o: $(SRC)/opt/%.c $(HEADERS)
	$(CC)$(CFLAGS) -c $< -o $(BUILD)/$@

%.o: $(SRC)/io/%.c $(HEADERS)
	$(CC)$(CFLAGS) -c $< -o $(BUILD)/$@

%.o: $(SRC)/test_helper/%.c $(HEADERS)
	$(CC)$(CFLAGS) -c $< -o $(BUILD)/$@


test: $(TESTBINARIES)
	for test in $(addprefix $(BUILD)/,$(TESTBINARIES)); do ./$$test; done
	$(info )
	$(info ********** EXECUTE TESTS **********)

checkstyle:
	#python3 ./cpplint.py --repository=. --filter=-runtime/int,-readability/casting,-runtime/threadsafe_fn,-runtime/printf,-build/include_subdir,-build/include_what_you_use $(SRC)/*/*.c $(SRC)/*/*.h

# main
connect4: four_main.o four_game.o four_io.o four_ai.o four_opt.o
	$(CC)$(CFLAGS) $(addprefix $(BUILD)/,$^) $(LIBRARIES) -o $(BUILD)/$@

#game
four_game_test: four_game_test.o four_game.o four_io.o four_ai.o
	$(CC)$(CFLAGS) $(addprefix $(BUILD)/,$^) $(LIBRARIES) -o $(BUILD)/$@

# io
four_io_test: four_io_test.o four_io.o four_game.o test_helper.o four_ai.o
	$(CC)$(CFLAGS) $(addprefix $(BUILD)/,$^) $(LIBRARIES) -o $(BUILD)/$@

# opt
four_opt_test: four_opt_test.o four_opt.o
	$(CC)$(CFLAGS) $(addprefix $(BUILD)/,$^) $(LIBRARIES) -o $(BUILD)/$@

# ai
four_ai_test: four_ai_test.o four_ai.o four_game.o four_io.o
	$(CC)$(CFLAGS) $(addprefix $(BUILD)/,$^) $(LIBRARIES) -o $(BUILD)/$@

#test_helper
test_helper_test: test_helper_test.o test_helper.o
	$(CC)$(CFLAGS) $(addprefix $(BUILD)/,$^) $(LIBRARIES) -o $(BUILD)/$@

