#include "Collision.h"

bool Collision::CheckCollision(Character& OtherActor)
{
	//topleft corner 
	if (OtherActor.x > colliderX && OtherActor.x < colliderX + colliderWidth)
	{
		if (OtherActor.y > colliderY && OtherActor.y < colliderY + colliderHeight)
		{
		std::cout << "hit" << std::endl;
		}
	} 

	//topright corner
	if (OtherActor.x + OtherActor.size.x > colliderX && OtherActor.x + OtherActor.size.x < colliderX + colliderWidth)
	{
		if (OtherActor.y > colliderY && OtherActor.y < colliderY + colliderHeight)
		{
		std::cout << "hit" << std::endl;
		}
	}

	//bottomleft corner
	if (OtherActor.x >colliderX && OtherActor.x < colliderX + colliderWidth )
	{
		if (OtherActor.y + OtherActor.size.y > colliderY && OtherActor.y + OtherActor.size.y < colliderY + colliderHeight)
		{
			std::cout << "hit" << std::endl;
		}
	}

	//bottomright corner
	if (OtherActor.x + OtherActor.size.x > colliderX && OtherActor.x + OtherActor.size.x < colliderX + colliderWidth)
	{
		if (OtherActor.y + OtherActor.size.y > colliderY && OtherActor.y + OtherActor.size.y < colliderY + colliderHeight)
		{
			std::cout << "hit" << std::endl;
		}
	}
	return false;
}
