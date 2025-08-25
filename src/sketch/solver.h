#pragma once
#include "entity2d.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SOLVER_MAX_ENTITIES 64
#define SOLVER_MAX_CONSTRAINTS 64

typedef enum {
    CONSTRAINT_HORIZONTAL,
    CONSTRAINT_VERTICAL,
    CONSTRAINT_PARALLEL,
    CONSTRAINT_PERPENDICULAR,
    CONSTRAINT_COINCIDENT,
    CONSTRAINT_DISTANCE
} ConstraintType;

typedef struct {
    ConstraintType type;
    void *a;
    void *b;
    double value;
} Constraint;

typedef struct {
    Point2D points[SOLVER_MAX_ENTITIES];
    int point_count;
    Line2D lines[SOLVER_MAX_ENTITIES];
    int line_count;
    Circle2D circles[SOLVER_MAX_ENTITIES];
    int circle_count;
    Constraint constraints[SOLVER_MAX_CONSTRAINTS];
    int constraint_count;
} Solver;

void solver_init(Solver *s);
Point2D *solver_add_point(Solver *s, double x, double y);
Line2D *solver_add_line(Solver *s, Point2D p1, Point2D p2);
Circle2D *solver_add_circle(Solver *s, Point2D c, double r);
void solver_add_constraint(Solver *s, ConstraintType type, void *a, void *b, double value);
void solver_solve(Solver *s);

#ifdef __cplusplus
}
#endif
