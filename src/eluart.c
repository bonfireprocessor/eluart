#pragma message "compling eluart"

#include <rtthread.h>
#include "eluart.h"


static luaL_Reg  *userlibs=NULL;
static int numModules = 0;
// {
  
//     {"riscv", eluart_open_riscv},
//     {"cpu", eluart_open_cpu},
//     {NULL,NULL}
// };  


const luaL_Reg * get_user_libs()
{
     return userlibs;
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

void eluart_registerModule(const char* name,lua_CFunction initfunc)
{
    userlibs=rt_realloc(userlibs,sizeof(luaL_Reg)*(numModules+2)); // Keep also space for null terminator
    RT_ASSERT(userlibs);
    
    userlibs[numModules].name=rt_strdup(name);
    RT_ASSERT(userlibs[numModules].name);
    userlibs[numModules].func=initfunc;
    numModules++;
    userlibs[numModules].name=RT_NULL;
    userlibs[numModules].func=RT_NULL;
}
