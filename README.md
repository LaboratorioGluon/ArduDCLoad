# ArduDCLoad	

A configurable multipurpose DC Load board developed directly [on Twitch](https://www.twitch.tv/labgluon)

The values of the resistors can be calculated to adapt the PCB to your needs.

With defaul values máximum values are:
- V_TEST: 15V, 3A
- V_In; 5V



And this is how it looks:

![PCB Image](/Imagenes/CargaElectronica.jpg)


# Design and customization

Here we will see how to customize the circuit for our need. The ADCL (ArduDCLoad) can be configure to mount a beefy TO-247 or small TO-220 MOSFETS. Also, it also contains the footprint for 10 resistors( L: 10mm, D: 3.6mm, P:15mm) or big chunky wirewound resistor (L:50mm, W:14mm).

Lets see how to adapt it to your need (we will calculate the values for the current values in the design)

## Select V_TEST and I_TEST

Set what do you need for V_TEST and I_TEST. The circuit can only support **around 5-6A** máximum.

In our case

> V_TEST = 15V
> I_TEST = 3A

## Select MOSFET measuring resistor

The ideal values would be between 1 to 0.1 Ohms. The lower the current you expect, the bigget the value should be. In our case, for 3A, with 1 Ohm, we have 3V drop, so we can go with 1 Ohm. (We expect to test more than 3V)



