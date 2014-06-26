/*
 * Monument.cpp
 *
 *  Created on: 13/06/2014
 *      Author: luis
 */

#include "Monument.h"

Monument::Monument(std::string url,Image* image,std::string location) {
	_url = url;
	_image = image;
	_location = location;

}

std::string Monument::getUrl()
{
	return std::string( _url );
}

Image* Monument::getImage(){
	return _image;
}

std::string Monument::getLocation()
{
	return std::string( _location );
}

void Monument::setUrl(std::string url)
{
	_url = url;
}

void Monument::setImage(Image* image)
{
	_image = image;
}

void Monument::setLocation(std::string location)
{
	_location = location;
}

Monument::~Monument() {
	// TODO Auto-generated destructor stub
}

