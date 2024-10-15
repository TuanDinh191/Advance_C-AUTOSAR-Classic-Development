#include <assert.h>

#define log(condition,cmd) assert(condition && #cmd)
int main()
{
    int x = 7;
    log(x==6, x phai bang 6);
    return 0;
}