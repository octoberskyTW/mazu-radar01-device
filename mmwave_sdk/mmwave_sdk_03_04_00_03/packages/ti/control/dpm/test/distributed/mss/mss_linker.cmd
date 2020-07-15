/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS
{
    /* System Heap: One heap for all dynamic memory allocations */
    systemHeap      : {} > DATA_RAM
    llProfileData   : {} > L3_RAM
    .MCPILogBuffer  : {} > DATA_RAM
}
/*----------------------------------------------------------------------------*/

