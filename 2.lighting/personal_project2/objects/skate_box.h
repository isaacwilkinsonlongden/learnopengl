#ifndef RAMP_STAIRS_H
#define RAMP_STAIRS_H
 
// A solid combo box: a sloped ramp on one end, a flat platform in the
// middle, and a staircase on the other end (tread 5's top quad was
// intentionally left out, leaving one degenerate zero-area triangle as
// a placeholder -- fine as-is, it just doesn't draw anything).
//
// Local dimensions:
//   width  = 3 units    (x: -1.5 to 1.5)
//   height = 0.8 units  (y: 0 to 0.8)
//   length = 6 units    (z: 0 to 6)
//     - ramp:     z 0 -> 2   (rises from y=0 to y=0.8)
//     - platform: z 2 -> 5   (flat top, y=0.8)
//     - stairs:   z 5 -> 6   (steps, 0.2 run / 0.16 rise each, down to y=0)
//
// Total vertex count: 135 (non-indexed, GL_TRIANGLES, 45 triangles)
// Layout matches setupObjectBuffers(): 3 floats position + 3 floats normal
// + 2 floats texcoord, stride 8 floats.
//
// Normals are flat (per-face, not smoothed) and were derived per-triangle:
// axis-aligned faces (left/right walls, tops, risers) got their outward
// axis normal directly; the sloped ramp face's normal was computed via
// cross product. Note the original vertex winding was NOT consistent
// across sections (the right-side wall used the opposite winding from
// everything else), so a naive normalize(cross(B-A, C-A)) per triangle
// would have pointed several faces inward -- this was corrected here.
 
