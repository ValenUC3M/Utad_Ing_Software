#include "projectileMovementComponent.h"
#include "projectileColisionComponent.h"
#include "platformRenderComponent.h"
#include "ballRenderComponent.h"
#include "ballColisionComponent.h"
#include "entity.h"
#include "manager.h"
#include "message.h"
#include "sys.h"

void ProjectileColisionComponent::Slot() 
{ 
	Manager* manager = manager->getInstance();
	std::vector<Entity*> entities = manager->getEntities();
	std::vector<Entity*> platforms = manager->getPlatforms();


	BallColisionComponent* otherEntityCollision = nullptr;
	bool colliding = false;
	// collision with balls
	for (Entity* otherEntity : entities)
	{
		if (entityOwner != otherEntity)
		{
			otherEntityCollision = otherEntity->FindComponent<BallColisionComponent>();

			float ballRadius = otherEntityCollision->GetRadius();
			vec2 ballPosition = otherEntityCollision->GetPosition();

			float limit2 = (m_radius + ballRadius) * (m_radius + ballRadius);

			// collision with the projectile head
			if (vlen2(m_position - ballPosition) <= limit2) {
				colliding = true;
				otherEntityCollision->entityOwner->toBeDeleted = true;
				break;
			}

			// collision with the projectile trace
			if (m_typeOfProjectile == 0)
			{
				// range from where no collision
				float maxDistanceX = (m_radius / 2) + ballRadius;

				bool topCheck = m_position.y > ballPosition.y;
				bool botCheck = m_startingPosition.y < ballPosition.y;
				bool distanceCheck = maxDistanceX >= abs(m_position.x - ballPosition.x);

				if (distanceCheck && topCheck && botCheck)
				{
					colliding = true;
					otherEntityCollision->entityOwner->toBeDeleted = true;
					break;
				}
			}
		}
	}

	// collision with platforms

	for (Entity* platform : platforms)
	{
		PLatformRenderComponent* pData = platform->FindComponent<PLatformRenderComponent>();

		vec2 pPos = pData->GetPosition(); 
		vec2 size = pData->GetSize();

		float distanceX = abs(pPos.x - m_position.x);
		float distanceY = abs(pPos.y - m_position.y);

		float maxDistanceX = abs(pData->GetSize().x / 2 + m_radius);
		float maxDistanceY = abs(pData->GetSize().y / 2 + m_radius);

		if (distanceX < maxDistanceX && distanceY < maxDistanceY)
		{
			colliding = true;
			break;
		}
	}

	// if collided or on ceiling
	if ((m_position.y > SCR_HEIGHT) || (m_position.y < FLOOR) || colliding) 
	{
		entityOwner->toBeDeleted = true;
	}

	if ((m_position.x > (SCR_WIDTH - m_radius)) || (m_position.x < m_radius))
	{
		NewVelocityMessage* lateralCollision = new NewVelocityMessage(vec2(-1, 1));
		entityOwner->SendMsg(lateralCollision);
		delete lateralCollision;
	}
}

void ProjectileColisionComponent::ReceiveMessage(Message* msg) 
{
	//if new position
	NewPositionMessage* newPositionMessage = dynamic_cast<NewPositionMessage*>(msg);
	if (newPositionMessage)
	{
		m_position = newPositionMessage->newPos;
	}
}