#include <vector>
#include <iostream>
#include <glad/glad.h>
#include "shader.h"
#include "util.h"

static GLuint compileShader(std::string& srcPath, GLenum type)
{
    GLuint id = glCreateShader(type);

    std::string src = readFile(srcPath);
    const GLchar* const tmp = src.c_str();
    glShaderSource(id, 1, &tmp, nullptr);
    glCompileShader(id);

    GLint success = 1;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLsizei length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);

        glGetShaderInfoLog(id, length, NULL, log.data());
        std::cerr << "Failed to compile shader:" << log.data() << std::endl;;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    id = glCreateProgram();

    vertexShader = compileShader(vertexPath, GL_VERTEX_SHADER);
    fragmentShader = compileShader(fragmentPath, GL_FRAGMENT_SHADER);
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    GLint success = 1;
    if (!success)
    {
        GLsizei length = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> log(length);

        glGetProgramInfoLog(id, length, NULL, log.data());
        std::cerr << "Failed to link shader program:" << log.data() << std::endl;;
    }


    GLint activeUniforms = 0;
    glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &activeUniforms);

    GLint uniformMaxLength = 0;
    glGetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxLength);

    std::vector<char> nameBuffer(uniformMaxLength);
    for (GLint i = 0; i < activeUniforms; i++)
    {
        GLsizei length = 0;
        GLint size;
        GLenum type;

        glGetActiveUniform(id, i, uniformMaxLength, &length, &size, &type, nameBuffer.data());

        std::string name(nameBuffer.data(), length);
        GLint location = glGetUniformLocation(id, name.c_str());

        uniforms[name] = location;
    }
}

Shader::~Shader(void)
{
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(id);
}

void Shader::use(void) const
{
	glUseProgram(id);
}

void Shader::setFloat(std::string name, float value) const
{
    if (uniforms.contains(name))
        glUniform1f(uniforms.at(name), value);
}
