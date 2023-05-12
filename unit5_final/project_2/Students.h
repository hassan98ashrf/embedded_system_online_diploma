/*
Author : Hassaan Ahsraf Elssalakawy
header of FIFO
*/

#ifndef _Student_H_
#define _Student_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include"string.h"
//setup std number
#define NAME_LENGTH 25
#define COURSES_NUMBER 5  //55 66 77 88   
#define STUDENTS_NUMBER 50 

//User configuration
struct Sstudents{
	char f_name[25];
	char l_name[25];
	int id;
	float GPA;
	int course[10];
};
typedef struct Sstudents Sstudents_Data_t;


#define element_type Sstudents_Data_t

//FIFO data type
typedef struct{
	uint32_t length;
	uint32_t count;
	element_type* base;
	element_type* head;
	element_type* tail;
} FIFO_Buffer_t;


typedef enum{
	FIFO_No_Error,
	FIFO_Full,
	FIFO_Empty,
	FIFO_Null,
	FIFO_error
} FIFO_Status;

//APIs
FIFO_Status FIFO_init(FIFO_Buffer_t* FIFO_Buffer , element_type* buf , uint32_t length);
FIFO_Status FIFO_enqueue(FIFO_Buffer_t* FIFO_Buffer , element_type item);
FIFO_Status add_student_manually(FIFO_Buffer_t* FIFO_Buffer );
FIFO_Status add_student_from_text(FIFO_Buffer_t* FIFO_Buffer);
FIFO_Status delete_student(FIFO_Buffer_t* FIFO_Buffer);
FIFO_Status delete_all(FIFO_Buffer_t* FIFO_Buffer);
FIFO_Status view_student(FIFO_Buffer_t* FIFO_Buffer );
FIFO_Status find_student_by_id(FIFO_Buffer_t* FIFO_Buffer);
FIFO_Status find_student_by_f_name(FIFO_Buffer_t* FIFO_Buffer);
FIFO_Status find_student_by_course(FIFO_Buffer_t* FIFO_Buffer);
void  print_students_number(FIFO_Buffer_t* FIFO_Buffer);
FIFO_Status update_Student(FIFO_Buffer_t* FIFO_Buffer);
FIFO_Status FIFO_isFull(FIFO_Buffer_t* FIFO_Buffer);
struct Sstudents* search_student_by_id(FIFO_Buffer_t* FIFO_Buffer,int ID);

#endif