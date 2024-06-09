#pragma once
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

namespace engine_core
{
	class Vertex_Array
	{
	public:
		Vertex_Array();
		~Vertex_Array();

		Vertex_Array(const Vertex_Array&) = delete;
		Vertex_Array& operator=(const Vertex_Array&) = delete;

		Vertex_Array(Vertex_Array&&) noexcept;
		Vertex_Array& operator=(Vertex_Array&&) noexcept;

		void add_vertex_buffer(const Vertex_Buffer& vertex_buffer);
		void set_index_buffer(const Index_Buffer& index_buffer);
		void bind() const;
		static void unbind();
		size_t get_indicies_count() const { return this->va_indicies_count; }
	private:
		unsigned int va_id = 0;
		unsigned int elements_count = 0;
		size_t va_indicies_count = 0;
	};
}