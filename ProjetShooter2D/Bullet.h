#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
public:
	Bullet(Texture* texture, Vector2f pos);
	~Bullet();

	Sprite shape;

	//Getter et Setter
	/*Sprite getShape();
	void setShape(Sprite shap);*/

protected:

private:
	//Sprite shape1;

};

