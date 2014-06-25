//----------------------------------------------------------------------------------------------------------------
//
//
//
//
//						文档名：						sdlwindow.h
//
//						文档创建日期：			2014年2月22日
//						文档更新日期：			2014年5月25日
//						文档创建者：				徐荣
//						文档更新者：				徐荣
//						文档创建者联系方式：Email:twtfcu3@126.com
//																QQ:12880312(twtfcu3@126.com)
//																网站:http://sdl.my-mx.cn
//
//						版权说明：
//						1.本文档使用者的权利
//							a)本文档使用者可以随时利用本文档创建其它文件。
//							b)本文档使用者可以随时修改本文档有效代码内容，
//								但不能更改或添加本文档用//开头及用/**/包含的任何注释语句。
//						2.本文档使用者的义务
//							a)使用者不得更改本文档的文档名
//							b)本文档使用者在使用本文档时请在您的文档开始处
//								说明本文档版权归本文档创建者所有。
//							c)本文档使用者更改本文档后
//								请您上传更新后的文档到http://github.com/sdlgui/sdlgui/
//							d)本文档使用者本人承担
//								使用本文档后的所有法律责任,
//								本文档创建者不为您使用本文件的所有行为容承担任何法律责任。
//
//
//
//
//------------------------------------------------------------------------------------------------------------------
#ifndef __SDLWINDOW_HANDLE__
#define __SDLWINDOW_HANDLE__
#ifdef DLLEXPORT
	#define def_dll __declspec(dllexport)
#else
	#define def_dll
#endif
#include "sdlbase.h"
#include <SDL2/SDL_thread.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string.h>
#include <map>
#include <list>
#include <string>
#include <sstream>
//-----------------------------------------------
using namespace std;
//--------------------------------------------------
class sdl_board;
template<class T,class B> class GUI;
class sdl_ime;
class sdl_frame;
class sdl_widget;
class sdl_clip;
//----------------------------------------------
//
// 					自定义消息常量定义
// 					每个集合为七位数的编码
//          前四位是这类集合的代码
//          后三位是集合子消息的代码
//
//---------------------------------------------
#define __event_macro__(x,y) x##y
//计时器消息集合1000
#define timer_event_macro(y) __event_macro__(1000,y) 
const int sdlgui_event_timer = timer_event_macro(001);
//
//按钮类消息集合1001
#define button_event_macro(y) __event_macro__(1001,y) 
const int sdlgui_button_up= button_event_macro(001);
const int sdlgui_button_down = button_event_macro(002);
const int sdlgui_button_click = button_event_macro(003);
//
//IME类消息集合1002
#define ime_event_macro(y) __event_macro__(1002,y) 
/* 输入上屏 */
const int sdlgui_ime_up= ime_event_macro(001);
/* 输入英文 */
const int sdlgui_ime_en= ime_event_macro(002);
/* 中文编码状态 */
const int sdlgui_ime_cn_edit= ime_event_macro(003);
/* 中文上屏状态 */
const int sdlgui_ime_cn_up= ime_event_macro(004);
/* 中文输入不可打印的控制符 */
const int sdlgui_ime_cn_ctrl= ime_event_macro(006);
/* 显示输入法窗口 */
const int sdlgui_ime_show= ime_event_macro(006);
/* 隐藏输入法窗口 */
const int sdlgui_ime_hide= ime_event_macro(007);
//
//文本输入框类消息集合1003
#define edit_event_macro(y) __event_macro__(1003,y) 
/* 文本更新 */
const int sdlgui_edit_change= edit_event_macro(001);
//滚动条类消息集合1004
#define scroll_event_macro(y) __event_macro__(1004,y) 
const int sdlgui_scroll_point= scroll_event_macro(001);
const int sdlgui_scroll_show= scroll_event_macro(002);
const int sdlgui_scroll_hide= scroll_event_macro(003);
//窗口事件类消息集合1005
#define window_event_macro(y) __event_macro__(1005,y) 
/* 消息焦点改变时发送的消息 */
const int sdlgui_window_focus= window_event_macro(001);

