#include "rbpch.h"
#include "opengl_vertex_array.h"

#include <glad/glad.h>

Robin::opengl_vertex_array::opengl_vertex_array()
{

}

Robin::opengl_vertex_array::~opengl_vertex_array()
{
	glDeleteVertexArrays(1, &m_renderer_id);
}

void Robin::opengl_vertex_array::bind() const
{
	glBindVertexArray(m_renderer_id);
}

void Robin::opengl_vertex_array::unbind() const
{
	glBindVertexArray(0);
}
