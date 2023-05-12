/*
Author : Hassaan Ahsraf Elssalakawy
FIFO.c
*/

#include "Students.h"


FILE *students_file;

FIFO_Status FIFO_init(FIFO_Buffer_t* FIFO_Buffer , element_type* buf , uint32_t length){
	//Check Buffer availability
	if(buf == NULL)
		return FIFO_Null;

	//Initialize FIFO
	FIFO_Buffer->base = buf;
	FIFO_Buffer->head = buf;
	FIFO_Buffer->tail = buf;
	FIFO_Buffer->length = length;
	FIFO_Buffer->count = 0;

	return FIFO_No_Error;
}

FIFO_Status add_student_manually(FIFO_Buffer_t* FIFO_Buffer ){
	
	Sstudents_Data_t new_student;
	printf("------------------------------\n");
	printf("Add the Student Details: \n");
	printf("------------------------------\n");
	printf("Enter the ID Number: ");
	scanf("%d",&new_student.id);
	//check if id exist
	if(search_student_by_id(FIFO_Buffer,new_student.id) != NULL){
		printf("\n[ERROR]: ID Number %d is already taken\n",new_student.id);
		return FIFO_error;
	}
	
	printf("Enter first name : ");
	scanf("%s",new_student.f_name);
	printf("Enter last name : ");
	scanf("%s",new_student.l_name);
	printf("Enter GPA : ");
	scanf("%f",&new_student.GPA);
	printf("Enter course's ID : \n");
	int i;
	for(i = 0; i<COURSES_NUMBER ; i++){
		printf("Course number %d: ",(i+1));
		scanf("%d",&new_student.course[i]);
	}
	
	//check add if done succesfully
	if(FIFO_enqueue(FIFO_Buffer,new_student)== FIFO_No_Error){
		printf("\n[INFO]: Student Details is added successfully\n");
	}
	else{
		printf("\n[ERROR]: Adding students manually failed\n");
		return FIFO_error;
	}
	
	print_students_number(FIFO_Buffer);
	return FIFO_No_Error;
}

FIFO_Status add_student_from_text(FIFO_Buffer_t* FIFO_Buffer){
	int i;
	Sstudents_Data_t new_student;
	printf("---------------------------\n");
	students_file = fopen("Students.txt","r");
	
	// check if the file  is NULL 
	if(students_file == NULL){
		printf("\n [ERROR] student.txt file not found.\n\n [ERROR] adding students from file failed.");
		return FIFO_Null;
	}
	
	//to determine if the end of the file 
	while(!feof(students_file)){
		fscanf(students_file,"%d",&new_student.id);
		
		//Check if ID number is exist or not.
		if(search_student_by_id(FIFO_Buffer,new_student.id) != NULL){
			printf("\n[ERROR]: ID Number %d is already taken\n",new_student.id);
			// ignroe the rest of the line
			fscanf(students_file, "%*[^\n]");
		}
		else{	
			// take data
			fscanf(students_file,"%s",new_student.f_name);
			fscanf(students_file,"%s",new_student.l_name);
			fscanf(students_file,"%f",&new_student.GPA);
			for(i = 0; i<COURSES_NUMBER ; i++){
				fscanf(students_file,"%d",&new_student.course[i]);
			}
			
			if(FIFO_enqueue(FIFO_Buffer,new_student)== FIFO_No_Error){
				printf("\n[INFO]: Student number %d Details is added successfully\n",new_student.id);
			}
			
			else{
				printf("\n[ERROR]: Adding student number %d failed\n",new_student.id);
				return FIFO_error;
			}
		}
	}
	printf("--------------------------------------------------\n");
	printf("[INFO] Students details are saved successfully\n");

	// Close the file
	fclose(students_file);
	
	print_students_number(FIFO_Buffer);
	return FIFO_No_Error;
}


FIFO_Status FIFO_isFull(FIFO_Buffer_t* FIFO_Buffer){
	//Check FIFO validity
	if(!(FIFO_Buffer->base) || !(FIFO_Buffer->head) || !(FIFO_Buffer->tail)){
		return FIFO_Null;
	}
	//Check if FIFO is full
	if(FIFO_Buffer->count == FIFO_Buffer->length){
		printf("==========FIFO is Full==========\n");
		return FIFO_Full;
	}
	return FIFO_No_Error;
}


