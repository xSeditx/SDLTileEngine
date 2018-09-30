#include"Entity.h"
#include"Fonts.h"
#include"World.h"

#define FORWARD       0
#define BACKWARDS     3
#define LEFT          1
#define RIGHT         2
/*========================================================================================================================================================================================

STATIC DEFINITIONS
Simplest way to handle this stuff in the timeframe required.
========================================================================================================================================================================================*/

Enemy           *Entity::CthuluEye,
*Entity::Dragon,
*Entity::GreenEye;
Player          *Entity::PlayerOne;
Powerup         *Entity::EnergySphere;
Projectile      *Entity::Bullets;
StaticObject    *Entity::Explosion;
EnemyProjectile *Entity::FireBall;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Enemy Enemy::EnemyList[MAX_ENEMIES];
int Enemy::NumberOfEnemies = 0;

std::vector<int>
Enemy::EnemyValidID;
//---------------------------------------------------------------------
Projectile Projectile::ProjectileList[MAX_PROJECTILES];
int Projectile::NumberOfProjectiles = 0;

std::vector<int>
Projectile::ProjectileValidID;
//---------------------------------------------------------------------

EnemyProjectile EnemyProjectile::EnemyProjectileList[MAX_PROJECTILES];
int EnemyProjectile::NumberOfProjectiles = 0;

std::vector<int>
EnemyProjectile::ProjectileValidID;
//---------------------------------------------------------------------

StaticObject StaticObject::StaticObjectList[MAX_STATICOBJECTS];
int StaticObject::NumberOfStaticObjectList = 0;

std::vector<int>
StaticObject::StaticObjectValidID;
//---------------------------------------------------------------------

Powerup Powerup::PowerupList[MAX_POWERUPS];
int Powerup::NumberOfPowerup = 0;

std::vector<int>
Powerup::PowerupValidID;
//---------------------------------------------------------------------

/*========================================================================================================================================================================================
__________________________________________________________________________________________________________________________________________________________________________________________
========================================================================================================================================================================================*/


/*========================================================================================================================================================================================

Game Mechanics

========================================================================================================================================================================================
NOTES: Various different mechanics for the Behaviors of different Enemies and Entitys this allows for overiding of the Update() method
Allowing me to specify direct mechanics for every different sprite if I wish.
========================================================================================================================================================================================*/


void Default_Response(Entity *other) //  Do Nothing
{
}
void DefaultEnemyUpdate(Enemy *object)
{

}
void EnemyProjectileResponse(Enemy *mob, Projectile *bullet)
{
}
void DefaultProjectileResponse(Entity *mob, Projectile *bullet)
{
}








/*========================================================================================================================================================================================

OBJECT CONSTRUCTION FUNCTIONS

========================================================================================================================================================================================*/
void Entity::Unload()
{
}

Enemy::Enemy()
{
	Health = 100;
	Alive = false;
	Position = Vec2(0, 0);
	Invincible = false;
	ID = 0;
	Age = 0;
	Type = EntityType::EnemyEntity;
	SetSpecialUpdate(DefaultEnemyUpdate);
}
Enemy::Enemy(Vec2  pos, Vec2 vel, Sprite img)
{
	Health = 100;
	Alive = true;
	Position = Vec2(0, 0);
	Picture = img;
	Age = 0;

	Invincible = false;

	CollisionResponse.SetEnemyResponse(Default_Response);
	CollisionResponse.SetPlayerReponse(Default_Response);
	CollisionResponse.SetPowerUpReponse(Default_Response);
	CollisionResponse.SetStaticObjectReponse(Default_Response);
	CollisionResponse.SetProjectileReponse(EnemyProjectileResponse);

	Type = EntityType::EnemyEntity;
	SetSpecialUpdate(DefaultEnemyUpdate);
}

