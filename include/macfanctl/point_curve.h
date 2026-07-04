#ifndef _CURVE_POINT_H
#define _CURVE_POINT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef MAX_CURVE_POINTS
#   define MAX_CURVE_POINTS 16
#endif

typedef struct {
    uint16_t temperature;
    uint16_t roundPerMinute;
    uint16_t interpolationTimeMiliseconds;
} CurvePoint;

typedef struct {
    CurvePoint pCurvePoints[MAX_CURVE_POINTS];
    uint32_t uCurvePoints;
} CurveGraph;

CurveGraph create_curve_graph();

int compare_curve_points(const void* a, const void* b);

bool insert_curve_point(CurveGraph* graph, CurvePoint point);

void finalize_curve_graph(CurveGraph* graph);

size_t get_floor_curve_point_from_graph(CurveGraph* graph, uint16_t temperature);

#endif