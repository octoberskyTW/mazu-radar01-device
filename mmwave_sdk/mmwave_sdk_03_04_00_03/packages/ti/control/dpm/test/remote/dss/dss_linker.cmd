/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

--stack_size=0x700
/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS
{
    /* System Heap: */
    systemHeap              : {} >> L2SRAM_UMAP0 | L2SRAM_UMAP1

    /* The LL Profile uses this memory section. */
    llProfileData           : {} > L3SRAM

    /* The MCPI Logs are placed here */
    .MCPILogBuffer          : {} > L2SRAM_UMAP0

    /* Data Injection Control: Shared between the MSS & DSS */
    .dataInjectionControl   : {} > HSRAM
}
/*----------------------------------------------------------------------------*/

