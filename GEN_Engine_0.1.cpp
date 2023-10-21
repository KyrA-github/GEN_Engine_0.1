#include "Includes/GLFW/glfw3.h" 

#include <iostream>
#include <conio.h>



class Window {

public:
    int init() {
        float square_X = 0.0f;
        float square_Y = 0.0f;

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
        program_started(window, square_X, square_Y);
    }

private:
    // функчия обновлния
    void program_started(GLFWwindow* window, float square_X, float square_Y) {

    while (!glfwWindowShouldClose(window)){
        key_pressing(square_X, square_Y);

        /* Рендеринг здесь */
        glClear(GL_COLOR_BUFFER_BIT); // Очищаем буфер цвета

       draw_square(square_X, square_Y);
        
        /* Обмен фронтального и заднего буферов */
        glfwSwapBuffers(window);
        glfwPollEvents(); // Обрабатываем события
    }

    glfwTerminate(); // Завершаем GLFW
    }

    // функция обработки нажатий
    void key_pressing(float square_X, float square_Y) {
        if (_kbhit()) {
            // Получаем код клавиши
            char key = _getch();

            // Обработка нажатия клавиши
            if (key == 'q' || key == 'Q') {
                std::cout << key << std::endl;
            }

            // Другие обработки клавиш можно добавить здесь
        }
    }

    // функчия рисовки
    void draw_square(float square_X, float square_Y) {
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
    Window Class_Window;

    Class_Window.init();

    return 0; // Возвращаем успешный код завершения программы (0)
}