Powerup::Powerup(Vec2 pos, Vec2 vel, Sprite *img)
{
	CollisionResponse.SetEnemyResponse(Default_Response);
	CollisionResponse.SetPlayerReponse(Default_Response);
	CollisionResponse.SetPowerUpReponse(Default_Response);
	CollisionResponse.SetStaticObjectReponse(Default_Response);
	CollisionResponse.SetProjectileReponse(EnemyProjectileResponse);

	Type = EntityType::PowerUpEntity;

	Position = pos;
	CollisionBox = img->MakeCollisionBox();
	CollisionBox->Position = pos;
	CollisionBox->Body.Force = vel;
	Picture = *img;
	Alive = false;
	SpecialUpdate = NULL;
	SpecialEffect = NULL;
}
Projectile::Projectile(Vec2 pos, Vec2 vel, Sprite *img)
{
	Position = pos;
	CollisionBox = img->MakeCollisionBox();
	CollisionBox->Position = pos;
	CollisionBox->Body.Velocity = vel; // Steady speed just changed this watch out
	Picture = *img;
	Alive = false;
	Type = EntityType::ProjectileEntity;
	SpecialUpdate = NULL;
}
StaticObject::StaticObject()
{
	Alive = false;
	Position = Vec2(0, 0);
	Invincible = true;
	ID = 0;
	Age = 0;
	Type = EntityType::StaticEntity;
	SpecialUpdate = NULL;
}
StaticObject::StaticObject(Vec2  pos, Vec2 vel, Sprite img)
{

	Alive = true;
	Position = Vec2(0, 0);
	Picture = img;
	Age = 0;

	Invincible = false;

	CollisionResponse.SetEnemyResponse(Default_Response);
	CollisionResponse.SetPlayerReponse(Default_Response);
	CollisionResponse.SetPowerUpReponse(Default_Response);
	CollisionResponse.SetStaticObjectReponse(Default_Response);
	CollisionResponse.SetProjectileReponse(EnemyProjectileResponse);
	Type = EntityType::StaticEntity;
	SetSpecialUpdate(DefaultEnemyUpdate);
}
EnemyProjectile::EnemyProjectile(Vec2 pos, Vec2 vel, Sprite *img)
{
	Position = pos;
	CollisionBox = img->MakeCollisionBox();
	CollisionBox->Position = pos;
	CollisionBox->Body.Velocity = vel;
	CollisionBox->Body.Force = Vec2(0, 0);
	Picture = *img;
	Alive = false;
	Type = EntityType::ProjectileEntity;
	BulletPower = 3;
	SpecialUpdate = NULL;
}


/*========================================================================================================================================================================================

INITIALIZATION FUNCTIONS

========================================================================================================================================================================================*/



void Enemy::Initialize()
{
	EnemyValidID.reserve(MAX_ENEMIES);
	for_loop(Count, MAX_ENEMIES)
	{
		EnemyValidID.push_back(MAX_ENEMIES - (Count + 1));
	}
}
void Entity::Initialize()
{
}
void Powerup::Initialize()
{
	PowerupValidID.reserve(MAX_POWERUPS);
	for_loop(Count, MAX_POWERUPS)
	{
		PowerupValidID.push_back(MAX_POWERUPS - (Count + 1));
	}
}
void Projectile::Initialize()
{
	ProjectileValidID.reserve(MAX_PROJECTILES);
	for_loop(Count, MAX_PROJECTILES)
	{
		ProjectileValidID.push_back(MAX_PROJECTILES - (Count + 1));
	}
}
void StaticObject::Initialize()
{
	StaticObjectValidID.reserve(MAX_STATICOBJECTS);
	for_loop(Count, MAX_STATICOBJECTS)
	{
		StaticObjectValidID.push_back(MAX_STATICOBJECTS - (Count + 1));
	}
}
void EnemyProjectile::Initialize()
{
	ProjectileValidID.reserve(MAX_PROJECTILES);
	for_loop(Count, MAX_PROJECTILES)
	{
		ProjectileValidID.push_back(MAX_PROJECTILES - (Count + 1));
	}
}


/*========================================================================================================================================================================================

SPAWN FUNCTIONS

========================================================================================================================================================================================*/


