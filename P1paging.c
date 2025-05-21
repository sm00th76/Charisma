#include <stdio.h>

#define PAGE_SIZE 10
#define PAGE_TABLE_ENTRIES 3

int page_table[PAGE_TABLE_ENTRIES] = {11, 23, 5}; // Page 0 → Frame 11, Page 1 → Frame 23, etc.

int translate_virtual_to_real(int VA) {
    int page_no = VA / PAGE_SIZE;
    int offset = VA % PAGE_SIZE;

    if (page_no >= PAGE_TABLE_ENTRIES) {
        printf(" Error: Page number %d is out of bounds!\n", page_no);
        return -1;
    }

    int frame_no = page_table[page_no];
    int real_address = frame_no * PAGE_SIZE + offset;

    printf("Virtual Address: %d\n", VA);
    printf("Page Number: %d, Offset: %d\n", page_no, offset);
    printf("Frame Number: %d\n", frame_no);
    printf("Real Address: %d\n", real_address);
    return real_address;
}

int main() {
    printf("===[ Phase 2: Virtual to Real Address Translation ]===\n");
    int VA = 12; // Example virtual address
    translate_virtual_to_real(VA);
    return 0;
}
