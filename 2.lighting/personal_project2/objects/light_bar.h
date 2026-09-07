#ifndef LIGHT_BAR_H
#define LIGHT_BAR_H

// A thin rectangular bar representing the room's light source, rendered with
// light_shader.vs/fs as a single flat, unlit color (lightColor) rather than
// being lit itself -- so unlike room.h/skate_box.h, it has no normals or
// texcoords, just raw positions.
//
// Local dimensions: width = 1 unit (x: -0.5 to 0.5), height = 0.1 units
// (y: -0.05 to 0.05), length = 5 units (z: -2.5 to 2.5).
//
// Layout: 3 floats position only, stride 3 floats (matches setupLightBuffers()).

inline float lightVertices[] = {
    // back wall
    -0.5f,  0.05f, -2.5f,
     0.5f,  0.05f, -2.5f,
     0.5f, -0.05f, -2.5f,
     0.5f, -0.05f, -2.5f,
    -0.5f, -0.05f, -2.5f,
    -0.5f,  0.05f, -2.5f,

    // front wall
    -0.5f,  0.05f,  2.5f,
     0.5f,  0.05f,  2.5f,
     0.5f, -0.05f,  2.5f,
     0.5f, -0.05f,  2.5f,
    -0.5f, -0.05f,  2.5f,
    -0.5f,  0.05f,  2.5f,

    // left wall
    -0.5f,  0.05f, -2.5f,
    -0.5f,  0.05f,  2.5f,
    -0.5f, -0.05f,  2.5f,
    -0.5f, -0.05f,  2.5f,
    -0.5f, -0.05f, -2.5f,
    -0.5f,  0.05f, -2.5f,

    // right wall
     0.5f,  0.05f, -2.5f,
     0.5f,  0.05f,  2.5f,
     0.5f, -0.05f,  2.5f,
     0.5f, -0.05f,  2.5f,
     0.5f, -0.05f, -2.5f,
     0.5f,  0.05f, -2.5f,

    // ceiling
    -0.5f,  0.05f, -2.5f,
     0.5f,  0.05f, -2.5f,
     0.5f,  0.05f,  2.5f,
     0.5f,  0.05f,  2.5f,
    -0.5f,  0.05f,  2.5f,
    -0.5f,  0.05f, -2.5f,

    // floor
    -0.5f, -0.05f, -2.5f,
     0.5f, -0.05f, -2.5f,
     0.5f, -0.05f,  2.5f,
     0.5f, -0.05f,  2.5f,
    -0.5f, -0.05f,  2.5f,
    -0.5f, -0.05f, -2.5f,
};

#endif