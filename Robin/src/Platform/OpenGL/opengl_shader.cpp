#include "rbpch.h"
#include "opengl_shader.h"

#include <glm/gtc/type_ptr.hpp>

namespace Robin
{
    static GLenum shader_type_from_string(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        RB_CORE_ASSERT(false, "Unknown shader type");
        return 0;
    }

    opengl_shader::opengl_shader(const std::string& file_path)
    {
        std::string source = read_file(file_path);
        auto shader_sources = pre_process(source);

        compile(shader_sources); 

        auto last_slash = file_path.find_last_of("/\\");
        last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;

        auto last_dot = file_path.rfind('.');
        auto count = last_dot == std::string::npos ? file_path.size() - last_slash : last_dot - last_slash;
        m_name = file_path.substr(last_slash, count);
    }

    opengl_shader::opengl_shader(const std::string& vertex_source, const std::string& fragment_source)
	{
        std::unordered_map<GLenum, std::string> sources;

        sources[GL_VERTEX_SHADER] = vertex_source;
        sources[GL_FRAGMENT_SHADER] = fragment_source;

        compile(sources);
    }

    opengl_shader::~opengl_shader()
	{
        glDeleteProgram(m_renderer_id);
	}

    std::string opengl_shader::read_file(const std::string& file_path)
    {
        std::string result;
        std::ifstream in(file_path, std::ios::in | std::ios::binary);

        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            RB_CORE_ERROR("Could not open file: '{0}'", file_path);
        }

        return result;
    }

    std::unordered_map<GLenum, std::string> opengl_shader::pre_process(const std::string& source)
    {
        std::unordered_map<GLenum, std::string> shader_sources; 

        const char* type_token = "#type";
        size_t type_token_length = strlen(type_token);
        size_t pos = source.find(type_token, 0);

        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            RB_CORE_ASSERT(eol != std::string::npos, "Syntax error");

            size_t begin = pos + type_token_length + 1; 
            std::string type = source.substr(begin, eol - begin);
            RB_CORE_ASSERT(shader_type_from_string(type), "invalid shader type specified");

            size_t next_line_pos = source.find_first_not_of("\r\n", eol);
            pos = source.find(type_token, next_line_pos);
            shader_sources[shader_type_from_string(type)] = 
                source.substr(next_line_pos, 
                    pos - (next_line_pos == std::string::npos ? source.size() - 1 : next_line_pos));
        }

        return shader_sources;
    }

    void opengl_shader::compile(const std::unordered_map<GLenum, std::string>& shader_sources)
    {
        m_renderer_id = glCreateProgram();

        RB_CORE_ASSERT(shader_sources.size() <= 2, "Only supporting 2 shaders for now");
        std::array<GLenum, 2> shader_ids;
        int shade_id_index = 0;

        GLint success = 0;
        for (auto& kv : shader_sources)
        {
            GLenum type = kv.first;
            const std::string& source = kv.second;

            GLuint shader = glCreateShader(type);

            const GLchar* source_cstr = source.c_str();
            glShaderSource(shader, 1, &source_cstr, NULL);
            glCompileShader(shader);

            // print compile errors if any
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (success == GL_FALSE)
            {
                GLint max_length = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

                std::vector<GLchar> info_log(max_length);
                glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);

                glDeleteShader(shader);

                RB_CORE_ERROR("{0}", info_log.data());
                RB_CORE_ASSERT(false, "Shader compile error");
                break;
            }

            glAttachShader(m_renderer_id, shader);
            shader_ids[shade_id_index++] = shader;
        }

        glLinkProgram(m_renderer_id);
        
        glGetProgramiv(m_renderer_id, GL_LINK_STATUS, &success);

        if (success == GL_FALSE)
        {
            GLint max_length = 0;
            glGetProgramiv(m_renderer_id, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> info_log(max_length);
            glGetProgramInfoLog(m_renderer_id, max_length, &max_length, &info_log[0]);

            for (auto id : shader_ids)
                glDeleteShader(id);

            RB_CORE_ERROR("{0}", info_log.data());
            RB_CORE_ASSERT(false, "fragment shader compile error");
        }

        for (auto id : shader_ids)
            glDetachShader(m_renderer_id, id);
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