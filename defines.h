#define READBIT(WORD,BIT) ((WORD>>BIT)&1)
#define RWBIT(DWORD,DBIT,SWORD,SBIT) \
        DWORD=((DWORD&~(1<<DBIT))| \
                                      (((SWORD>>SBIT)&1)<<DBIT))

#define WNIBBLE(WORD,STARTBITPOS,NIBBLE) \
        WORD=((WORD&~(15<<STARTBITPOS))|\
                                     (NIBBLE<<STARTBITPOS))

#define RNIBBLE(WORD,STARTBITPOS) \
                                ((WORD>>STARTBITPOS)&15)

#define WBYTE(WORD,STARTBITPOS,BYTE) \
        WORD=((WORD&~((u32)255<<STARTBITPOS))|\
                                     ((u32)BYTE<<STARTBITPOS))

#define RBYTE(WORD,STARTBITPOS) \
                                ((WORD>>STARTBITPOS) & 255)
#define SCLRBIT(WORD,BIT) (WORD=1<<BIT)
#define SETBIT(WORD,BIT) (WORD|=1<<BIT)
#define SSETBIT(WORD,BIT) (WORD=1<<BIT)
#define CLRBIT(WORD,BIT) (WORD&=~(1<<BIT))
#define CPLBIT(WORD,BIT) (WORD^=1<<BIT)
#define SETBYTE(WORD,STARTBITPOS) (WORD=255<<STARTBITPOS)
