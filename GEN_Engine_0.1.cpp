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
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL); // Создаем окно размером 640x480 пикселей с заголовком "Hello World"
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
        
    // функчия обновлния
    void program_started(GLFWwindow* window) {

        while (!glfwWindowShouldClose(window)){
            key_pressing(window);

            /* Рендеринг здесь */
            glClear(GL_COLOR_BUFFER_BIT); // Очищаем буфер цвета

           draw_square();
        
            /* Обмен фронтального и заднего буферов */
            glfwSwapBuffers(window);
            glfwPollEvents(); // Обрабатываем события
        }

        glfwTerminate(); // Завершаем GLFW
    }

    // функция обработки нажатий
    void key_pressing(GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            square_Y -= 0.01f;
            std::cout << "Y\n";

        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            square_Y += 0.01f;
            std::cout << "Y\n";

        }
    }

    // функчия рисовки
    void draw_square() {
        glBegin(GL_QUADS);

            glVertex2f(-0.5f + square_X, 0.5f + square_Y); // Верхний левый угол
            glVertex2f(0.5f + square_X, 0.5f + square_Y);  // Верхний правый угол
            glVertex2f(0.5f + square_X, -0.5f + square_Y); // Нижний правый угол
            glVertex2f(-0.5f + square_X, -0.5f + square_Y); // Нижний левый угол

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
