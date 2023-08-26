#include <stdio.h>
#include "Linked_List.h"

SStudent * gpFirstStudent = NULL;

void main()
{
    uint8_t option;
    uint32_t temp;
    while(1)
    {    
        printf("================================================\n");
        printf("\tChoose one of the following options :\n");
        printf("1: AddStudent\n2: Delete_Student\n3: List_Length\n4: Get Student Using Index\n5: Get Student Using Index From The End\n6: Get The Student at The Middle of List\n7: Reverse Student List \n8: View All Students \n9: Delete All Students\nEnter Option Number : ");
        scanf(" %d",&option);
        getchar();
        printf("================================================\n");
        switch(option)
        {
            case 1:
            Add_Student();
            break;
            case 2:
            Remove_Student();
            break;
            case 3:
            printf("The Length of the list is : %d\n",List_Length_Recursive(gpFirstStudent));
            break;
            case 4:
            printf("Enter The Index : ");
            Dscanf("%d",&temp);
            GetNth(temp);
            break;
            case 5:
            printf("Enter The Index From The End : ");
            Dscanf("%d",&temp);
            GetNth_From_End(temp);
            break;
            case 6:
            Get_Middle();
            break;
            case 7:
            List_Reverse();
            break;
            case 8:
            View_Students();
            break;
            case 9:
            Delete_All();
            break;
            default :
            printf("Error : Invalid option");
        }
    }
}
