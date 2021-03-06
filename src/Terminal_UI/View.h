#ifndef VIEW_H
#define VIEW_H

#include <ncurses.h>
#include <string>

#include "../api/SpotifyApi.h"

class View {

protected:
	WINDOW* parentWindow;

	SpotifyApi spotifyApi;

	int terminalScreenWidth, terminalScreenHeight;


public:
		
	virtual void refresh() = 0;
	virtual void initialize() = 0;

	void prompt(WINDOW* window, unsigned int x, unsigned int y, const char* str) {
		mvwprintw(window, y, x, str);
	}
};

#endif