int Enemy::Spawn(Vec2 pos, Vec2 vel, Sprite img)
{
	if (EnemyValidID.empty() != true)
	{
		int Index = EnemyValidID.back();
		EnemyList[Index].Alive = true;
		EnemyList[Index].Health = 100;
		EnemyList[Index].Position = pos;
		EnemyList[Index].Picture = img;

		//*********************************!!!! WARNING !!!!!!  What The Fuck Is This Shit ************************************************
		// GLM Occasionally throws an Error here for seeingly no reason so instead of using their = I will attempt to use
		// Just a typical = instead of the glm::vec2 = and pray that fixes it

		//FUCK ITS STILL HAPPENING WTF

		// This time Enemies just stopped spawning for about an entire minute for seemingly no reason.
		// I had one life left and I came back they never spawned and then thrown this Access error.
		// I have no idea... Its got to be because of threading the loading screen, that is the only thing I can think of right now 
		// because that is around the time this all started.
		//   916: 			this->_Orphan_all();
		// 000CDC65  mov         esi,esp  
		// 000CDC67  mov         ecx,dword ptr [this]  
		// 000CDC6A  call        dword ptr ds:[121624h]  //<- Must be the error
		// 000CDC70  cmp         esi,esp    // Next line of code to be called.
		// 000CDC72  call        __RTC_CheckEsp (0BBEE2h)  
		//  In the above This is SpriteSheet Explosion1;
		// Damnit... Index == 194 and yet EnemyList only has 50 Elements... Thats gotta be it
		// How has that not been crashing it already?
		// Nope not it atleast not why the enemies stop spawning. The ValidID has gone totally blank...
		// UPDATE: *I BELIEVE I SOLVED THIS ISSUE AND IT WAS AN ERROR DUE TO NOT ENOUGH ENEMIES BEING ABLE TO SPAWN OR SOME SHIT LIKE THAT
		EnemyList[Index].Speed.x = vel.x;
		EnemyList[Index].Speed.y = vel.y;
		// ******************************************************************************************************************************
		EnemyList[Index].CollisionBox = EnemyList[Index].Picture.MakeCollisionBox();
		EnemyList[Index].CollisionBox->Body.Position = pos;
		EnemyList[Index].ID = Index;
		EnemyList[Index].Age = 0;
		EnemyList[Index].Worth = 50;
		//        EnemyList[Index].CollisionBox->Body.Velocity = Vec2(0,5);
		EnemyValidID.pop_back();
		return Index;
	}
	return 0;
}
int Powerup::Spawn(Vec2 pos, Vec2 vel, Sprite *img)
{
	if (PowerupValidID.empty() != true)
	{
		int Index = PowerupValidID.back();
		// PowerupList[Index] = *Entity::Bullets;
		PowerupList[Index].Alive = true;
		PowerupList[Index].Position = pos;
		PowerupList[Index].Picture = *img;
		//PowerupList[Index].Speed = vel;
		PowerupList[Index].CollisionBox = PowerupList[Index].Picture.MakeCollisionBox();
		PowerupList[Index].CollisionBox->Body.Position = pos;
		PowerupList[Index].ID = Index;
		PowerupList[Index].Age = 0;
		PowerupList[Index].EnergyBuff = 10;
		PowerupList[Index].CollisionBox->Body.Velocity = vel;
		PowerupValidID.pop_back();
		return Index;
	}
	return 0;
}
int Projectile::Spawn(Vec2 pos, Vec2 vel, Projectile *object)
{
	if (ProjectileValidID.empty() != true)
	{
		int Index = ProjectileValidID.back();
		ProjectileList[Index] = *Entity::Bullets;

		ProjectileList[Index].Alive = true;
		ProjectileList[Index].Position = pos;

		ProjectileList[Index].Speed = vel;

		ProjectileList[Index].CollisionBox = object->CollisionBox; //ProjectileList[Index].Picture.MakeCollisionBox();
		ProjectileList[Index].CollisionBox->Body.Position = pos;
		ProjectileList[Index].ID = Index;
		ProjectileList[Index].Age = 0;
		ProjectileList[Index].CollisionBox->Body.Velocity = vel;
		ProjectileValidID.pop_back();
		return Index;
	}
	return 0;
}
int Projectile::Spawn(Vec2 pos, Vec2 vel, Sprite *img)
{
	if (ProjectileValidID.empty() != true)
	{
		int Index = ProjectileValidID.back();
		ProjectileList[Index] = *Entity::Bullets;

		ProjectileList[Index].Alive = true;
		ProjectileList[Index].Position = pos;
		ProjectileList[Index].Picture = *img;
		ProjectileList[Index].Speed = vel;
		ProjectileList[Index].CollisionBox = ProjectileList[Index].Picture.MakeCollisionBox();
		ProjectileList[Index].CollisionBox->Body.Position = pos;
		ProjectileList[Index].ID = Index;
		ProjectileList[Index].Age = 0;
		ProjectileList[Index].CollisionBox->Body.Velocity = vel;
		ProjectileValidID.pop_back();
		return Index;
	}
	return 0;
}
int StaticObject::Spawn(Vec2 pos, Vec2 vel, double lifespan, Sprite img)
{
	if (StaticObjectValidID.empty() != true)
	{

		int Index = StaticObjectValidID.back();
		StaticObjectList[Index].Alive = true;
		StaticObjectList[Index].Timer = SDL_GetTicks();
		StaticObjectList[Index].Position = pos;
		StaticObjectList[Index].Picture = img;
		StaticObjectList[Index].Speed = vel;
		StaticObjectList[Index].CollisionBox = StaticObjectList[Index].Picture.MakeCollisionBox();
		StaticObjectList[Index].CollisionBox->Body.Position = pos;
		StaticObjectList[Index].ID = Index;
		StaticObjectList[Index].Age = 0;
		StaticObjectList[Index].CollisionBox->Body.Velocity = Vec2(0, 5);
		StaticObjectValidID.pop_back();
		return Index;
	}
	return 0;
}
int EnemyProjectile::Spawn(Vec2 pos, Vec2 vel, EnemyProjectile *object)
{
	if (ProjectileValidID.empty() != true)
	{
		int Index = ProjectileValidID.back();
		EnemyProjectileList[Index] = *Entity::FireBall;


		EnemyProjectileList[Index].Alive = true;
		EnemyProjectileList[Index].Position = pos;

		EnemyProjectileList[Index].Speed = vel;

		EnemyProjectileList[Index].CollisionBox = object->CollisionBox; //ProjectileList[Index].Picture.MakeCollisionBox();
		EnemyProjectileList[Index].CollisionBox->Body.Position = pos;
		EnemyProjectileList[Index].ID = Index;
		EnemyProjectileList[Index].Age = 0;
		EnemyProjectileList[Index].CollisionBox->Body.Velocity = vel;
		ProjectileValidID.pop_back();
		return Index;
	}
	return 0;
}
int EnemyProjectile::Spawn(Vec2 pos, Vec2 vel, Sprite *img)
{
	if (ProjectileValidID.empty() != true)
	{
		int Index = ProjectileValidID.back();
		EnemyProjectileList[Index] = *Entity::FireBall;
		EnemyProjectileList[Index].Alive = true;
		EnemyProjectileList[Index].Position = pos;
		EnemyProjectileList[Index].Picture = *img;
		EnemyProjectileList[Index].Speed = vel;
		EnemyProjectileList[Index].CollisionBox = EnemyProjectileList[Index].Picture.MakeCollisionBox();
		EnemyProjectileList[Index].CollisionBox->Body.Position = pos;
		EnemyProjectileList[Index].ID = Index;
		//EnemyProjectileList[Index].BulletPower = 25;// Change1.... Should I uncomment this
		EnemyProjectileList[Index].Age = 0;
		EnemyProjectileList[Index].CollisionBox->Body.Velocity = vel;

		ProjectileValidID.pop_back();
		return Index;
	}
	return 0;
}


