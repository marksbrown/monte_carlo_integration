#include "montecarlo.h"
#include "cases.h"

double absolute_deviation(double predicted, double expected){
    return fabs(predicted - expected);
}


result monte_carlo_deviation(int N, result *expected, result (*monte_carlo)(int)){
    /* Determine Deviation from Expected */
    
    result r = (monte_carlo)(N);
    r.volume = absolute_deviation(expected->volume, r.volume);   
    r.COM.x = absolute_deviation(expected->COM.x, r.COM.x);
    r.COM.y = absolute_deviation(expected->COM.y, r.COM.y);
    r.COM.z = absolute_deviation(expected->COM.y, r.COM.z);
    return r;
}

result expected_partial_torus(){
    result r;
    r.volume = 22.194176;
    r.COM.x = 2.4076; 
    r.COM.y = 0.16210;
    r.COM.z = 0.0;
    return r;
}

result expected_sphere(){
    result r;
    r.volume = 4.1887902047863905;
    r.COM.x = 1.0;
    r.COM.y = 1.0;
    r.COM.z = 1.0;
    return r;
}

void add_results(result *f, result *s){
    f->volume += s->volume;
    f->COM.x += s->COM.x;
    f->COM.y += s->COM.y;
    f->COM.z += s->COM.z;
}

int main(){
    //result e = expected_partial_torus();
    result e = expected_sphere();
    int j;
    int N;
    int repeats;
    int M;
    M = 10;
    result r;
    for (j = 5; j < 30; j++){
        N = (int) pow(1.5, j);
        for (repeats = 0; repeats < M; repeats ++){
            
            result new_r = monte_carlo_deviation(N, &e, &sphere);
            if (repeats == 0){
                r = new_r;
            } else {
                add_results(&r, &new_r);
            }
        }
        printf("%d,%f,%f,%f,%f\n", N, r.volume / M, r.COM.x / M, r.COM.y / M, r.COM.z / M);
    }
    
}