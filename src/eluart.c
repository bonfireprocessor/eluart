#pragma message "compling eluart"

#include "eluart.h"

static const luaL_Reg loadeduserlibs[] =
{
  
    {"riscv", eluart_open_riscv},
    {"cpu", eluart_open_cpu},
    {NULL,NULL}
};  


const luaL_Reg * get_user_libs()
{
     return loadeduserlibs;
}

lua_Integer eluart_toInteger(lua_State *L,int index)
{
int isnum;
lua_Integer result = lua_tointegerx(L,index,&isnum);

    if (!isnum) {
        luaL_error(L,"Argument %d cannot be conveted to an integer",index);
        return 0;
    } else {
        return result;
    }
}