

int line_condition(point *apoint){
    if (apoint->x > -0.5 && apoint->x <= 0.5){
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

int cylinder_condition(point *apoint){
    // unit cylinder centred on origin aligned to z axis
    double r;
    r = pow(apoint->x, 2) + pow(apoint->y, 2);
    if (r <= 1 && apoint->z > -0.5 && apoint->z <= 0.5){
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

int hemisphere_condition (point *apoint){
    // unit hemisphere centred on (1,1,0) pointing along the z axis
    double r;
    r = pow(apoint->x - 1, 2) + pow(apoint->y - 1, 2) + pow(apoint->z, 2);
    if (r <= 1 && apoint->z >= 0){
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
    // unit cube centred on origin
    if (apoint->x > -0.5 && apoint->x <= 0.5 && 
        apoint->y > -0.5 && apoint->y <= 0.5 && 
        apoint->z > -0.5 && apoint->z <= 0.5){
        return 1;
    } else {
        return 0;
    }
}


int partial_torus_condition(point *apoint){

    double x = apoint->x;
    double y = apoint->y;
    double z = apoint->z;

    double R = pow(x, 2) + pow(y, 2);
    double r = pow(z, 2) + pow(pow(R, 0.5) - 3, 2);
    if (x >= 1 && y >= -3 && r <= 1){
        return 1;
    }else {
        return 0;
    }
}

// Examples


result line(int N){
    // unit line
    mc line;
    line.condition = line_condition;
    line.next_point = randomise_point;
    
    line.limits.x.l = -1;
    line.limits.x.h = 1;
    line.limits.y.l = 0;
    line.limits.y.h = 0;
    line.limits.z.l = 0;
    line.limits.z.h = 0;
    
    return com_monte_carlo(N, &line);
}


result circle(int N){
    // unit circle in XY plane centred on (1,1,0)
    mc circle;
    circle.condition = circle_condition;
    circle.next_point = randomise_point;
    
    circle.limits.x.l = 0;
    circle.limits.x.h = 2;
    circle.limits.y.l = 0;
    circle.limits.y.h = 2;
    circle.limits.z.l = 0;
    circle.limits.z.h = 0;
    return com_monte_carlo(N, &circle);
}


result cylinder(int N){
// unit cylinder centred on (0,0) along z axis between -0.5 and 0.5
    mc cylinder;
    cylinder.condition = cylinder_condition;
    cylinder.next_point = randomise_point;
    
    cylinder.limits.x.l = -1;
    cylinder.limits.x.h = 1;
    cylinder.limits.y.l = -1;
    cylinder.limits.y.h = 1;
    cylinder.limits.z.l = -1;
    cylinder.limits.z.h = 1;
    return com_monte_carlo(N, &cylinder);
}


result sphere(int N){
    // unit sphere centred on (1,1,1)
    mc sphere;
    sphere.condition = sphere_condition;
    sphere.next_point = randomise_point;
    
    sphere.limits.x.l = 0;
    sphere.limits.x.h = 2;
    sphere.limits.y.l = 0;
    sphere.limits.y.h = 2;
    sphere.limits.z.l = 0;
    sphere.limits.z.h = 2;

    return com_monte_carlo(N, &sphere);
}


result hemisphere(int N){
    // unit hemisphere centred on (1,1,1) pointing along z
    mc hemisphere;
    hemisphere.condition = hemisphere_condition;
    hemisphere.next_point = randomise_point;
    
    hemisphere.limits.x.l = 0;
    hemisphere.limits.x.h = 2;
    hemisphere.limits.y.l = 0;
    hemisphere.limits.y.h = 2;
    hemisphere.limits.z.l = 0;
    hemisphere.limits.z.h = 2;
    return com_monte_carlo(N, &hemisphere);
}


result square(int N){
    // unit square
    mc square;
    square.condition = square_condition;
    square.next_point = randomise_point;
    square.limits.x.l = 0;
    square.limits.x.h = 2;
    square.limits.y.l = 0;
    square.limits.y.h = 2;
    square.limits.z.l = 0;
    square.limits.z.h = 0;
    return com_monte_carlo(N, &square);
}


result cube(int N){
    // unit square
    mc cube;
    cube.condition = cube_condition;
    cube.next_point = randomise_point;
    cube.limits.x.l = -1;
    cube.limits.x.h = 1;
    cube.limits.y.l = -1;
    cube.limits.y.h = 1;
    cube.limits.z.l = -1;
    cube.limits.z.h = 1;
    
    return com_monte_carlo(N, &cube);
}

result partial_torus(int N){
    mc torus;
    torus.condition = partial_torus_condition;
    torus.next_point = randomise_point;
    
    torus.limits.x.l = -4;
    torus.limits.x.h = 4;
    torus.limits.y.l = -4;
    torus.limits.y.h = 4;
    torus.limits.z.l = -1;
    torus.limits.z.h = 1;
    
    return com_monte_carlo(N, &torus);
}

