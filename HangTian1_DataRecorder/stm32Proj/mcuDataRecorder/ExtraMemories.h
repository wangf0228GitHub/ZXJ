#pragma once

//E.g. int IDT71V321_DATA g_Initialized = 1;
#define IDT71V321_DATA __attribute__((section(".idt71v321_data")))

//E.g. int IDT71V321_BSS g_Uninitialized;
#define IDT71V321_BSS __attribute__((section(".idt71v321_bss")))


