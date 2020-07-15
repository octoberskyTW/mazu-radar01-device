/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS
{
    .l2Heap  : { } >> L2SRAM_UMAP0 | L2SRAM_UMAP1
    systemHeap : {} >>  L2SRAM_UMAP0 | L2SRAM_UMAP1
    .MCPILogBuffer  : { } > HSRAM
    .l1Heap  : { } > L1DSRAM
    .hsram   : { } > HSRAM

    GROUP : > L3SRAM PAGE 0
    {
        .l3ram align=128
        /* Due to limited space in L2SRAM, put some code in L3RAM */
	{
            main.oe674(.fardata:gFrameConfig)
            main.oe674(.text)
            libtestlogger_xwr16xx.ae674<*.oe674>(.text)
            gen_frame_data.oe674(.text)
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