inline float skateBoxVertices[] = {
    // ---- ramp top (sloped) ----
    -1.5f, 0.0f, 0.0f,   0.0f, 0.9285f, -0.3714f,   0.0f, 0.0f,
     1.5f, 0.0f, 0.0f,   0.0f, 0.9285f, -0.3714f,   3.0f, 0.0f,
     1.5f, 0.8f, 2.0f,   0.0f, 0.9285f, -0.3714f,   3.0f, 2.0f,
     1.5f, 0.8f, 2.0f,   0.0f, 0.9285f, -0.3714f,   3.0f, 2.0f,
    -1.5f, 0.8f, 2.0f,   0.0f, 0.9285f, -0.3714f,   0.0f, 2.0f,
    -1.5f, 0.0f, 0.0f,   0.0f, 0.9285f, -0.3714f,   0.0f, 0.0f,
 
    // ---- platform top (flat) ----
    -1.5f, 0.8f, 2.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.8f, 2.0f,   0.0f, 1.0f, 0.0f,   3.0f, 0.0f,
     1.5f, 0.8f, 5.0f,   0.0f, 1.0f, 0.0f,   3.0f, 3.0f,
     1.5f, 0.8f, 5.0f,   0.0f, 1.0f, 0.0f,   3.0f, 3.0f,
    -1.5f, 0.8f, 5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 3.0f,
    -1.5f, 0.8f, 2.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
 
    // ---- tread 1 (y=0.64) ----
    -1.5f, 0.64f, 5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.64f, 5.0f,   0.0f, 1.0f, 0.0f,   3.0f, 0.0f,
     1.5f, 0.64f, 5.2f,   0.0f, 1.0f, 0.0f,   3.0f, 0.2f,
     1.5f, 0.64f, 5.2f,   0.0f, 1.0f, 0.0f,   3.0f, 0.2f,
    -1.5f, 0.64f, 5.2f,   0.0f, 1.0f, 0.0f,   0.0f, 0.2f,
    -1.5f, 0.64f, 5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
 
    // ---- tread 2 (y=0.48) ----
    -1.5f, 0.48f, 5.2f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.48f, 5.2f,   0.0f, 1.0f, 0.0f,   3.0f, 0.0f,
     1.5f, 0.48f, 5.4f,   0.0f, 1.0f, 0.0f,   3.0f, 0.2f,
     1.5f, 0.48f, 5.4f,   0.0f, 1.0f, 0.0f,   3.0f, 0.2f,
    -1.5f, 0.48f, 5.4f,   0.0f, 1.0f, 0.0f,   0.0f, 0.2f,
    -1.5f, 0.48f, 5.2f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
 
    // ---- tread 3 (y=0.32) ----
    -1.5f, 0.32f, 5.4f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.32f, 5.4f,   0.0f, 1.0f, 0.0f,   3.0f, 0.0f,
     1.5f, 0.32f, 5.6f,   0.0f, 1.0f, 0.0f,   3.0f, 0.2f,
     1.5f, 0.32f, 5.6f,   0.0f, 1.0f, 0.0f,   3.0f, 0.2f,
    -1.5f, 0.32f, 5.6f,   0.0f, 1.0f, 0.0f,   0.0f, 0.2f,
    -1.5f, 0.32f, 5.4f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
 
    // ---- tread 4 (y=0.16) ----
    -1.5f, 0.16f, 5.6f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.16f, 5.6f,   0.0f, 1.0f, 0.0f,   3.0f, 0.0f,
     1.5f, 0.16f, 5.8f,   0.0f, 1.0f, 0.0f,   3.0f, 0.2f,
     1.5f, 0.16f, 5.8f,   0.0f, 1.0f, 0.0f,   3.0f, 0.2f,
    -1.5f, 0.16f, 5.8f,   0.0f, 1.0f, 0.0f,   0.0f, 0.2f,
    -1.5f, 0.16f, 5.6f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
 
    // ---- tread 5 (y=
     1.5f, 0.0f, 6.0f,   0.0f, 1.0f, 0.0f,   3.0f, 0.2f,
     1.5f, 0.0f, 6.0f,   0.0f, 1.0f, 0.0f,   3.0f, 0.2f,
    -1.5f, 0.0f, 6.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.2f,
 
    // ---- riser 1 (z=5.0) ----
    -1.5f, 0.64f, 5.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     1.5f, 0.64f, 5.0f,   0.0f, 0.0f, 1.0f,   3.0f, 0.0f,
     1.5f, 0.8f, 5.0f,   0.0f, 0.0f, 1.0f,   3.0f, 0.16f,
     1.5f, 0.8f, 5.0f,   0.0f, 0.0f, 1.0f,   3.0f, 0.16f,
    -1.5f, 0.8f, 5.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.16f,
    -1.5f, 0.64f, 5.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
 
    // ---- riser 2 (z=5.2) ----
    -1.5f, 0.48f, 5.2f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     1.5f, 0.48f, 5.2f,   0.0f, 0.0f, 1.0f,   3.0f, 0.0f,
     1.5f, 0.64f, 5.2f,   0.0f, 0.0f, 1.0f,   3.0f, 0.16f,
     1.5f, 0.64f, 5.2f,   0.0f, 0.0f, 1.0f,   3.0f, 0.16f,
    -1.5f, 0.64f, 5.2f,   0.0f, 0.0f, 1.0f,   0.0f, 0.16f,
    -1.5f, 0.48f, 5.2f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
 
    // ---- riser 3 (z=5.4) ----
    -1.5f, 0.32f, 5.4f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     1.5f, 0.32f, 5.4f,   0.0f, 0.0f, 1.0f,   3.0f, 0.0f,
     1.5f, 0.48f, 5.4f,   0.0f, 0.0f, 1.0f,   3.0f, 0.16f,
     1.5f, 0.48f, 5.4f,   0.0f, 0.0f, 1.0f,   3.0f, 0.16f,
    -1.5f, 0.48f, 5.4f,   0.0f, 0.0f, 1.0f,   0.0f, 0.16f,
    -1.5f, 0.32f, 5.4f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
 
    // ---- riser 4 (z=5.6) ----
    -1.5f, 0.16f, 5.6f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     1.5f, 0.16f, 5.6f,   0.0f, 0.0f, 1.0f,   3.0f, 0.0f,
     1.5f, 0.32f, 5.6f,   0.0f, 0.0f, 1.0f,   3.0f, 0.16f,
     1.5f, 0.32f, 5.6f,   0.0f, 0.0f, 1.0f,   3.0f, 0.16f,
    -1.5f, 0.32f, 5.6f,   0.0f, 0.0f, 1.0f,   0.0f, 0.16f,
    -1.5f, 0.16f, 5.6f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
 
    // ---- riser 5 (z=5.8) ----
    -1.5f, 0.0f, 5.8f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
     1.5f, 0.0f, 5.8f,   0.0f, 0.0f, 1.0f,   3.0f, 0.0f,
     1.5f, 0.16f, 5.8f,   0.0f, 0.0f, 1.0f,   3.0f, 0.16f,
     1.5f, 0.16f, 5.8f,   0.0f, 0.0f, 1.0f,   3.0f, 0.16f,
    -1.5f, 0.16f, 5.8f,   0.0f, 0.0f, 1.0f,   0.0f, 0.16f,
    -1.5f, 0.0f, 5.8f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
 
    // ---- left side profile (x=-1.5), fan-triangulated from the front-bottom corner ----
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.8f, 2.0f,   -1.0f, 0.0f, 0.0f,   2.0f, 0.8f,
    -1.5f, 0.8f, 5.0f,   -1.0f, 0.0f, 0.0f,   5.0f, 0.8f,
 
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.8f, 5.0f,   -1.0f, 0.0f, 0.0f,   5.0f, 0.8f,
    -1.5f, 0.64f, 5.0f,   -1.0f, 0.0f, 0.0f,   5.0f, 0.64f,
 
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.64f, 5.0f,   -1.0f, 0.0f, 0.0f,   5.0f, 0.64f,
    -1.5f, 0.64f, 5.2f,   -1.0f, 0.0f, 0.0f,   5.2f, 0.64f,
 
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.64f, 5.2f,   -1.0f, 0.0f, 0.0f,   5.2f, 0.64f,
    -1.5f, 0.48f, 5.2f,   -1.0f, 0.0f, 0.0f,   5.2f, 0.48f,
 
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.48f, 5.2f,   -1.0f, 0.0f, 0.0f,   5.2f, 0.48f,
    -1.5f, 0.48f, 5.4f,   -1.0f, 0.0f, 0.0f,   5.4f, 0.48f,
 
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.48f, 5.4f,   -1.0f, 0.0f, 0.0f,   5.4f, 0.48f,
    -1.5f, 0.32f, 5.4f,   -1.0f, 0.0f, 0.0f,   5.4f, 0.32f,
 
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.32f, 5.4f,   -1.0f, 0.0f, 0.0f,   5.4f, 0.32f,
    -1.5f, 0.32f, 5.6f,   -1.0f, 0.0f, 0.0f,   5.6f, 0.32f,
 
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.32f, 5.6f,   -1.0f, 0.0f, 0.0f,   5.6f, 0.32f,
    -1.5f, 0.16f, 5.6f,   -1.0f, 0.0f, 0.0f,   5.6f, 0.16f,
 
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.16f, 5.6f,   -1.0f, 0.0f, 0.0f,   5.6f, 0.16f,
    -1.5f, 0.16f, 5.8f,   -1.0f, 0.0f, 0.0f,   5.8f, 0.16f,
 
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.16f, 5.8f,   -1.0f, 0.0f, 0.0f,   5.8f, 0.16f,
    -1.5f, 0.0f, 5.8f,   -1.0f, 0.0f, 0.0f,   5.8f, 0.0f,
 
    -1.5f, 0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.5f, 0.0f, 5.8f,   -1.0f, 0.0f, 0.0f,   5.8f, 0.0f,
    -1.5f, 0.0f, 6.0f,   -1.0f, 0.0f, 0.0f,   6.0f, 0.0f,
 
    // ---- right side profile (x=1.5), same fan pattern ----
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.8f, 2.0f,   1.0f, 0.0f, 0.0f,   2.0f, 0.8f,
     1.5f, 0.8f, 5.0f,   1.0f, 0.0f, 0.0f,   5.0f, 0.8f,
 
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.8f, 5.0f,   1.0f, 0.0f, 0.0f,   5.0f, 0.8f,
     1.5f, 0.64f, 5.0f,   1.0f, 0.0f, 0.0f,   5.0f, 0.64f,
 
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.64f, 5.0f,   1.0f, 0.0f, 0.0f,   5.0f, 0.64f,
     1.5f, 0.64f, 5.2f,   1.0f, 0.0f, 0.0f,   5.2f, 0.64f,
 
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.64f, 5.2f,   1.0f, 0.0f, 0.0f,   5.2f, 0.64f,
     1.5f, 0.48f, 5.2f,   1.0f, 0.0f, 0.0f,   5.2f, 0.48f,
 
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.48f, 5.2f,   1.0f, 0.0f, 0.0f,   5.2f, 0.48f,
     1.5f, 0.48f, 5.4f,   1.0f, 0.0f, 0.0f,   5.4f, 0.48f,
 
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.48f, 5.4f,   1.0f, 0.0f, 0.0f,   5.4f, 0.48f,
     1.5f, 0.32f, 5.4f,   1.0f, 0.0f, 0.0f,   5.4f, 0.32f,
 
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.32f, 5.4f,   1.0f, 0.0f, 0.0f,   5.4f, 0.32f,
     1.5f, 0.32f, 5.6f,   1.0f, 0.0f, 0.0f,   5.6f, 0.32f,
 
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.32f, 5.6f,   1.0f, 0.0f, 0.0f,   5.6f, 0.32f,
     1.5f, 0.16f, 5.6f,   1.0f, 0.0f, 0.0f,   5.6f, 0.16f,
 
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.16f, 5.6f,   1.0f, 0.0f, 0.0f,   5.6f, 0.16f,
     1.5f, 0.16f, 5.8f,   1.0f, 0.0f, 0.0f,   5.8f, 0.16f,
 
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.16f, 5.8f,   1.0f, 0.0f, 0.0f,   5.8f, 0.16f,
     1.5f, 0.0f, 5.8f,   1.0f, 0.0f, 0.0f,   5.8f, 0.0f,
 
     1.5f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.5f, 0.0f, 5.8f,   1.0f, 0.0f, 0.0f,   5.8f, 0.0f,
     1.5f, 0.0f, 6.0f,   1.0f, 0.0f, 0.0f,   6.0f, 0.0f,
};
 
#endif