#ifndef LEARNOPENGL_SHADER_H
#define LEARNOPENGL_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


class Shader
{
public:
    Shader(const char * vertShaderPath, const char * fragShaderPath)
    {
        // 1. retrieve the vertexShader/fragmentShader source code from filePath

        std::string vertShaderCode;
        std::string fragShaderCode;

        if (std::ifstream fin {vertShaderPath, std::ifstream::in})
        {
            std::ostringstream sout;
            sout << fin.rdbuf();
            vertShaderCode = sout.str();
        }
        else
        {
            std::cout << std::unitbuf
                      << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                      << "\n[ERROR] " << "Vertex shader file not successfully read!"
                      << std::nounitbuf << std::endl;

            std::abort();
        }

        if (std::ifstream fin {fragShaderPath, std::ifstream::in})
        {
            std::ostringstream sout;
            sout << fin.rdbuf();
            fragShaderCode = sout.str();
        }
        else
        {
            std::cout << std::unitbuf
                      << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                      << "\n[ERROR] " << "Fragment shader file not successfully read!"
                      << std::nounitbuf << std::endl;

            std::abort();
        }

        const char * vertShaderPtr = vertShaderCode.data();
        const char * fragShaderPtr = fragShaderCode.data();

        // 2. compile shaders

        // vertexShader shader
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertShaderPtr, nullptr);
        glCompileShader(vertexShader);
        checkCompileErrors(vertexShader, "VERTEX");

        // fragmentShader shader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragShaderPtr, nullptr);
        glCompileShader(fragmentShader);
        checkCompileErrors(fragmentShader, "FRAGMENT");

        // shader program
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        checkCompileErrors(shaderProgram, "PROGRAM");

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void use()
    {
        glUseProgram(shaderProgram);
    }

    void setBool(const std::string & name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int) value);
    }

    void setInt(const std::string & name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

    void setFloat(const std::string & name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, float x, float y, float z, float w) const
    {
        glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    unsigned int getShaderProgramHandle() const
    {
        return shaderProgram;
    }

private:
    // utility function for checking shader compilation/linking errors.
    static void checkCompileErrors(unsigned int shader, const std::string & type)
    {
        int success;
        char infoLog[1024];

        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);

                std::cout << std::unitbuf
                          << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                          << "\n[ERROR] " << type << " shader compilation failed"
                          << "\n[ERROR] " << infoLog
                          << std::nounitbuf << std::endl;

                std::abort();
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);

            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);

                std::cout << std::unitbuf
                          << "[ERROR] " << __FILE__ << ':' << __LINE__ << ' ' << __PRETTY_FUNCTION__
                          << "\n[ERROR] " << R"(Shader program linking failed)"
                          << "\n[ERROR] " << infoLog
                          << std::nounitbuf << std::endl;

                std::abort();
            }
        }
    }

private:
    unsigned int shaderProgram;
};

#endif // LEARNOPENGL_SHADER_H
