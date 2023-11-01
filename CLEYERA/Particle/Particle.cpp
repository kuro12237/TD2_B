#include"Particle/Particle.h"

void Particle::Initialize(IParticleState* state, const uint32_t NumInstance)
{
	if (InitializeLock){
		//Initializeが二回呼び出されている
		LogManager::Log("Particle Initialize ERROR " + name_+"\n");
		assert(0);
	}
	state_ = state;
	NumInstance_ = NumInstance;
	state_->Initialize(this);
	InitializeLock = true;
}

void Particle::Draw(ViewProjection viewProjection)
{
	if (particles_.size() >= NumInstance_ )
	{
		//Instanceの数よりリストの数が増えるとエラー
		LogManager::Log("Particle Draw ERROR "+ name_+"\n");
		assert(0);
	}

	state_->Draw(this,particles_,viewProjection);
}

list<Particle_param> Particle::begin()
{
	//生存フラグがtrueになったらリストから解放
	for (list<Particle_param>::iterator p=particles_.begin(); p != particles_.end();)
	{
		if ((*p).isAlive)
		{
			particles_.erase(p);
		}
		else {
			++p;
		}
	}
	//今リストに登録してある物をうつしてリストを消去
	//また登録しなおす
	list<Particle_param> p = particles_;
	particles_.clear();
	return p;
}