//-------------------------------------
//
//
//             用于继承的专用类
//
//
//-------------------------------------
//用于GUI类的继承与事件处理
//事件处理分为两类，第一类是GUI类自身的系统和用户功能实现。
//第二类是用户调用GUI对象的事件接口。
//GUI类的自身实现分为系统功能和用户功能，系统功能是类成员，用户功能是类静态成员
template <class T,class B>
class GUI : public B
{
	//friend int event_process(void* obj);
	friend class sdl_frame;
	public:
		int(*event_fun)(T*,SDL_Event*);
	public:
		T* This;
	public:
		GUI();
		virtual int event(SDL_Event*);//GUI专用类事件统一调用函数
		int event(int(*)(T*,SDL_Event*));//GU专用类内部事件处理函数（设置用户事件函数接口）
		virtual int sysevent(SDL_Event*e){return 0;};//GUI专用类系统事件处理函数的虚类
		int handle(int handle){return 0;}
	protected:
		static int sysprocess(T*,SDL_Event*);
		static int userprocess(T*,SDL_Event*);
};
//-------------------------------------
//
//
//             窗口底板类
//
//
//-------------------------------------
typedef class sdl_board : public GUI<sdl_board,sdlsurface>
{
	public:
		friend class sdl_frame;
	public:
		sdl_board();
	  sdl_board(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags);
		~sdl_board();
	  int init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags);
		int init();
		int sysevent(SDL_Event*e){return 0;}
	public:
		/* 显示当前窗口 */
		int show();
		/* 隐藏当前窗口 */
		int hide();
		/* 返回当前窗口的显示状态 */
		int is_show();
		/* 设置当前窗口标题 */
		int pos(int,int);
		/* 设置父级窗口对象 */
		sdl_board* parent(sdl_board*);
		/* 返回父级窗口对象 */
		sdl_board* parent();
		/* 返回给定对象是否为当前窗口的子窗口 */
		int is_child(sdl_board*);
		/* 添加子级窗口 */
		template<class T>T* add(const char*,int,int,int,int,Uint32);
		template<class T>T* add(T*);
		/* 调整当前窗口Z序 */
		int z_top(sdl_board*,sdl_board*,int);
		/* 初始化时用于绘图窗口的虚函数 */
		virtual int draw(){return 0;}
		/* 重画当前窗口 */
		int redraw();
		/* 返回给定坐标的子窗口对象 */
		//-----------------------------------------------
	public:
		/* 重载委托事件函数处理 */
		int handle(int);
		/* 连接委托函数 */
		virtual int connect_event(string,sdl_board*,int);
		int event_signal(string);
		/* 鼠标点击事件 */
		virtual int on_click(sdl_board*,void*);
	protected:
		sdlsurface *_board;
		sdl_board** _hit_board_ptr;
		SDL_Rect  _rect;
		SDL_Point _pos,_size;
		sdl_board *_parent;
		sdl_board *_end,*_head;
		sdl_board *_next,*_last;
		int _is_show;
		int _is_destroy;
		map<sdl_board*,int> _board_list;
}*sdl_board_ptr;
//sdl_board** sdl_board::_hit_board_ptr=NULL;
//-------------------------------------
//
//
//            定义事件句柄类型 
//
//
//-------------------------------------
/*
		定义事件句柄类型 
		要求所有事件函数返回整型值，
		调用对象与参数为事件参数
 */
struct sdl_event_handle
{
	int handle;
	sdl_board* object;
};
//-------------------------------------
//
//
//            对象事件委托结构体 
//
//
//-------------------------------------
/* 
	对象事件委托结构体 
 */
class sdl_event_struct
{
	friend class sdl_event_object;
	friend class sdl_event_manager;
	public:
		def_dll sdl_event_struct()
		{
			_event.clear();
			_event_call_count = 0;
		}
		/* 
			对象事件注册功能，
			注册时要一个事件函数名的字串与函数名入口地址
		 */
		def_dll int event_register(string,sdl_event_handle);
		/*
			 对象事件注消功能
			 注消时要用到事件函数名的字串
		*/
		def_dll int event_unregister(string);
		/* 
				事件调用累计增量 
		 */
		def_dll int push();
		/* 
				事件调用后减量 
		 */
		def_dll int pull();
		/* 
				事件调用计数 
		 */
		def_dll int count();
	protected:
		//事件函数入口列表
		def_dll	map<string,sdl_event_handle> _event;
		//事件调用计数存储器
		int _event_call_count;
};
def_dll int sdl_event_struct::event_register(string event_string,sdl_event_handle event_function)
{
	_event.insert(pair<string,sdl_event_handle>(event_string,event_function));
	return 0;
}
def_dll int sdl_event_struct::event_unregister(string event_string)
{
	_event.erase(event_string);
	return 0;
}
def_dll int sdl_event_struct::push()
{
	_event_call_count++;
	return _event_call_count;
}
def_dll int sdl_event_struct::pull()
{
	if(_event_call_count)_event_call_count--;
	return _event_call_count;
}
def_dll int sdl_event_struct::count()
{
	return _event_call_count;
}




//-------------------------------------
//
//
//            对象事件项目列表 
//
//
//-------------------------------------
/* 
		对象事件项目列表 
		用于管理每个对象其中一个事件的托管入口调用
 
 */
