#include <core/rendering/OpenGL/IndexBuffer.hpp>
#include <core/Log.hpp>
#include <glad/glad.h>

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

	Index_Buffer::Index_Buffer(const void* data, const size_t count, const Vertex_Buffer::EUsage usage)
		: ib_count(count)
	{
		glGenBuffers(1, &this->ib_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ib_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->ib_count * sizeof(GLuint), data, usage_to_GLenum(usage));
	}

	Index_Buffer::~Index_Buffer()
	{
		glDeleteBuffers(1, &this->ib_id);
	}

	Index_Buffer& Index_Buffer::operator=(Index_Buffer&& rhs) noexcept
	{
		this->ib_id = rhs.ib_id;
		rhs.ib_id = 0;
		return *this;
	}

	Index_Buffer::Index_Buffer(Index_Buffer&& rhs) noexcept
		: ib_id(rhs.ib_id)
	{
		rhs.ib_id = 0;
	}

	void Index_Buffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ib_id);
	}

	void Index_Buffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}