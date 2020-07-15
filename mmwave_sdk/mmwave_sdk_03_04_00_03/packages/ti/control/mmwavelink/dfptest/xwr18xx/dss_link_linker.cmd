/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */
--retain="*(.intvecs)"

-stack 0x1000

/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */
SECTIONS
{
    systemHeap      : { } > L2SRAM_UMAP0
    .MCPILogBuffer  : { } > L2SRAM_UMAP0
    .l3ram: {} > L3SRAM
    .configFiles > L3SRAM
    {
        /*The config files are copied to internal structures during the*/
        /*test initialization, therefore there is no access to L3 in realtime*/
        dfptest_config_001.oe674
        dfptest_config_002.oe674
        dfptest_config_003.oe674
        dfptest_config_004.oe674
        dfptest_config_005.oe674
        dfptest_config_006.oe674
        dfptest_config_007.oe674
        dfptest_config_008.oe674
        dfptest_config_009.oe674
        dfptest_config_010.oe674
    }

}
/*----------------------------------------------------------------------------*/

