/*
 * @File:   lua2rtt.c
 * @Author: liu2guang
 * @Date:   2018-05-06 09:16:56
 *
 * @LICENSE: https://github.com/liu2guang/lua2rtt/blob/master/LICENSE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-06     liu2guang    The first version.
 * 2018-07-03     liu2guang    Update lua5.1.2->lua5.3.4.
 */

#include "lua2rtt.h"
#include "shell.h"

static struct lua2rtt handle = {0};

// static rt_uint8_t lua2rtt_getc(void)
// {
//     rt_uint8_t ch = 0;
//     while(rt_device_read(handle.device, (-1), &ch, 1) != 1)
//     {
//         rt_sem_take(&(handle.rx_sem), RT_WAITING_FOREVER);
//     }
//     return ch;
// }

// static rt_err_t lua2rtt_rxcb(rt_device_t dev, rt_size_t size)
// {
//     return rt_sem_release(&(handle.rx_sem));
// }



static inline void lua2rtt_exit()
{
     rt_sem_release(&(handle.exit_sem));
}

static void lua2rtt_run(void *p)
{
    const char *device_name = RT_CONSOLE_DEVICE_NAME;

    handle.device = rt_device_find(device_name);
    if(handle.device == RT_NULL)
    {
        LUA2RTT_DBG("The msh device find failed.\n");
        lua2rtt_exit();
        return;
    }

    //handle.rx_indicate = handle.device->rx_indicate;
    //rt_device_set_rx_indicate(handle.device, lua2rtt_rxcb);

    if(handle.argc == 1)
    {
        rt_kprintf("\nPress CTRL+D to exit Lua.\n");
    }
    extern int lua_main(int argc, char **argv);
    lua_main(handle.argc, handle.argv);

    // rt_sem_detach(&(handle.rx_sem));
    // rt_device_set_rx_indicate(handle.device, handle.rx_indicate);
    // rt_kprintf("Exit Lua interactive mode.\n");
   
    lua2rtt_exit();
}

static int lua2rtt(int argc, char **argv)
{
    static rt_bool_t history_init = RT_FALSE;

    if(history_init == RT_FALSE)
    {
        rt_memset(&handle, 0x00, sizeof(struct lua2rtt));
        history_init = RT_TRUE;
    }
    else
    {
        handle.thread = RT_NULL;
        handle.stat = LUA2RTT_WAIT_NORMAL;
        handle.argc = 0;
            
        handle.device = RT_NULL;
        handle.rx_indicate = RT_NULL;
    }

    rt_sem_init(&(handle.rx_sem), "lua2rtt_rxsem", 0, RT_IPC_FLAG_FIFO);
    rt_sem_init(&(handle.exit_sem), "lua_exitsem", 0, RT_IPC_FLAG_FIFO);

    handle.argc = argc;
    handle.argv = rt_malloc(sizeof(char*)*argc);
    
    for(int i=0;i<argc;i++) {
        rt_size_t len = rt_strlen(argv[i]);
        handle.argv[i] = (char *)rt_malloc(len + 1);
        rt_memset(handle.argv[i], 0x00, len + 1);
        rt_strncpy(handle.argv[i], argv[i], len);
    }


    rt_uint8_t prio = rt_thread_self()->current_priority+1;
    handle.thread = rt_thread_create("lua", lua2rtt_run, RT_NULL, LUA2RTT_THREAD_STACK_SIZE, prio, 10);
    int result = RT_EOK;
    if(handle.thread == RT_NULL)
    {
      
        LUA2RTT_DBG("The Lua interpreter thread create failed.\n");
        result =RT_ERROR;
        goto cleanup;
    }
    rt_thread_startup(handle.thread);
    rt_sem_take(&(handle.exit_sem),RT_WAITING_FOREVER); // Wait for Lua thread to exit

    cleanup: 

    rt_sem_detach(&(handle.rx_sem));
    rt_sem_detach(&(handle.exit_sem));
    
    for(int i=0;i<handle.argc;i++) 
    {
        rt_free(handle.argv[i]);
    }
    rt_free(handle.argv);
    return result;
}
MSH_CMD_EXPORT_ALIAS(lua2rtt, lua, Execute Lua parser.);
