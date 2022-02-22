.DEFAULT_GOAL := main

CC := gcc
CFALGS := -O0 -g3

SOURCE = main.c stateMachine.c elevator.c requestManager.c timer.c elevio.c



.PHONY : clean
clean  :
	rm -f *.o

main : $(SOURCE)
	$(CC) -o $@ $(SOURCE) $(CFLAGS)




