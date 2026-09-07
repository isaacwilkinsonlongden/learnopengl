#ifndef ROOM_H
#define ROOM_H
 
// An enclosed rectangular room (walls, floor, ceiling), viewed from the
// inside. Normals point INWARD (into the room's interior), since these
// surfaces are meant to be seen from inside the box rather than outside
// it -- the opposite convention from an exterior solid.
//
// Room interior bounds: x in (-10, 10), y in (-2.5, 2.5), z in (-5, 5)
//
// Layout: 3 floats position + 3 floats normal + 2 floats texcoord,
// stride 8 floats (matches setupObjectBuffers() from the lighting chapters --
// update glVertexAttribPointer offsets/stride accordingly).
//
// As with the skate box, per-triangle winding here is not uniform (e.g.
// front wall and back wall wind oppositely, as do floor/ceiling), so
// normals were assigned directly per named face (based on which axis is
// constant across each triangle) rather than trusted from a raw
// normalize(cross(B-A, C-A)) -- that would have produced outward normals
// on some faces and inward on others.
 
inline float wallVertices[] = {
    // back wall
    -10.0f, 2.5f, -5.0f,   0.0f, 0.0f, 1.0f,   0.0f, 3.0f,
     10.0f, 2.5f, -5.0f,   0.0f, 0.0f, 1.0f,   5.0f, 3.0f,
     10.0f, -2.5f, -5.0f,   0.0f, 0.0f, 1.0f,   5.0f, 0.0f,
     10.0f, -2.5f, -5.0f,   0.0f, 0.0f, 1.0f,   5.0f, 0.0f,
    -10.0f, -2.5f, -5.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -10.0f, 2.5f, -5.0f,   0.0f, 0.0f, 1.0f,   0.0f, 3.0f,
 
    // front wall
    -10.0f, 2.5f, 5.0f,   0.0f, 0.0f, -1.0f,   0.0f, 3.0f,
     10.0f, 2.5f, 5.0f,   0.0f, 0.0f, -1.0f,   5.0f, 3.0f,
     10.0f, -2.5f, 5.0f,   0.0f, 0.0f, -1.0f,   5.0f, 0.0f,
     10.0f, -2.5f, 5.0f,   0.0f, 0.0f, -1.0f,   5.0f, 0.0f,
    -10.0f, -2.5f, 5.0f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
    -10.0f, 2.5f, 5.0f,   0.0f, 0.0f, -1.0f,   0.0f, 3.0f,
 
    // left wall
    -10.0f, 2.5f, -5.0f,   1.0f, 0.0f, 0.0f,   0.0f, 3.0f,
    -10.0f, 2.5f, 5.0f,   1.0f, 0.0f, 0.0f,   2.5f, 3.0f,
    -10.0f, -2.5f, 5.0f,   1.0f, 0.0f, 0.0f,   2.5f, 0.0f,
    -10.0f, -2.5f, 5.0f,   1.0f, 0.0f, 0.0f,   2.5f, 0.0f,
    -10.0f, -2.5f, -5.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -10.0f, 2.5f, -5.0f,   1.0f, 0.0f, 0.0f,   0.0f, 3.0f,
 
    // right wall
     10.0f, 2.5f, -5.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 3.0f,
     10.0f, 2.5f, 5.0f,   -1.0f, 0.0f, 0.0f,   2.5f, 3.0f,
     10.0f, -2.5f, 5.0f,   -1.0f, 0.0f, 0.0f,   2.5f, 0.0f,
     10.0f, -2.5f, 5.0f,   -1.0f, 0.0f, 0.0f,   2.5f, 0.0f,
     10.0f, -2.5f, -5.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     10.0f, 2.5f, -5.0f,   -1.0f, 0.0f, 0.0f,   0.0f, 3.0f,
};
 
inline float floorCeilingVertices[] = {
    // ceiling
    -10.0f, 2.5f, -5.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,
     10.0f, 2.5f, -5.0f,   0.0f, -1.0f, 0.0f,   20.0f, 0.0f,
     10.0f, 2.5f, 5.0f,   0.0f, -1.0f, 0.0f,   20.0f, 10.0f,
     10.0f, 2.5f, 5.0f,   0.0f, -1.0f, 0.0f,   20.0f, 10.0f,
    -10.0f, 2.5f, 5.0f,   0.0f, -1.0f, 0.0f,   0.0f, 10.0f,
    -10.0f, 2.5f, -5.0f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,
 
    // floor
    -10.0f, -2.5f, -5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     10.0f, -2.5f, -5.0f,   0.0f, 1.0f, 0.0f,   20.0f, 0.0f,
     10.0f, -2.5f, 5.0f,   0.0f, 1.0f, 0.0f,   20.0f, 10.0f,
     10.0f, -2.5f, 5.0f,   0.0f, 1.0f, 0.0f,   20.0f, 10.0f,
    -10.0f, -2.5f, 5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
    -10.0f, -2.5f, -5.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
};
 
#endif
