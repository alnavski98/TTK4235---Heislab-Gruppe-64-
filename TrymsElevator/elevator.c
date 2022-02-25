#include "elevator.h"

elevatorState elevatorInit(){
    // Initiate to UNDEFINED
    elevio_init();
    printf("Connected to server \n");
    elevatorState elevator;
    elevator.State = UNDEFINED;
    elevator.Floor = -1;
    elevator.PrevFloor = -1;
    elevator.Dir = 0; //Assumes it dosen't move when we start up. 
    elevator.currentFloorRequest = -1;
    printf("Finished function \n");
    return elevator;
}

void printElevatorState(elevatorState elevator){
    printf("################################### \n");
    printf("State = %d, Floor = %d, Direction = %d, Previous floor = %d \n", elevator.State, elevator.Floor, elevator.Dir, elevator.PrevFloor);
    printf("################################### \n");
}

void move(MotorDirection dir){
    elevio_motorDirection(dir);
}

void stopElevator(){
    elevio_motorDirection(DIRN_STOP);
}

int compareFloor(int Floor, int floorRequest){
    if (Floor == floorRequest){
        return 1;
    }else{
        return 0;
    }
}

int requestIsAbove(int Floor, int floorRequest){
    if(Floor < floorRequest){
        return 1;
    }else{
        return 0;
    }
}

void openDoor(){
    elevio_doorOpenLamp(1);
}
void closeDoor(){
    elevio_doorOpenLamp(0);
}