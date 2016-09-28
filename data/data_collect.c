#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT 10
int main(void)
{
    FILE *enroll = NULL;//collge_enroll
    FILE *field = NULL;//collge studying object field
    FILE *output =NULL;
    if((enroll = fopen("./EnrollResult_edited.csv","r")) == NULL)
    {
        printf("error! enroll can not read!\n");
        exit(1);
    }
    if((field = fopen("./105ULISTDEPARTMENTLIST01.csv","r")) == NULL)
    {
        printf("error! field cnan not read!\n");
        exit(1);
    }
    if((output = fopen("./output.csv","w"))==NULL)
    {
        printf("can not create output files\n");
        exit(1);
    }
    int count=0;
    //140101,100
    while(!feof(enroll))//until enroll reach eof
    {
        count++;
        int department_number=0;
        float enroll_rate=0.0;
        if(fscanf(enroll, "%d,%f",&department_number,&enroll_rate)!=2)
        {
            printf("%d|%f",department_number,enroll_rate);
            printf("some error about enroll read\n");
            exit(1);
        }
        printf("count:%d=%d\n",count,department_number);
        while(!feof(field))
        {
            int field_number,dis,subject,sub_department_number;
            // 領域代碼    學門代碼    學類代碼    科系代碼
// 3499A0 = 3499330
// 3499A1 = 3499331
// 3499A2 = 3499332
// 3499A3 = 3499333
// 3499A4 = 3499334
// 3499A5 = 3499335
// 3499A6 = 3499336
// 3499A7 = 3499337
// 3499A8 = 3499338
// 3499A9 = 3499339
// 3499B0 = 3499340
// 3499B1 = 3499341
// 3499B2 = 3499342
// 3499B3 = 3499343
// 3499B4 = 3499344
// 3499B5 = 3499345
// 3499B6 = 3499346
            //0=-
            if(fscanf(field, "%d,%d,%d,%d",&field_number,&dis,&subject,&sub_department_number)!=4)
            {
                printf("%d|%d|%d|%d",field_number,dis,subject,sub_department_number);
                printf("some error about field read\n");
                exit(1);
            }
            if(department_number==sub_department_number)
            {
                printf("subject:%d=%d\n",department_number,subject);
                //touch
                fprintf(output, "%d,%f,%d,%d,%d\n",department_number,enroll_rate,field_number,dis,subject);
                // printf("C");
                break;
            }
            // printf("A");
        }
        fseek(field, 0, SEEK_SET);
        // printf("B");
    }
    fclose(enroll);
    fclose(field);
    fclose(output);
    return 0;
}