/*
 * IncFile1.h
 *
 * Created: 5/30/2023 3:20:46 PM
 *  Author: hassa
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_


#define SETBIT(reg,bit)    reg = reg |  (1<<bit)
#define CLEARBIT(reg,bit)  reg = reg &~ (1<<bit)
#define TOGGLEBIT(reg,bit) reg = reg ^  (1<<bit)
#define READBIT(reg,bit)   ((reg>>bit)&1)



#endif /* INCFILE1_H_ */ 