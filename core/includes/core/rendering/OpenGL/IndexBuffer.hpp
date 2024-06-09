#pragma once
#include <core/rendering/OpenGL/VertexBuffer.hpp>

namespace engine_core
{
	class Index_Buffer
	{
	public:

		Index_Buffer(const void* data, const size_t count, const Vertex_Buffer::EUsage usage = Vertex_Buffer::EUsage::Static);
		~Index_Buffer();

		Index_Buffer(const Index_Buffer&) = delete;
		Index_Buffer& operator=(const Index_Buffer&) = delete;
		Index_Buffer(Index_Buffer&&) noexcept;
		Index_Buffer& operator=(Index_Buffer&&) noexcept;

		void bind() const;
		static void unbind();
		size_t get_count() const { return ib_count; }
	private:
		unsigned int ib_id = 0;
		size_t ib_count = 0;
	};

}