FIFO_Status FIFO_enqueue(FIFO_Buffer_t* FIFO_Buffer , Sstudents_Data_t item){
	//Check FIFO validity
	if(!(FIFO_Buffer->base) || !(FIFO_Buffer->head) || !(FIFO_Buffer->tail))
		return FIFO_Null;

	//Check if FIFO is full
	if(FIFO_isFull(FIFO_Buffer) == FIFO_Full){
		printf("[ERROR]: Student Data Base is FULL\n");
		return FIFO_isFull(FIFO_Buffer);
	}
	else{
		// Enqueue an element
		*(FIFO_Buffer->head) = item;
		FIFO_Buffer->count++;


		if(FIFO_Buffer->head == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(Sstudents_Data_t))))
			FIFO_Buffer->head = FIFO_Buffer->base;
		else
			FIFO_Buffer->head++;

		return FIFO_No_Error;
	}
}


FIFO_Status view_student(FIFO_Buffer_t* FIFO_Buffer ){
	struct Sstudents* temp = FIFO_Buffer->tail;
	//check if FIFO is valid or not
	if(!FIFO_Buffer->base || !FIFO_Buffer->head || !FIFO_Buffer->tail){
		printf("-------------------------------\n");
		printf("[ERROR]: Students Data Base is NULL\n");
		printf("-------------------------------\n");
		return FIFO_Null ;
	}

	//check if FIFO is empty or not
	if(FIFO_Buffer->count == 0){
		printf("-------------------------------\n");
		printf("[ERROR]: Students Data Base is Empty\n");
		printf("-------------------------------\n");
		return FIFO_Empty;
	}
	
	//print FIFO elements
	for(int i=0 ; i< FIFO_Buffer->count ; i++){
		printf("-------------------------------\n");
		printf("\tFirst name: %s\n",(temp->f_name));
		printf("\tLast name: %s\n",(temp->l_name));
		printf("\tID Number: %d\n",(temp->id));
		printf("\tGPA: %.2f\n",(temp->GPA));
		for(int j=0;j<5;j++){
			printf("\tCourse ID : %d\n",(temp->course[j]));
		}
		temp++;
	}
	return FIFO_No_Error;
}



FIFO_Status delete_student(FIFO_Buffer_t* FIFO_Buffer){
	int i,check,student_number;
	Sstudents_Data_t* student = FIFO_Buffer->tail;
	printf("---------------------------\n");
	//check if FIFO is valid or not
	if(!FIFO_Buffer->base || !FIFO_Buffer->head || !FIFO_Buffer->tail){
		printf("[ERROR]: Student Data Base  not found");
		return FIFO_Null;
	}
	//check if FIFO is empty
	if(FIFO_Buffer->count == 0){
		printf("[ERROR]: Student Data Base is Empty");
		return FIFO_Empty;
	}
	
	printf("Enter the ID Number: ");
	scanf("%d",&student_number);
	
	for(i=0;i< FIFO_Buffer->count;i++){
		//Delete a student from QUEUE
		if(student->id == student_number){
			//Deteting the student
			*student = *(FIFO_Buffer->tail);
			FIFO_Buffer->count-- ;
			
			if(FIFO_Buffer->tail == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(Sstudents_Data_t)))){
				FIFO_Buffer->tail = FIFO_Buffer->base;
			}
			else{
				FIFO_Buffer->tail++;
			}
			check = 1;
			break;
		}
		else{
			check = 0;
		}
		student++;
	}
	
	if(check){
		printf("[INFO]: Deleting the student Number %d done successfully\n",student_number);
	}
	else{	
		printf("[ERROR]: Deleting the student is failed\n");
	}
	return FIFO_No_Error;
}


struct Sstudents* search_student_by_id(FIFO_Buffer_t* FIFO_Buffer,int ID){
	int i;
	struct Sstudents* student = FIFO_Buffer->tail;
	
	for(i = 0 ; i < FIFO_Buffer->count ; i++)
	{
		if(student->id == ID){
			break;
		}
		//if we reach to the last element in QUEUE
		if(student == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type)))){
			student = FIFO_Buffer->base;
		}
		else{
			student++;
		}
	}
	
	if(i == FIFO_Buffer->count){
		student = NULL;
	}
	return student;
}

