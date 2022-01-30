#include <rtthread.h>
#include "eluart.h"
#include "bonfire.h"
//#include "lua2rtt.h"

#include <string.h>
#include "encoding.h"



static int riscv_readcsr( lua_State* L )
{
  unsigned csr = ( unsigned )luaL_checknumber( L, 1 );
  unsigned r;
  switch(csr) {
  case CSR_MISA: r=read_csr(misa); break;
  case CSR_MIMPID: r=read_csr(mimpid); break;
  case CSR_MSTATUS:  r=read_csr(mstatus); break;
  case CSR_MIE:  r=read_csr(mie); break;
  case CSR_MIP:  r=read_csr(mip); break;
  default: r= -1;
  }

  lua_pushnumber( L,( lua_Number ) r );
  return 1;
}

static volatile uint32_t *pmtime = (uint32_t*)MTIME_BASE; // Pointer to memory mapped RISC-V Timer registers

static int riscv_readmtime( lua_State* L )
{

  lua_pushnumber( L, (lua_Number)pmtime[0] );

  return 1;
}


static int riscv_readmcycle( lua_State* L )
{
//TODO: Implement...  
rt_uint64_t cycle=0; // 

  lua_pushnumber( L, (lua_Number)cycle);
  return 1;
}


static int riscv_cpuid(lua_State* L)
{
rt_uint32_t impid =  read_csr(mimpid);

   lua_pushfstring( L,"%d.%d",impid >> 16,impid & 0xffff );
   return 1;
   
}

static int riscv_readminstret(lua_State* L)
{
rt_uint64_t val; 

  if ( (read_csr(mimpid) & 0xffff)<31 ) {
    luaL_error( L, "instret counter not implemented on cpuid: %p",read_csr(mimpid));
    return 0; 
  }
    
#if __riscv_xlen == 32
  while (1) {
    rt_uint32_t hi = read_csr( minstreth );
    rt_uint32_t lo = read_csr( minstret );
    if (hi == read_csr( minstreth )) {
      val= ( (rt_uint64_t)hi << 32 ) | lo;
      break;
    }  
  }
#else
   val= read_csr(minstret);
#endif  

   lua_pushnumber( L,( lua_Number )val );

  return 1;
}




//#include "lrodefs.h"
LUA_REG_TYPE riscv_map[] =
{
  { LSTRKEY( "readcsr" ), LFUNCVAL( riscv_readcsr ) },
  { LSTRKEY( "readmtime" ), LFUNCVAL( riscv_readmtime ) },
  { LSTRKEY( "readmcycle" ), LFUNCVAL( riscv_readmcycle ) },
  { LSTRKEY( "readminstret" ), LFUNCVAL( riscv_readminstret ) },
  { LSTRKEY( "cpuid" ), LFUNCVAL( riscv_cpuid ) },
  

/*
 
  { LSTRKEY( "misa" ), LNUMVAL( CSR_MISA ) },
  { LSTRKEY( "mimpid" ), LNUMVAL( CSR_MIMPID ) },
  { LSTRKEY( "mstatus" ), LNUMVAL( CSR_MSTATUS ) },
  { LSTRKEY( "mie" ), LNUMVAL( CSR_MIE ) },
  { LSTRKEY( "mip" ), LNUMVAL( CSR_MIP ) },
*/

  { RT_NULL, RT_NULL }
};

int eluart_open_riscv(lua_State *L)
{
  luaL_newlib(L,riscv_map);
  return 1;
  
}



// int init(lua_State *L)
// {
//   luaL_requiref(L,"riscv",luaopen_riscv,1);
//   return 1;
// }