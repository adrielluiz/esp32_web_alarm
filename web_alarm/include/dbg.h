#ifndef DBG_H
#define DBG_W


void dbg_printfs(int level, const char *fmt, ...);
void dbg_printfsl(int level, const char *fmt);

#define DBG_PRINTFL(level,fmt, ...) dbg_printfs(level,fmt,__VA_ARGS__)
#define DBG_PRINTFSL(level,fmt)     dbg_printfsl(level,fmt)

#endif