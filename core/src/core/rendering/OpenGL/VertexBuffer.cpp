#include <core/rendering/OpenGL/VertexBuffer.hpp>
#include <glad/glad.h>
#include <core/Log.hpp>

namespace engine_core
{
	constexpr GLenum usage_to_GLenum(const Vertex_Buffer::EUsage usage) 
	{
		switch (usage)
		{
			case Vertex_Buffer::EUsage::Static: return GL_STATIC_DRAW;
			case Vertex_Buffer::EUsage::Dynamic: return GL_DYNAMIC_DRAW;
			case Vertex_Buffer::EUsage::Stream: return GL_STREAM_DRAW;
		}

		log("Unknown VB usage");
		return GL_STREAM_DRAW;
	}

	constexpr unsigned int shader_data_type_get_components_count(const Shader_Data_Type type)
	{
		switch (type) 
		{
			case Shader_Data_Type::Float:
			case Shader_Data_Type::Int:
				return 1;
			case Shader_Data_Type::Float2:
			case Shader_Data_Type::Int2:
				return 2;
			case Shader_Data_Type::Float3:
			case Shader_Data_Type::Int3:
				return 3;
			case Shader_Data_Type::Float4:
			case Shader_Data_Type::Int4:
				return 4;
		}

		log("Shader data type unknown");
		return 0;
	}

	constexpr unsigned int shader_data_type_size(const Shader_Data_Type type)
	{
		switch (type)
		{
			case Shader_Data_Type::Float:
			case Shader_Data_Type::Float2:
			case Shader_Data_Type::Float3:
			case Shader_Data_Type::Float4:
				return sizeof(GLfloat) * shader_data_type_get_components_count(type);
			case Shader_Data_Type::Int:
			case Shader_Data_Type::Int2:
			case Shader_Data_Type::Int3:
			case Shader_Data_Type::Int4:
				return sizeof(GLint) * shader_data_type_get_components_count(type);
		}

		log("Shader data type unknown");
		return 0;
	}

	constexpr unsigned int shader_data_type_to_component_type(const Shader_Data_Type type)
	{
		switch (type)
		{
			case Shader_Data_Type::Float:
			case Shader_Data_Type::Float2:
			case Shader_Data_Type::Float3:
			case Shader_Data_Type::Float4:
				return GL_FLOAT;
			case Shader_Data_Type::Int:
			case Shader_Data_Type::Int2:
			case Shader_Data_Type::Int3:
			case Shader_Data_Type::Int4:
				return GL_INT;
		}

		log("Shader data type unknown");
		return 0;
	}

	Buffer_Element::Buffer_Element(const Shader_Data_Type sh_type) 
		:type(sh_type),
		 component_type(shader_data_type_to_component_type(sh_type)),
		 components_count(shader_data_type_get_components_count(sh_type)),
		 size(shader_data_type_size(sh_type)),
		 offset(0)
	{}

	Vertex_Buffer::Vertex_Buffer(const void* data, const size_t size, Buffer_Layout bf_layout, const EUsage usage)
		: vb_layout(std::move(bf_layout))
	{
		glGenBuffers(1, &this->vb_id);
		glBindBuffer(GL_ARRAY_BUFFER, this->vb_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage_to_GLenum(usage));
	}

	Vertex_Buffer::~Vertex_Buffer()
	{
		glDeleteBuffers(1, &this->vb_id);
	}

	Vertex_Buffer& Vertex_Buffer::operator=(Vertex_Buffer&& rhs) noexcept
	{
		this->vb_layout = std::move(rhs.vb_layout);
		this->vb_id = rhs.vb_id;
		rhs.vb_id = 0;
		return *this;
	}

	Vertex_Buffer::Vertex_Buffer(Vertex_Buffer&& rhs) noexcept
		: vb_layout(std::move(rhs.vb_layout)),
		  vb_id(rhs.vb_id)
	{
		rhs.vb_id = 0;
	}

	void Vertex_Buffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->vb_id);
	}

	void Vertex_Buffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}