/*
 * utils.h
 *
 * Created: 5/30/2023 7:22:48 PM
 *  Author: hassa
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define SETBIT(reg,bit)    reg = reg |  (1<<bit)
#define CLEARBIT(reg,bit)  reg = reg &~ (1<<bit)
#define TOGGLEBIT(reg,bit) reg = reg ^  (1<<bit)
#define READBIT(reg,bit)   ((reg>>bit)&1)



#endif /* UTILS_H_ */