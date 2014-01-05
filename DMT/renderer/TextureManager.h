
#ifndef _TEXTURE_MANAGER_
#define _TEXTURE_MANAGER_
#include <unordered_map>
#include "Texture.h"
#include "..\Sys\sys_graphics.h"
#include "..\framework\typedefs.h"
class TextureManager {
	typedef struct {
		Texture texture;
		int count;
		bool loaded;
	} texture_info_t;

	typedef std::unordered_map<guid,texture_info_t> textureCache;
	typedef std::unordered_map<SiString,guid> guidCache;

	guid lookupGUID(const SiString& name) {
		return guids[name];
	}

	public:
		TextureManager() {}

		~TextureManager() {
			for (textureCache::iterator cur = textures.begin();cur != textures.end();++cur) {
				Sys_ReleaseTexture(cur->second.texture.texture);
			}
		}

		Texture* allocateTexture(const guid id) {
			if (textures.find(id) != textures.end()) {
				return;
			}
			Texture newTexture;
			newTexture.id = id;
			texture_info_t newTex_info;
			newTex_info.count =0;
			newTex_info.loaded = false;
			newTex_info.texture = newTexture;
			textures[id] = newTex_info;
		}

		void loadTexture(const guid id) {
			if (!textures[id].loaded) {
				Sys_CreateTexture(textures[id].texture);
				textures[id].count = 1;
				textures[id].loaded = true;
			} else {
				++textures[id].count;
			}
		}

		Texture* allocateTexture(const SiString& name) {
			allocateTexture(lookupGUID(name));
		}

		Texture* loadTextureFromFile(const SiString& name,const int format) {
			guid id = lookupGUID(name);
			if (textures.find(id) != textures.end()) {
				//exists
				++textures[id].count;
				if (textures[id].loaded)
					//loaded and ready to use
					return &textures[id].texture;
			} else {
				// doesn't exist
				texture_info_t newTexture;
				newTexture.texture.format = format;
				newTexture.count = 1;
				textures[id] = newTexture;
			}
			textures[id].loaded = true;
			Sys_LoadTextureFromFile(textures[id].texture,name);
			return &textures[id].texture;

		}

		void unloadTexture(const guid id) {
			if (textures.find(id) == textures.end())
				//Not in cache
				return;
			if (--textures[id].count > 0)
				return;

			Sys_ReleaseTexture(textures[id].texture.texture);
			textures[id].loaded = false;
		}

		void unloadTexture(const SiString& name) {
			unloadTexture(lookupGUID(name));
		}

	private:
		textureCache textures;
		guidCache guids;

};

#endif