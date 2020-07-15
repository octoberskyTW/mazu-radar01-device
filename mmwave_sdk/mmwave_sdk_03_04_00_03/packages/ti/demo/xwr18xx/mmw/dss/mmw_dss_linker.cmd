/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS
{
    systemHeap : {} >> L2SRAM_UMAP0 | L2SRAM_UMAP1
    .hwaBufs: load = HWA_RAM, type = NOINIT
    .l3ram: {} >> L3SRAM
    .dpc_l2Heap: { } >> L2SRAM_UMAP0 | L2SRAM_UMAP1
    .demoSharedMem: { } >> HSRAM
}
/*----------------------------------------------------------------------------*/

