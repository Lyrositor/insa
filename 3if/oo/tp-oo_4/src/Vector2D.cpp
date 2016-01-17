#include "Vector2D.h"

std::string Vector2D::serialize()
{
    return std::to_string(x) + ";" + std::to_string(y);
}

void Vector2D::unserialize()
{

}
