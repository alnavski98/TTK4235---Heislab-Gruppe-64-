#include "elevator.h"


void initElevator(){
    // Initiate to UNDEFINED
    printf("Elevator initiating \n");
    
    elevio_init();
    printf("Connected to server \n");
    elev.State = UNDEFINED;
    elev.Floor = -1;
    elev.Dir = 0; //Assumes it dosen't move when we start up. 
    elev.currentFloorRequest = -1;
    elev.requestInDIr = -1;
    printf("Finished function \n");
}

void printElevatorState(){
    printf("\n");
    printf("Elevator status: \n");
    printf("#+------------------------------------+\n");
    printf("| State = %d, Floor = %d, Direction = %d |\n", elev.State, elev.Floor, elev.Dir);
    printf("#+------------------------------------+\n");
    printf("\n");
}

void move(MotorDirection dir){
    elevio_motorDirection(dir);
}

void stopElevator(){
    elevio_motorDirection(DIRN_STOP);
}

int OnFloor(int floor){
    if (elev.Floor == floor){
        return 1;
    }else{
        return 0;
    }
}

int requestIsAbove(){
    if(elev.Floor < elev.currentFloorRequest){
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

void pollFloorSensor(){
        int Floor = elevio_floorSensor();
        if(Floor != elev.Floor && Floor != -1){
            elev.Floor = Floor;
            elevio_floorIndicator(Floor);
        }
}

void pollStopButton(){
    if(elevio_stopButton()){
        printf("Stop Button pressed\n");
        stopElevator();
        elev.Dir = DIRN_STOP;
        elevio_stopLamp(1);
        elev.State = STOPBUTTON;
    }
}
void pollObstructionButton(){
    if(elevio_obstruction()){
        printf("Obstruction in Door!\n");
        elev.State = OBSTRUCTION;
    }
}