FIFO_Status delete_all(FIFO_Buffer_t* FIFO_Buffer){
	if(!FIFO_Buffer->base || !FIFO_Buffer->head || !FIFO_Buffer->tail){
		printf("==========FIFO is Null==========\n");
		return FIFO_Null;
	}
	//check if FIFO is empty
	if(FIFO_Buffer->count == 0){
		printf("==========FIFO is empty==========\n");
		return FIFO_Empty;
	}
	while(FIFO_Buffer->count !=0){
		FIFO_Buffer->count-- ;
		
		if(FIFO_Buffer->tail == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type)))){
			FIFO_Buffer->tail = FIFO_Buffer->base;
		}
		else{
			FIFO_Buffer->tail++;
		}
	}
	printf("[INFO]: Deleting the student is done successfully\n");
	return FIFO_No_Error;
}


FIFO_Status find_student_by_id(FIFO_Buffer_t* FIFO_Buffer){
	int i,ID_Number;
	struct Sstudents* student = FIFO_Buffer->tail;
	
	printf("---------------------------\n");
	printf("Add the Student Details: \n");
	printf("---------------------------\n");
	printf("Enter the ID Number: ");
	scanf("%d",&ID_Number);
	
	for(i=0; i<FIFO_Buffer->count ;i++){
		if(student->id == ID_Number){
			break;
		}
		else{
			//case: last element in QUEUE
			if(student == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type)))){
				student = FIFO_Buffer->base;
			}
			else{
				student++;
			}
		}
	}
	
	if(i == FIFO_Buffer->count){
		printf("\n[ERROR]: ID Number %d not found\n",ID_Number);
		return FIFO_error;
	}
	else{
		printf("The Student Details are:\n");
		printf("\tFirst name: %s\n",(student->f_name));
		printf("\tLast name: %s\n",(student->l_name));
		printf("\tID Number: %d\n",(student->id));
		printf("\tGPA: %.2f\n",(student->GPA));
		for(int j=0;j<COURSES_NUMBER;j++){
			printf("\tCourse ID is: %d\n",(student->course[j]));
		}
	}
	return FIFO_No_Error;
}


FIFO_Status find_student_by_f_name(FIFO_Buffer_t* FIFO_Buffer){
	int i;
	char First_name[20];
	struct Sstudents* student = FIFO_Buffer->tail;
	
	printf("---------------------------\n");
	printf("Add the Student Details: \n");
	printf("---------------------------\n");
	printf("Enter The First Name: ");
	scanf("%s",First_name);
	
	for(i=0; i<FIFO_Buffer->count ;i++){
		if(!strcmp(student->f_name,First_name)){
			break;
		}
		else{
			//case ::last element in QUEUE
			if(student == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type)))){
				student = FIFO_Buffer->base;
			}
			else{
				student++;
			}
		}
	}
	
	if(i == FIFO_Buffer->count){
		printf("\n[ERROR]: First Name %s not found\n",First_name);
		return FIFO_error;
	}
	else{
		printf("The Student Details are:\n");
		printf("\tFirst name: %s\n",(student->f_name));
		printf("\tLast name: %s\n",(student->l_name));
		printf("\tID Number: %d\n",(student->id));
		printf("\tGPA: %.2f\n",(student->GPA));
		for(int j=0;j<5;j++){
			printf("\tCourse ID is : %d\n",(student->course[j]));
		}
	}
	return FIFO_No_Error;
}


