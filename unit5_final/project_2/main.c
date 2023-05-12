/*
Author : Hassaan Ahsraf Elssalakawy
main.c
*/

#include "Students.h"
#include"stdio.h"

int main()
{
	int choice;
	Sstudents_Data_t students_buffer[STUDENTS_NUMBER];
	FIFO_Buffer_t Students_data;
	
	//Initialize QUEUE
	FIFO_init(&Students_data , students_buffer , STUDENTS_NUMBER);
	
	do{
		printf("\t Choose on of the following options\n\n");
		printf("1: Add Student Manually\n");
		printf("2: Add Student From Text File\n");
		printf("3: Find Student by ID Number\n");
		printf("4: Find Student by First Name\n");
		printf("5: Find Student by Course ID\n");
		printf("6: Find The total Number of The Students \n");
		printf("7: Delete Student by ID Number\n");
		printf("8: Update Student by ID Number\n");
		printf("9: Show all informations of the Students\n");
		printf("10: Delete All Student\n");
		printf("\nYour option is : ");
		scanf("%d",&choice);

		switch(choice){
			case 1:
				add_student_manually(&Students_data);
				break;
			case 2: 
				add_student_from_text(&Students_data);
				break;
			case 3:
				find_student_by_id(&Students_data);
				break;
			case 4:
				find_student_by_f_name(&Students_data);
				break;
			case 5:
				find_student_by_course(&Students_data);
				break;
			case 6:
				print_students_number(&Students_data);
				break;
			case 7:
				delete_student(&Students_data);
				break;
			case 8:
				update_Student(&Students_data);
				break;
			case 9:
				view_student(&Students_data);
				break;
			case 10:
				delete_all(&Students_data);
				break;
			default :
				printf("\n========Your choice is invalid========\n");
				break;
		}
		printf("\n-------------------------------\n");
		printf("You want to continue ?\n");
		printf("1: Yes.\n");
		printf("2: No.\n");
		printf("-------------------------------\n");
		scanf("%d",&choice);
	}while(choice == 1);

	return 0;
}
