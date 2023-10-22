#include "Includes/GLFW/glfw3.h" 

#include <iostream>
#include <conio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <Windows.h>

#pragma comment (lib, "opengl32.lib")



class Window {

public:
    int init() {
        GLFWwindow* window; // Объявляем указатель на окно GLFW

        /* Инициализируем библиотеку */
        if (!glfwInit()) // Если инициализация не удалась,
            return -1; // завершаем программу с кодом ошибки -1

        /* Создаем окно в режиме с оконным режимом и его контекстом OpenGL */
        window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL); // Создаем окно размером 640x480 пикселей с заголовком "Hello World"
        if (!window) // Если окно не создано,
        {
            glfwTerminate(); // завершаем GLFW
            return -1; // и завершаем программу с кодом ошибки -1
        }

        /* Делаем контекст окна текущим */
        glfwMakeContextCurrent(window);
        program_started(window);
    }

private:
    float vert[20] = { 1,1,0, 1,-1,0, -1,-1,0, -1,1,0 };
    float xAlfa = 20;
    float zAlfa = 0;
    float pyramid[20] = {0,0,2, 1,1,0, 1,-1,0, -1,-1,0, 1,1,0};
    POINTFLOAT pos = { 0,0 };

    // функчия обновлния
    void program_started(GLFWwindow* window) {

        glEnable(GL_DEPTH_TEST);


        //glLoadIdentity();
        ////glOrtho(-2, 2, -2, 2, -1, 1);
        glFrustum(-1, 1, -1, 1, 2, 80);


        while (!glfwWindowShouldClose(window)) {
            /* Рендеринг здесь */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Очищаем буфер цвета
            glClearColor(0.2f, 0.5f, 0.7f, 1.0f); // Цвет фона черный

            glPushMatrix();
            MoveCamera(window);
            ShowWorld();
            glPopMatrix();
            //glEnd();




            /* Обмен фронтального и заднего буферов */
            glfwSwapBuffers(window);
            glfwPollEvents(); // Обрабатываем события
            Sleep(16);
        }

        glfwTerminate(); // Завершаем GLFW
    }



    void ShowWorld() {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vert);
        for (int i = -5; i < 5; i++) {
            for (int j = -5; j < 5; j++) {
                glPushMatrix();
                if ((i + j) % 2 == 0) {
                    glColor3f(1, 0.5f, 0.1f);
                    glTranslatef(i * 2, j * 2, 0);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                }
                else
                {
                    glColor3f(1, 0, 1);
                    glTranslatef(i * 2, j * 2, 0);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                }
                glPopMatrix();
            }
        }
        glVertexPointer(3, GL_FLOAT, 0, &pyramid);
        glColor3f(1, 0, 0);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

        glPushMatrix();
            glTranslatef(3, 3, 0);
            glScaled(1, 1, 0.5);
            glColor3f(1, 1, 0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-3, 5, 0);
            glRotatef(45, 0, 0, 1);
            glColor3f(0, 0.5, 1);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
        glPopMatrix();



        glDisableClientState(GL_VERTEX_ARRAY);
    }

    void MoveCamera(GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            xAlfa = ++xAlfa > 180 ? 180 : xAlfa;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            zAlfa++;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            xAlfa = --xAlfa < 0 ? 0 : xAlfa;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            zAlfa--;
        }

        float ugol = zAlfa / 180 * M_PI;
        float speed = 0;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            speed = 0.1f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            speed = -0.1f;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            speed = 0.1f;
            ugol -= M_PI * 0.5;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            speed = 0.1f;
            ugol += M_PI * 0.5;
        }

        if (speed != 0) {
            pos.x += sin(ugol) * speed;
            pos.y += cos(ugol) * speed;
        }

        glRotated(-xAlfa, 1, 0, 0);
        glRotated(-zAlfa, 0, 0, 1);
        glTranslatef(-pos.x, -pos.y, -3);
    }

};


int main()
{
    setlocale(NULL, "RUS");
    Window Class_Window;

    Class_Window.init();

    return 0; // Возвращаем успешный код завершения программы (0)
}
