//----------------------Created by Anik Saha---------------------------//
#include <bits/stdc++.h>
#include <GLFW/glfw3.h>
using namespace std;
//---------------------------Good luck---------------------------------//

int main(int, char **argv)
{
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif
    // FastIO;
    // cout << "Hello, world!" << endl;

    GLFWwindow *window;
    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}