#pragma once
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    double x;
    double y;
} Point2D;

typedef struct {
    Point2D p1;
    Point2D p2;
} Line2D;

typedef struct {
    Point2D center;
    double radius;
} Circle2D;

Point2D point2d(double x, double y);
Line2D line2d(Point2D p1, Point2D p2);
Circle2D circle2d(Point2D c, double r);

#ifdef __cplusplus
}
#endif
