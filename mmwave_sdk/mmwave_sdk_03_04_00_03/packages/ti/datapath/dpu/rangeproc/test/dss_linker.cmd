/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS
{
    systemHeap : {} >> L2SRAM_UMAP0 | L2SRAM_UMAP1
    .dataBufL2 : {} >> L2SRAM_UMAP0 | L2SRAM_UMAP1
    .MCPILogBuffer  : { } > L2SRAM_UMAP0 | L2SRAM_UMAP1
    .l3data : {} > L3SRAM
	.dataBuf : {} > L3SRAM
    .l1data : {} > L1DSRAM
    
}
/*----------------------------------------------------------------------------*/

