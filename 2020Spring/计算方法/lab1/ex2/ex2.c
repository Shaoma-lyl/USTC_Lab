//
// Created by 廖洲洲 on 2020/3/27.
//
#include <stdio.h>
int main(){
    double result,tmp;
    printf("       \t方法(a)\t方法(b)\t方法(c)\n");
    printf("计算结果\t");
    result=4040.045551380452+(-2759471.276702747)+(-31.64291531266504)+2755462.874010974+0.0000557052996742893;
    printf("%.6e\t",result);
    result=0.0000557052996742893+2755462.874010974+(-31.64291531266504)+(-2759471.276702747)+4040.045551380452;
    printf("%.6e\t",result);
    tmp=2755462.874010974+4040.045551380452+0.0000557052996742893;
    result=(-2759471.276702747)+(-31.64291531266504);
    result=result+tmp;
    printf("%.6e\t",result);
}

