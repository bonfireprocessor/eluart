#include <rtthread.h>
#include "luaconf.h"


int _lua_readline(const char *prompt,char *buf,int szBuf)
{
    linenoise(prompt,buf,szBuf);
    int len=rt_strlen(buf);
    // if (len>0) {
    //     linenoiseHistoryAdd(buf);        
    // }
    return len;
}

int _lua_initreadline()
{
    linenoiseSetMultiLine(1);
}

void _lua_saveline(const char *line)
{
char * lcopy = rt_strdup(line);

    if (lcopy) {
        for(int i=0;i<rt_strlen(lcopy);i++) {
           if (lcopy[i]=='\n') lcopy[i]=' ';            
        }
        linenoiseHistoryAdd(lcopy);
        rt_free(lcopy);
    }
}