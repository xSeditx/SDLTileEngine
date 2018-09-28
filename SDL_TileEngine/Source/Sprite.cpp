#include"Sprite.h"


State::State(SDL_Rect srcrect,uint numframes)
     :TOTAL_FRAMES(numframes)
{
        CURRENT_FRAME = 0;
    	FRAMES.reserve(numframes);
    	uint x = srcrect.x;
    	for_loop(Count, numframes)
        {
    		    SDL_Rect frame;
    		    frame.x = x;
    		    frame.y = srcrect.y;
    		    frame.w = srcrect.w;
    		    frame.h = srcrect.h;
			   *this += frame; //FIXED Remember to get back to fixing the Overloaded Operator so that you can += new frames and states into your frame list.
    		    x += srcrect.w;
    	}
}
std::vector<SDL_Rect> &State::ADD_FRAME(SDL_Rect frame)
{
		FRAMES.emplace_back(frame);
	return FRAMES;
} // Adds a frame to the State

