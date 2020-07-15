// ============================================================================
// Linker Command File for Linking c674 DSP Programs
//
// These linker options are for command line linking only. For IDE linking,
// you should set your linker options in Project Properties.
//         -c                    Link Using C Conventions
//        -stack     0x1000        Software Stack Size
//        -heap    0x1000        Heap Area Size
// ===========================================================================
-stack 0x1000
-heap 0x1000

// ============================================================================
//                         Specify the System Memory Map
// ============================================================================
MEMORY
{
    L1P:    o = 0x11E00000        l = 0x00008000
    L1D:    o = 0x11F00000        l = 0x00008000
    L2:     o = 0x11800000        l = 0x00040000
    DDR2:   o = 0xC0000000        l = 0x08000000
}

// ============================================================================
//                 Specify the Sections Allocation into Memory
// ============================================================================
SECTIONS
{
    .cinit        >        DDR2               // Initialization Tables
    .pinit        >        DDR2               // Constructor Tables
    .init_array   >        DDR2               // 
    .binit        >        DDR2               // Boot Tables
    .const        >        L2               // Constant Data
    .switch       >        L2               // Jump Tables
    .text         >        L2               // Executable Code
    .text:_c_int00: align=1024 > L2         // Entrypoint
    .l2data		> L2
    .l3data		> DDR2
    .l1data > L1D
    .l1prog > L1P
    GROUP (NEARDP_DATA)                       // group near data
    {
       .neardata
       .rodata
       .bss                                   // note: removed fill = 0
    }             >        L2
    .far: fill = 0x0, load > L2             // Far Global & Static Variables
    .fardata      >        L2               // Far RW Data
    .stack        >        L2               // Software System Stack
    .sysmem       >        L2               // Dynamic Memory Allocation Area
    
    .cio          >        L2               // C I/O Buffer
    .vecs         >        DDR2               // Interrupt Vectors
}
