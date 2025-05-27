#include "rbpch.h"
#include "shader.h"

#include <glad/glad.h>

namespace Robin
{
	Robin::shader::shader(const std::string& vertex_source, const std::string& fragment_source)
	{
        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        const GLchar* source = vertex_source.c_str();
        glShaderSource(vertex, 1, &source, NULL);
        glCompileShader(vertex);

        // print compile errors if any
        GLint success;
        glGetShaderiv(GL_VERTEX_SHADER, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE)
        {
            GLint max_length = 0; 
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> info_log(max_length);
            glGetShaderInfoLog(vertex, max_length, &max_length, &info_log[0]);

            glDeleteShader(vertex);

            RB_CORE_ERROR("{0}", info_log.data());
            RB_CORE_ASSERT(false, "vertex shader compile error");
        }

        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        source = fragment_source.c_str();
        glShaderSource(fragment, 1, &source, NULL);
        glCompileShader(fragment);

        glGetShaderiv(GL_FRAGMENT_SHADER, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE)
        {
            GLint max_length = 0;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> info_log(max_length);
            glGetShaderInfoLog(vertex, max_length, &max_length, &info_log[0]);

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            RB_CORE_ERROR("{0}", info_log.data());
            RB_CORE_ASSERT(false, "fragment shader compile error");
        }

        m_renderer_id = glCreateProgram();
        glAttachShader(m_renderer_id, vertex);
        glAttachShader(m_renderer_id, fragment);
        glLinkProgram(m_renderer_id);

        glGetProgramiv(m_renderer_id, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE)
        {
            GLint max_length = 0;
            glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> info_log(max_length);
            glGetProgramInfoLog(m_renderer_id, max_length, &max_length, &info_log[0]);

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            RB_CORE_ERROR("{0}", info_log.data());
            RB_CORE_ASSERT(false, "fragment shader compile error");
        }

        glDetachShader(m_renderer_id, vertex);
        glDetachShader(m_renderer_id, fragment);
    }

	Robin::shader::~shader()
	{
        glDeleteProgram(m_renderer_id);
	}

	void Robin::shader::bind() const
	{
        glUseProgram(m_renderer_id);
	}

	void Robin::shader::unbind() const
	{
        glUseProgram(0);
	}
}