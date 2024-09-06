#include <GL/glut.h>
#include <stdio.h>

// โครงสร้างข้อมูลสำหรับจุดในระบบสามมิติ
typedef struct {
    float x, y, z;
} Point3D;

// โครงสร้างข้อมูลสำหรับพื้นผิวในระบบสามมิติ
typedef struct {
    int v1, v2, v3; // index ของจุดยอดในแต่ละพื้นผิว
} Face3D;

// อาร์เรย์ของจุดยอดและพื้นผิว
Point3D vertices[100];
Face3D faces[100];
int vertex_count = 0, face_count = 0;

// ฟังก์ชันสำหรับการอ่านโมเดลจากไฟล์ .obj
void load_model(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("ไม่สามารถเปิดไฟล์ %s\n", filename);
        return;
    }

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            // อ่านจุดยอด
            sscanf(line, "v %f %f %f", &vertices[vertex_count].x, &vertices[vertex_count].y, &vertices[vertex_count].z);
            vertex_count++;
        } else if (line[0] == 'f') {
            // อ่านพื้นผิว
            sscanf(line, "f %d %d %d", &faces[face_count].v1, &faces[face_count].v2, &faces[face_count].v3);
            face_count++;
        }
    }

    fclose(file);
    printf("โหลดโมเดลเสร็จสิ้น: %d จุดยอด, %d พื้นผิว\n", vertex_count, face_count);
}

// ฟังก์ชันสำหรับการวาดโมเดล 3D
void draw_model() {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < face_count; i++) {
        // วาดแต่ละพื้นผิว
        glVertex3f(vertices[faces[i].v1 - 1].x, vertices[faces[i].v1 - 1].y, vertices[faces[i].v1 - 1].z);
        glVertex3f(vertices[faces[i].v2 - 1].x, vertices[faces[i].v2 - 1].y, vertices[faces[i].v2 - 1].z);
        glVertex3f(vertices[faces[i].v3 - 1].x, vertices[faces[i].v3 - 1].y, vertices[faces[i].v3 - 1].z);
    }
    glEnd();
}

// ฟังก์ชันสำหรับการวาดแกน (Axes)
void draw_axes() {
    glBegin(GL_LINES);

    // แกน X สีแดง
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-5.0, 0.0, 0.0);
    glVertex3f(5.0, 0.0, 0.0);

    // แกน Y สีเขียว
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -5.0, 0.0);
    glVertex3f(0.0, 5.0, 0.0);

    // แกน Z สีน้ำเงิน
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -5.0);
    glVertex3f(0.0, 0.0, 5.0);

    glEnd();
}

// ฟังก์ชันสำหรับการแสดงผล (Display)
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // วาดแกน
    draw_axes();

    // วาดโมเดล
    draw_model();

    glutSwapBuffers();
}

// ฟังก์ชันการตั้งค่าเริ่มต้น
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // ตั้งค่าสีพื้นหลังเป็นสีดำ
    glEnable(GL_DEPTH_TEST);          // เปิดใช้งานการตรวจสอบความลึก (3D)
}

// ฟังก์ชันสำหรับการปรับขนาดหน้าต่าง
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ตั้งค่ากล้องให้เป็นมุมมอง Isometric
    gluLookAt(5.0, 5.0, 5.0,   // ตำแหน่งกล้อง
              0.0, 0.0, 0.0,   // มองไปที่จุดศูนย์กลาง
              0.0, 1.0, 0.0);  // แกน Y ชี้ขึ้น
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Model Viewer");

    init(); // เรียกฟังก์ชันตั้งค่าเริ่มต้น
    load_model("model.obj"); // โหลดโมเดลจากไฟล์

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
