#pragma once

namespace Robin
{
	enum class shader_data_type
	{
		none = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t shader_data_type_size(shader_data_type type)
	{
		switch (type)
		{
			case shader_data_type::Float: return 4;
			case shader_data_type::Float2: return 4 * 2;
			case shader_data_type::Float3: return 4 * 3;
			case shader_data_type::Float4: return 4 * 4;
			case shader_data_type::Mat3: return 4 * 3 * 3;
			case shader_data_type::Mat4: return 4 * 4 * 4;
			case shader_data_type::Int: return 4;
			case shader_data_type::Int2: return 4 * 2;
			case shader_data_type::Int3: return 4 * 3;
			case shader_data_type::Int4: return 4 * 4;
			case shader_data_type::Bool: return 1;
		}

		RB_CORE_ASSERT(false, "Uknown shader data type");
		return 0;
	}

	struct buffer_element
	{
		std::string name;
		shader_data_type type;
		uint32_t size;
		uint32_t offset;
		bool normalised;

		buffer_element() {}

		buffer_element(shader_data_type type_in, const std::string& name_in, bool normalised_in = false)
			: name(name_in), type(type_in), size(shader_data_type_size(type_in)), offset(0), normalised(normalised_in)
		{}

		uint32_t get_component_count() const
		{
			switch (type)
			{
				case shader_data_type::Float: return 1;
				case shader_data_type::Float2: return 2;
				case shader_data_type::Float3: return 3;
				case shader_data_type::Float4: return 4;
				case shader_data_type::Mat3: return 3 * 3;
				case shader_data_type::Mat4: return 4 * 4;
				case shader_data_type::Int: return 1;
				case shader_data_type::Int2: return 2;
				case shader_data_type::Int3: return 3;
				case shader_data_type::Int4: return 4;
				case shader_data_type::Bool: return 1;
			}

			RB_CORE_ASSERT(false, "Uknown shader data type");
			return 0;
		}
	};

	class buffer_layout
	{
	public:
		buffer_layout()
			: m_elements(NULL), m_stride(0) {}

		buffer_layout(const std::initializer_list<buffer_element>& elements) 
			: m_elements(elements)
		{
			calculate_offsets_and_stride();
		}

		inline uint32_t get_stride() const { return m_stride; }
		inline const std::vector<buffer_element>& get_elements() const { return m_elements; }

		std::vector<buffer_element>::iterator begin() { return m_elements.begin(); }
		std::vector<buffer_element>::iterator end() { return m_elements.end(); }
		std::vector<buffer_element>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<buffer_element>::const_iterator end() const { return m_elements.end(); }
	private:
		void calculate_offsets_and_stride()
		{
			uint32_t offset = 0;
			m_stride = 0;

			for (auto& element : m_elements)
			{
				element.offset = offset; 
				offset += element.size;
				m_stride += element.size;
			}
		}
	private:
		std::vector<buffer_element> m_elements;
		uint32_t m_stride;
	};

	class vertex_buffer
	{
	public:
		virtual ~vertex_buffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const buffer_layout& get_layout() const = 0;
		virtual void set_layout(const buffer_layout& layout) = 0;

		static vertex_buffer* create(float* vertices, uint32_t size);
	};

	class index_buffer
	{
	public:
		virtual ~index_buffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const uint32_t get_count() const = 0;


		static index_buffer* create(uint32_t* indices, uint32_t size);
	};
}