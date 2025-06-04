#include "rbpch.h"
#include "opengl_shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace Robin
{
	opengl_shader::opengl_shader(const std::string& vertex_source, const std::string& fragment_source)
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

    opengl_shader::~opengl_shader()
	{
        glDeleteProgram(m_renderer_id);
	}

	void opengl_shader::bind() const
	{
        glUseProgram(m_renderer_id);
	}

	void opengl_shader::unbind() const
	{
        glUseProgram(0);
	}

    void opengl_shader::set_int(const std::string& name, const int value) const
    {
        glUniform1i(glGetUniformLocation(m_renderer_id, name.c_str()), value);
    }

    void opengl_shader::set_float3(const std::string& name, const glm::vec3& vector) const
    {
        glUniform3f(glGetUniformLocation(m_renderer_id, name.c_str()), vector.x, vector.y, vector.z);
    }

    void opengl_shader::set_float4(const std::string& name, const glm::vec4& vector) const
    {
        glUniform4f(glGetUniformLocation(m_renderer_id, name.c_str()), vector.x, vector.y, vector.z, vector.w);
    }

    void opengl_shader::set_mat4(const std::string& name, const glm::mat4& matrix) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_renderer_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}