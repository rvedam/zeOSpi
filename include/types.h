/*
 * types.h - Definició de tipus i estructures de dades
 */

#ifndef __TYPES_H__
#define __TYPES_H__

/** System types definition **/
/*****************************/

typedef unsigned char       Byte;
typedef unsigned short int  Word;
typedef unsigned long       DWord;

#define highWord(address) (Word)(((address) >> 16) & 0xFFFF)
#define lowWord(address) (Word)((address) & 0xFFFF)
#define midByte(address) (Byte)(((address) >> 16) & 0xFF)
#define highByte(address) (Byte)(((address) >> (16 + 8)) & 0xFF)
#define high4Bits(limit) (Byte)(((limit) >> 16) & 0x0F)

typedef struct  /* Segment Descriptor */
{
  Word  limit;
  Word  lowBase;
  Byte  midBase;
  Byte  flags1;
  Byte  flags2;
  Byte  highBase;
} Descriptor;     /* R1: pg. 3-11, 4-3 */

typedef struct /* Gate */
{
  Word  lowOffset;
  Word  segmentSelector;
  Word  flags;
  Word  highOffset;
} Gate;     /* R1: pg. 5-11 */

typedef struct              /* TASK STATE SEGMENT      */
{                           /*                         */
  Word  PreviousTaskLink;   /* 0          R1: pg. 6-5  */
  Word  none1;              /*                         */
  DWord esp0;               /* 4  \                    */
  Word  ss0;                /* 8  |                    */
  Word  none2;              /*    |                    */
  DWord esp1;               /* 12 |  Stack pointers    */
  Word  ss1;                /* 16 |-    for each       */
  Word  none3;              /*    |  privilege level   */
  DWord esp2;               /* 20 |                    */
  Word  ss2;                /*    |                    */
  Word  none4;              /* 24/                     */
  DWord cr3;                /* 28\                     */
  DWord eip;                /* 32 |                    */
  DWord eFlags;             /* 36 |                    */
  DWord eax;                /* 40 |                    */
  DWord ecx;                /* 44 |                    */
  DWord edx;                /* 48 |                    */
  DWord ebx;                /* 52 |                    */
  DWord esp;                /* 56 |                    */
  DWord ebp;                /* 60 |                    */
  DWord esi;                /* 64 |                    */
  DWord edi;                /* 68 |- Saved registers   */
  Word  es;                 /* 72 |                    */
  Word  none5;              /*    |                    */
  Word  cs;                 /* 76 |                    */
  Word  none6;              /*    |                    */
  Word  ss;                 /* 80 |                    */
  Word  none7;              /*    |                    */
  Word  ds;                 /* 84 |                    */
  Word  none8;              /*    |                    */
  Word  fs;                 /* 88 |                    */
  Word  none9;              /*    |                    */
  Word  gs;                 /* 92 |                    */
  Word  none10;             /*   /                     */
  Word  LDTSegmentSelector; /* 96                      */
  Word  none11;             /*     The offset in the   */
  Word  debugTrap;          /* 100 TSS Segment to the  */
  Word  IOMapBaseAddress;   /* 102 io permision bitmap */
} TSS; /* size = 104 B + i/o permission bitmap and     */
       /* interrupt redirection bitmap (R1 pg 6.6)     */

/** Registers: **/
/****************/
typedef struct
{
  Word  limit __attribute__ ((packed));
  DWord base  __attribute__ ((packed));
} Register; /* GDTR, IDTR */
/*                                            */
/*  /--------------------------------------\  */
/* |      Base Address       |     Limit    | */
/*  \--------------------------------------/  */
/* 47                       16            0   */
/*                             R1: pg. 2-10   */
/**********************************************/

/** Segment Selector **/
/**********************/

typedef Word Selector;
/*                                                     */
/*  /--------------------------------------\           */
/*  |   Index                       |TI|RPL|           */
/*  \--------------------------------------/           */
/*  15                             3  2 1 0            */
/*                                                     */
/*  Index = Index in the GDT/LDT descriptor table      */
/*  TI    = 0 -> GDT ; 1 -> LDT                        */
/*  RPL   = Requestor Privilege Level     R1: pg. 3-9  */
/*******************************************************/

/**************************************************************************/
/*** THE EFLAGS ****************************************** R1: pg. 2-8 ****/
/**                                                                      **/
/**   -----------------------------------------------------------------  **/
/**  |                     |I|V|V|A|V|R| |N| I |O|D|I|T|S|Z| |A| |P| |C| **/
/**  | Reserved (set to 0) | |I|I| | | |0| | O | | | | | | |0| |0| |1| | **/
/**  |                     |D|P|F|C|M|F| |T|PL |F|F|F|F|F|F| |F| |F| |F| **/
/**   -----------------------------------------------------------------  **/
/**  31                  22 21        16  14  12    9 8 7 6 5 4 3 2 1 0  **/
/**                                                                      **/
/** ID :  Identification Flag          IF:   Interrupt Enable Flag       **/
/** VIP:  Virtual Interrupt Pending    TF:   Trap Flag                   **/
/** VIF:  Virtual Interrupt Flag       SF:   Sign Flag                   **/
/** AC:   Alignment Check              ZF:   Zero Flag                   **/
/** VM:   Virtual 8086 Mode            AF:   Auxiliary Carry Flag        **/
/** RF:   Resume Flag                  PF:   Parity Flag                 **/
/** NT:   Nested task Flag             CF:   Carry Flag                  **/
/** IOPL: I/O Privilege Level                                            **/
/**                                                                      **/
/**************************************************************************/
#define INITIAL_EFLAGS 0x00000200

#define NULL 0

typedef union 
{
  unsigned int entry;
  struct {    
    unsigned int present  : 1;
    unsigned int rw       : 1;
    unsigned int user     : 1;
    unsigned int write_t  : 1;
    unsigned int cache_d  : 1;
    unsigned int accessed : 1;
    unsigned int dirty    : 1;
    unsigned int ps_pat   : 1;
    unsigned int global   : 1;
    unsigned int avail    : 3;
    unsigned int pbase_addr : 20;
  } bits;
} page_table_entry;


typedef union
{
  unsigned int entry;
  struct {
    unsigned int accesstype : 2; // 0b01 for second level page table
    unsigned int sbz1       : 1; // should be zero
    unsigned int ns         : 1; // secure(0)/non-secure(1)
    unsigned int sbz2       : 1; // should be zero
    unsigned int domain     : 4;
    unsigned int p          : 1; // ECC enabled, not supported in ARM1176JZF-S
    unsigned int ptbase_addr : 22;
  } bits;
} fl_page_table_entry;

typedef union
{
  unsigned int entry;
  struct {
    unsigned int xn         : 1; // execute-never(1), executable(0) (instructions on the memory)
    unsigned int setbit     : 1; // set to 1 for 4KB pages
    unsigned int b          : 1; // bufferable
    unsigned int c          : 1; // cacheable
    unsigned int ap         : 2; // acces permission, use with apb bit. Table 6-1
    unsigned int tex        : 3; // Type extension field. Page 6-14
    unsigned int apx        : 1; // access permission extension
    unsigned int s          : 1; // non-shared(0)/shared(1)
    unsigned int ng         : 1; // global(0)/process-specific(1)
    unsigned int pbase_addr : 20;
  } bits;
} sl_page_table_entry; //page 6-39


#endif  /* __TYPES_H__ */