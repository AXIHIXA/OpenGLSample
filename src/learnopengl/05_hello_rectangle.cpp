#include <bits/stdc++.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow * window, int width, int height);

void processInput(GLFWwindow * window);


int main()
{
    // 1. OpenGL content by GLFW

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window = glfwCreateWindow(800, 600, "OpenGLDemo", nullptr, nullptr);

    if (!window)
    {
        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Failed to create GLFW window!"
                  << std::nounitbuf << std::endl;
        glfwTerminate();
        std::abort();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 2. load OpenGL functions by GLAD

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Failed to initialize GLAD!"
                  << std::nounitbuf << std::endl;

        std::abort();
    }

    // 3. compile & link shader programs

    // vertex shader
    const char * vertexShaderSource = "#version 330 core\n"
                                      "layout (location = 0) in vec3 aPos;\n"
                                      "void main()\n"
                                      "{\n"
                                      " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                      "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);

        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Vertex shader compilation failed!"
                  << "\n[ERROR] " << infoLog
                  << std::nounitbuf << std::endl;

        std::abort();
    }

    // fragment shader
    const char * fragmentShaderSource = "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                        "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);

        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Fragment shader compilation failed!"
                  << "\n[ERROR] " << infoLog
                  << std::nounitbuf << std::endl;

        std::abort();
    }

    // attach compiled shaders to shader program object and link them
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);

        std::cout << std::unitbuf
                  << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                  << "\n[ERROR] " << "Shader program linking failed!"
                  << "\n[ERROR] " << infoLog
                  << std::nounitbuf << std::endl;

        std::abort();
    }

    // Shaders are already attached to shaderProgram object.
    // Shaders themselves are now useless and should be deallocated.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 4. Vertex coordinate in Normalized Device Coordinate (NDC).
    float vertices[] = {
            0.5f, 0.5f, 0.0f,    // top right
            0.5f, -0.5f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f, 0.5f, 0.0f    // top left
    };

    unsigned int indices[] = {   // note that we start from 0!
            0, 1, 3,             // first triangle
            1, 2, 3              // second triangle
    };

    // 5.
    // Send vertex data to vertex shader
    // by creating memory (vertex buffer objects, VBO) on GPU where we store these vertex data.
    // VBOs store float arrays storing vertex coordinates
    // and how it should be interpreted into vec3 in GLSL (i.e. indexes, strides, offsets, etc.)

    // VBOs are stored and organized by vertex array object (VAO).
    // A VAO organizes MULTIPLE VBOs.
    // Once binded to OpenGL context by glBindVertexArray(), this AVO is active and will record
    // calls to functions specifying how VBO should be interpreted and their destinations in vertex shader:
    // glVertexAttribPointer(), glEnableVertexAttribArray() / glDisableVertexAttribArray()

    // A VAO may also has ONE element buffer object (EBO)
    // which is used together with glDrawElements(), where EBO determines which vertices form which triangle.
    // An active VAO stores the glBindBuffer() calls when the target is GL_ELEMENT_ARRAY_BUFFER.
    // This also means it stores its unbind calls.
    // So make sure you DON'T unbind the element array buffer before unbinding your VAO,
    // otherwise it doesn’t have an EBO configured.

    // VAO initialization code
    // Done once (unless your object frequently changes)
    // Bind VAO first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Bind this buffer to OpenGL context GL_ARRAY_BUFFER.
    // Recall that OpenGL is a state machine, which means from now on,
    // any buffer call we make (on the GL_ARRAY_BUFFER target)
    // will be used to configure the currently bound buffer, which is VBO.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // call glBufferData() function that copies the previously defined vertex data into the buffer’s memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // tell opengl how to interpret current VBO into "layout (location = 0) in vec3 aPos"
    // current VBO is specified by global context GL_ARRAY_BUFFER
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(0);

    // EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Note that this is allowed.
    // The call to glVertexAttribPointer registered VBO
    // as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens.
    // Modifying other VAOs requires a call to glBindVertexArray anyways
    // so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // WARNING
    // A VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER.
    // This also means it stores its unbind calls.
    // So make sure you DON'T unbind the element array buffer before unbinding your VAO,
    // otherwise it doesn’t have an EBO configured.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    // 6. render loop

    // viewport
    // NDC coordinates will then be transformed to screen-space coordinates via the
    // viewport transform using the data you provided with glViewport()
    glViewport(0, 0, 800, 600);

    // draw in wireframe polygons or filled polygons
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window))
    {
        // process input
        processInput(window);

        // rendering code here

        // background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow * window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
