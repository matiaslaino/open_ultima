#pragma once

#include <SDL.h>
struct SDL_Deleter {
	void operator()(SDL_Surface* ptr) { if (ptr) SDL_FreeSurface(ptr); }
	void operator()(SDL_Texture* ptr) { if (ptr) SDL_DestroyTexture(ptr); }
	void operator()(SDL_Renderer* ptr) { if (ptr) SDL_DestroyRenderer(ptr); }
	void operator()(SDL_Window* ptr) { if (ptr) SDL_DestroyWindow(ptr); }
	void operator()(SDL_RWops* ptr) { if (ptr) SDL_RWclose(ptr); }
};

template<class T, class D = std::default_delete<T>>
struct shared_ptr_with_deleter : public std::shared_ptr<T>
{
	explicit shared_ptr_with_deleter(T* t = nullptr)
		: std::shared_ptr<T>(t, D()) {}

	void reset(T* t = nullptr) {
		std::shared_ptr<T>::reset(t, D());
	}
};