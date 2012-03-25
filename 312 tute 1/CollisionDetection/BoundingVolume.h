
#ifndef __BOUNDINGVOLUME_H__
#define __BOUNDINGVOLUME_H__

#include "../includes.h"

class BoundingVolume
{
public:
	virtual std::string Get_type()const=0;
protected:
	std::string m_type;
};

#endif