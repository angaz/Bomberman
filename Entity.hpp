#ifndef NEW_ENTITY_HPP
#define NEW_ENTITY_HPP

#include <glm/glm.hpp>

#include "Model.hpp"

class Entity {
public:
	Entity() = default;
	~Entity() = default;

	Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, const Model &model);

	void		addPosition(const glm::vec3 &delta);
	void		setPosition(const glm::vec3 &position);
	void		addRotation(const glm::vec3 &delta);
	void		setRotation(const glm::vec3 &rotation);

	const Model		&getModel() const;
	glm::vec3	getPosition() const;
	glm::vec3	getRotation() const;
	float 		getScale() const;

private:
	Model		_model;
	glm::vec3	_position;
	glm::vec3	_rotation;
	float 		_scale;
};


#endif //NEW_ENTITY_HPP