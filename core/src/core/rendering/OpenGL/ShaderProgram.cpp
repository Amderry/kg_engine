#include <core/rendering/OpenGL/ShaderProgram.hpp>
#include <core/Log.hpp>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace engine_core
{
	bool compile_shader(const char* source, const GLenum shader_type, GLuint& shader_id)
	{
		shader_id = glCreateShader(shader_type);
		glShaderSource(shader_id, 1, &source, nullptr);
		glCompileShader(shader_id);

		GLint success;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			char info_log[1024];
			glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);

			log("Shader was not compiled", info_log);
			return false;
		}
		return true;
	}

	Shader_Program::Shader_Program(const char* v_shader_src, const char* fr_shader_src)
	{
		GLuint vertex_shader_id = 0;

		if (!compile_shader(v_shader_src, GL_VERTEX_SHADER, vertex_shader_id)) {
			log("Compile time error");
			glDeleteShader(vertex_shader_id);
			return;
		}

		GLuint fragment_shader_id = 0;

		if (!compile_shader(fr_shader_src, GL_FRAGMENT_SHADER, fragment_shader_id)) {
			log("Compile time error");
			glDeleteShader(fragment_shader_id);
			return;
		}

		this->sh_id = glCreateProgram();
		glAttachShader(this->sh_id, vertex_shader_id);
		glAttachShader(this->sh_id, fragment_shader_id);
		glLinkProgram(this->sh_id);

		GLint success;
		glGetProgramiv(this->sh_id, GL_LINK_STATUS, &success);
		if (success == GL_FALSE)
		{
			char info_log[1024];
			glGetProgramInfoLog(this->sh_id, 1024, nullptr, info_log);
			glDeleteProgram(this->sh_id);
			this->sh_id = 0;
			glDeleteShader(vertex_shader_id);
			glDeleteShader(fragment_shader_id);
			log("Program was not linked", info_log);
			return;
		}
		else
		{
			this->is_compiled = true;
		}

		glDetachShader(this->sh_id, vertex_shader_id);
		glDetachShader(this->sh_id, fragment_shader_id);
		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);
	}

	Shader_Program::~Shader_Program()
	{
		glDeleteProgram(this->sh_id);
	}

	void Shader_Program::bind() const
	{
		glUseProgram(this->sh_id);
	}

	void Shader_Program::unbind()
	{
		glUseProgram(0);
	}

	Shader_Program& Shader_Program::operator=(Shader_Program&& rhs) noexcept
	{
		glDeleteProgram(this->sh_id);
		this->sh_id = rhs.sh_id;
		this->is_compiled = rhs.is_compiled;

		rhs.sh_id = 0;
		rhs.is_compiled = false;
		return *this;
	}

	Shader_Program::Shader_Program(Shader_Program&& rhs) noexcept
	{
		this->sh_id = rhs.sh_id;
		this->is_compiled = rhs.is_compiled;

		rhs.sh_id = 0;
		rhs.is_compiled = false;
	}

	void Shader_Program::set_matrix4(const char* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(this->sh_id, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void Shader_Program::set_vec3f(const char* name, const glm::vec3 vector)
	{
		glUniform3fv(glGetUniformLocation(this->sh_id, name), 1, glm::value_ptr(vector));
	}

	void Shader_Program::set_float(const char* name, const float uniform_float)
	{
		glUniform1f(glGetUniformLocation(this->sh_id, name), uniform_float);
	}
}