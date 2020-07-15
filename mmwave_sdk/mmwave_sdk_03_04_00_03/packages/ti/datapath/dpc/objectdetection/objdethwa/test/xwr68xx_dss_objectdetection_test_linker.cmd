/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS
{
    systemHeap : {} >>  L2SRAM_UMAP0 | L2SRAM_UMAP1
    .MCPILogBuffer  : { } > L1DSRAM
    .hwaBufs: load = HWA_RAM, type = NOINIT
    .l2Heap  : { } >> L2SRAM_UMAP0 | L2SRAM_UMAP1
    .hsram   : { } >> HSRAM

    .code:
    {
        libmmwavealg_xwr68xx.ae674(.text)
        mathlib.ae674(.text)
        main.oe674(.text)
    } >> L1PSRAM | L2SRAM_UMAP1 | L2SRAM_UMAP0

    GROUP : > L3SRAM PAGE 0
    {
        .l3ram align=128
        /* Due to limited space in L2SRAM, put some code in L3RAM */
	{
            main.oe674(.fardata:gFrameConfig)
            gen_frame_data.oe674(.text)
            libtestlogger_xwr68xx.ae674<*.oe674>(.text)
            libdpm_xwr68xx.ae674<*.oe674>(.text)
            rts6740_elf.lib<_printfi.c.obj>(.text)
            rts6740_elf.lib<pow.c.obj>(.text)
            rts6740_elf.lib<divd.c.obj>(.text)
            rts6740_elf.lib<imath64.c.obj>(.text)	
            rts6740_elf.lib<fopen.c.obj>(.text)
            rts6740_elf.lib<fclose.c.obj>(.text)
            rts6740_elf.lib<fread.c.obj>(.text)
            rts6740_elf.lib<atan.c.obj>(.text)
	}
    }
}
/*----------------------------------------------------------------------------*/

