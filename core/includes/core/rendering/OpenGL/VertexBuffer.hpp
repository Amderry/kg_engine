#pragma once
#include <vector>

namespace engine_core
{
	enum class Shader_Data_Type
	{
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4
	};

	struct Buffer_Element
	{
		Shader_Data_Type type;
		uint32_t component_type;
		size_t components_count;
		size_t size;
		size_t offset;

		Buffer_Element(const Shader_Data_Type sh_type);
	};

	class Buffer_Layout
	{
	public:
		Buffer_Layout(std::initializer_list<Buffer_Element> elements)
			: bf_elements(std::move(elements))
		{
			size_t offset = 0;
			this->bf_stride = 0;

			for (auto& element : bf_elements)
			{
				element.offset = offset;
				offset += element.size;
				bf_stride += element.size;
			}
		}

		const std::vector<Buffer_Element>& get_elements() const { return this->bf_elements; }
		size_t get_stride() const { return this->bf_stride; }
	private:
		std::vector<Buffer_Element> bf_elements;
		size_t bf_stride = 0;
	};

	class Vertex_Buffer
	{
	public:
		enum class EUsage
		{
			Static,
			Dynamic,
			Stream
		};

		Vertex_Buffer(const void* data, const size_t size, Buffer_Layout buf_layout, const EUsage usage = Vertex_Buffer::EUsage::Static);
		~Vertex_Buffer();

		Vertex_Buffer(const Vertex_Buffer&) = delete;
		Vertex_Buffer& operator=(const Vertex_Buffer&) = delete;

		Vertex_Buffer(Vertex_Buffer&&) noexcept;
		Vertex_Buffer& operator=(Vertex_Buffer&&) noexcept;

		void bind() const;
		static void unbind();

		const Buffer_Layout& get_layout() const { return this->vb_layout; }
	private:
		unsigned int vb_id = 0;
		Buffer_Layout vb_layout;
	};
}