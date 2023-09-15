#include "../inc/Student_Management_System.h"
void Add_Student_File()
{
    printf("----------------------------\n");
    eFIFO_Status_t status;
    FILE * fptr;
    if(fptr = fopen("Students_Data.txt","r"))
    {
        while(1)
        {
            sStudent_t * New_Student = (sStudent_t *)malloc(sizeof(sStudent_t));
            if(fscanf(fptr,"%d",&(New_Student->Roll_Number))==EOF) //That means if the new line is empty
            {
                free(New_Student);
                break;
            }
            //Check if The roll number is already taken.
            if(Roll_Found == FIFO_Search_Roll(New_Student->Roll_Number))
            {
                fscanf(fptr,"%*s %*s %*f %*d %*d %*d %*d %*d");//Discard(Ignore) the rest of this roll information
                printf("[ERROR] : Roll Number %d is Already Taken and The Student isn't added try again !\n",New_Student->Roll_Number);
                free(New_Student);
            }
            else // if not taken
            {
                fscanf(fptr,"%s %s %f",New_Student->First_Name,New_Student->Last_Name,&(New_Student->Student_GPA));
                // fscanf(fptr,"%s",New_Student->First_Name);
                // fscanf(fptr,"%s",New_Student->Last_Name);
                // fscanf(fptr,"%f",&(New_Student->Student_GPA));
                for(int i = 0 ; i < Courses_Number ; i++)
                {
                    fscanf(fptr,"%d",&(New_Student->Registered_Courses[i]));
                }
                status = FIFO_Enqueue(New_Student);
                //Check For FIFO STATUS
                if(FIFO_Full == status)//Add Student and check for fifo if full
                {
                    printf("----------------------------\n");
                    printf("[ERROR] Starting From ID [%d] Students aren't added ,as the data base is full !\n",New_Student->Roll_Number);
                    free(New_Student);
                    return;
                }
                else if(FIFO_Error == status)
                {
                    printf("----------------------------\n");
                    printf("[ERROR] Starting From ID [%d] Students aren't added ,due to an error !\n",New_Student->Roll_Number);
                    free(New_Student);
                    return;
                }
            } 
        }
    }
    else
    {
        printf("[ERROR] File Not Found !!");
        return;
    }
    printf("[INFO] Students Details are added Successfully !\n");
    fclose(fptr);
}
void Add_Student()
{
    printf("----------------------------\n");
    eFIFO_Status_t status;
    sStudent_t * New_Student = (sStudent_t *)malloc(sizeof(sStudent_t));
    //if the user entered an already taken roll number
    if(Roll_Found == Get_Student_Data(New_Student))
    {
        free(New_Student);
        return;
    }

    status = FIFO_Enqueue(New_Student);
    //Check For FIFO STATUS
    if(FIFO_Full == status)//Add Student and check for fifo if full
    {
        printf("----------------------------\n");
        printf("[ERROR] ID [%d] isn't added ,as the data base is full !\n",New_Student->Roll_Number);
        free(New_Student);
        return;
    }
    else if(FIFO_Error == status) //General ERROR
    {
        printf("----------------------------\n");
        printf("[ERROR] ID [%d] isn't added ,due to an error !\n",New_Student->Roll_Number);
        free(New_Student);
        return;
    }

    printf("[INFO] Student Details is added Successfully !\n");
}
void Get_Student(Search_status Method)
{
    uint32_t Roll_Number;
    uint8_t Name[40];
    uint32_t Course_ID;
    uint8_t flag=1;

    SNode_t * Current_Student = Students_FIFO->Tail;
    printf("----------------------------\n");
    if(Roll_Search == Method)
    {
    printf("Enter Roll Number of the Student : ");
    scanf("%d",&Roll_Number);
    while(Current_Student)
    {
        if(Roll_Number == Current_Student->StudentData->Roll_Number)
        {
            Print_Student(Current_Student);
            return;
        }
        Current_Student = Current_Student->P_Next_Student;
    }
    printf("[ERROR] : There's No Student with this roll number !\n");
    }
    else if (Name_Search == Method)
    {
    printf("Enter First Name of the Student : ");
    scanf("%s",Name);
    while(Current_Student)
    {
        if(!stricmp(Name,Current_Student->StudentData->First_Name))
        {
            Print_Student(Current_Student);
			//we will not return as if there's multiple students with the same first name
			flag = 0;
        }
        Current_Student = Current_Student->P_Next_Student;
    }
	if(flag)
	{
		printf("[ERROR] : There's No Student with this First Name !\n");
    }
	}
    else if(Course_Search == Method)
    {
    printf("Enter Course ID : ");
    scanf("%d",&Course_ID);
    while(Current_Student)
    {
        for(int i = 0 ; i < Courses_Number ; i++)
        {

            if(Course_ID == Current_Student->StudentData->Registered_Courses[i])
            {
                Print_Student(Current_Student);
                flag = 0 ;
            }
        }
        Current_Student = Current_Student->P_Next_Student; 
    }
    //If there's no students in the course
    if(flag)
    printf("[ERROR] : There's No Students Registered in this course !\n");
    }
}
void Number_of_Students()
{
    printf("----------------------------\n");
    printf("[INFO] The total number of Students is : %d\n",Students_FIFO->Count);
    printf("[INFO] You can add up to %d Students\n[INFO] You can add %d more Students\n",Students_FIFO->Length,(Students_FIFO->Length)-(Students_FIFO->Count));
}
void Delete_Student()
{
    uint32_t Roll_Number;
    SNode_t * DelStudent = Students_FIFO->Tail;
    SNode_t * Prev_Student = NULL;
    printf("----------------------------\n");
    printf("Enter Roll Number of the Student : ");
    scanf("%d",&Roll_Number);
    while(DelStudent)
    {
        if(Roll_Number == DelStudent->StudentData->Roll_Number)
        {
            if(!Prev_Student) // IF the node is at the tail
            {
                Prev_Student = DelStudent;
                Students_FIFO->Tail = DelStudent -> P_Next_Student;
                Students_FIFO->Count--;
                free(Prev_Student);
                printf("[INFO] Student with Roll Number (%d) is removed Successfully !\n",Roll_Number);
                return;
            }
            else
            {
                Prev_Student->P_Next_Student = DelStudent->P_Next_Student;
                Students_FIFO->Count--;
                free(DelStudent);
                printf("[INFO] Student with Roll Number (%d) is removed Successfully !\n",Roll_Number);
                return;
            }
        }
        Prev_Student = DelStudent;
        DelStudent = DelStudent->P_Next_Student;
    }
    printf("[ERROR] : There's No Student with this roll number !\n");
}
void Update_Student()
{
    uint8_t flag_and_Choice=0;
    uint32_t Roll_Number,New_Course;
    SNode_t * Current_Student = Students_FIFO->Tail;
    printf("----------------------------\n");
    printf("Enter the Roll Number of the Student you want to Update : ");
    scanf("%d",&Roll_Number);
    while(Current_Student)
    {
        if(Roll_Number == Current_Student->StudentData->Roll_Number)
        {   
            flag_and_Choice = 1; //Acts as a flag
            break;
        }
        Current_Student = Current_Student->P_Next_Student;
    }
    if(flag_and_Choice)
    {
        printf("What do you want to update ? : \n");
        printf("1-First Name\n");
        printf("2-Last Name\n");
        printf("3-Roll Number\n");
        printf("4-GPA\n");
        printf("5-Courses\n");
        scanf("%d",&flag_and_Choice); //Acts as a choice
        switch(flag_and_Choice)
        {
            case 1:
            {
                printf("Enter the new First Name : ");
                scanf("%s",Current_Student->StudentData->First_Name);
                break;
            }
            case 2:
            {
                printf("Enter the new Last Name : ");
                scanf("%s",Current_Student->StudentData->Last_Name);
                break;
            }
            case 3:
            {
                printf("Enter the new Roll Number : ");
                while(1)
                {
                    scanf("%d",&Roll_Number); //We will use the function parameter as i don't need it's value anymore
                    if(Roll_Found == FIFO_Search_Roll(Roll_Number))
                    {
                        printf("[ERROR] The Roll Number is Already Taken !\nEnter Another Roll Number : ");
                        continue;
                    }
                    Current_Student->StudentData->Roll_Number = Roll_Number;
                    break;
                }
                break;
            }
            case 4:
            {
                printf("Enter the new GPA : ");
                scanf("%f",&(Current_Student->StudentData->Student_GPA));
                break;
            }
            case 5:
            {
                printf("Enter the new Courses List : \n");
                for( int i = 0 ; i < Courses_Number ; i++)
                {
                    printf("Course %d ID is : ",i+1);
                    scanf("%d",&(Current_Student->StudentData->Registered_Courses[i]));
                }
                break;
            }
            default:
            {
                printf("[ERROR] Invalid Choice ! try again ...\n");
                return;
            }
        }
        printf("[INFO] Updated Successsfully !\n");
    }
    else
    {
        printf("[ERROR] : There's No Student with this roll number !\n");
    }
}
void Print_Student(SNode_t * Student)
{
    printf("----------------------------\n");
    printf("Student First Name : %s\n",Student->StudentData->First_Name);
    printf("Student Last Name : %s\n",Student->StudentData->Last_Name);
    printf("Student Roll Number : %d\n",Student->StudentData->Roll_Number);
    printf("Student GPA : %g\n",Student->StudentData->Student_GPA);
    printf("Student Registered Courses : \n");
    for( int i = 0 ; i < Courses_Number ; i++)
    {
        printf("Course %d ID is : %d\n",i+1,Student->StudentData->Registered_Courses[i]);
    }
}
void Print_All_Students()
{
	if(0 == Students_FIFO->Count)
	{
        printf("----------------------------\n");
		printf("[ERROR] There's no students to show !! \n");
        printf("----------------------------\n");
		return;
	}
    SNode_t * Current_Student = Students_FIFO->Tail;
    while(Current_Student)
    {
        Print_Student(Current_Student);
        Current_Student = Current_Student->P_Next_Student;
    }
}
eFIFO_Status_t Get_Student_Data(sStudent_t * New_Student)
{
    uint8_t i;
    printf("Add the Student Details\n");
    printf("----------------------------\n");
    printf("Student First Name : ");
    scanf("%s",New_Student->First_Name);
    printf("Student Last Name : ");
    scanf("%s",New_Student->Last_Name);
    printf("Student Roll Number : ");
    scanf("%d",&(New_Student->Roll_Number));
    if(Roll_Found == FIFO_Search_Roll(New_Student->Roll_Number))
    {
        printf("[ERROR] : Roll Number %d is Already Taken and The Student isn't added try again !\n",New_Student->Roll_Number);
        return Roll_Found;
    }
    printf("Student GPA : ");
    scanf("%f",&(New_Student->Student_GPA));
    printf("Enter The ID of Courses Registered : \n");
    for( i = 0 ; i < Courses_Number ; i++)
    {
        printf("Course %d ID is : ",i+1);
        scanf("%d",&(New_Student->Registered_Courses[i]));
    }
    return FIFO_No_Error;
}
void Introduce_Program()
{
    printf("----------------------------\n");
    printf("Choose The Task that you want to preform : \n");
    printf("1. Add the Student Details Manually\n");
    printf("2. Add the Student Details From Text File\n");
    printf("3. Find a Student Details by Roll Number\n");
    printf("4. Find a Student Details by First Name\n");
    printf("5. Find a Student Details by Course ID\n");
    printf("6. Find the Total number of Students\n");
    printf("7. Delete a Student Details by Roll Number\n");
    printf("8. Update a Student Details by Roll Number\n");
    printf("9. Show All Students Information\n");
    printf("10. Exit\n");
}