class sdl_event_object
{
	friend class sdl_event_manager;
	public:
		def_dll sdl_event_object();
		/* 
			注册一个事件
			参数为事件字串
		 */
		def_dll int event_register(string);
		/* 
			注消一个事件
			参数为事件字串
		 */
		def_dll int event_unregister(string);
		/* 
			事件调用累计一次 
		 */
		def_dll int push();
		/* 
			事件调用一次 
		 */
		def_dll int pull();
		/* 
			事件累计次数 
		 */
		def_dll int count();
	protected:
		def_dll int _event_count;
		def_dll map<string,sdl_event_struct*> _object_event_list;
};
def_dll sdl_event_object::sdl_event_object()
{
	_event_count = 0;
	_object_event_list.clear();
}
def_dll int sdl_event_object::event_register(string event_string)
{
	sdl_event_struct* _event_ingress = new sdl_event_struct;
	_object_event_list.insert(pair<string,sdl_event_struct*>(event_string,_event_ingress));	
	return 0;
}
def_dll int sdl_event_object::event_unregister(string event_string)
{
	_object_event_list.erase(event_string);	
	return 0;
}
def_dll int sdl_event_object::push()
{
	_event_count++;
	return _event_count;
}
def_dll int sdl_event_object::pull()
{
	_event_count--;
	return _event_count;
}
def_dll int sdl_event_object::count()
{
	return _event_count;
}





//-------------------------------------
//
//
//           事件管理器 
//
//
//-------------------------------------
/* 
			事件管理器

			用于调用对象事件
			实现委托功能与事件多线程化

			功能
			1.加入/移除对象
			2、给对象注册/注销事件
			3、给对象事件加入/删除事件委托函数
			4、自行处理对象事件
 */
