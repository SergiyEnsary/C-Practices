//
// Created by sergiy on 1/8/21.
//

#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP  20

/*
 * print Fahrenheit-Celsius table
 *  for fahr = 0, 20, ..., 300
 */

int fahren(){
    int fahr;

    printf("\n***These are the temperature.c runs***\n");
    printf("%s\t%s\n", "Fahrenheit", "Celsius");

    for(fahr = LOWER; fahr <= UPPER; fahr+=STEP){
        printf("%10d\t%7.1f\n", fahr, (5.0/9.0) * (fahr-32));
    }
    return 1;
}

int cels(){
    float fahr, celsius;
    int low, up, step;

    low = 0;
    up = 300;
    step = 20;

    celsius = up;
    printf("\n***These are the temperature.c runs***\n");
    printf("%s\t%s\n", "Celsius", "Fahrenheit");
    while (celsius >= low){
        fahr = ((9.0/5.0) * celsius)+32.0;
        printf("%6.0f\t%10.1f\n", celsius, fahr);
        celsius -= step;
    }
    return 1;
}
