#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <unistd.h>
#include <stdint.h>


struct Segment 
{

int begin;
int end;

};

void factorial(void *args );
void module(void *args );

int res=1; 
int mod=-1; 
int tnum=-1; 
int k=-1; 
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv)
{
    int i;
    int j;
    while(true)
    {
        int current_optind = optind ? optind : 1;

        static struct option options[] = {{"k", required_argument, 0, 0},
                                        {"tnum", required_argument, 0, 0},
                                        {"mod", required_argument, 0, 0},
                                        {0, 0, 0, 0}};

        int option_index = 0;
        int c = getopt_long(argc, argv, "f", options, &option_index);

        if (c == -1) break;
        switch (c) 
        {
        case 0:
            switch (option_index) 
            {
            case 0:
                k = atoi(optarg);
        
            if(k<=0)
                {
                    printf("number can't be negative \n");		
                    return -1;
                }
            
                break;
            case 1:
                tnum = atoi(optarg);
        
            if(tnum<1)
                {
                    printf("amount of threads can't be negative\n");	
                    return -1;
                }
                
                break;
            case 2:
            mod = atoi(optarg);
                if(mod<1)
                {
                    printf("module can't be negative \n");
                    return -1;
                }
                break;

            default:
                printf("Index %d is out of options\n", option_index);
            }
            break;

        case '?':
            break;

        default:
            printf("getopt returned character code 0%o?\n", c);
        }
    }

    if (optind < argc) 
    {
        printf("Has at least one no option argument\n");
        return 1;
    }

    if (k == -1 || mod == -1 || tnum == -1) 
    {
        printf("Usage: %s --k \"num\" --mod \"num\" --tnum \"num\" \n",
            argv[0]);
        return 1;
    }

    struct Segment seg[tnum];


    if(tnum==1)
    {
        seg[0].begin=1;
        seg[0].end=k;
        factorial((void *)&seg[0]);
        module((void *)&seg[0]);
        printf("The factorial %d modulo %d is equal %ld \n", k, mod, res);
        return 0;
    }

    int beginf=0; int endf=0;
    int beginm=0; int endm=0;

    int step_factorial, step_module;
    
    if(tnum>=2*k)
    {
        step_factorial=1;
        step_module=1;
        tnum=k;
    }

    else if((tnum % 2)==0)
    {
        step_factorial=k/(tnum/2);
        step_module=step_factorial;
    }
    else
    {
        step_factorial=k/((tnum+1)/2);
        step_module=k/((tnum-1)/2);
    }
    
    pthread_t threads[tnum];

    for( i=0; i<tnum; i=i+2)
    {
        beginf=endf+1;
        endf=beginf+step_factorial;
        if( (i+2)>=tnum) endf=k;
        seg[i].begin=beginf;
        seg[i].end=endf;
        if (pthread_create(&threads[i], NULL, factorial,(void *)&seg[i])) 
        {      
            printf("Error: pthread_create failed!\n");
            return 1;
        }

    }

    for(j=1; j<tnum; j=j+2)
    { 
        beginm=endm+1;
        endm=beginm+step_module;
        if( (j+2)>=tnum)
        endm=k;
        seg[j].begin=beginm;
        seg[j].end=endm;
        if (pthread_create(&threads[j], NULL, module,(void *)&seg[j]))
        {   
            printf("Error: pthread_create failed!\n");
            return 1;
        }

    }

    for (i = 0; i < tnum-2; i+=2) 
    {
        pthread_join(threads[i],NULL);
    }
    for (i = 1; i < tnum; i+=2) 
    {
        pthread_join(threads[i],NULL);
    }

    if((tnum % 2)==0)
    {
        module((void*)&seg[tnum-1]);
    }
    else
    {
        module((void*)&seg[tnum-2]);
    } 
    printf("The factorial %d modul %d is equal %ld \n", k, mod, res);
    return 0;
}

void factorial(void* args)
{
    int i;
    struct Segment *s = (struct Segment *)args;
    pthread_mutex_lock(&mut);
    for(i=s->begin; i<=s->end; i++)
    {
        res=res*i;

    }
    pthread_mutex_unlock(&mut);

}


void module(void* args)
{
    int i;
    struct Segment *s = (struct Segment *)args;
    pthread_mutex_lock(&mut);
    for(i=s->begin; i<=s->end; i++)
    {

        res=res%mod;

    }

    pthread_mutex_unlock(&mut);
}