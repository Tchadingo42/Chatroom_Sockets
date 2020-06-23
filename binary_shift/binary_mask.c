#include <stdio.h>

int                   main(void)
{
    unsigned char     var;
    unsigned char     var2;
    unsigned char     var3;

    var = 10;
    var2 = 15;
    var3 = 1;

    var = var | 0x4;
    var2 = var2 & 0x4;
    var3 = var3 | (1<<2);

    printf("var1->[%d]\nvar2->[%d]\nvar3->[%d]\n", var, var2, var3);
    return (0);
}
