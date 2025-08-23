#ifndef MODEL_MATERIAL_H
#define MODEL_MATERIAL_H

struct Color {
    float r{1.0f};
    float g{1.0f};
    float b{1.0f};
};

struct Material {
    float density{1.0f};
    Color color{};
};

#endif // MODEL_MATERIAL_H
