
#ifndef _TEXTURE_MANAGER_
#define _TEXTURE_MANAGER_
#include <unordered_map>
#include "Texture.h"
#include "..\Sys\sys_graphics.h"
class TextureManager {
	typedef struct {
		Texture texture;
		int count;
		bool loaded;
	} texture_info_t;

	typedef std::unordered_map<SiString,texture_info_t> textureCache;


	public:
		TextureManager() {}

		~TextureManager() {
			for (textureCache::iterator cur = textures.begin();cur != textures.end();++cur) {
				Sys_ReleaseTexture(cur->second.texture.texture);
			}
		}

		void allocateTexture(const SiString& name,Texture &newTexture) {
			if (textures.find(name) != textures.end()) {
				return;
			}
			Sys_CreateTexture(newTexture);
			texture_info_t newTex_info;
			newTex_info.count =1;
			newTex_info.loaded = true;
			textures[name] = newTex_info;
		}

		Texture* loadTextureFromFile(const SiString& name,const int format) {
			if (textures.find(name) != textures.end()) {
				//exists
				++textures[name].count;
				if (textures[name].loaded)
					//loaded and ready to use
					return &textures[name].texture;
			} else {
				// doesn't exist
				texture_info_t newTexture;
				newTexture.texture.format = format;
				newTexture.count = 1;
				textures[name] = newTexture;
			}
			textures[name].loaded = true;
			Sys_LoadTextureFromFile(textures[name].texture,name);
			return &textures[name].texture;

		}
		void unloadTexture(const SiString& name) {
			if (textures.find(name) == textures.end())
				//Not in cache
				return;
			if (--textures[name].count > 0)
				return;

			textures[name].loaded = false;
			Sys_ReleaseTexture(textures[name].texture.texture);
		}

	private:
		textureCache textures;

};

#endif