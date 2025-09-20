#pragma once
#include <string>
#include <unordered_map>

class Shader
{

public:
	Shader(void) = delete;
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader(void);

	void use(void) const;

	void setFloat(std::string name, float value) const;

private:
	GLuint id;
	GLuint vertexShader, fragmentShader;

	std::unordered_map<std::string, GLint> uniforms;
};