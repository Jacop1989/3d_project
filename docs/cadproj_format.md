# CAD Project File Format (.cadproj)

The `.cadproj` format stores geometry together with placeholders for
parametric and assembly information. It is a simple text-based format
intended for experimentation.

## Structure

```
CADPROJ 1.0
vertices <count>
<x> <y> <z>
...
faces <count>
<v1> <v2> <v3>
...
# parametric and assembly data would follow
```

- `CADPROJ 1.0` – file identifier and version.
- `vertices` section lists all vertex coordinates.
- `faces` section lists triangular faces referencing vertex indices (1-based).
- Lines starting with `#` are comments and can include parametric definitions
  and assembly relationships. Future versions may encode these sections in
  JSON to interface with external CAD kernels.

This design allows basic geometry exchange today while leaving room for
parametric features (e.g., sketches, constraints) and assembly hierarchy to be
added later.
