#include <glm/glm.hpp>

namespace engine_core
{
	class Shader_Program
	{
	public:
		Shader_Program(const char* v_shader, const char* fr_shader);
		Shader_Program(Shader_Program&&) noexcept;
		Shader_Program& operator=(Shader_Program&&) noexcept;
		~Shader_Program();

		Shader_Program() = delete;
		Shader_Program(const Shader_Program&) = delete;
		Shader_Program& operator= (const Shader_Program&) = delete;

		void bind() const;
		static void unbind();
		bool get_is_compiled() const { return is_compiled; };
		void set_matrix4(const char* name, const glm::mat4& matrix);
		void set_vec3f(const char* name, const glm::vec3 vector);
		void set_float(const char* name, const float uniform_float);
	private:
		bool is_compiled = false;
		unsigned int sh_id = 0;
	};
}