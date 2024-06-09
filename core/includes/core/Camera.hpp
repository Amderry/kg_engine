#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_float4x4.hpp>

namespace engine_core
{
	class Camera
	{
	public:
		enum class Projection_Type
		{
			Perspective,
			Ortographic
		};

		Camera(const glm::vec3& position = { 0, 0, 0 },
			   const glm::vec3& rotation = { 0, 0, 0 },
			   const Projection_Type projection_type = Projection_Type::Perspective);

		void set_position(const glm::vec3& position);
		void set_rotation(const glm::vec3& rotation);
		void set_position_rotation(const glm::vec3& position, const glm::vec3& rotation);
		void set_projection_type(const Projection_Type projection_type);
		glm::mat4 get_view_matrix();
		glm::mat4 get_projection_matrix() const { return this->cm_projection_matrix; }

		void move_forward(const float delta);
		void move_up(const float delta);
		void move_right(const float delta);

		void add_movement_and_rotation(const glm::vec3& movement_delta, const glm::vec3& rotation_delta);

		const glm::vec3& get_camera_position() const { return this->cm_position; };
		const glm::vec3& get_camera_rotation() const { return this->cm_rotation; };

	private:
		void update_view_matrix();
		void update_projection_matrix();
		glm::vec3 cm_position;
		glm::vec3 cm_rotation; //x - крен, y - тангаж, z - рыскание

		glm::mat4 cm_view_matrix;
		glm::mat4 cm_projection_matrix;

		glm::vec3 cm_direction;
		glm::vec3 cm_right;
		glm::vec3 cm_up;

		static constexpr glm::vec3 s_world_up{ 0.f, 0.f, 1.f };
		static constexpr glm::vec3 s_world_forward{ 1.f, 0.f, 0.f };
		static constexpr glm::vec3 s_world_right{ 0.f, 1.f, 0.f };

		Projection_Type cm_projection_type;

		bool is_update_view_matrix = false;
	};
}