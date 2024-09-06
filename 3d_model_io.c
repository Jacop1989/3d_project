#include <stdio.h>
#include <stdlib.h>

// โครงสร้างข้อมูลสำหรับจุดในระบบสามมิติ
typedef struct {
    float x, y, z;
} Vertex;

// โครงสร้างข้อมูลสำหรับหน้าในระบบสามมิติ
typedef struct {
    int v1, v2, v3;
} Face;

Vertex vertices[100];
Face faces[100];
int vertex_count = 0;
int face_count = 0;

// ฟังก์ชันโหลดไฟล์ .obj
void load_obj(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("ไม่สามารถเปิดไฟล์ %s\n", filename);
        return;
    }

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v') {
            // อ่านพิกัดของจุด
            sscanf(line, "v %f %f %f", &vertices[vertex_count].x, &vertices[vertex_count].y, &vertices[vertex_count].z);
            vertex_count++;
        } else if (line[0] == 'f') {
            // อ่านข้อมูลหน้าของโมเดล
            sscanf(line, "f %d %d %d", &faces[face_count].v1, &faces[face_count].v2, &faces[face_count].v3);
            face_count++;
        }
    }

    fclose(file);
    printf("โหลดไฟล์สำเร็จ: %d จุด, %d หน้า\n", vertex_count, face_count);
}

// ฟังก์ชันบันทึกไฟล์ .obj
void save_obj(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("ไม่สามารถเขียนไฟล์ %s\n", filename);
        return;
    }

    // เขียนข้อมูลจุด
    for (int i = 0; i < vertex_count; i++) {
        fprintf(file, "v %.2f %.2f %.2f\n", vertices[i].x, vertices[i].y, vertices[i].z);
    }

    // เขียนข้อมูลหน้า
    for (int i = 0; i < face_count; i++) {
        fprintf(file, "f %d %d %d\n", faces[i].v1, faces[i].v2, faces[i].v3);
    }

    fclose(file);
    printf("บันทึกไฟล์สำเร็จ: %s\n", filename);
}

int main() {
    load_obj("model.obj");

    // แสดงข้อมูลจุด
    for (int i = 0; i < vertex_count; i++) {
        printf("จุด %d: %.2f, %.2f, %.2f\n", i + 1, vertices[i].x, vertices[i].y, vertices[i].z);
    }

    // แสดงข้อมูลหน้า
    for (int i = 0; i < face_count; i++) {
        printf("หน้า %d: %d, %d, %d\n", i + 1, faces[i].v1, faces[i].v2, faces[i].v3);
    }

    // บันทึกไฟล์ใหม่
    save_obj("new_model.obj");

    return 0;
}
