# Design

The software is splitted into 3 components:
- Input : Handling the inputs of the buttons/rotary encoder
- Screen : Send the data to the screen and handle the info and display
- DcLoad : Control the PWM output to control the actual DC Load

# Project Structure + Conventions

- src/
    - taskInput/
        - mainInput.cpp/h
    - taskScreen/
        - mainScreen.cpp/h
    - taskDcLoad/
        - mainDcLoad.cpp/h
    - taskConfig.h
    - globalConfig.h
    - main.cpp

## Tasks

Each task will have a structure with the data it can gather. `struct <component>Data;`



## Naming

```
<component><part>()
ie: inputMainLoop()

```

# System
The system will be Arduino Nano AtMega328p

ADCs:
Interrupts: 

# Components

## Input

- Data:
    - RotaryPulses
    - PushButtons[2]
    - ADC read.
- Period: 100 ms
- Interrupts:
    - 


## Screen

- Data: 
    - Current Mode
    - Current/Power value set.
- Period: 300 ms

### Screens

#### Welcome

Print something like 

---------------
"  Welcome!  "
" ArduDCLoad "
---------------


#### 


## DcLoad

- Data: None
- Period: 50 ms

