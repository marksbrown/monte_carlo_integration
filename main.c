#include "montecarlo.h"

int partial_torus_condition(point *apoint){

    double x = apoint->x;
    double y = apoint->y;
    double z = apoint->z;

    double R = pow(x, 2) + pow(y, 2);
    double r = pow(z - 1, 2) + pow(pow(R, 0.5) - 3, 2);
    if (x >= 1 && y >= -3 && r <= 1){
        return 1;
    }else {
        return 0;
    }
}

result partial_torus(int N){
    mc torus;
    torus.condition = partial_torus_condition;
    torus.next_point = randomise_point;
    
    torus.limits.x.l = -4;
    torus.limits.x.h = 4;
    torus.limits.y.l = -4;
    torus.limits.y.h = 4;
    torus.limits.z.l = 0;
    torus.limits.z.h = 2;
    
    return com_monte_carlo(N, &torus);
}

double absolute_deviation(double predicted, double expected){
    return fabs(predicted - expected);
}

void partial_torus_deviation(int N){
    /* print the deviations in all four values from expected!*/
    double expected_volume;
    expected_volume = 22.194176;

    point expected_COM;
    expected_COM.x = 2.4076; 
    expected_COM.y = 0.16210;
    expected_COM.z = 1.0;
    
    result r = partial_torus(N);
    //printf("Volume : %f\n COM : (%f, %f, %f)\n", r.volume, r.COM.x, r.COM.y, r.COM.z);
    double dV = absolute_deviation(expected_volume, r.volume);   
    double dx = absolute_deviation(expected_COM.x, r.COM.x);
    double dy = absolute_deviation(expected_COM.y, r.COM.y);
    double dz = absolute_deviation(expected_COM.y, r.COM.z);
    printf("%d,%f,%f,%f,%f\n", N, dV, dx, dy, dz);
}

int main(){
    int j;
    int N;
    for (j = 3; j < 40; j++){
        N = (int) pow(1.5, j);
        partial_torus_deviation(N);
    }
    
}