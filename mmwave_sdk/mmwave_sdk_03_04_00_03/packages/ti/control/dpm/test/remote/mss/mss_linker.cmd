/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS
{
    /* System Heap: One heap for all dynamic memory allocations */
    systemHeap              : {} > DATA_RAM

    /* The LL Profile uses this memory section. */
    llProfileData           : {} > L3_RAM

    /* The MCPI Logs are stored here */
    .MCPILogBuffer          : {} > DATA_RAM

    /* Data Injection Control: Shared between the MSS & DSS */
    .dataInjectionControl   : {} > HS_RAM
}
/*----------------------------------------------------------------------------*/

