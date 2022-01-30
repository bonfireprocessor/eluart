#ifndef __ELUART_H__
#define __ELUART_H__

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int eluart_open_riscv(lua_State *L);
int eluart_open_cpu(lua_State *L);

// Compatibilty with orginal elua code

#define LUA_REG_TYPE static const struct luaL_Reg
#define LSTRKEY(str) str
#define LFUNCVAL(f) f
#define LREGISTER(L,n,m) luaL_openlib(L,n,m)
#define LNILKEY RT_NULL
#define LNILVAL RT_NULL

// Helper functions

// Tries to convert value at <index> to an lua_Integer, raise an error
// "value cannot be converted to an integer"
lua_Integer eluart_toInteger(lua_State *L,int index); 

#endif 