/*========================================================================================================================================================================================

UPDATE FUNCTIONS

========================================================================================================================================================================================*/

void Enemy::Update()
{
	SpecialUpdate(this);
}

void Powerup::Update()
{
	if (Alive)
	{
		Age++; // Increase the age so we can kill it if its getting to old.
		if (Age >= 500)
		{
			Kill();
			return;
		}

		// CollisionBox->Body.Velocity = Speed; //Set the Velocity Tinker with this to get a good speed out of the projectiles
		CollisionBox->Update();

		if (CollisionBox->IsCollision(Entity::PlayerOne->CollisionBox)) // Means it collided with the player
		{
			SpecialEffect();
			Kill();
			Print("Picked up Powerup");
		}
		Position = CollisionBox->Position;// Set the Position of the Bullet to the CollisionBox position
		Picture.Position = Position;     // Set the Sprite Image to the Position of the Projectile
	}
}
void Projectile::Update()
{
	if (Alive)
	{
		Age++; // Increase the age so we can kill it if its getting to old.
		if (Age > 200)
		{
			Kill();
			return;
		}

		CollisionBox->Body.Velocity = Speed; // Apply force so it moves. Tinker with this to get a good speed out of the projectiles
		CollisionBox->Update();

		for (auto &E : Enemy::EnemyList) // Check to see if the Players Bullet hit an Enemy
		{
			if (E.Alive) // But only if the Bullet is Alive
			{
				if (E.CollisionBox->IsCollision(CollisionBox))
				{
					E.Health -= BulletPower;
					Kill();

					Print("Bullet Hit Enemy");
				}
			}
		}
		Position = CollisionBox->Position;// Set the Position of the Bullet to the CollisionBox position
		Picture.Position = Position;     // Set the Sprite Image to the Position of the Projectile
	}
}
void StaticObject::Update()
{
	if (Alive == true)
	{
		Age++;
		CollisionBox->Body.Force = Vec2(0, 0);//Speed;

		CollisionBox->Update();
		Position = CollisionBox->Position;
		Picture.Position = Position;

		if (Position.y > SCREENHEIGHT + SCREEN_BUFFER_AREA || Position.y < -SCREEN_BUFFER_AREA)
		{
			Kill();
		}

		if (SDL_GetTicks() - Timer >= 1000)
		{
			Kill();
		}
	}

}
void EnemyProjectile::Update()
{
	if (Alive)
	{
		Age++; // Increase the age so we can kill it if its getting to old.
		if (Age >= 200)
		{
			Kill();
			return;
		}

		CollisionBox->Body.Velocity = Speed; //Set the Velocity Tinker with this to get a good speed out of the projectiles
		CollisionBox->Update();

		//if (CollisionBox->IsCollision(Entity::PlayerOne->CollisionBox)) // Means it collided with the player
		//{
		//	Entity::PlayerOne->Health -= BulletPower;
		//	//Entity::PlayerOne->Invincible = true;
		//	Entity::PlayerOne->InvincibilityTimer = SDL_GetTicks();
		//	Death->Play();
		//	Kill();
		//	Print("Player Hit by FireBall");
		//}
		Position = CollisionBox->Position;// Set the Position of the Bullet to the CollisionBox position
		Picture.Position = Position;     // Set the Sprite Image to the Position of the Projectile
	}
}

