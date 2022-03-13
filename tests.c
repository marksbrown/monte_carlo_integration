/*
Tests!

1. Sanity Checks - Determine if each function is behaving itself
2. Simple checks - Determine 1 (line) pi (circle), determine 4/3 * pi (sphere)
*/

#include "montecarlo.h"
#include "assert.h"

void run_tests();

int main(){
    run_tests();
}

int line_condition(point *apoint){
    if (apoint->x > 0 && apoint->x < 1){
        return 1;
    } else {
        return 0;
    }
}

int circle_condition(point *apoint){
    // unit circle centred on (1,1) in XY plane
    double r;
    r = pow(apoint->x - 1, 2) + pow(apoint->y - 1, 2);
    if (r <= 1){
        return 1;
    } else {
        return 0;
    }
}

int sphere_condition(point *apoint){
    // unit sphere centred on (1,1,1)
    double r;
    r = pow(apoint->x - 1, 2) + pow(apoint->y - 1, 2) + pow(apoint->z - 1, 2);
    if (r <= 1){
        return 1;
    } else {
        return 0;
    }
}

int square_condition(point *apoint){
    // unit square from (0,0,0) to (1,1,0)
    if (apoint->x >= 0 && apoint->x < 1 && apoint->y >= 0 && apoint->y < 1){
        return 1;
    } else {
        return 0;
    }
}

int cube_condition(point *apoint){
    // unit cube from (0,0,0) to (1,1,1)
    if (apoint->x >= 0 && apoint->x < 1 && apoint->y >= 0 && apoint->y < 1 && apoint->z >= 0 && apoint->z < 1){
        return 1;
    } else {
        return 0;
    }
}



int test_line(){
    // unit line
    int N = (int) 1E6;
    mc line;
    line.condition = line_condition;
    line.next_point = randomise_point;
    
    line.limits.x.l = 0;
    line.limits.x.h = 2;
    line.limits.y.l = 0;
    line.limits.y.h = 0;
    line.limits.z.l = 0;
    line.limits.z.h = 0;
    
    result r = com_monte_carlo(N, &line);
    printf("=== Unit line ===\n");
    printf("Length : %f (1.00)\n ", r.volume);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return 0;
}

int test_circle(){
    // unit circle in XY plane centred on (1,1,0)
    int N = (int) 1E6;
    mc circle;
    circle.condition = circle_condition;
    circle.next_point = randomise_point;
    
    circle.limits.x.l = 0;
    circle.limits.x.h = 2;
    circle.limits.y.l = 0;
    circle.limits.y.h = 2;
    circle.limits.z.l = 0;
    circle.limits.z.h = 0;
    
    
    double expected = 3.141592653589793;
    result r = com_monte_carlo(N, &circle);
    printf("=== Unit Circle ===\n");
    printf("Area : %f (%f)\n", r.volume, expected);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return 0;
}

int test_sphere(){
    // unit sphere centred on (1,1,1)
    int N = (int) 1E6;
    mc sphere;
    sphere.condition = sphere_condition;
    sphere.next_point = randomise_point;
    
    sphere.limits.x.l = 0;
    sphere.limits.x.h = 2;
    sphere.limits.y.l = 0;
    sphere.limits.y.h = 2;
    sphere.limits.z.l = 0;
    sphere.limits.z.h = 2;
    double expected = 4.1887902047863905;
    result r = com_monte_carlo(N, &sphere);
    printf("=== Unit Sphere ===\n");
    printf("Volume : %f (%f)\n", r.volume, expected);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return 0;
}

int test_square(){
    // unit square
    int N = (int) 1E6;
    mc square;
    square.condition = square_condition;
    square.next_point = randomise_point;
    square.limits.x.l = 0;
    square.limits.x.h = 2;
    square.limits.y.l = 0;
    square.limits.y.h = 2;
    
    
    result r = com_monte_carlo(N, &square);
    printf("=== Unit Square ===\n");
    printf("Area : %f (1.00)\n", r.volume);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return 0;
}

int test_cube(){
    // unit square
    int N = (int) 1E6;
    mc cube;
    cube.condition = cube_condition;
    cube.next_point = randomise_point;
    cube.limits.x.l = 0;
    cube.limits.x.h = 2;
    cube.limits.y.l = 0;
    cube.limits.y.h = 2;
    cube.limits.z.l = 0;
    cube.limits.z.h = 2;
    
    
    result r = com_monte_carlo(N, &cube);
    printf("=== Unit Cube ===\n");
    printf("Volume : %f (1.00)\n", r.volume);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return 0;
}

void run_tests(){
    assert(test_line() == 0);
    assert(test_square() == 0);
    assert(test_cube() == 0);
    assert(test_circle() == 0);
    assert(test_sphere() == 0);
    printf("All silent failure or some success!\n");
}