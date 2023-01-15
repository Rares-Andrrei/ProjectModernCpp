#include "Advantages.h"

Advantages::Advantages()
{
	m_qTypeV = nullptr;
	m_qTypeN = nullptr;
}

void Advantages::getCurrentQuestion(QTypeNumerical qTypeN)
{
	m_qTypeN = new QTypeNumerical(qTypeN);
	if (m_qTypeV)
	{
		delete m_qTypeV;
	}
	m_qTypeV = nullptr;
}

void Advantages::getCurrentQuestion(QTypeVariants qTypeV)
{
	if (m_qTypeN)
	{
		delete m_qTypeN;
	}
	m_qTypeN = nullptr;
	m_qTypeV = new QTypeVariants(qTypeV);
}

Advantages::~Advantages()
{
	if (m_qTypeN)
	{
		delete m_qTypeN;
	}
	if (m_qTypeV)
	{
		delete m_qTypeV;
	}
}