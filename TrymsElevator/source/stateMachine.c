# include "stateMachine.h"

void stateUNDEFINED(){
    while(1){
        int Floor = getFloorSensor();
        if (Floor == -1){
            moveElevator(DIRN_DOWN);
            elev.Dir[1] = DIRN_DOWN;
        }else{
            stopElevator();
            elev.Dir[1] = DIRN_STOP;
            elev.Floor = Floor;
            turnOnFloorLamp(Floor);
            elev.State = IDLE;
            break;
        }
    }

    printf("State defined! \n");
    printElevatorState();
}

void stateIDLE(){
    // Check stop button
    pollStopButton();

    // Check requests
    if(elev.currentFloorRequest != -1){
        if( checkIfOnFloor(elev.currentFloorRequest)){
            floorReached();
            elev.currentFloorRequest = -1;
        }else if(requestIsAbove()){
            moveElevator(DIRN_UP);
            elev.State = MOVING;
            elev.Dir[1] = DIRN_UP;
        }else{
            moveElevator(DIRN_DOWN);
            elev.State = MOVING;
            elev.Dir[1] = DIRN_DOWN;
        }
        printElevatorState();
        printRequestManager();
    }
}

void stateIDLEINBETWEEN(){

    // Check stop button
    pollStopButton();

    // Check requests
    if(elev.currentFloorRequest != -1){
        if(checkIfOnFloor(elev.currentFloorRequest)){
            if(elev.Dir[0] == DIRN_UP){
                elev.Floor = elev.Floor + 1;
                moveElevator(DIRN_DOWN);
                elev.Dir[1] = DIRN_DOWN;
            } else if(elev.Dir[0] == DIRN_DOWN){     
                elev.Floor = elev.Floor - 1;           
                moveElevator(DIRN_UP);
                elev.Dir[1] = DIRN_UP;
            }
            elev.State = MOVING;

        }else if(requestIsAbove()){
            moveElevator(DIRN_UP);
            elev.State = MOVING;
            elev.Dir[1] = DIRN_UP;
        }else{
            moveElevator(DIRN_DOWN);
            elev.State = MOVING;
            elev.Dir[1] = DIRN_DOWN;
        }
        printElevatorState();
        printRequestManager();
    }
}

void stateMOVING(){
    //Check stop button
    pollStopButton();

    // Check if request in dir. is reached
    if(checkIfOnFloor(elev.requestInDIr)){
        floorReached();
        elev.requestInDIr = -1;

        printElevatorState();
        printRequestManager();
    }

    // Check if request is reached
    if(checkIfOnFloor(elev.currentFloorRequest)){
        floorReached();
        elev.currentFloorRequest = -1;

        printElevatorState();
        printRequestManager();
    }
}

void stateDOOROPEN(){
    end = endTimer();

    // Check for obstruction
    pollObstructionButton();
    
    // Check for stop button
    pollStopButton();

    // Close door after 3 seconds
    if(timeSpent(end, start) >= 3){
        closeDoor();
        elev.State = IDLE;

        printElevatorState();
        printRequestManager();
    }
}

void stateOBSTRUCTION(){
    // Check stop button
    pollStopButton();

    // Check if obstruction removed
    if(!getObstruction()){
        printf("Obstruction removed\n");
        elev.State = DOOROPEN;
        start = startTimer();
    }
}

void stateSTOPBUTTON(){
    // Delete all requests. 
    deleteAllRequests();

    // If we are on floor -> open door
    if(getFloorSensor() != -1){ 
        openDoor();
    }

    // Wait till stopbutton is not pressed
    waitStopUnpressed();
    
    // If on floor go to door open or If inbetween floors go to IDLEINBETWEEN
    if(getFloorSensor()== -1){
        elev.State = IDLEINBETWEEN;
    }else{
        elev.State = DOOROPEN;
        start = startTimer();
    }
    
    // Print state
    printElevatorState();
    printRequestManager();
}



void stateMachine(){
    // Initiating elevator
    initElevator();
    printElevatorState();

    // Initiating requestManager
    initRequestManager();
    printRequestManager();

    while(1){
        // Update floor
        pollFloorSensor();
        
        // Poll buttons, update requestManager
        pollElevatorButtons();
        //updateNrRequests();
        
        // Get requests and requests in direction of travel. 
        getNewRequest();
        checkRequestInDIrection();

        switch(elev.State){
            case UNDEFINED:
                stateUNDEFINED();
                break;

            case IDLE:
                stateIDLE();
                break;

            case IDLEINBETWEEN:
                stateIDLEINBETWEEN();
                break;

            case MOVING:
                stateMOVING();
                break;

            case DOOROPEN:
                stateDOOROPEN();
                break;

            case OBSTRUCTION:
                stateOBSTRUCTION();
                break;

            case STOPBUTTON:
                stateSTOPBUTTON();
                break;

            default: 
                printf("Not Working\n");
                break;
            
        }
    }
}