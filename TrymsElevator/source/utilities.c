#include "utilities.h"


void floorReached(int floor){
    stopElevator();
    elev.Dir[1] = DIRN_STOP;

    openDoor();
    elev.State = DOOROPEN;

    deleteRequest();

    start = startTimer();
}

void wait(){
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