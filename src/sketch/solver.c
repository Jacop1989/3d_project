#include "solver.h"
#include <math.h>

void solver_init(Solver *s) {
    s->point_count = 0;
    s->line_count = 0;
    s->circle_count = 0;
    s->constraint_count = 0;
}

Point2D *solver_add_point(Solver *s, double x, double y) {
    Point2D p = {x, y};
    s->points[s->point_count] = p;
    return &s->points[s->point_count++];
}

Line2D *solver_add_line(Solver *s, Point2D p1, Point2D p2) {
    Line2D l = {p1, p2};
    s->lines[s->line_count] = l;
    return &s->lines[s->line_count++];
}

Circle2D *solver_add_circle(Solver *s, Point2D c, double r) {
    Circle2D circ = {c, r};
    s->circles[s->circle_count] = circ;
    return &s->circles[s->circle_count++];
}

void solver_add_constraint(Solver *s, ConstraintType type, void *a, void *b, double value) {
    Constraint c = {type, a, b, value};
    s->constraints[s->constraint_count++] = c;
}

static void apply_constraint(Constraint *c) {
    switch (c->type) {
    case CONSTRAINT_HORIZONTAL: {
        Line2D *l = (Line2D *)c->a;
        double avg = (l->p1.y + l->p2.y) / 2.0;
        l->p1.y = l->p2.y = avg;
        break;
    }
    case CONSTRAINT_VERTICAL: {
        Line2D *l = (Line2D *)c->a;
        double avg = (l->p1.x + l->p2.x) / 2.0;
        l->p1.x = l->p2.x = avg;
        break;
    }
    case CONSTRAINT_PARALLEL: {
        Line2D *l1 = (Line2D *)c->a;
        Line2D *l2 = (Line2D *)c->b;
        double dx = l1->p2.x - l1->p1.x;
        double dy = l1->p2.y - l1->p1.y;
        l2->p2.x = l2->p1.x + dx;
        l2->p2.y = l2->p1.y + dy;
        break;
    }
    case CONSTRAINT_PERPENDICULAR: {
        Line2D *l1 = (Line2D *)c->a;
        Line2D *l2 = (Line2D *)c->b;
        double dx = l1->p2.x - l1->p1.x;
        double dy = l1->p2.y - l1->p1.y;
        l2->p2.x = l2->p1.x - dy;
        l2->p2.y = l2->p1.y + dx;
        break;
    }
    case CONSTRAINT_COINCIDENT: {
        Point2D *p1 = (Point2D *)c->a;
        Point2D *p2 = (Point2D *)c->b;
        p2->x = p1->x;
        p2->y = p1->y;
        break;
    }
    case CONSTRAINT_DISTANCE: {
        Point2D *p1 = (Point2D *)c->a;
        Point2D *p2 = (Point2D *)c->b;
        double dx = p2->x - p1->x;
        double dy = p2->y - p1->y;
        double len = sqrt(dx * dx + dy * dy);
        if (len != 0.0) {
            double scale = c->value / len;
            p2->x = p1->x + dx * scale;
            p2->y = p1->y + dy * scale;
        }
        break;
    }
    }
}

void solver_solve(Solver *s) {
    for (int i = 0; i < s->constraint_count; ++i) {
        apply_constraint(&s->constraints[i]);
    }
}
