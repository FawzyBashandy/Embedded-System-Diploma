#include <stdio.h>
#include "FIFO.h"
#define BUFFER_LENGTH 5

int main() {
    Elements_type buffer[BUFFER_LENGTH] ,temp;
    FIFO_Buff_t FIFO;
    Buffer_Status status;

    // Initialize the FIFO buffer
    status = FIFO_Init(&FIFO, buffer, BUFFER_LENGTH);
    if (status != FIFO_No_Error) {
        printf("Error initializing FIFO. Status: %d\n", status);
        return 1;
    }

    // Enqueue items into the FIFO buffer
    for (int i = 1; i <= 5; i++) {
        status = FIFO_Enqueue(&FIFO, i);
        if (status != FIFO_No_Error) {
            printf("Error Enqueueing item into FIFO. Status: %d\n", status);
            return 1;
        }
    }
	printf("=============Items in Buffer After Enqueue ============\n");
    // Read and print all items in the FIFO buffer
    status = FIFO_Read_All(&FIFO);
    if (status != FIFO_No_Error) {
        printf("Error reading FIFO buffer. Status: %d\n", status);
        return 1;
    }
	for(int i=0 ; i<2 ; i++)
	{
		status = FIFO_Dequeue(&FIFO ,&temp);
		if (status != FIFO_No_Error) {
			printf("Error reading FIFO buffer. Status: %d\n", status);
			return 1;
		}
	}
	printf("=============Items in Buffer After DeQueue ============\n");
	status = FIFO_Read_All(&FIFO);
    if (status != FIFO_No_Error) {
        printf("Error reading FIFO buffer. Status: %d\n", status);
        return 1;
    }
	status = FIFO_Enqueue(&FIFO, 9);
	status = FIFO_Enqueue(&FIFO, 8);
    if (status != FIFO_No_Error) 
	{
        printf("Error Enqueueing item into FIFO. Status: %d\n", status);
        return 1;
    }
	// Read and print all items in the FIFO buffer
	printf("=============Items in Buffer After Enqueue ============\n");
    status = FIFO_Read_All(&FIFO);
    if (status != FIFO_No_Error) {
        printf("Error reading FIFO buffer. Status: %d\n", status);
        return 1;
    }
	
	printf("=============LAST Enqueue ============\n");
	status = FIFO_Enqueue(&FIFO, 30);
    if (status != FIFO_No_Error) 
	{
        printf("Error Enqueueing item into FIFO. Status: %d\n", status);
        return 1;
    }
    return 0;
}