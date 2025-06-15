#pragma once

#include "Robin.h"

class sandbox_3D : public Robin::layer
{
public: 
	sandbox_3D();
	~sandbox_3D();

	void on_attach() override; 
	void on_detach() override;
	void on_update(Robin::timestep timestep) override;
	void on_imgui_render() override;
	void on_event(Robin::event& event) override;

private:
	bool on_button_press(Robin::mouse_button_pressed_event& e);
	bool on_button_release(Robin::mouse_button_released_event &e);
	bool is_cursor_visible();
private:
	Robin::shader_library m_shader_library;

	Robin::ref<Robin::vertex_array> m_vertex_array;
	Robin::ref<Robin::texture_2D> m_texture;
	Robin::ref<Robin::texture_2D> m_transparent_texture;
	Robin::ref<Robin::texture_2D> m_current_texture;

	Robin::ref<Robin::vertex_array> m_screen_vertex_array;
	Robin::ref<Robin::framebuffer> m_framebuffer;

	glm::mat4 m_transform;
	glm::mat4 m_origin;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_colour;

	float m_scale;

	Robin::perspective_camera m_camera;
	glm::vec3 m_camera_position;
	float m_camera_rotation;

	float m_camera_speed = 1.0f;
	float m_camera_rotation_speed = 20.0f;

	float m_last_x = 0.f;
	float m_last_y = 0.f;
	bool m_first_mouse = true;
};

