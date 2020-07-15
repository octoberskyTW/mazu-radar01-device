/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS
{
     systemHeap : {} > DATA_RAM
    .MCPILogBuffer  : { } > DATA_RAM
    .dataBuf > DATA_RAM
    .hwaBufs: load = HWA_RAM, type = NOINIT

    .l3data > L3_RAM
}
/*----------------------------------------------------------------------------*/

