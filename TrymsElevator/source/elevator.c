#include "elevator.h"


void initElevator(){
    // Initiate to UNDEFINED
    printf("Elevator initiating \n");
    
    elevio_init();
    printf("Connected to server \n");
    elev.State = UNDEFINED;
    elev.Floor = -1;
    elev.Dir[1] = 0; //Assumes it dosen't move when we start up. 
    elev.currentFloorRequest = -1;
    elev.requestInDIr = -1;
    printf("Finished function \n");
}

void printElevatorState(){
    printf("\n");
    printf("Elevator status: \n");
    printf("#+------------------------------------+\n");
    printf("| State = %d, Floor = %d, Direction = %d |\n", elev.State, elev.Floor, elev.Dir[1]);
    printf("#+------------------------------------+\n");
    printf("\n");
}

void moveElevator(MotorDirection dir){
    elevio_motorDirection(dir);
}

int getFloorSensor(){
    return elevio_floorSensor();
}

int getStopButton(){
    return elevio_stopButton();
}

void stopElevator(){
    elevio_motorDirection(DIRN_STOP);
}

void openDoor(){
    elevio_doorOpenLamp(1);
}
void closeDoor(){
    elevio_doorOpenLamp(0);
}

void turnOnFloorLamp(int Floor){
    elevio_floorIndicator(Floor);
}

int getObstruction(){
    return elevio_obstruction();
}