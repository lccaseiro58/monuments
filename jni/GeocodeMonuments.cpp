#include "GeocodeMonuments.h"

#include "Common/Log.h"

#include <iostream>
#include <dirent.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

GeocodeMonuments::GeocodeMonuments( Detector detID, DescriptorExtractor desID, DescriptorMatcher dmID)
{
	_fH = new FeatureHandler( detID, desID, dmID );

	_ratio = 0.85;
	_nMatchesThresh = 0;
	_showMatches = false;
}

void GeocodeMonuments::setMonument( std::string name,std::string imagePath, std::string url, std::string location  )
{
	Image* img = processImage(imagePath);
	Monument* m = new Monument(url,img,location);
	_monuments.push_back( std::make_pair< std::string, Monument* >( name, m) );
}

void GeocodeMonuments::findMonument( std::string imagePath )
{
	clock_t t;
	t = clock();
	Image* img = processImage(imagePath);

	bool found = false;
	std::string bestMatchName;
	Image* bestMatchImage;
	int max = 0;
	std::vector< std::pair< std::string, Monument*  > >::iterator it = _monuments.begin();
	for( ; !found && it != _monuments.end(); it++ )
	{
		_fH->findGoodMatches( img, it->second->getImage(), _ratio );
		int matchThreshold = img->getGoodMatches( it->second->getImage() ).size();

		if( matchThreshold >= _nMatchesThresh && max < matchThreshold )
		{
			max = matchThreshold;
			bestMatchName = it->first;
			bestMatchImage = it->second->getImage();
		}
	}
	t = clock() - t;
	float calcDuration = ( (float) t ) / CLOCKS_PER_SEC;

	if(max > 0){
		found = true;
		std::cout << "Found Monument for image '" << imagePath << "': " << bestMatchName
						<< ". With " << max << " feature matches, finished in   "
						 << Log::to_string( calcDuration ) << " seconds.\n" << std::endl;
	}
	if(found && _showMatches)
	{
		cv::Mat out;
		img->drawMatches( bestMatchImage, max, MA_GD, out, cv::Scalar(255,0,0,255) );
		cv::namedWindow("Matches", CV_WINDOW_NORMAL);
		cv::imshow("Matches", out);
		cv::waitKey(0);
	}

	if( !found ) std::cout << "Was not able to find monument for image '" << imagePath << "'." << std::endl;
}

/*
void GeocodeMonuments::getMatchesSize( cv::Mat desc1, cv::Mat desc2, int* size )
{
	Image* img1 = new Image(desc1);
	img1->setDescriptors(desc1);
	Image* img2 = new Image(desc2);
	img2->setDescriptors(desc2);
	int max = 0;
	int matchThreshold;
	_fH->findGoodMatches( img1, img2, _ratio );
	matchThreshold = img1->getGoodMatches( img2 ).size();
	*size = matchThreshold;
}
*/

void GeocodeMonuments::showDir( std::string path )
{
	getFileList(path);

	std::set< std::string >::iterator it = _files.begin();
	for( ; it != _files.end(); it++ )
	{
		Image* img = processImage(path+"/"+*it );
		img->show("Image");
		cv::waitKey();
	}
}


void GeocodeMonuments::testDir( std::string path )
{
	getFileList(path);

	std::set< std::string >::iterator it = _files.begin();
	for( ; it != _files.end(); it++ )
	{
		findMonument( path+"/"+*it );
	}
	_files.clear();
}

void GeocodeMonuments::updateDir(std::string name ,std::string path, std::string url,std::string local)
{
	getFileList(path);
	std::set< std::string >::iterator it = _files.begin();
	for( ; it != _files.end(); it++ )
	{
		setMonument(name,path+"/"+*it,url,local);
	}
	_files.clear();
}

Image* GeocodeMonuments::processImage( std::string path )
{
	Image* img = new Image( path, 0.0f, 0.0f, 0.0f, 0.0f );

	_fH->detect( img );
	_fH->computeDescriptors( img );

	return img;
}

Image* GeocodeMonuments::processImageMat( cv::Mat m )
{
	Image* img = new Image( m );

	_fH->detect( img );
	_fH->computeDescriptors( img );

	return img;
}

void GeocodeMonuments::processDC(cv::Mat m, cv::Mat r){
	Image* img = new Image( m );
	Image* img2 = new Image(r);

		_fH->detect( img );
		_fH->computeDescriptors( img );

		r = img->getDescriptors();
}

void GeocodeMonuments::setShowMatches(bool value)
{
	_showMatches = value;
}

void GeocodeMonuments::printFileNames()
{
	for( std::set< std::string >::iterator it = _files.begin(); it != _files.end(); it++ )
	{
		std::cout << (*it) << std::endl;
	}
}

void GeocodeMonuments::clearFileList()
{
	_files.clear();
}

void GeocodeMonuments::getFileList( std::string path )
{
	DIR *dir;
	struct dirent *ent;
	if( ( dir = opendir( path.c_str() ) ) != NULL )
	{
		while( ( ent = readdir( dir ) ) != NULL)
		{
			if( ent->d_type == DT_REG )
			{
				_files.insert( std::string( ent->d_name ) );
			}
		}
		closedir (dir);
	}
	else
	{
	  Log::exit_error("Unable to access directory " + path );
	}
}

GeocodeMonuments::~GeocodeMonuments() {}
