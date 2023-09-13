#ifndef SMS_H_
#define SMS_H_
#include <stdint.h>
#include "FIFO.h"
//####################
//######   Apis  #####
//####################

void Add_Student_File();
void Add_Student();
void Get_Student(Search_status Method);
void Number_of_Students();
void Delete_Student();
void Update_Student();
void Print_Student();
void Print_All_Students();
eFIFO_Status_t Get_Student_Data(sStudent_t * New_Student);
void Introduce_Program();
#endif