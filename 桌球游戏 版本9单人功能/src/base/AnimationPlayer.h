#pragma once 

class Animation;
class Frame;
class AnimationPlayer
{
public:
	AnimationPlayer();
	
	void Update(float deltaTime);

	//得到当前的桢: 参数(outParam)
	bool  GetCurrentFrame(Frame *&frame);
	void SetAnimation(Animation *pAnima);
	Animation * GetAnimation()const
	{
		return m_anim;
	}

	void SetSpeed(float speed)
	{
		m_Speed=  speed;
	}

	void Play()
	{
		m_ifPlay = true;
	}

	void Stop()
	{
		m_ifPlay = false;
	}

protected:
	Animation * m_anim;
	size_t m_currentIndex;
	//是否开始播放
	bool m_ifPlay;
	float m_Interval, m_Timer, m_Speed;
};