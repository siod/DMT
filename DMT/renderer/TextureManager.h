
#include <unordered_map>
#include "..\Sys\sys_graphics.h"
class TextureManager {
	typedef struct {
		Texture texture;
		int count;
		int format;
		bool loaded;
	} texture_info_t;

	typedef std::unordered_map<SiString,texture_info_t> textureCache;


	public:
		TextureManager() {}

		~TextureManager() {
			for (textureCache::iterator cur = textures.begin();cur != textures.end();++cur) {
				Sys_ReleaseTexture(cur->second.texture);
			}
		}

		Texture* loadTexture(const SiString& name,int format) {
			if (textures.find(name) != textures.end()) {
				//exists
				++textures[name].count;
				if (textures[name].loaded)
					//loaded and ready to use
					return &textures[name].texture;
			} else {
				// doesn't exist
				texture_info_t newTexture;
				newTexture.format = format;
				newTexture.count = 1;
				textures[name] = newTexture;
			}
			textures[name].loaded = true;
			textures[name].texture = Sys_LoadTextureFromFile(name,textures[name].format);
			return &textures[name].texture;

		}
		void unloadTexture(const SiString& name) {
			if (textures.find(name) == textures.end())
				//Not in cache
				return;
			if (--textures[name].count > 0)
				return;

			textures[name].loaded = false;
			Sys_ReleaseTexture(textures[name].texture);
		}

	private:
		textureCache textures;

};
