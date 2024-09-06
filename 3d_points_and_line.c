#include <GL/glut.h>
#include <stdio.h>

// โครงสร้างข้อมูลสำหรับจุดในระบบสามมิติ
typedef struct {
    float x, y, z;
} Point3D;

// โครงสร้างข้อมูลสำหรับเส้นในระบบสามมิติ
typedef struct {
    Point3D start;
    Point3D end;
} Line3D;

// ตัวอย่างข้อมูลจุด
Point3D p1 = {0.0, 0.0, 0.0};
Point3D p2 = {1.0, 1.0, 1.0};

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

// ฟังก์ชันสำหรับการวาดจุด
void draw_point(Point3D point) {
    glPointSize(8.0); // ตั้งขนาดจุด
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0); // ตั้งค่าสีเป็นสีขาว
    glVertex3f(point.x, point.y, point.z); // วาดจุด
    glEnd();
}

// ฟังก์ชันสำหรับการวาดเส้น
void draw_line(Line3D line) {
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 1.0); // ตั้งค่าสีของเส้น
    glVertex3f(line.start.x, line.start.y, line.start.z);
    glVertex3f(line.end.x, line.end.y, line.end.z);
    glEnd();
}

// ฟังก์ชันสำหรับการแสดงผล (Display)
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // วาดแกน
    draw_axes();

    // วาดจุด
    draw_point(p1);
    draw_point(p2);

    // วาดเส้นระหว่างสองจุด
    Line3D line = {p1, p2};
    draw_line(line);

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

    // ตั้งค่ากล้องให้เป็นมุม Isometric
    gluLookAt(5.0, 5.0, 5.0,   // ตำแหน่งกล้อง
              0.0, 0.0, 0.0,   // มองไปที่จุดศูนย์กลาง
              0.0, 1.0, 0.0);  // แกน Y ชี้ขึ้น
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Points and Line with Axes");

    init(); // เรียกฟังก์ชันตั้งค่าเริ่มต้น

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
