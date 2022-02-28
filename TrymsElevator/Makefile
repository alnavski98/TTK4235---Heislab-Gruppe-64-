.DEFAULT_GOAL := main

CC := gcc
CFALGS := -O0 -g3

SOURCE = main.c elevio.c timer.c elevator.c requestManager.c stateMachine.c


.PHONY : clean
clean  :
	rm -f *.o

main : $(SOURCE)
	$(CC) -o $@ $(SOURCE) $(CFLAGS)




