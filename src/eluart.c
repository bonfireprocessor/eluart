#pragma message "compling eluart"

#include "eluart.h"

static const luaL_Reg loadeduserlibs[] =
{
  
    {"riscv", eluart_open_riscv},
    {NULL,NULL}
};  


const luaL_Reg * get_user_libs()
{
     return loadeduserlibs;
}