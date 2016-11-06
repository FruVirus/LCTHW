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

int zeds_device(char *from,char *to,int count)
{
    {
        int n = (count + 6)/7;

        switch(count%7)
        {
            case 0:
again:      *to++ = *from++;
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
{
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

    // My version.
    rc = zeds_device(from,to,1000);
    check(rc == 1000,"Zed's device failed: %d",rc);
    check(valid_copy(to,1000,'x'),"Zed's device failed copy.");

    return 0;

error:
    return 1;
}
