#include "Includes/GLFW/glfw3.h" 

#include <iostream>
#include <conio.h>



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
    float square_X = 0.0f;
    float square_Y = 0.0f;
    float square_X_2 = 0.0f;
    float square_Y_2 = -0.9f;

   //первый квадрат
    float V_L_X = -0.2f + square_X;
    float V_L_Y =  0.2f + square_Y;

    float V_R_X = 0.2f + square_X;
    float V_R_Y = 0.2f + square_Y;

    float N_R_X = 0.2f + square_X;
    float N_R_Y = -0.2f + square_Y;

    float N_L_X = -0.2f + square_X;
    float N_L_Y = -0.2f + square_Y;

    // Высота и ширина первого квадрата
    float height1 = V_L_Y - N_L_Y;
    float width1 = V_R_X - V_L_X;

    //второй квадрат
    float V_L_X_2 = -0.4f + square_X_2;
    float V_L_Y_2 =  0.2f + square_Y_2;

    float V_R_X_2 =  0.4f + square_X_2;
    float V_R_Y_2 =  0.2f + square_Y_2;

    float N_L_X_2 = -0.4f + square_X_2;
    float N_L_Y_2 = -0.2f + square_Y_2;

    float N_R_X_2 =  0.4f + square_X_2;
    float N_R_Y_2 = -0.2f + square_Y_2;

    // Высота и ширина второго квадрата
    float height2 = V_L_Y_2 - N_L_Y_2;
    float width2 = V_R_X_2 - V_L_X_2;

    int jump_go = 100;

    float G = 0.001f;
    float JUMP = 0.003f;

    bool jump_col = true;


    // функчия обновлния
    void program_started(GLFWwindow* window) {

        while (!glfwWindowShouldClose(window)){
            std::cout << square_Y << std::endl;

            key_pressing(window);

            /* Рендеринг здесь */
            glClear(GL_COLOR_BUFFER_BIT); // Очищаем буфер цвета
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Цвет фона черный

            jump();

            if (!colazion(window)) {
                square_Y -= G;
            }

            draw();

            /* Обмен фронтального и заднего буферов */
            glfwSwapBuffers(window);
            glfwPollEvents(); // Обрабатываем события
        }

        glfwTerminate(); // Завершаем GLFW
    }
    void jump() {
        if (jump_go < 100 && jump_col) {
            square_Y += JUMP;
            jump_col = false;
            jump_go++;
        }
        else
        {
            jump_col = true;
        }
        

    }

    bool colazion(GLFWwindow* window) {
        // Проверяем столкновение между двумя AABB
        if (checkCollision()) {
            // Столкновение обнаружено
            square_Y += 0.001f;
            return true;
        }
        else {
            return false;
        }
    }
    
    bool checkCollision() {
        return (V_L_X < V_L_X_2 + width2 && V_L_X + width1 > V_L_X_2 && V_L_Y < V_L_Y_2 + height2 && V_L_Y + height1 > V_L_Y_2);
    }

    // функция обработки нажатий
    void key_pressing(GLFWwindow* window) {
        
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            square_X -= 0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            square_X += 0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_RELEASE && jump_col) {
            jump_go = 0;
            std::cout << "Space\n";
        }
    }

    // функчия рисовки
    void draw() {

        V_L_X = -0.2f + square_X;
        V_L_Y = 0.2f + square_Y;

        V_R_X = 0.2f + square_X;
        V_R_Y = 0.2f + square_Y;

        N_R_X = 0.2f + square_X;
        N_R_Y = -0.2f + square_Y;

        N_L_X = -0.2f + square_X;
        N_L_Y = -0.2f + square_Y;

        glBegin(GL_QUADS);
                
            glVertex2f(V_L_X, V_L_Y); // Верхний левый угол
            glVertex2f(V_R_X, V_R_Y); // Верхний правый угол
            glVertex2f(N_R_X, N_R_Y); // Нижний правый угол
            glVertex2f(N_L_X, N_L_Y); // Нижний левый угол

            glVertex2f(V_L_X_2, V_L_Y_2); // Верхний левый угол
            glVertex2f(V_R_X_2, V_R_Y_2); // Верхний правый угол
            glVertex2f(N_R_X_2, N_R_Y_2); // Нижний правый угол
            glVertex2f(N_L_X_2, N_L_Y_2); // Нижний левый угол

            

            glEnd();
    }

};


int main()
{
    setlocale(NULL, "RUS");
    Window Class_Window;

    Class_Window.init();

    return 0; // Возвращаем успешный код завершения программы (0)
}
