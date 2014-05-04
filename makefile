DogeShell: DogeShell.c input.c linked_list.c history.c dynamic_char_array.c
	gcc -o DogeShell -Wall -Wextra -Werror --std=c99 DogeShell.c input.c linked_list.c history.c dynamic_char_array.c

clean:
	rm DogeShell linked_list input

cleanObjectFiles:
	rm *.o