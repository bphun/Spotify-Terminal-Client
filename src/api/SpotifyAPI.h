#ifndef SPOTIFY_API_H
#define SPOTIFY_API_H

#include <fstream>

#include "models/Pager.h"
#include "models/Album.h"
#include "models/Artist.h"
#include "models/Device.h"
#include "models/Playlist.h"
#include "models/SavedAlbum.h"
#include "models/SavedTrack.h"
#include "models/CursorPager.h"
#include "models/PlayHistory.h"
#include "models/Recommendations.h"
#include "models/CurrentlyPlayingTrack.h"
#include "models/CurrentlyPlayingContext.h"

#include "utils/curl/CurlUtils.h"
#include "utils/sockets/Socket.h"

typedef std::map<std::string, std::string> options_t;

/**
 * 
 * A C++ wrapper for the Spotify Web API. This API supports
 * all current API requests made publicly available to the general public.
 * To use this API, you will need a Spotify Premium account and your Client ID and Client Secret
 * to be able to make Web API requets.
 * 
 */

class SpotifyApi {

private:

	std::string spotifyClientID;
	std::string accessToken;
	std::string refreshToken;
	std::string spotifyClientSecret;
	std::string authorizationCode;
	std::string clientAuthenticationCode;
	
	bool isUserAuthenticated;

	#ifdef LOCALTEST
	std::string backendURL = "http://localhost";
	#else 
	std::string backendURL = "http://192.168.1.150";
	#endif

	CurlUtils curlUtils;

	void requestAccessToken();
	void requestClientConfigStrings();
	void requestSecrets(std::string clientId);		

	void writeStringToFile(std::string str, std::string filePath);
	void insertOptions(std::vector<std::string> source, std::string key, options_t &destination);

	std::string replaceAll(std::string& str, const std::string from, const std::string to);
	std::string readFileAt(std::string path);

public:

	SpotifyApi();

	bool userAuthenticated();

	void logout();
	void authenticateSpotifyUser(std::string accessToken);

	bool createClientUser(std::string username, std::string password);
	bool authenticateClientUser(std::string username, std::string password);

	/* Album */

	void saveAlbums(std::vector<std::string> albumIds, options_t options = options_t());
	void removeSavedAlbums(std::vector<std::string> albumIds, options_t options = options_t());
	bool checkSavedAlbums(std::vector<std::string> albumIds, options_t options = options_t());
	Album fetchAlbum(std::string albumID, options_t options = options_t());
	Pager<Album> fetchNewReleases(options_t options = options_t());
	Pager<SavedAlbum> fetchSavedAlbums(options_t options = options_t());
	Pager<Track> fetchAlbumTracks(std::string albumID, options_t = options_t());
	Pager<Album> searchAlbums(std::string query, options_t options = options_t());
	Pager<Album> fetchArtistAlbums(std::string artistID, options_t options = options_t());
	std::vector<Album> fetchAlbums(std::vector<std::string> albumIDs, options_t options = options_t());


	/* Artist */

	void followArtist(std::string artistID, options_t options = options_t());
	bool checkFollowingArtist(std::string artistID, options_t options = options_t());
	Artist fetchArtist(std::string artistID, options_t options = options_t());
	Pager<Artist> fetchUserTopArtists(options_t options = options_t());
	Pager<Artist> searchArtists(std::string query, options_t options = options_t());
	std::vector<Artist> fetchArtistRelatedArtists(std::string artistID, options_t options = options_t());
	std::vector<Artist> fetchArtists(std::vector<std::string> artistIDs, options_t options = options_t());
	std::vector<Track> fetchArtistTopTracks(std::string artistID, std::string country, options_t options = options_t());


	/* Playlist */

	void editPlaylist(std::string userId, std::string playlistId, options_t options = options_t());
	void followPlaylist(std::string ownerID, std::string playlistdID, options_t options = options_t());
	void unfollowPlaylist(std::string ownerID, std::string playlistdID, options_t options = options_t());
	void removeTracksFromPlaylist(std::string userID, std::string playlistId, std::vector<std::string> trackIDs, std::string snapshotID);
	void addTracksToPlaylist(std::string userId, std::string playlistId, std::vector<std::string> trackUris, options_t options = options_t());
	void reorderPlaylistTracks(std::string userId, std::string playlistId, int rangeStart, int insertBefore, options_t options = options_t());
	void replacePlaylistTracks(std::string userId, std::string playlistId, std::vector<std::string> trackUris, options_t options = options_t());
	bool checkUserFollowingPlaylist(std::string userId, std::string playlistId, std::vector<std::string> userIds, options_t options = options_t());
	Playlist createPlaylist(std::string userID, std::string name, options_t options = options_t());
	Playlist fetchPlaylist(std::string userId, std::string playlistId, options_t options = options_t());
	Pager<PlaylistTrack> fetchPlaylistTracks(std::string userId, std::string playlistId, options_t options = options_t());
	Pager<Playlist> fetchUserPlaylists(options_t options = options_t());
	Pager<Playlist> fetchFeaturedPlaylists(options_t options = options_t());
	Pager<Playlist> searchPlaylists(std::string query, options_t options = options_t());
	Pager<Playlist> fetchUserPlaylists(std::string userId, options_t options = options_t());


	/* Tracks */

	void saveTracks(std::vector<std::string> trackIDs, options_t options = options_t());
	void unsaveTracks(std::vector<std::string> trackIDs, options_t options = options_t());
	bool checkSavedTracks(std::vector<std::string> trackIDs, options_t options = options_t());
	Track fetchTrack(std::string trackID, options_t options = options_t());
	Recommendations fetchRecommendations(options_t options = options_t());
	CurrentlyPlayingTrack fetchUserCurrentPlayingTrack(options_t options = options_t());
	Pager<SavedTrack> fetchSavedTracks(options_t options = options_t());
	Pager<Track> fetchUserTopTracks(options_t options = options_t());
	Pager<Track> searchTracks(std::string query, options_t options = options_t());
	std::vector<Track> fetchTracks(std::vector<std::string> trackIds, options_t options = options_t());


	/* playback */

	CursorPager<PlayHistory> fetchUserRecentlyPlayed(options_t options = options_t());
	CurrentlyPlayingContext fetchUserCurrentPlayback(options_t options = options_t());
	std::vector<Device> fetchUserDevices(options_t options = options_t());


	/* User */

	void followUser(std::string userID, options_t options = options_t());
	void unfollowUser(std::string userID, options_t options = options_t());
	bool checkFollowingUser(std::string userID, options_t options = options_t());
	User fetchUser(options_t options = options_t());


	/* Stream Control */

	void pause(options_t options = options_t());
	void play(options_t options = options_t());
	void skipToNext(options_t options = options_t());
	void skipToPrevious(options_t options = options_t());
	void toggleShuffle(bool state, options_t options = options_t());
	void setRepeat(std::string state, options_t options = options_t());
	void setVolume(int volumePercent, options_t options = options_t());
	void transferUserPlayback(std::string deviceId, options_t options = options_t());

};

#endif