/*========================================================================================================================================================================================

DEATH & DESPAW FUNCTIONS

========================================================================================================================================================================================*/

void Enemy::Kill()
{
	EnemyValidID.push_back(ID);
	Alive = false;
}
void Powerup::Kill()
{
	PowerupValidID.push_back(ID);
	Alive = false;
}
void Projectile::Kill()
{
	ProjectileValidID.push_back(ID);
	Alive = false;
}
void StaticObject::Kill()
{
	StaticObjectValidID.push_back(ID);
	Alive = false;
}
void EnemyProjectile::Kill()
{
	ProjectileValidID.push_back(ID);
	Alive = false;
}


/*========================================================================================================================================================================================

RENDERING FUNCTIONS

========================================================================================================================================================================================*/

void Enemy::Render()
{
	Picture.Render();
}
void Powerup::Render()
{
	Picture.Render();
}
void Projectile::Render()
{
	Picture.Position = CollisionBox->Position;
	Picture.Render();
}
void StaticObject::Render()
{
	Picture.Render();
}
void EnemyProjectile::Render()
{
	Picture.Position = CollisionBox->Position;
	Picture.Render();
}

/*========================================================================================================================================================================================

RESPONSE FUNCTIONS

========================================================================================================================================================================================*/


void Enemy::Response(Entity *other)
{
	switch (other->Type)
	{
	case EnemyEntity:
		CollisionResponse.EnemyResponse(other);
		break;

	case StaticEntity:
		CollisionResponse.StaticObjectReponse(other);
		break;

	case PowerUpEntity:
		CollisionResponse.PowerUpReponse(other);
		break;

	case PlayerEntity:
		CollisionResponse.PlayerReponse(other);
		break;
	}
}
void Powerup::Response(Entity *other)
{
}
void Projectile::Response(Entity *other) {}
void StaticObject::Response(Entity *other)
{
	switch (other->Type)
	{
	case EnemyEntity:
		CollisionResponse.EnemyResponse(other);
		break;

	case StaticEntity:
		CollisionResponse.StaticObjectReponse(other);
		break;

	case PowerUpEntity:
		CollisionResponse.PowerUpReponse(other);
		break;

	case PlayerEntity:
		CollisionResponse.PlayerReponse(other);
		break;
	}
}
void EnemyProjectile::Response(Entity *other) {}