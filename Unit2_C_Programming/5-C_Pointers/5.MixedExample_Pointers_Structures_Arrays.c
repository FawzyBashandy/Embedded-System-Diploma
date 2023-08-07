#include <stdio.h>

struct Semployee
{
    char name[50];
    int id;
};


int main()
{
    struct Semployee employee1={"FooZ",1},employee2={"Alex",2};
    struct Semployee * arr[2]={&employee1,&employee2};
    struct Semployee *(*ptr)[2]=&arr;
    printf("Employee Name : %s\nEmployee ID:%d",(**(*ptr+1)).name,(**(*ptr+1)).id);

}