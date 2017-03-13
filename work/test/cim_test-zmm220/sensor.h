/*************************************************
                                           
 ZEM 200                                          
                                                    
 sensor.h 
                                                      
 Copyright (C) 2003-2006, ZKSoftware Inc.      		
                                                      
*************************************************/

#ifndef	_SENSOR_H_
#define	_SENSOR_H_

#define CMOS_WIDTH 	640
#define CMOS_HEIGHT 	480

void InitSensor(int LeftLine, int TopLine, int Width, int Height, int FPReaderOpt);
void FreeSensor(void);
int CaptureSensor(char *Buffer);

#endif

