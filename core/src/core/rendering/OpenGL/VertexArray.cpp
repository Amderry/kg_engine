#include <core/rendering/OpenGL/VertexArray.hpp>
#include <glad/glad.h>
#include <core/Log.hpp>

namespace engine_core 
{
	Vertex_Array::Vertex_Array()
	{
		glGenVertexArrays(1, &this->va_id);
	}

	Vertex_Array::~Vertex_Array()
	{
		glDeleteVertexArrays(1, &this->va_id);
	}

	Vertex_Array& Vertex_Array::operator=(Vertex_Array&& rhs) noexcept
	{
		this->va_id = rhs.va_id;
		this->elements_count = rhs.elements_count;

		rhs.va_id = 0;
		rhs.elements_count = 0;

		return *this;
	}

	Vertex_Array::Vertex_Array(Vertex_Array&& rhs) noexcept
	{
		this->va_id = rhs.va_id;
		this->elements_count = rhs.elements_count;

		rhs.va_id = 0;
		rhs.elements_count = 0;
	}

	void Vertex_Array::bind() const
	{
		glBindVertexArray(this->va_id);
	}

	void Vertex_Array::unbind()
	{
		glBindVertexArray(0);
	}

	void Vertex_Array::add_vertex_buffer(const Vertex_Buffer& vertex_buffer)
	{
		this->bind();
		vertex_buffer.bind();

		for (const Buffer_Element& cur_element : vertex_buffer.get_layout().get_elements())
		{
			glEnableVertexAttribArray(this->elements_count);
			glVertexAttribPointer(
				this->elements_count,
				static_cast<GLint>(cur_element.components_count),
				cur_element.component_type,
				GL_FALSE,
				static_cast<GLsizei>(vertex_buffer.get_layout().get_stride()),
				reinterpret_cast<const void*>(cur_element.offset)
			);
			++this->elements_count;
		}
	}

	void Vertex_Array::set_index_buffer(const Index_Buffer& index_buffer)
	{
		this->bind();
		index_buffer.bind();
		this->va_indicies_count = index_buffer.get_count();
	}
}