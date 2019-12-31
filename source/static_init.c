extern unsigned int** got_spriteToProfileList;
extern unsigned int* _ZN7Profile19spriteToProfileListE;

typedef void (*InitFunc)(void);
extern InitFunc __init_array_start;
extern InitFunc __init_array_end;

void static_init()
{
    got_spriteToProfileList = &_ZN7Profile19spriteToProfileListE;

    for (InitFunc* p = &__init_array_start; p < &__init_array_end; p++)
        (*p)();
}

int __cxa_atexit(void (*func)(void*), void* arg, void* d)
{
    return 0;
}

void* __dso_handle = 0;
