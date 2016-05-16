/*
 * IR_Sensor.h
 *
 *  Created on: 2-mei.-2016
 *      Author: Redouane
 */

//properties
#ifndef SRC_IR_SENSOR_H_
#define SRC_IR_SENSOR_H_



//function(s)
void Timer3_Init();
/* Timer 3  -   Snelheid bepalen via de sensor
   sensor moet aangesloten zijn op pin D3 en interrupt 3 zal gebruikt worden
*/

void LCDSnelheid();

/* snelheid van de schijf weergeven op het LCD-scherm van het dwenguino bord */


#endif /* SRC_IR_SENSOR_H_ */