class sdl_event_manager
{
	public:
		/* 
			加入事件对象 参数为对象地址
		 */
		def_dll static int push(sdl_board*);
		/* 
			移除事件对象 参数为对象地址
		 */
		def_dll static int pull(sdl_board*);
		/* 
		 加入对象事件，参数为对象地址，事件字串 
		 */
		def_dll static int push(sdl_board*,string);
		/* 
			移除对象事件，参数为对象地址，事件字串 
		 */
		def_dll static int pull(sdl_board*,string);
		/* 
			加入对象事件委托入口函数
			参数为对象地址，事件字串，委托入口函数地址
		 */
		def_dll static int push(sdl_board*,string,sdl_board*,int);
		/* 
			移除对象事件委托入口函数
			参数为对象地址，事件字串，委托入口函数地址
		 */
		def_dll static int pull(sdl_board*,string,sdl_board*,int);
		/* 
			对象事件调用 
		 */
		def_dll static int call_event(sdl_board*,string);
		/* 
			多线程管理事件列表 
		 */
		def_dll static int start();
	protected:
		def_dll static int run(void*);
	protected:
		def_dll static map<sdl_board*,sdl_event_object*> _event_list;		
		def_dll static SDL_Thread* _event_process_thread;

};
def_dll map<sdl_board*,sdl_event_object*> sdl_event_manager::_event_list;
def_dll SDL_Thread* sdl_event_manager::_event_process_thread = NULL;
////////////////////////////////////////////////////
//
//
//
//
//
////////////////////////////////////////////////////
def_dll int sdl_event_manager::push(sdl_board* obj)
{
	sdl_event_object *obj_event_list = new sdl_event_object;
	sdl_event_manager::_event_list.insert(pair<sdl_board*,sdl_event_object*>(obj,obj_event_list));
	return 0;
}
def_dll int sdl_event_manager::pull(sdl_board* obj)
{
	sdl_event_manager::_event_list.erase(obj);
	return 0;
}
def_dll int sdl_event_manager::push(sdl_board* obj,string event_string)
{
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	sdl_event_object* event; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(obj);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再注册事件到对象事件列表 */
	//cout<<"event_register start"<<endl;
	event = (sdl_event_object*)(event_iter->second);
	//cout<<"event_register stop"<<endl;
	/* 使用对象事件列表自身注册功能 */
	return event->event_register(event_string);
}
def_dll int sdl_event_manager::pull(sdl_board* obj,string event_string)
{
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	sdl_event_object* event; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(obj);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再注册事件到对象事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 使用对象事件列表自身注册功能 */
	return event->event_unregister(event_string);
}
def_dll int sdl_event_manager::push(sdl_board* connect_object,string event_string,sdl_board* event_object,int event_handle)
{
	stringstream event_object_string;
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	map<string,sdl_event_struct*>::iterator event_struct_iter;
	sdl_event_object* event; 
	sdl_event_struct* event_struct; 
	sdl_event_handle _handle;
	_handle.object = event_object;
	_handle.handle = event_handle;
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(connect_object);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再读取注册事件对象的事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 
		 然后找到对象事件列表中的事件(委托)结构
			没有找到返回-1 
	 */
	event_struct_iter = event->_object_event_list.find(event_string);
	if(event_struct_iter == event->_object_event_list.end())
	{
		return -1;
	}
	/* 使用对象事件列表自身注册功能 */
	event_object_string<<event_object<<"_"<<_handle.handle;
	event_struct = (sdl_event_struct*)event_struct_iter->second;

	return event_struct->event_register(event_object_string.str(),_handle);
}
def_dll int sdl_event_manager::pull(sdl_board* connect_object,string event_string,sdl_board* event_object,int event_hendle)
{
	stringstream event_object_string;
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	map<string,sdl_event_struct*>::iterator event_struct_iter;
	sdl_event_object* event; 
	sdl_event_struct* event_struct; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(connect_object);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再读取注册事件对象的事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 
		 然后找到对象事件列表中的事件(委托)结构
			没有找到返回-1 
	 */
	event_struct_iter = event->_object_event_list.find(event_string);
	if(event_struct_iter == event->_object_event_list.end())
	{
		return -1;
	}
	/* 使用对象事件列表自身注册功能 */
	event_object_string<<event_object<<"_"<<event_hendle;
	event_struct = (sdl_event_struct*)event_struct_iter->second;

	return event_struct->event_unregister(event_object_string.str());
}
def_dll int sdl_event_manager::call_event(sdl_board* event_object,string event_string)
{
	stringstream event_object_string;
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	map<string,sdl_event_struct*>::iterator event_struct_iter;
	sdl_event_object* event; 
	sdl_event_struct* event_struct; 
	/* 先找到对象列表中的对象事件列表的引索 */
	event_iter = sdl_event_manager::_event_list.find(event_object);
	if(event_iter == sdl_event_manager::_event_list.end())
	{
		return -1;
	}
	/* 再读取注册事件对象的事件列表 */
	event = (sdl_event_object*)event_iter->second;
	/* 
		 然后找到对象事件列表中的事件(委托)结构
			没有找到返回-1 
	 */
	event_struct_iter = event->_object_event_list.find(event_string);
	if(event_struct_iter == event->_object_event_list.end())
	{
		return -1;
	}
	/* 使用对象事件列表累计 */
	event_struct = (sdl_event_struct*)event_struct_iter->second;
	return event_struct->push();
}
def_dll int sdl_event_manager::start()
{
	sdl_event_manager::_event_process_thread = SDL_CreateThread(sdl_event_manager::run,"sdl_event_manager::run",NULL);
}
def_dll int sdl_event_manager::run(void* p)
{
	stringstream event_object_string;
	map<sdl_board*,sdl_event_object*>::iterator event_iter;
	map<string,sdl_event_struct*>::iterator event_struct_iter;
	map<string,sdl_event_handle>::iterator event_struct_handle_iter;
	sdl_event_object* event; 
	sdl_event_struct* event_struct; 
	sdl_event_handle event_struct_handle;
	while(1)
	{
		/* 引索所有的托管函数地址 */
		/* 先找到对象列表中的对象事件列表的引索 */
		//event_iter = sdl_event_manager::_event_list.begin();
		for(event_iter = sdl_event_manager::_event_list.begin();event_iter!=sdl_event_manager::_event_list.end();event_iter++)
		{
			/* 再读取注册事件对象的事件列表 */
			event = (sdl_event_object*)event_iter->second;
			/* 
				然后找到对象事件列表中的事件(委托)结构
			*/
			for(event_struct_iter = event->_object_event_list.begin();event_struct_iter!=event->_object_event_list.end();event_struct_iter++)
			{
				/* 使用对象事件列表累计 */
				event_struct = (sdl_event_struct*)event_struct_iter->second;
				if(event_struct->count())
				{
					for(event_struct_handle_iter = event_struct->_event.begin();event_struct_handle_iter!=event_struct->_event.end();event_struct_handle_iter++)
					{
						/* 调用托管的事件函数 */
						event_struct_handle = (sdl_event_handle)event_struct_handle_iter->second;
						if(event_struct_handle.object)
						{
							event_struct_handle.object->handle(event_struct_handle.handle);
						}
					}
					event_struct->pull();
				}
			}
		}
	}
	return 0;
}
//------------------------------------
//
//           工具类
//
//
//------------------------------------
typedef class sdl_widget : public GUI<sdl_widget,sdl_board>
{
	public:
		sdl_widget();
		sdl_widget(const char*,int,int,int,int,Uint32);
		~sdl_widget();
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int sysevent(SDL_Event*);
}*sdl_widget_ptr;
//-------------------------------------
//
//
//             窗口框架类
//
//-------------------------------------
typedef class sdl_frame : public GUI<sdl_frame,sdl_board>
{
	public:
		friend class sdl_board;
	public:
		sdl_frame();
		sdl_frame(const char*,int,int,int,int,Uint32);
		~sdl_frame();
		int init();
		int init(const char*,int,int,int,int,Uint32);
		int redraw();
		virtual int sysevent(SDL_Event*);
		int run();
		sdlwindow* frame();
		//------------------------------------------------
		int pos(int,int);
		int size(int,int);
		int size(int*,int*);
		int show();
		int hide();
		//------------------------------------
		double fps();
	protected:
		/* 事件分流 */
		int event_shunt(SDL_Event*);
	public:
		//sdl_ime ime;
	protected:
		static sdl_board* _capture_win;
	protected:
		sdlwindow* _window;
		sdlsurface _screen;
		SDL_Event _main_event;
		double _fps;
		SDL_Point _window_rect;
		/* 消息处理循环变量 */
		int _is_exit;
		/* 处理消息流的子级线程 */
		SDL_Thread* _event_thread;
}*sdl_frame_ptr;
//--------------------------------------------------
//
//
//
//
//
//
//
//
//
//
//
//
//---------------------------------------------------
//---------------------------------------------
/* 
	主要是处理消息分流而设计的类,
	它的构造函数首先会申请两个事件节点,
	第一个节点为首节点，第二个节点为尾节点,
	首节点的向上指向节点永远是指向尾节点的,
	如果首尾节点相邻，则表示本窗口的,
	所有事件处理完毕，将合并新的缓冲事件,
 */
