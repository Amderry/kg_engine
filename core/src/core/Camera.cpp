#include <core/Camera.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace engine_core
{
	Camera::Camera(const glm::vec3& position, const glm::vec3& rotation, const Projection_Type projection_type)
		: cm_position(position), cm_rotation(rotation), cm_projection_type(projection_type)
	{
		update_view_matrix();
		update_projection_matrix();
	}

	void Camera::update_view_matrix()
	{
		const float roll_in_radians = glm::radians(this->cm_rotation.x);
		const float pitch_in_radians = glm::radians(this->cm_rotation.y);
		const float yaw_in_radians = glm::radians(this->cm_rotation.z);

		glm::mat4 translation_matrix
		{
			1,              0,              0,              0,
			0,              1,              0,              0,
			0,              0,              1,              0,
			-this->cm_position[0], -this->cm_position[1], -this->cm_position[2], 1
		};

		glm::mat3 rotation_matrix_z
		{
			cos(yaw_in_radians), sin(yaw_in_radians), 0, 
		   -sin(yaw_in_radians), cos(yaw_in_radians), 0,
		   0,                         0,                        1
		};

		glm::mat3 rotation_matrix_y
		{
		   cos(pitch_in_radians), 0, -sin(pitch_in_radians),
		   0,						  1,					    0,
		   sin(pitch_in_radians),0,   cos(pitch_in_radians)
		};

		glm::mat3 rotation_matrix_x
		{
		   1, 0, 0,
		   0, cos(roll_in_radians), sin(roll_in_radians),
		   0, -sin(roll_in_radians), cos(roll_in_radians)
		};

		const glm::mat3 euler_rotate_matrix = rotation_matrix_z * rotation_matrix_y * rotation_matrix_x;

		this->cm_direction = glm::normalize(euler_rotate_matrix * s_world_forward);
		this->cm_right = glm::normalize(euler_rotate_matrix * s_world_right);
		this->cm_up = glm::normalize(euler_rotate_matrix * s_world_up);

		this->cm_view_matrix = glm::lookAt(this->cm_position, this->cm_position + this->cm_direction, this->cm_up);
	}

	void Camera::update_projection_matrix()
	{
		if (this->cm_projection_type == Projection_Type::Perspective)
		{
			float r = 0.1f;
			float t = 0.1f;
			float f = 10;
			float n = 0.1f;

			this->cm_projection_matrix = glm::mat4(n / r, 0, 0, 0,
				0, n / t, 0, 0,
				0, 0, (-f - n) / (f - n), -1,
				0, 0, -2 * f * n / (f - n), 0);
		}
		else
		{
			float r = 2;
			float t = 2;
			float f = 100;
			float n = 0.1f;

			this->cm_projection_matrix = glm::mat4(1 / r, 0, 0, 0,
				0, 1 / t, 0, 0,
				0, 0, -2 / (f - n), 0,
				0, 0, (-f - n) / (f - n), 1);
		}
	}

	void Camera::set_position(const glm::vec3& position)
	{
		this->cm_position = position;
		this->update_view_matrix();
	}

	void Camera::set_rotation(const glm::vec3& rotation)
	{
		this->cm_rotation = rotation;
		this->update_view_matrix();
	}

	void Camera::set_position_rotation(const glm::vec3& position, const glm::vec3& rotation)
	{
		this->cm_position = position;
		this->cm_rotation = rotation;
		this->update_view_matrix();
	}

	void Camera::set_projection_type(const Projection_Type projection_type)
	{
		this->cm_projection_type = projection_type;
		this->update_projection_matrix();
	}

	glm::mat4 Camera::get_view_matrix()
	{
		if (this->is_update_view_matrix)
		{
			update_view_matrix();
			this->is_update_view_matrix = false;
		}
		return this->cm_view_matrix;
	}

	void Camera::move_forward(const float delta)
	{
		this->cm_position += this->cm_direction * delta;
		this->is_update_view_matrix = true;
	}

	void Camera::move_up(const float delta)
	{
		this->cm_position += this->cm_up * delta;
		this->is_update_view_matrix = true;
	}

	void Camera::move_right(const float delta)
	{
		this->cm_position += this->cm_right * delta;
		this->is_update_view_matrix = true;
	}
	void Camera::add_movement_and_rotation(const glm::vec3& movement_delta, const glm::vec3& rotation_delta)
	{
		this->cm_position += this->cm_direction * movement_delta.x;
		this->cm_position += this->cm_right	    * movement_delta.y;
		this->cm_position += this->cm_up        * movement_delta.z;
		this->cm_rotation += rotation_delta;
		this->is_update_view_matrix = true;
	}
}