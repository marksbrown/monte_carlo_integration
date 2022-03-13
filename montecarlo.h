#include <stdio.h>
#include <math.h>

// typedefs
typedef struct point
{
  double x;
  double y;
  double z;
} point;

typedef struct limit
{
    double l;  // lower
    double h;  // higher
} limit;

typedef struct lim3D
{
    limit x;
    limit y;
    limit z;
} lim3D;

typedef struct initial_conditions
{
    int (*condition)(point *);  // condition if within volume
    void (*next_point)(point *, lim3D *);  // how to get next point
    lim3D limits;  // cuboid dimensions to generate points within
} mc;

typedef struct result
{
    point COM;  // centre of mass
    double volume;  // estimated volume
} result;

// Prototypes
int checkzero(double v, double e);  // assume close to zero is zero

double random_double();
double random_scaled(limit lim);
void randomise_point(point *p_point, lim3D *lim);
void update_point(point *p_point, lim3D *lim);
point calculate_elementals(lim3D *lims);
double calculate_cuboid_volume(lim3D *lims);
// prototypes for points
point dimensions(lim3D *lim);
void add(point *self, point *other);
void scale_point(point *apoint, double v);
void set_to_origin(point *apoint);

result com_monte_carlo(int N, mc *initial_conditions);  // important bit

// functions

double random_double()
{
// generate the next random number from the seed, updates the seed and
// returns the seed scaled to a double between 0 (exclusive) and 1 (inclusive)
// some constants that have historically often been used for this method
static const int a = 16807;
static const int c = 0;
static const long long m = 2147483647;
// a random ’seed’ value. Pick any nonzero number for a different
// random series.
static long long seed = 1;
seed = (a * seed + c) % m;
// scale the updated value by first typecasting it to a floating point,
// turning the division into a floating point division
return ((double) seed) / m;
}

double random_scaled(limit lim){
    /*
    Generate a random number between lower and higher
    */
    return random_double() * (lim.h - lim.l) + lim.l;
}

point calculate_elementals(lim3D *lims){
    point apoint;
    apoint.x = lims->x.h - lims->x.l;
    apoint.y = lims->y.h - lims->y.l;
    apoint.z = lims->z.h - lims->z.l;
    return apoint;    
}

point dimensions(lim3D *lim){
    // determine number of dimensions in limits
    point dE = calculate_elementals(lim);
    double e;
    e = (double) 1E-9;
    
    if (checkzero(dE.x, e) == 0){
        dE.x = 0;
    }
    if (checkzero(dE.y, e) == 0){
        dE.y = 0;
    }
    if (checkzero(dE.z, e) != 0){
        dE.z = 0;
    }
    return dE;
}

void randomise_point(point *p_point, lim3D *lim)
{
    // randomise between 0 and 1 for all coordinates
    p_point->x = random_scaled(lim->x);  
    p_point->y = random_scaled(lim->y); 
    p_point->z = random_scaled(lim->z);
}

void add(point *self, point *other){
    self->x += other->x;
    self->y += other->y;
    self->z += other->z;
}

void scale_point(point *apoint, double v){
    apoint->x *= v;
    apoint->y *= v;
    apoint->z *= v;
}

void set_to_origin(point *apoint){
    apoint->x = 0;
    apoint->y = 0;
    apoint->z = 0;
}

int checkzero(double v, double e){
    if (fabs(v) < e){
        return 1;
    } else{
        return 0;
    }
}

double calculate_cuboid_volume(lim3D *lims){
    /*
    Line (only in x)
    Area (only in XY)
    Volume Otherwise
    */
    point de = calculate_elementals(lims);
    double e = (double) 1E-9;
    if (checkzero(de.z, e) == 1 && checkzero(de.y, e) == 0)
    {   
        return de.x * de.y;
    }
    else if (checkzero(de.z, e) == 1 && checkzero(de.y, e) == 1)
    {   
        return de.x;
    }
    else
    {
        return de.x * de.y * de.z;
    }
}
static int j;

result com_monte_carlo(int N, mc *initial_conditions){
    /*
    Determine Centre of Mass (assuming uniform density)
    */
    
    point apoint, com;
    set_to_origin(&com);
    double V = calculate_cuboid_volume(&initial_conditions->limits);
    extern int j;  // can be used to generate points deterministically
    int points_matching_condition;
    points_matching_condition = 0;

    int not_matching;
    not_matching = 0;
    for (j = 0; j < N; j++){
        (*initial_conditions->next_point)(&apoint, &initial_conditions->limits);
        if ((*initial_conditions->condition)(&apoint)){ 
            add(&com, &apoint);
            points_matching_condition += 1;
        } else {
            not_matching += 1;
        }
    }
    
    
    result r;
    r.volume =  (double) points_matching_condition / N * V;
    scale_point(&com, (double) 1./ points_matching_condition);
    r.COM = com;
    return r;
}



