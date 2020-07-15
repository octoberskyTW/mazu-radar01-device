/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS
{
    systemHeap : {} >> L2SRAM_UMAP0 | L2SRAM_UMAP1
    .l2data : {} >> L2SRAM_UMAP0 | L2SRAM_UMAP1
    .MCPILogBuffer  : { } > L2SRAM_UMAP0 | L2SRAM_UMAP1
    .l3ram : {} > L3SRAM
	.l1data : {} > L1DSRAM
    
}
/*----------------------------------------------------------------------------*/