//GUI继承专用类构造函数
template<class T,class B>
GUI<T,B>::GUI():B()
{
	//This = dynamic_cast<T*>(this);
	This = (T*)(this);
	event_fun = NULL;
}
//----------------------------------------
//GUI继承专用类对象事件设置函数
template<class T,class B>
int GUI<T,B>::event(int(*f)(T*,SDL_Event*))
{
	if(f)
	{
		event_fun = f; 
		return 0;
	}
	return -1;
}
//------------------------------------
//GUI继承专用类事件调用函数
template<class T,class B>
int GUI<T,B>::event(SDL_Event* e)
{
	userprocess(This,e);
	sysprocess(This,e);
	return 0;
}
//--------------------------------------
//GUI继承专用类系统事件设置函数
template<class T,class B>
int GUI<T,B>::sysprocess(T* obj,SDL_Event* e)
{
	T* _this = ((GUI<T,B>*)obj)->This;
	if(_this!=NULL)return _this->sysevent(e);
	return -1;
}
//--------------------------------------
//GUI继承专用类用户事件设置函数
template<class T,class B>
int GUI<T,B>::userprocess(T* obj,SDL_Event* e)
{
	//return 0;
	T* _this = ((GUI<T,B>*)obj)->This;
	if(_this!=NULL && _this->event_fun!=NULL)
	{
		return (*(_this->event_fun))(_this,e);
	}
	return -1;
}
//-----------------------------------------------

