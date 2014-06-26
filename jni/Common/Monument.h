
#ifndef MONUMENT_H_
#define MONUMENT_H_

#include "Image.h"
#include "Log.h"

class Monument {
public:
	Monument();
	Monument(std::string url,Image* image,std::string location);
	virtual ~Monument();

	std::string getUrl();
	Image* getImage();
	std::string getLocation();
	void setUrl(std::string);
	void setImage(Image*);
	void setLocation(std::string);

protected:
	std::string _url;
	Image* _image;
	std::string _location;
};

#endif
