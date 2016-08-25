/***************************************
 * Filename: mempool.c
 * Title: mempool Test Module
 * Desc: mempool create
 ****************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/slab.h>
#include <linux/mempool.h>

#define MIN_ELEMENT     4
#define TEST_ELEMENT    4

typedef struct 
{
    int number;
    char string[128];
} TMemElement;


int elementcount = 0;

void *mempool_alloc_test(int gfp_mask, void *pool_data)
{
    TMemElement  *data;
    printk( "----> mempool_alloc_test\n" );        
    
    data = kmalloc( sizeof( TMemElement ), gfp_mask );
    if( data != NULL ) data->number = elementcount++;
    return data;
}

void mempool_free_test(void *element, void *pool_data)
{
    printk( "----> call mempool_free_test\n" );        
    if( element != NULL ) kfree( element );
}

int mempool_init(void)      
{ 
    mempool_t   *mp;    
    TMemElement *element[TEST_ELEMENT];
    int          lp;
    
    printk("Module MEMPOOL Test\n" );
    
    memset( element, 0, sizeof( element ) );
    
    printk( "call mempool_create\n" );
    //mp = mempool_create( MIN_ELEMENT, mempool_alloc_test, mempool_free_test, NULL );
    mp = mempool_create( 3, mempool_alloc_test, mempool_free_test, NULL );
    
    printk( "mempool allocate\n" );
    for( lp=0; lp < TEST_ELEMENT; lp++ )
    {
        element[lp] = mempool_alloc(mp, GFP_KERNEL );
        if( element[lp] == NULL ) printk( "allocte fail\n" );
        else
        {
            sprintf( element[lp]->string, "alloc data %d\n", element[lp]->number );
            printk( element[lp]->string );
        }
    }
    
    printk( "mempool free\n" );
    for( lp=0; lp < TEST_ELEMENT; lp++ )
    {
        if( element[lp] != NULL ) mempool_free( element[lp], mp );
    }
    
    printk( "call mempool_destroy\n" );
    mempool_destroy( mp );
    
    return 0; 
}

void mempool_exit(void)  
{ 
    printk("Module MEMPOOL Test End\n"); 
}

module_init(mempool_init);
module_exit(mempool_exit);

MODULE_LICENSE("Dual BSD/GPL");