//------------------------------------------
//
//
//
//
//---------------------------------------------
//-------------------------------------
//底板空白构造函数
sdl_board::sdl_board()
:
GUI<sdl_board,sdlsurface>()
{
	init();
}
//-------------------------------------------
//底板带参构造函数
//---------------------------------------
sdl_board::sdl_board(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
:
GUI<sdl_board,sdlsurface>()
{
	init();
	init(ptitle,px,py,pw,ph,pflags);
}
//-----------------------------------------------
//底板析构函数
sdl_board::~sdl_board()
{
	//cout<<"sdl_board::~sdl_board()"<<text()<<endl;
	/* 释放缓冲表面 */
	if(_board)delete _board;
	if(_hit_board_ptr)delete[] _hit_board_ptr;
}
//底板初始函数
int sdl_board::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
{
	//cout<<"init board start"<<endl;
	string cur_platform;
	if(sdlsurface::init(0,pw,ph,32,0,0,0,0))return -1;
	//-------------
	_rect.x = px;
	_rect.y = py;
	_rect.w = pw;
	_rect.h = ph;
	//--------------
	if(_board)delete _board;
	_board = new sdlsurface(0,pw,ph,32,0,0,0,0);
	//----------------
	//-----------------
	//if(ptitle)
	{
		cur_platform = SDL_GetPlatform();
		if(!cur_platform.compare("Windows"))
		{
			//_text_board = new sdltext("c:/windows/fonts/simkai.ttf",16);
		}
		else
		if(!cur_platform.compare("Linux"))
		{
			//_text_board = new sdltext("/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc",16);
		}
		else
		if(!cur_platform.compare("Android"))
		{
			//_text_board = new sdltext("/system/fonts/DroidSanSansFallback.ttf",16);
		}
		//if(_text_board)_text_board->render_utf8_solid(ptitle,_text_color);
	}
	//
	/* 注册委托函数 */
	sdl_event_manager::push(this);
	sdl_event_manager::push(this,"on_click");
	connect_event("on_click",this,sdlgui_button_click);
	return 0;
}
//------------------------------------------
//底板初始空函数
int sdl_board::init()
{
	if(sdlsurface::init())return -1;
	memset((char*)&_pos,0x00,sizeof(SDL_Point));
	memset((char*)&_size,0x00,sizeof(SDL_Point));
	memset((char*)&_rect,0x00,sizeof(SDL_Rect));
	_is_show = 1;
	_is_destroy = 0;
	_parent = NULL;
	_end = NULL;
	_head = NULL;
	_next = NULL;
	_last = NULL;
	_board = NULL;
	_hit_board_ptr = NULL;
	/* 初始子窗口节点列表 */
	_board_list.clear();
	return 0;
}
//--------------------------------------
//设置窗口底板位置
int sdl_board::pos(int x,int y)
{
	_rect.x = x;
	_rect.y = y;
	return 0;
}
//设置父级窗口
sdl_board* sdl_board::parent(sdl_board* parent)
{
	_parent = parent;
	return _parent;
}
//------------------------------------------
//返回父级窗口
sdl_board* sdl_board::parent()
{
	return _parent;
}
//-------------------------------------------------
/* 
	 返回给定对象是否为当前窗口的子窗口 
	 如果是子级窗口返回0,否则返回-1 
 */
int sdl_board::is_child(sdl_board* obj)
{
	sdl_board* t = obj;
	//如果指定窗口与指定窗口的父级窗口都存在则处理数据
	while(t && t->parent())
	{
		//如果指定窗口的父级窗口与当前窗口相等,返回0
		if(t->parent() == this)return 1;
		//向父级窗口跳转
		t = t->parent();
	}
	//如果一直没有返回表示指定窗口不是当前窗口的子级,则返回-1
	return 0;
}
//-------------------------------------
//添加子内部窗口底板
template<class T>T* sdl_board::add(const char* title,int px,int py,int pw,int ph,Uint32 pflags)
{
	T* t = dynamic_cast<T*>(new T);
	t->init(title,px,py,pw,ph,pflags);
	//cout<<"add board start"<<endl;
	t->_parent = this;
	z_top(t,NULL,1);
	//cout<<"add board end"<<endl;
	return t;
}
//---------------------------------------------------
//添加外部子窗口底板
template<class T>T* sdl_board::add(T* obj)
{
	if(obj)
	{
		obj->_parent = this;
		z_top(obj,NULL,1);
		return obj;
	}
	return NULL;
}
//-----------------------------------------
//调整子窗口Z序
/* 
		子窗口Z序的最顶层窗口（即列表尾节点）的NEXT应为NULL 
		如果b为空
			如果z为0表示删除a节点
			否则如果z>0表示插入头节点
			否则如果z<0表示插入尾节点
		否则
			如果z为0表示交换a和b的位置
			否则如果z>0表示a移动到b的后面
			否则如果z<0表示a移动到b的前面
 */
int sdl_board::z_top(sdl_board* a,sdl_board *b,int z=1)
{
	map<sdl_board*,int>::iterator node;
	if(!a)return -1;
	/* 如果没有b对象表示直接插入 */
	if(!b)
	{
		if(z>0)
		{
			_board_list.insert(pair<sdl_board*,int>(a,0));
		}
		else
		if(z<0)
		{
			_board_list.insert(_board_list.begin(),pair<sdl_board*,int>(a,0));
		}
		else
		{
			_board_list.erase(a);
		}
	}
	else
	{
		if(z>0)
		{
			node = _board_list.find(b)++;
			_board_list.erase(a);
			_board_list.insert(node,pair<sdl_board*,int>(a,0));
		}
		else
		if(z<0)
		{
			node = _board_list.find(b)++;
			_board_list.erase(a);
			_board_list.insert(node,pair<sdl_board*,int>(a,0));
		}
		else
		{
			node = _board_list.find(a);
			_board_list.erase(a);
			_board_list.insert(_board_list.find(b),pair<sdl_board*,int>(a,0));
			_board_list.erase(b);
			_board_list.insert(node,pair<sdl_board*,int>(b,0));
		}
	}
	return 0;
}
//--------------------------------------------------------
//重绘底板窗口
int sdl_board::redraw()
{
	sdl_board* node_board;
	map<sdl_board*,int>::iterator node = _board_list.begin();
	blit_surface(NULL,_board,NULL);
	while(node!=_board_list.end())
	{
		node_board = (sdl_board*)node->first;
		node_board->redraw();
		node_board->_board->blit_surface(NULL,_board,NULL);
		node++;
		cout<<node_board<<endl;
	}
	return 0;
}
//显示一个底板窗口
int sdl_board::show()
{
	_is_show = 1;
	return 0;
}
//---------------------------------------------
//隐藏一个底板窗口
int sdl_board::hide()
{
	_is_show = 0;
	return 0;
}
//---------------------------------------------
//一个底板窗口的显示状态
int sdl_board::is_show()
{
	return _is_show;
}
//---------------------------------------------
//底板窗口委托事件处理
int sdl_board::handle(int id)
{
	switch(id)
	{
		case sdlgui_button_click:
			on_click(This,NULL);
		break;
		default:
		break;
	}
	return 0;
}
//----------------------------------------------
//底板窗口连接委托事件函数
int sdl_board::connect_event(string event_string,sdl_board* event_object,int event_handle)
{
	return sdl_event_manager::push(This,event_string,event_object,event_handle);
}
//----------------------------------------------
//给底板窗口发送信号
int sdl_board::event_signal(string event_string)
{
	return sdl_event_manager::call_event(This,event_string);
}
//---------------------------------------------
//底板窗口鼠标点击事件委托函数
int sdl_board::on_click(sdl_board* obj,void* data)
{
	cout<<"click board is:"<<this<<endl;
}
//-------------------------------------------
//
//
//
//
//
//
//--------------------------------------
//窗口框架空白构造函数
sdl_frame::sdl_frame()
:
GUI<sdl_frame,sdl_board>()
{
	init();
}
//--------------------------------------
//窗口框架带参构造函数
sdl_frame::sdl_frame(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
:
GUI<sdl_frame,sdl_board>()
{
	init();
	init(ptitle,px,py,pw,ph,pflags);	
}
//--------------------------------------
//框架析构函数
sdl_frame::~sdl_frame()
{
	if(_window)
	{
		delete _window;
	}
}
//-------------------------
//
int sdl_frame::init()
{
	if(sdl_board::init())return -1;
	_window = NULL;
	//_renderer = NULL;
	_event_thread = NULL;
	_is_exit = 0;
	return 0;
}
//-------------------------
//窗口框架初始函数
int sdl_frame::init(const char* ptitle,int px,int py,int pw,int ph,Uint32 pflags)
{
	if(sdl_board::init("",px,py,pw,ph,0))return -1;
	/* 设置窗口位置 */
	_rect.x = 0;
	_rect.y = 0;
	//-------------------
	//创建窗口
	_window = new sdlwindow(ptitle,px,py,pw,ph,pflags);
	/* 创建渲染器 */
	if(_window)
	{
		/* 取窗口大小 */
		_window->size(&_window_rect.x,&_window_rect.y);
		//_screen.init(ptitle,px,py,_window_rect.x,_window_rect.y,pflags);
		size(_window_rect.x,_window_rect.y);
		//_rect.h = _window_rect.y;
		//_rect.w = _window_rect.y;
	}
	_screen.surface(_window->get_window_surface()->surface());
	/* 开启消息流子级线程 */
	//_event_thread = SDL_CreateThread(all_event_process,"event_process",(void*)this);
	return 0;
}
//-----------------------------------
//返回窗口框架的窗口对象。
sdlwindow* sdl_frame::frame()
{
	return _window;
}
//-----------------
//重载底板类的重画函数
//用于把_board对象显示到窗口框架
int sdl_frame::redraw()
{
	//sdl_board::_frame_count = 0;
	sdl_board::redraw();
	_board->blit_surface(NULL,&_screen,NULL);
	//_window->update_window_surface();
	return 0;
}
//-------------------------------------
//返回当前FPS
double sdl_frame::fps()
{
	return _fps;
}
//-------------------------
//用于消息事件分流
int sdl_frame::event_shunt(SDL_Event* e)
{
	static sdl_board* t;
	static int x,y;
	SDL_Event te;
	SDL_UserEvent ue;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			SDL_GetMouseState(&x,&y);
		break;
		case SDL_FINGERUP:
		case SDL_FINGERDOWN:
		case SDL_FINGERMOTION:
			x = e->tfinger.x * _window_rect.x;
			y = e->tfinger.y * _window_rect.y;
		break;
	}
	//t = hit_board(x,y);
	t = (t==0)?(sdl_board*)this : t;
	switch(e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		case SDL_FINGERDOWN:
			//if(sdl_frame::_capture_win)
			{
				//sdl_frame::_capture_win->event(e);
				//sdl_frame::_capture_win->event_signal("on_click");
			}
			//
			if(t != this)t->event(e);
		break;
		case SDL_MOUSEBUTTONUP:
		case SDL_FINGERUP:
		case SDL_FINGERMOTION:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			//if(t != this)t->event(e);
			//if(sdl_frame::_capture_win)
			{
				//sdl_frame::_capture_win->event(e);
				//sdl_frame::_capture_win->event_signal("on_click");
			}
			//else
			{
				t->event(e);
				t->event_signal("on_click");
			}
		break;
		case SDL_KEYUP:
		break;
		case SDL_TEXTINPUT:
			//ime.input(*e->text.text);
		case SDL_KEYDOWN:
			//if(_active_win != this)_active_win->event(e);
			//_active_win->event(e);
		break;
	}
	return 0;
}
//重载窗口的系统事件处理函数。
int sdl_frame::sysevent(SDL_Event* e)
{
	switch(e->type)
	{
		case SDL_WINDOWEVENT:
			switch(e->window.event)
			{
				/* 屏幕重显窗口时，分配新的窗口表面 */
				/* 窗口大小调整时，分配新的窗口表面 */
				case SDL_WINDOWEVENT_RESIZED:
				case SDL_WINDOWEVENT_RESTORED:
					_screen.surface(_window->get_window_surface()->surface());
				break;
				default:
					cout<<"Window Event"<<endl;
				break;
			}
		break;
		case SDL_QUIT:
			_is_exit = 1;
		break;
	}
	return sdl_board::sysevent(e);
}
//-------------------------------------------
//窗口框架运行函数
int sdl_frame::run()
{
	clock_t _frame_timer;
	double sleep = 0;
	//sdltexture* tex=NULL;
	while(!_is_exit)
	{
		_frame_timer = clock();
		while(SDL_PollEvent(&_main_event))
		{
			switch(_main_event.type)
			{
				case SDL_QUIT:
					event(&_main_event);
				break;
				case SDL_WINDOWEVENT:
					event(&_main_event);
				break;
				case SDL_USEREVENT:
					/* 计时器消息分流 */
					if(_main_event.user.code == sdlgui_event_timer)
					{
							((sdl_board*)_main_event.user.data1)->event(&_main_event);
					}
					else
					{
						event(&_main_event);
					}
				break;
				default:
					/* 其它消息分流 */
					event_shunt(&_main_event);
				break;
			}
		}
		redraw();
		//
		/* 刷新屏幕 */
		_window->update_window_surface();
		/* 计算帧频 */
		_fps = 1000 / ((clock() - _frame_timer + 0.001));
		sleep = 1000/60-1000/_fps;
		sleep = (sleep>0)?sleep:0;
		SDL_Delay((sleep<(1000/60))?sleep:(1000/60));
	}
	return 0;
}
//------------------------------------------------
//------------------------------------------
//更新窗口位置
int sdl_frame::pos(int x,int y)
{
	if(!_window)return -1;
	return _window->pos(x,y);
}
//----------------------------------------------
//更新窗口大小
int sdl_frame::size(int w,int h)
{
	if(!_window)return -1;
	if(_window->size(w,h))return -1;
	//if(sdl_board::size(w,h))return -1;
	_screen.surface(_window->get_window_surface()->surface());
	return 0;
}
int sdl_frame::size(int* w,int* h)
{
	if(!_window)return -1;
	return _window->size(w,h);
}
//----------------------------------------------
//显示窗口
int sdl_frame::show()
{
	if(!_window)return -1;
	return _window->show();
}
//----------------------------------------------
//显示窗口
int sdl_frame::hide()
{
	if(!_window)return -1;
	return _window->hide();
}
//---------------------------------------------------------------
//
//
//
//
//---------------------------------------------------------------
//窗口工具构造函数
sdl_widget::sdl_widget()
:
GUI<sdl_widget,sdl_board>()
{
	init();
}
sdl_widget::sdl_widget(const char* title,int px,int py,int pw,int ph,Uint32 pflags)
:
GUI<sdl_widget,sdl_board>()
{
	init(title,px,py,pw,ph,pflags);
}
//---------------------------------------------------------
//窗口工具析构函数
sdl_widget::~sdl_widget()
{
	//cout<<this<<endl;
}
int sdl_widget::init()
{
	if(sdl_board::init())return -1;
	return 0;
}
int sdl_widget::init(const char* title,int px,int py,int pw,int ph,Uint32 pflags)
{
	if(sdl_board::init(title,px,py,pw,ph,pflags))return -1;
	return 0;
}
int sdl_widget::sysevent(SDL_Event* e)
{
	return sdl_board::sysevent(e);
}
#endif//__SDLWINDOW_HANDLE__
