#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // brk  and sbrk
#include <assert.h>

struct block_meta {
    size_t size;
    int free;
    struct block_meta *next;
};

#define META_SIZE sizeof(struct block_meta)

/* Variable global_base holds the start address of heap for running progam */
void *global_base = NULL;

struct block_meta
*find_free_block(struct block_meta **last, size_t size)
{
    /* Create new struct and give it a heap start address */
    struct block_meta *block = global_base;

    /*
        Go through linked list and check if there is free block of memory
        that is free and have enough space
    */
    while (block && !(block->free && block->size >= size)) {
        *last = block;
        block = block->next;
    }

    return block;
}


void
free_space(void *ptr)
{
    if (!ptr) {
        return;
    }
    /* Create new block_meta struct and give it a pointer ptr address */
    struct block_meta *block_ptr  = ptr;

    /*
        Since ptr points to data that user use and we need metadata, then
        subtract 1 memory location from it
    */
    block_ptr = block_ptr-1;

    /* Mark free = true for block metadata */
    block_ptr->free = 1;
}


struct block_meta
*request_space(struct block_meta *last_block, size_t size)
{

    struct block_meta *block;

    /* Get current system break */
    block = sbrk(0);

    /*  Request more space*/
    void *request = sbrk(size + META_SIZE);
    if (request < 0) {
        return NULL;
    }

    /* If this is not first time requesting space, set last point to new space */
    if (last_block) {
        last_block->next = block;
    }

    block->size = size;
    block->next = NULL;
    block->free = 0;

    return block;
}

void
*mymalloc(size_t size) {

    if (size <= 0) {
        return NULL;
    }

    struct block_meta *block;

    /* if this is first time of use */
    if (global_base == NULL) {
        block = request_space(NULL, size);
        if (!block) {
            return NULL;
        }
        global_base = block;
    }
    else {
        /* Curent page break*/
        struct block_meta *last_block = global_base;
        block = find_free_block(&last_block, size);

        if (!block) {
            block = request_space(last_block, size);

            if (!block) {
                return NULL;
            }
        }
    }
    /* Since block points to block metadata, but we need address that user can use*/
    return (block+1);
}

int
main(int argc, char *argv[])
{

    char *p = mymalloc(12);
    char *p1 = mymalloc(12);
    char *p2 = mymalloc(12);

    printf("Pointer p address: %d\n", p);
    printf("Pointer p1 address: %d\n", p1);
    printf("Pointer p2 address: %d\n", p2);

    free_space(p);
    char *p3 = mymalloc(12);

    printf("Pointer p3 address: %d\n", p3);

    exit(EXIT_SUCCESS);
}
