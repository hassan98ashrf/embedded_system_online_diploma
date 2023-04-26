/*
Autthor : Hassan Ashraf Elsalakawy
		Linked list
		main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//data
struct Sdata {
	unsigned int id;
	char name[40];
	float height
};

//linked list node
struct Sstudent{
	struct Sdata student;
	struct Sstudent * ptr_next_student;
};
struct Sstudent * ptr_first_student=NULL;
//---------APIs
//add new record

void add_student(){
	struct Sstudent * ptr_new_student;  //to assigne new record and change every loop
	struct Sstudent * ptr_last_student; //to assigne last record by compare with nect student (== null for finaal record)
	char temp_text[40]; //get data from user
	//check empty == yes 
	if (ptr_first_student == NULL){
		//creat new record
		ptr_new_student = (struct Sstudent*)malloc (sizeof(struct Sstudent));
		//assign ptr_first_student
		ptr_first_student = ptr_new_student; 
	}
	else{ //not empty
		ptr_last_student = ptr_first_student; 
		// navigate until reach the final ptr
		while (ptr_last_student -> ptr_next_student)
			ptr_last_student = ptr_last_student -> ptr_next_student; //till ptr last student = null
		//creat new record
		ptr_new_student = (struct Sstudent*)malloc (sizeof(struct Sstudent));
		ptr_last_student -> ptr_next_student = ptr_new_student;     // now ptr of last sudent refer to new record
	}
	//fill new record
	printf("\nEnter your ID : ");
	gets(temp_text);
	ptr_new_student -> student.id = atoi(temp_text);
	
	printf("\nEnter your name : ");
	gets(ptr_new_student -> student.name );
	
	printf("\nEnter your height : ");
	gets(temp_text);
	ptr_new_student -> student.height = atof(temp_text);
	
	//set next pointer
	ptr_new_student -> ptr_next_student= NULL; 
	
}

/////////////////////////////////////////////
//delet student record
int delet_student(){
	char temp_text[40];
	unsigned int select_id;
	//get id from user
	printf("\nEnter ID you want to delet : ");
	gets(temp_text);
	select_id = atoi(temp_text);
	
	// check if list is empty
	if(ptr_first_student){
		//we need to know selected and previous
		struct Sstudent * ptr_select_student = ptr_first_student ; //assume we select the first 
		struct Sstudent * ptr_previous_student = NULL ; 
			
		//loop all record
		while(ptr_select_student){
			//compare with selected 
			if(ptr_select_student ->student.id == select_id){
				//check if ist first or not
				if(ptr_previous_student){	//not frst
					ptr_previous_student -> ptr_next_student = ptr_select_student -> ptr_next_student; //next of previous(deleted) = next of selected (deleted)
				}
				else{ // first
					ptr_first_student = ptr_select_student -> ptr_next_student;
				}
				free(ptr_select_student);
				return 1;
			}
			ptr_previous_student = ptr_select_student;
			ptr_select_student = ptr_select_student -> ptr_next_student;
			
		}
		
	}
	printf("\nCannot find your ID .......");
	return 0;
	
}

///////////////////////////////////
//view all student

void view_all_students(){
	struct Sstudent * ptr_current_student = ptr_first_student;
	int count = 0;
	if(ptr_first_student==NULL){
		printf("\nList is empty");
	}
	else{
		printf("\n====List of students==== :");
		while(ptr_current_student){
			printf("\n-Student number : %d ",count+1);
			printf("\nID : %d ",ptr_current_student->student.id);
			printf("\nName : %s ",ptr_current_student->student.name);
			printf("\nHeight : %f ",ptr_current_student->student.height);
			ptr_current_student = ptr_current_student->ptr_next_student;
			count++;
			printf("\n");
		}
		
	}
	
}

///////////////////////////////////
//delet all student

void delet_all_students(){
	struct Sstudent * ptr_current_student = ptr_first_student;
	
	if(ptr_first_student==NULL){
		printf("\nList is empty");
	}
	else{
		
		while(ptr_current_student){
			struct Sstudent * ptr_temp_sttudent = ptr_current_student;
			ptr_current_student = ptr_current_student->ptr_next_student;
			free(ptr_temp_sttudent);
		}
		ptr_first_student =NULL;
	}
	
}





void number_of_node(){

	int selected_node = select_node();

	//Check list is not empty
	if(ptr_first_student){

		struct Sstudent* ptr_current_student = ptr_first_student;
		int count = 0;

		while(ptr_current_student){

			if(selected_node == count){
				printf("\n Node at index %d", selected_node);
				printf("\n \t ID: %d", ptr_current_student->student.id);
				printf("\n \t Name: %s", ptr_current_student->student.name);
				printf("\n \t Height: %f", ptr_current_student->student.height);
				printf("\n----------------------");
				return;
			}

			ptr_current_student = ptr_current_student->ptr_next_student;
			count++;
		}
	}
	else{
		printf("\nList is empty");
		return;
	}
	printf("\nSelected Index is out of list boundaries");
}

void number_of_node_form_end(){

	int selected_node = select_node();

	//Check list is not empty
	if(ptr_first_student){

		struct Sstudent* ptr_main_student = ptr_first_student;
		struct Sstudent* ptr_ref_student = ptr_first_student;

		//Move ptr_ref_student with distance = selected node
		for(int i = 0; i <= selected_node; i++){
			ptr_ref_student = ptr_ref_student->ptr_next_student;
			if(ptr_ref_student == NULL){
				printf("\nSelected Index is out of list boundaries");
				return;
			}
		}

		//Move both pointers together till ptr of ref student == NULL
		while(ptr_ref_student){
			ptr_ref_student = ptr_ref_student->ptr_next_student;
			ptr_main_student = ptr_main_student->ptr_next_student;
		}

		printf("\n Node at index %d from end", selected_node);
		printf("\n \t ID: %d", ptr_main_student->student.id);
		printf("\n \t Name: %s", ptr_main_student->student.name);
		printf("\n \t Height: %f", ptr_main_student->student.height);
		printf("\n----------------------");
		return;
	}
	else{
		printf("\nList is empty");
		return;
	}
}

void lenght_list(){

	int count = 0;

	//Check list is not empty
	if(ptr_first_student){

		struct Sstudent* ptr_current_student = ptr_first_student;

		while(ptr_current_student){
			ptr_current_student = ptr_current_student->ptr_next_student;
			count++;
		}
	}

	printf("\nLength of List = %d", count);
}

void middle_list(){

	//Check list is not empty
	if(ptr_first_student){

		struct Sstudent* ptr_slow = ptr_first_student;
		struct Sstudent* ptr_fast = ptr_first_student;
		int index = 0;

		while(ptr_fast && ptr_fast->ptr_next_student){
			ptr_slow = ptr_slow->ptr_next_student;
			ptr_fast = ptr_fast->ptr_next_student;
			ptr_fast = ptr_fast->ptr_next_student;
			index++;
		}

		printf("\n Middle of List at index %d", index);
		printf("\n \t ID: %d", ptr_slow->student.id);
		printf("\n \t Name: %s", ptr_slow->student.name);
		printf("\n \t Height: %f", ptr_slow->student.height);
		printf("\n----------------------");
		return;
	}
	else{
		printf("\nList is empty");
		return;
	}
}

void reverse_list(){

	//Check list is not empty
	if(ptr_first_student){

		struct Sstudent* ptr_previous_student = ptr_first_student;
		struct Sstudent* ptr_current_student = ptr_first_student;
		struct Sstudent* ptr_next = NULL;
		
		ptr_current_student = ptr_current_student->ptr_next_student;
		ptr_previous_student->ptr_next_student = NULL;

		while(ptr_current_student){
			ptr_next = ptr_current_student->ptr_next_student;
			ptr_current_student->ptr_next_student = ptr_previous_student;
			ptr_previous_student = ptr_current_student;
			ptr_current_student = ptr_next;
		}

		ptr_first_student = ptr_previous_student;
		printf("\nList is Reversed Successfully");
		return;
	}
	else{
		printf("\nList is empty");
		return;
	}
}




int selectID(){

	char id[20];
	printf("\nEnter ID to be deleted: ");
	gets(id);
	return atoi(id);
}

int select_node(){

	char node[20];
	printf("\nEnter index of Node: ");
	gets(node);
	return atoi(node);
}


//////////////////////////////////////
void main(){
	char temp_text[40];
	while(1){
		printf("\n==================");
		printf("\n\tChooes of the following option :");
		printf("\n\t 1- add student");
		printf("\n\t 2- delet student");
		printf("\n\t 3- view all students");
		printf("\n\t 4- delet all students");
		printf("\n\t 5: nth Node");
		printf("\n\t 6: nth Node from End");
		printf("\n\t 7: Length of List");
		printf("\n\t 8: Middle of List");
		printf("\n\t 9: Reverse List");
		printf("\n\t your choice is : ");
	    gets(temp_text);
		printf("==================\n");
		switch(atoi(temp_text)){
			case 1:
			add_student();
			break;
			case 2:
			delet_student();
			break;
			case 3:
			view_all_students();
			break;
			case 4:
			delet_all_students();
			break;
			case 5:
			number_of_node();
			break;
			case 6:
			number_of_node_form_end();
			break;
			case 7:
			lenght_list();
			break;
			case 8:
			middle_list();
			break;
			case 9:
			reverse_list();
			break;
			default:
				printf("\n\t you enter wrong number\n ");
		}
		
	}
}