FIFO_Status find_student_by_course(FIFO_Buffer_t* FIFO_Buffer){
	int i,j,course_id,counter=0;
	struct Sstudents* student = FIFO_Buffer->tail;
	printf("---------------------------\n");
	if(!FIFO_Buffer->count || !FIFO_Buffer->base || !FIFO_Buffer->head || !FIFO_Buffer->tail){
		printf("\n[ERROR]: Find The Student Failed\n",course_id);
		return FIFO_error;
	}
	
	printf("Enter Course ID: ");
	scanf("%d",&course_id);
	for(i=0; i<FIFO_Buffer->count ;i++){
		//Loop throw the courses Id until finding 
		for(j=0;j<COURSES_NUMBER;j++){
			if(student->course[j] == course_id){
				counter++;
				printf("--------------------------\n");
				printf("The Student Details are:\n");
				printf("\tFirst name: %s\n",(student->f_name));
				printf("\tLast name: %s\n",(student->l_name));
				printf("\tID Number: %d\n",(student->id));
				printf("\tGPA: %.2f\n",(student->GPA));
				break;
			}
		}
		//case: last element in QUEUE
		if(student == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type)))){
			student = FIFO_Buffer->base;
		}
		else{
			student++;
		}
	}
	if((counter == 0) && (i == FIFO_Buffer->count)){
		printf("\n[ERROR]: Course ID (%d) not found\n",course_id);
		return FIFO_error;
	}
	else{
		printf("\n[INFO] Total number of students enrolled: %d\n", counter);
	}
	return FIFO_No_Error;
}


void  print_students_number(FIFO_Buffer_t* FIFO_Buffer){
	printf("---------------------------\n");
	printf("[INFO]: The total number of Student is %d\n",FIFO_Buffer->count);
	printf("[INFO]: You can add up to %d\n",STUDENTS_NUMBER);
	printf("[INFO]: You can add %d more students\n",(STUDENTS_NUMBER - FIFO_Buffer->count));
}


FIFO_Status update_Student(FIFO_Buffer_t* FIFO_Buffer){
	int i,choice,Course_ID,id_Number;
	char temp[20];
	struct Sstudents* student = FIFO_Buffer->tail;
	printf("--------------------------------------\n");
	if(!FIFO_Buffer->count || !FIFO_Buffer->base || !FIFO_Buffer->head || !FIFO_Buffer->tail){
		printf("[ERROR]: Students Data Base Empty\n");
		return FIFO_error;
	}
	printf("Enter the ID Number: ");
	scanf("%d",&id_Number);
	
	for(i=0; i<FIFO_Buffer->count ;i++){
		if(student->id == id_Number){
			break;
		}
		else{
			//case : last element in QUEUE
			if(student == (FIFO_Buffer->base + (FIFO_Buffer->length * sizeof(element_type)))){
				student = FIFO_Buffer->base;
			}
			else{
				student++;
			}
		}
	}
	if(i == FIFO_Buffer->count){
		printf("\n[ERROR]: ID Number %d not found\n",id_Number);
		return FIFO_error;
	}
	else{
		printf("Enter the ID number to update the entry:\n");
		printf("1. First name.\n");
		printf("2. Last name.\n");
		printf("3. ID number.\n");
		printf("4. GPA.\n");
		printf("5. Courses.\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Enter first name : ");
				scanf("%s",student->f_name);
				printf("----------------------------\n");
				printf("[INFO]: UPDATED SUCCESSFULLY.\n");
				break;
			case 2: 
				printf("Enter last name : ");
				scanf("%s",student->l_name);
				printf("----------------------------\n");
				printf("[INFO]: UPDATED SUCCESSFULLY.\n");
				break;
			case 3:
				printf("Enter ID Number: ");
				scanf("%d",&student->id);
				printf("----------------------------\n");
				printf("[INFO]: UPDATED SUCCESSFULLY.\n");
				break;
			case 4:
				printf("Enter GPA : ");
				scanf("%f",&student->GPA);
				printf("----------------------------\n");
				printf("[INFO]: UPDATED SUCCESSFULLY.\n");
				break;
			case 5:
			do{
				printf("Enter Courses ID you want to update: ");
				scanf("%d",&Course_ID);
			
				for(i = 0; i<COURSES_NUMBER ; i++){
					if(student->course[i] == Course_ID){
						printf("Enter the new Course  ID: ");
						scanf("%d",&student->course[i]);
						choice = 0;
						break;
					}
				}
				if(!choice){
					printf("[INFO]: UPDATED SUCCESSFULLY.\n");
				}
				else{
					printf("----------------------------\n");
					printf("[ERROR]: Course ID not found\n");
					printf("----------------------------\n");
					printf("Try Again?\n");
					printf("1. Yes\n");
					printf("0. No\n");
					scanf("%d",&choice);	
				}
			}while(choice);
				break;
		}
	}
	return FIFO_No_Error;
}
