#include "imgui_tweaker.hpp"


void AddLineDashed(
        ImDrawList* draw_list,
        const ImVec2& a, const ImVec2& b, ImU32 col, float thickness, unsigned int segments, unsigned int on_segments, unsigned int off_segments)
{
    if ((col >> 24) == 0)
        return;
    int on = 0, off = 0;
    ImVec2 dir = (b - a) / segments;
    for (int i = 0; i <= segments; i++)
    {
        ImVec2 point(a + dir * i);
        if (on < on_segments) {
            draw_list->_Path.push_back(point);
            on++;
        }
        else if (on == on_segments && off == 0) {
            draw_list->_Path.push_back(point);
            draw_list->PathStroke(col, false, thickness);
            off++;
        }
        else if (on == on_segments && off < off_segments) {
            off++;
        }
        else {
            draw_list->_Path.resize(0);
            draw_list->_Path.push_back(point);
            on = 1;
            off = 0;
        }
    }
    draw_list->PathStroke(col, false, thickness);
}

void PathArcToDashedAndStroke(
        ImDrawList* draw_list,
        const ImVec2& centre, float radius, float a_min, float a_max, ImU32 col, float thickness, int num_segments, int on_segments, int off_segments)
{
    if (radius == 0.0f)
        draw_list->_Path.push_back(centre);
    draw_list->_Path.reserve(draw_list->_Path.Size + (num_segments + 1));
    int on = 0, off = 0;
    for (int i = 0; i <= num_segments + 1; i++)
    {
        const float a = a_min + ((float)i / (float)num_segments) * (a_max - a_min);
        ImVec2 point(centre.x + cosf(a) * radius, centre.y + sinf(a) * radius);
        if (on < on_segments) {
            draw_list->_Path.push_back(point);
            on++;
        }
        else if (on == on_segments && off == 0) {
            draw_list-> _Path.push_back(point);
            draw_list->PathStroke(col, false, thickness);
            off++;
        }
        else if (on == on_segments && off < off_segments) {
            off++;
        }
        else {
            draw_list->_Path.resize(0);
            draw_list->_Path.push_back(point);
            on = 1;
            off = 0;
        }
    }
    draw_list->PathStroke(col, false, thickness);
}

void AddCircleDashed(
        ImDrawList* draw_list,
        const ImVec2& centre, float radius, ImU32 col, int num_segments, float thickness, int on_segments, int off_segments)
{
    if ((col >> 24) == 0 || on_segments == 0)
        return;

    const float a_max = IM_PI * 2.0f * ((float)num_segments - 1.0f) / (float)num_segments;
    PathArcToDashedAndStroke(draw_list, centre, radius - 0.5f, 0.0f, a_max, col, thickness, num_segments, on_segments, off_segments);
}