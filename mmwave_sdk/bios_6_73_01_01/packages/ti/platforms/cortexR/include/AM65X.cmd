/*----------------------------------------------------------------------------*/
/* AM65X.cmd                                                                  */
/*                                                                            */
/* (c) Texas Instruments 2018, All rights reserved.                           */
/*                                                                            */

/* USER CODE BEGIN (0) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */
MEMORY{
    ATCM       (RWX) : origin=0x00000000 length=0x00008000 fill=0xFFFFFFFF
    BTCM       (RWX) : origin=0x41010000 length=0x00008000
    RAM0       (RW)  : origin=0x41C00000 length=0x00080000
}

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS{
    .text    align(8) : {} > ATCM | BTCM | RAM0
    .const   align(8) : {} > ATCM | BTCM | RAM0
    .cinit   align(8) : {} > ATCM | BTCM | RAM0
    .pinit   align(8) : {} > ATCM | BTCM | RAM0
    .bss              : {} > RAM0
    .data             : {} > BTCM | RAM0
    .sysmem           : {} > RAM0
    .args             : {} > RAM0
    .stack            : {} > ATCM | BTCM | RAM0 fill=0xFFFFFFFF
}
/*----------------------------------------------------------------------------*/
