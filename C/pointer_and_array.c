#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    uint32_t myNumbers[4] = {25, 50, 75, 100}; // 4 byte (32-bit) * 4 elements = 16 byte (128-bit)
    uint32_t i;
    printf("%zu\n", sizeof(i)); // 4 byte (32-bit)

    // Get the real length of array myNumbers
    // 16 byte (128-bit) / 4 byte (32-bit) = 4 element
    size_t len = sizeof(myNumbers) / sizeof(myNumbers[0]);

    printf("\n===== The Memory Address of Each Index ====\n");
    for (i = 0; i < len; i++) {
        printf("\nIndex: %d and its Address: %p\n", i,  &myNumbers[i]);
    }
    printf("\n===========================================\n");

    // The memory address of the first element is the same as the name of the array
    // This means we can work with arrays through pointers;
    printf("\n%p\n", myNumbers);
    printf("%p\n", &myNumbers[0]);

    // Access the first element of the array using the `*` operator to access it
    printf("\n%u\n", *myNumbers);

    // Access and print elements in myNumbers array using a pointer
    printf("\n===== The Value of Each Index Using Pointer ====");
    uint32_t *ptr = myNumbers;
    for (i = 0; i < len; i++) {
        printf("\nIndex%d: %d", i, *(ptr + i));
    }
    printf("\n================================================\n");

    // Update the value of array elements with pointers
    printf("\n===== Update the value of array elements with pointers ====");
    printf("\nThe index0 value before updated: %d", *ptr);
    printf("\nThe index2 value before updated: %d", *(ptr + 2));

    *ptr = 24;
    *(ptr + 2) = 25;

    printf("\nThe index0 value after updated: %d", *ptr);
    printf("\nThe index2 value after updated: %d", *(ptr + 2));
    printf("\n============================================================\n");

    return 0;
}