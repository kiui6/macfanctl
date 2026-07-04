#include "curve_point.h"

CurveGraph create_curve_graph() {
    return (CurveGraph){0};
}

int compare_curve_points(const void* a, const void* b) {
    const CurvePoint* pa = (const CurvePoint*)a;
    const CurvePoint* pb = (const CurvePoint*)b;
    return (int)pa->temperature - (int)pb->temperature;
}

void insert_curve_point(CurveGraph* graph, CurvePoint point) {
    if (graph->uCurvePoints < MAX_CURVE_POINTS) {
        graph->pCurvePoints[graph->uCurvePoints] = point;
        graph->uCurvePoints = graph->uCurvePoints + 1;
    } else {
        // Log error
    }
}

void finalize_curve_graph(CurveGraph* graph) {
    qsort(graph->pCurvePoints, graph->uCurvePoints, sizeof(CurvePoint), compare_curve_points);
}

size_t get_floor_curve_point_from_graph(CurveGraph* graph, uint16_t temperature) {
    for(int i = 0; i < graph->uCurvePoints; i++) {
        if(graph->pCurvePoints[i].temperature > temperature) {
            return i;
        }
    }

    return graph->uCurvePoints;
}