#include <stdio.h>
#include "LIFO.h"

#define BUFFER_LENGTH 10

int main() {
    Element_Size buffer[BUFFER_LENGTH] ,temp;
    LIFO_buffer_t LIFO;
    Buffer_Status status;

    // Initialize the LIFO buffer
    status = LIFO_Init(&LIFO, buffer, BUFFER_LENGTH);
    if (status != LIFO_No_Error) {
        printf("Error initializing LIFO. Status: %d\n", status);
        return 1;
    }

    // Push items into the LIFO buffer
    for (int i = 1; i <= 5; i++) {
        status = LIFO_Push(&LIFO, i);
        if (status != LIFO_No_Error) {
            printf("Error pushing item into LIFO. Status: %d\n", status);
            return 1;
        }
    }

    // Read and print all items in the LIFO buffer
    status = LIFO_Read_All(&LIFO);
    if (status != LIFO_No_Error) {
        printf("Error reading LIFO buffer. Status: %d\n", status);
        return 1;
    }

	status = LIFO_Pop(&LIFO ,&temp);
	if (status != LIFO_No_Error) {
        printf("Error reading LIFO buffer. Status: %d\n", status);
        return 1;
    }
	
	// Read and print all items in the LIFO buffer
    status = LIFO_Read_All(&LIFO);
    if (status != LIFO_No_Error) {
        printf("Error reading LIFO buffer. Status: %d\n", status);
        return 1;
    }
    return 0;
}