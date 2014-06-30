#ifndef __SDLGUI_TOOLS_HEAD__
#define __SDLGUI_TOOLS_HEAD__
#include "sdlbase.h"
#include "sdlwindow.h"
#include "sdlthread.h"
#include "sdl_event_manager.h"
using namespace std;
typedef class sdl_button : public GUI<sdl_button,sdl_widget>
{
	public:
		sdl_button();
		sdl_button(const char*,int,int,int,int,Uint32);
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
		int on_click(sdl_board*,void*);
		int on_release(sdl_board*,void*);
	protected:
		sdl_clip _page;		
}*sdl_button_ptr;
sdl_button::sdl_button()
	:
		GUI<sdl_button,sdl_widget>()
{
	init();
}
sdl_button::sdl_button(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
	:
		GUI<sdl_button,sdl_widget>()
{
	init(ptitle,px,py,pw,ph,pflag);
}
int sdl_button::init()
{
	if(sdl_widget::init())return -1;
	return 0;
}
int sdl_button::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflag)
{
	SDL_Rect rt;
	if(sdl_widget::init(ptitle,px,py,pw,ph,pflag))return -1;
	_page.sdlsurface::init(0,pw*4,ph,32,0,0,0,0);
	_page.clip(pw,ph);
	fill_rect(NULL,0x00ff00);
	rt.x = 0;
	rt.y = 0;
	rt.w = pw;
	rt.h = ph;
	_page.fill_rect(&rt,0x00ff00);
	rt.x = pw*1;
	rt.y = ph*1;
	_page.fill_rect(&rt,0x0000ff);
	rt.x = pw*2;
	rt.y = ph*2;
	_page.fill_rect(&rt,0xff0000);
	return 0;
}
int sdl_button::sysevent(SDL_Event*e)
{
	switch(e->type)
	{
		default:
			break;
	}
	return sdl_widget::sysevent(e);
}
int sdl_button::on_click(sdl_board* obj,void* data)
{
	//fill_rect(NULL,0x00ff00);	
	_page.clip(0,0,this,NULL);
	return 0;
}
int sdl_button::on_release(sdl_board* obj,void* data)
{
	_page.clip(1,0,this,NULL);
	return 0;
}
#endif// __SDLGUI_TOOLS_HEAD__
