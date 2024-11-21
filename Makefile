all:
	cc main.c views.c strutils.c -fsanitize=address
