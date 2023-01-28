#include"main.h"


int main(int argc, char *argv[])
{
    Display *display=0;
    Window window=0;
    makeWindow(&window, &display);
    GLenum status = glewInit();
    if(status != GLEW_OK) { printf("No can GLEW\n"); exit(1); };
    mainLoop(window, display);
    printf("Bye\n");
}
