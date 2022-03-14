#include "utilities.h"


void floorReached(int floor){
    stopElevator();
    elev.Dir[1] = DIRN_STOP;

    openDoor();
    elev.State = DOOROPEN;

    deleteRequestsOnFloor();

    start = startTimer();
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