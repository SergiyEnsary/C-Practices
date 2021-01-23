//
// Created by sergiy on 1/22/21.
//
void swap(&a, &b);

pointers(){
    int x=1, y=2, z[10];
    int *ip; /** ip is a pointer to int **/

    ip = &x; /** ip now points to x **/
    y = *ip; /** y is now 1 **/
    *ip = 0; /** x is now 0 **/
    ip = &z[0]; /** ip now points to z[0] **/

    *ip = *ip +10; //increment ip by 10
}

void swap(int *px, int *py){
    int temp;

    temp = *px;
    *px = *py;
    *py = temp;
}