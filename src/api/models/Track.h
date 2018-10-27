#ifndef TRACK_H
#define TRACK_H

#include <map>
#include <vector>
#include <string>

// #include <iostream>

#include "User.h"
#include "Artist.h"
// #include "TrackLink.h"

#include "../utils/json.h"

class Track {

private:

	bool explicitSong;
	bool playable;
	int durationMs;
	int discNumber;
	int trackNumber;
	std::string id;
	std::string uri;
	std::string href;
	std::string name;
	std::string type;
	std::string previewUrl;
	std::vector<Artist> artists;
	std::vector<std::string> availableMarkets;
	std::map<std::string, std::string> externalUrls;
	// TrackLink linkedFrom;

public:

	Track();
	Track(nlohmann::json trackJson);

	bool isExplicit();
	bool isPlayable();
	int getDurationMs();
	int getDiscNumber();
	int getTrackNumber();
	std::string getID();
	std::string getURI();
	std::string getHref();
	std::string getName();
	std::string getType();
	std::string getPreviewUrl();
	std::vector<Artist> getArtists();
	std::vector<std::string> getAvailableMarkets();
	std::map<std::string, std::string> getExternalUrls();
	// TrackLink getLinkedFrom();
	
};

#endif