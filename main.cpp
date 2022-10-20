#include<iostream>
#include "adder.h"
#include "glfw3.h"
using namespace std;

int main(){


    cout<<"KARALİ";

    cout<< "\n" <<add(72.1f,73.8f) << '\n';

    GLFWwindow *window;

    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit( EXIT_FAILURE);

    }
    window = glfwCreateWindow(300,300, "Gears",NULL, NULL);

    if(!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit( EXIT_FAILURE );

    }

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0; 
}