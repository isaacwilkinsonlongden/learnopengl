#ifndef LIGHT_HANGER_H
#define LIGHT_HANGER_H

// A thin vertical metal rod suspending the light fixture from the ceiling.
// One mesh, drawn twice -- once above each of the two outer point lights.
//
// Defined in the SAME local space as light_bar.h and light_frame.h (origin at
// the bar's centre), so translating by lightPositions[1] or lightPositions[2]
// drops it directly above that light: those two lights share the bar's
// y = 2.0, so the local y range below lands where it should in world space.
//
//   section: x +/-0.03, z +/-0.03   (0.06 square, matching the frame's band
//                                  thickness so the fixture reads as one piece)
//   local y: 0.02 .. 0.51        -> world y 2.02 .. 2.51
//
// Both ends deliberately overlap what they meet rather than stopping flush:
// the bottom sits inside the bar (whose top is at y 2.05) and the top pokes
// just past the ceiling plane (y 2.5). That hides both end caps and, more
// importantly, avoids putting either cap coplanar with an existing surface,
// which would z-fight. The caps are kept anyway -- 4 triangles, and it leaves
// the rod a closed solid.
//
// NOTE: the 0.49-unit length is baked in, and assumes the bar sits at y = 2.0
// beneath a ceiling at y = 2.5. Moving the bar vertically means regenerating
// these numbers.
//
// As with room.h, skate_box.h and light_frame.h, winding is not uniform across
// faces, so normals are assigned explicitly per named face rather than derived
// from a cross product.
//
// Texcoords come from local-space position at 1 repeat per unit -- the same
// scale used by light_frame.h and room.h, keeping texel density consistent
// across the whole fixture.
//
// Layout: 3 floats position + 3 floats normal + 2 floats texcoord, stride 8
// floats (matches setupBuffers(..., lit = true)). 6 faces / 12 triangles /
// 36 vertices.

inline float lightHangerVertices[] = {
    // front (+z)
     -0.030f,   0.020f,   0.030f,   0.000f,   0.000f,   1.000f,  -0.030f,   0.020f,
      0.030f,   0.020f,   0.030f,   0.000f,   0.000f,   1.000f,   0.030f,   0.020f,
      0.030f,   0.510f,   0.030f,   0.000f,   0.000f,   1.000f,   0.030f,   0.510f,
      0.030f,   0.510f,   0.030f,   0.000f,   0.000f,   1.000f,   0.030f,   0.510f,
     -0.030f,   0.510f,   0.030f,   0.000f,   0.000f,   1.000f,  -0.030f,   0.510f,
     -0.030f,   0.020f,   0.030f,   0.000f,   0.000f,   1.000f,  -0.030f,   0.020f,

    // back (-z)
     -0.030f,   0.020f,  -0.030f,   0.000f,   0.000f,  -1.000f,  -0.030f,   0.020f,
      0.030f,   0.020f,  -0.030f,   0.000f,   0.000f,  -1.000f,   0.030f,   0.020f,
      0.030f,   0.510f,  -0.030f,   0.000f,   0.000f,  -1.000f,   0.030f,   0.510f,
      0.030f,   0.510f,  -0.030f,   0.000f,   0.000f,  -1.000f,   0.030f,   0.510f,
     -0.030f,   0.510f,  -0.030f,   0.000f,   0.000f,  -1.000f,  -0.030f,   0.510f,
     -0.030f,   0.020f,  -0.030f,   0.000f,   0.000f,  -1.000f,  -0.030f,   0.020f,

    // right (+x)
      0.030f,   0.020f,  -0.030f,   1.000f,   0.000f,   0.000f,  -0.030f,   0.020f,
      0.030f,   0.020f,   0.030f,   1.000f,   0.000f,   0.000f,   0.030f,   0.020f,
      0.030f,   0.510f,   0.030f,   1.000f,   0.000f,   0.000f,   0.030f,   0.510f,
      0.030f,   0.510f,   0.030f,   1.000f,   0.000f,   0.000f,   0.030f,   0.510f,
      0.030f,   0.510f,  -0.030f,   1.000f,   0.000f,   0.000f,  -0.030f,   0.510f,
      0.030f,   0.020f,  -0.030f,   1.000f,   0.000f,   0.000f,  -0.030f,   0.020f,

    // left (-x)
     -0.030f,   0.020f,  -0.030f,  -1.000f,   0.000f,   0.000f,  -0.030f,   0.020f,
     -0.030f,   0.020f,   0.030f,  -1.000f,   0.000f,   0.000f,   0.030f,   0.020f,
     -0.030f,   0.510f,   0.030f,  -1.000f,   0.000f,   0.000f,   0.030f,   0.510f,
     -0.030f,   0.510f,   0.030f,  -1.000f,   0.000f,   0.000f,   0.030f,   0.510f,
     -0.030f,   0.510f,  -0.030f,  -1.000f,   0.000f,   0.000f,  -0.030f,   0.510f,
     -0.030f,   0.020f,  -0.030f,  -1.000f,   0.000f,   0.000f,  -0.030f,   0.020f,

    // top cap (hidden above the ceiling)
     -0.030f,   0.510f,  -0.030f,   0.000f,   1.000f,   0.000f,  -0.030f,  -0.030f,
      0.030f,   0.510f,  -0.030f,   0.000f,   1.000f,   0.000f,   0.030f,  -0.030f,
      0.030f,   0.510f,   0.030f,   0.000f,   1.000f,   0.000f,   0.030f,   0.030f,
      0.030f,   0.510f,   0.030f,   0.000f,   1.000f,   0.000f,   0.030f,   0.030f,
     -0.030f,   0.510f,   0.030f,   0.000f,   1.000f,   0.000f,  -0.030f,   0.030f,
     -0.030f,   0.510f,  -0.030f,   0.000f,   1.000f,   0.000f,  -0.030f,  -0.030f,

    // bottom cap (hidden inside the bar)
     -0.030f,   0.020f,  -0.030f,   0.000f,  -1.000f,   0.000f,  -0.030f,  -0.030f,
      0.030f,   0.020f,  -0.030f,   0.000f,  -1.000f,   0.000f,   0.030f,  -0.030f,
      0.030f,   0.020f,   0.030f,   0.000f,  -1.000f,   0.000f,   0.030f,   0.030f,
      0.030f,   0.020f,   0.030f,   0.000f,  -1.000f,   0.000f,   0.030f,   0.030f,
     -0.030f,   0.020f,   0.030f,   0.000f,  -1.000f,   0.000f,  -0.030f,   0.030f,
     -0.030f,   0.020f,  -0.030f,   0.000f,  -1.000f,   0.000f,  -0.030f,  -0.030f,
};

#endif
