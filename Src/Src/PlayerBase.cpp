#include "PlayerBase.h"

PlayerBase::PlayerBase()
	:Zone()
{
	this->SetScore(300);
}

PlayerBase PlayerBase::operator--()
{
	this->m_lives--;
	return *this;
}

PlayerBase PlayerBase::operator--(int)
{
	return (*this)--;
}
