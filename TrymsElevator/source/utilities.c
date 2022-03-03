#include "utilities.h"


void floorReached(int floor){
    stopElevator();
    elev.Dir[1] = DIRN_STOP;

    openDoor();
    elev.State = DOOROPEN;

    deleteRequest();

    start = startTimer();
}

void waitStopUnpressed(){
    start = startTimer();
    end = endTimer();
    while(timeSpent(end, start) < 0.5){
        if(getStopButton()){
            start = startTimer();
        }
        end = endTimer();
    }
    elevio_stopLamp(0);
}


int checkIfOnFloor(int floor){
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



int getFloorSensor(){
    return elevio_floorSensor();
}

int getStopButton(){
    return elevio_stopButton();
}

void turnOnFloorLamp(int Floor){
    elevio_floorIndicator(Floor);
}

int getObstruction(){
    return elevio_obstruction();
}