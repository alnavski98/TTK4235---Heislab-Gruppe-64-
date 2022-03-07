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

void printElevator(){
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

void stopElevator(){
    elevio_motorDirection(DIRN_STOP);
}

void openDoor(){
    elevio_doorOpenLamp(1);
}
void closeDoor(){
    elevio_doorOpenLamp(0);
}


void pollFloorSensor(){
    int Floor = getFloorSensor();
    if(Floor != elev.Floor && Floor != -1){
        elev.Floor = Floor;
        turnOnFloorLamp(Floor);
    }
}

void pollStopButton(){
    if(elevio_stopButton()){
        //printf("Stop Button pressed\n");
        stopElevator();
        elev.Dir[0] = elev.Dir[1];
        elev.Dir[1] = DIRN_STOP;
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



int getFloorSensor(){
    return elevio_floorSensor();
}

int getStopButton(){
    return elevio_stopButton();
}



int getObstruction(){
    return elevio_obstruction();
}

void turnOnFloorLamp(int Floor){
    elevio_floorIndicator(Floor);
}

void setStopLamp(int value){
    elevio_stopLamp(value);
}

void setButtonLamp(int floor, int button, int value){
    elevio_buttonLamp(floor,button,value);
}

int checkButtonPress(int floor, int button){
    return elevio_callButton(floor, button);
}