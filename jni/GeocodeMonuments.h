#ifndef GEOCODEMONUMENTS_H_
#define GEOCODEMONUMENTS_H_

#include "Common/Image.h"
#include "Features/FeatureHandler.h"
#include "Common/Monument.h"

#include <string>
#include <set>
#include <utility>

class GeocodeMonuments {
public:
	GeocodeMonuments( Detector detID, DescriptorExtractor desID, DescriptorMatcher dmID );

	void setMonument( std::string name, std::string imagePath, std::string url, std::string location );
	void findMonument( std::string imagePath );
	//void getMatchesSize( cv::Mat desc1, cv;;Mat desc2 ,int* size);

	void setShowMatches(bool value);

	void showDir( std::string path );

	void testDir( std::string path );

	void updateDir(std::string name ,std::string path, std::string url,std::string local);

	Image* processImage( std::string path );
	Image* processImageMat( cv::Mat m );
	void processDC(cv::Mat m, cv::Mat r);
	virtual ~GeocodeMonuments();

protected:
	std::set< std::string > _files;

	std::vector< std::pair< std::string, Monument*  > > _monuments;

	FeatureHandler* _fH;
	double _ratio;
	int _nMatchesThresh;
	bool _showMatches;

private:
	void getFileList(std::string path);
	void clearFileList();
	void printFileNames();
};

#endif /* GEOCODEMONUMENTS_H_ */
