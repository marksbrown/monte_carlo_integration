/*
Tests!

1. Sanity Checks - Determine if each function is behaving itself
2. Simple checks - Determine 1 (line) pi (circle), determine 4/3 * pi (sphere)
*/

#include "montecarlo.h"
#include "cases.h"

int N = (int) 1E6;
double PRECISION = 1E-2;  // 1 in 100

int run_tests();

int main(){
    int f = run_tests();
    if (f == 0){
        printf("All tests returned no error!\n\n");
    }else{
        printf("%d tests failed :(\n\n", f);
    }
}

int error_calculate(double predicted, double expected){
    
    // return 0 if difference between v and w is less than PRECISION
    double dx;
    dx = fabs(predicted - expected) / expected;
    if (dx < PRECISION){
        return 0;
    } else {
        printf("\n\n!!!!!!!!!!\nDeviation!\n%f | %f | %f\n!!!!!!!!!!\n\n", predicted, expected, dx);
        return 1;  // error!
    }
}

int test_line(){
    double expected;
    expected = 1.0;
    result r = line(N);
    printf("=== Unit line ===\n");
    printf("Length : %f (%f)\n ", r.volume, expected);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return error_calculate(r.volume, expected);
}


int test_circle(){
    double expected = 3.141592653589793;
    result r = circle(N);
    printf("=== Unit Circle ===\n");
    printf("Area : %f (%f)\n", r.volume, expected);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return error_calculate(r.volume, expected);
}


int test_cylinder(){
    double expected = 3.141592653589793;
    result r = cylinder(N);
    printf("=== Unit Cylinder ===\n");
    printf("Volume : %f (%f)\n", r.volume, expected);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return error_calculate(r.volume, expected);
}

int test_sphere(){
    double expected = 4.1887902047863905;
    result r = sphere(N);
    printf("=== Unit Sphere ===\n");
    printf("Volume : %f (%f)\n", r.volume, expected);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return error_calculate(r.volume, expected);
}


int test_hemisphere(){
    double expected = 2.0943951023931953;
    result r = hemisphere(N);
    printf("=== Unit hemisphere ===\n");
    printf("Volume : %f (%f)\n", r.volume, expected);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return error_calculate(r.volume, expected);
}


int test_square(){
    double expected;
    expected = 1.0;
    result r = square(N);
    printf("=== Unit Square ===\n");
    printf("Area : %f (%f)\n", r.volume, expected);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return error_calculate(r.volume, expected);
}

int test_cube(){
    double expected_volume;
    expected_volume = 1.0;
    result r = square(N);
    printf("=== Unit Cube ===\n");
    printf("Volume : %f (%f)\n", r.volume, expected_volume);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return error_calculate(r.volume, expected_volume);
}


int test_partial_torus(){
    double expected_volume;
    expected_volume = 22.194176;
    
    result r = partial_torus(N);
    printf("=== Partial Torus ===\n");
    printf("Volume : %f (%f)\n", r.volume, expected_volume);
    printf("COM (%f, %f, %f)\n", r.COM.x, r.COM.y, r.COM.z);

    return error_calculate(r.volume, expected_volume);
}

int run_tests(){
    /* returns 0 if all tests pass */
    int fail = 0;
    fail += test_line();
    fail += test_square();
    fail += test_cube();
    fail += test_circle();
    fail += test_cylinder();
    fail += test_sphere();
    fail += test_hemisphere();
    fail += test_partial_torus();
    return fail;
}