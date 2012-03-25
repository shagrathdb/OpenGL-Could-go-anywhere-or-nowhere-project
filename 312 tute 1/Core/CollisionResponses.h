#include "../Global/Global.h"
#include "../AI/HonirAI.h"
#include "../AI/HonirBossAI.h"
#include "../Weapons/Projectile.h"
#include "../Level/Level.h"
#include "../Level/WaveLevel.h"

using namespace Honir::Global;

void AITakeDamage(CollisionData* cd)
{
	Projectile* bullet;
	HonirAI* tempAI;

	if(cd->objectA->GetObjectType() == "Projectile")
	{
		bullet = static_cast<Projectile*>(cd->objectA);
		tempAI = static_cast<HonirAI*>(cd->objectB);
	}
	else
	{
		bullet = static_cast<Projectile*>(cd->objectB);
		tempAI = static_cast<HonirAI*>(cd->objectA);
	}

	if((bullet->GetOwner() != tempAI) && (!tempAI->IsDeathRecorded()))
	{
		// tempAI take damage value from the projectile here
        tempAI->ApplyDamage(bullet->GetDamage());

        if (!tempAI->IsAlive())
        {
			tempAI->RecordDeath();
			WaveLevel::Instance()->Enemy_died();
            _wl->GetPlayer()->IncScore(1);
        }

		bullet->MichaelBayStrikes();

		bullet->Destroy();
	}
}

void BossTakeDamage(CollisionData* cd)
{
	Projectile* bullet;
	HonirBossAI* tempAI;

	if(cd->objectA->GetObjectType() == "Projectile")
	{
		bullet = static_cast<Projectile*>(cd->objectA);
		tempAI = static_cast<HonirBossAI*>(cd->objectB);
	}
	else
	{
		bullet = static_cast<Projectile*>(cd->objectB);
		tempAI = static_cast<HonirBossAI*>(cd->objectA);
	}

	if((bullet->GetOwner() != tempAI) && (!tempAI->IsDeathRecorded()))
	{
        // tempAI take damage value from the projectile here
        tempAI->ApplyDamage(bullet->GetDamage());

        if (!tempAI->IsAlive())
        {
			tempAI->RecordDeath();
			WaveLevel::Instance()->Enemy_died();
            _wl->GetPlayer()->IncScore(10);
        }

		bullet->MichaelBayStrikes();

		bullet->Destroy();
	}
}

void PlayerTakeDamage(CollisionData* cd)
{
	Projectile* bullet;
	Player* playa;

	if(cd->objectA->GetObjectType() == "Projectile")
	{
		bullet = static_cast<Projectile*>(cd->objectA);
		playa = static_cast<Player*>(cd->objectB);
	}
	else
	{
		bullet = static_cast<Projectile*>(cd->objectB);
		playa = static_cast<Player*>(cd->objectA);
	}
	
	if((bullet->GetOwner() != playa) && (bullet->IsAlive()))
	{
		// Player take damage value from the projectile here
        _wl->GetPlayer()->ApplyDamage(bullet->GetDamage());

		bullet->Destroy();
	}
}

void HitObstruction(CollisionData* cd)
{
	Projectile* bullet;

	if(cd->objectA->GetObjectType() == "Projectile")
	{
		bullet = static_cast<Projectile*>(cd->objectA);
	}
	else
	{
		bullet = static_cast<Projectile*>(cd->objectB);
	}
		
	bullet->MichaelBayStrikes();
	
	bullet->Destroy();
}