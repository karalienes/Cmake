#include<iostream>
#include "adder.h"
#include "glfw3.h"
#include <CMAKE_TUTORIAL_Config.h>
using namespace std;

int main(int argc, char * argv[]){


    cout<<"KARALİ";

    cout<< "\n" <<add(72.1f,73.8f) << '\n';

    cout<<argv[0]<<" Version "<< CMAKE_TUTORIAL_VERSION_MAJOR << "." << CMAKE_TUTORIAL_VERSION_MINOR << "\n";
    // version console yazılması için gerekli olan source code 

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