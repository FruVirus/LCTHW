#include "dbg.h"

int normal_copy(char *from,char *to,int count)
{
    int i = 0;

    for(i = 0;i < count;i++)
    {
        to[i] = from[i];
    }

    return i;
}

int duffs_device(char *from,char *to,int count)
{
    {
        int n = (count + 7)/8;

        switch(count%8)
        {
            case 0:
                do
                {
                    *to++ = *from++;
                    case 7:
                    *to++ = *from++;
                    case 6:
                    *to++ = *from++;
                    case 5:
                    *to++ = *from++;
                    case 4:
                    *to++ = *from++;
                    case 3:
                    *to++ = *from++;
                    case 2:
                    *to++ = *from++;
                    case 1:
                    *to++ = *from++;
                } while(--n > 0);
        }
    }

    return count;
}

int zeds_device(char *from,char *to,int count)
{
    {
        int n = (count + 7)/8;

        switch(count%8)
        {
            case 0:
again:      *to++ = *from++;
            case 7:
            *to++ = *from++;
            case 6:
            *to++ = *from++;
            case 5:
            *to++ = *from++;
            case 4:
            *to++ = *from++;
            case 3:
            *to++ = *from++;
            case 2:
            *to++ = *from++;
            case 1:
            *to++ = *from++;

            if(--n > 0)
                goto again;
        }
    }

    return count;
}

int valid_copy(char *data,int count,char expects)
{
    int i = 0;

    for(i = 0;i < count;i++)
    {
        if(data[i] != expects)
        {
            log_err("[%d] %c != %c",i,data[i],expects);
            
            return 0;
        }
    }

    return 1;
}

int main(int argc,char *argv[])
{2 set tabstop=4 shiftwidth=4 expandtab
    int x = 2;
    printf("%d\n",++x*3);
    printf("%d\n",3*x++);
    char from[1000] = {'a'};
    char to[1000] = {'c'};
    int rc = 0;

    // Setup the 'from' to have some stuff.
    memset(from,'x',1000);
    //for(int i = 0;i < 1000;i++)
        //printf("%c, ",from[i]);
    
    // Set it to a failure mode.
    memset(to,'y',1000);
    check(valid_copy(to,1000,'y'),"Not initialized right.");

    // Use normal copy to.
    rc = normal_copy(from,to,1000);
    check(rc == 1000,"Normal copy failed: %d",rc);
    check(valid_copy(to,1000,'x'),"Normal copy failed.");

    // Reset.
    memset(to,'y',1000);

    // Duff's version.
    rc = duffs_device(from,to,1000);
    check(rc == 1000,"Duff's device failed: %d",rc);
    check(valid_copy(to,1000,'x'),"Duff's device failed copy.");

    // Reset.
    memset(to,'y',1000);

    // My version.
    rc = zeds_device(from,to,1000);
    check(rc == 1000,"Zed's device failed: %d",rc);
    check(valid_copy(to,1000,'x'),"Zed's device failed copy.");

    return 0;

error:
    return 1;
}

/*
    int a = 10;
    int *b = &a;
    printf("%d\n",*b);
    printf("%p\n",b);
    printf("%p\n",&b);
    int **bb = &b;
    printf("%p\n",bb);
    printf("%p\n",&a);
    printf("%lu\n",sizeof(b));
*/
