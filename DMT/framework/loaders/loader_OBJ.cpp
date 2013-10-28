#include "loader_OBJ.h"
#include <fstream>
#include <sstream>
#include "..\math.h"


//http://en.wikipedia.org/wiki/Wavefront_.obj_file
void loader_OBJ::addVertex(std::string& input,std::vector<vec3>& vec) {
	std::stringstream data(input);
	data.ignore(5,' ');
	vec3 vertex;
	data >> vertex.x;
	data >> vertex.y;
	data >> vertex.z;
	vec.push_back(vertex);
}

void loader_OBJ::addTexCoord(std::string& input,std::vector<vec2>& vec) {
	std::stringstream data(input);
	data.ignore(5,' ');
	vec2 coord;
	data >> coord.x;
	data >> coord.y;
	// Not supporting 3d tex coords
	float junk;
	data >> junk;
	vec.push_back(coord);
}
/*
void loader_OBJ::LightingInfo(std::string& input,size_t num,std::vector<vec3>& vec) {
	std::stringstream data(input);
	data.ignore(5,' ');
	float temp;
	for (size_t i(0);i<num;++i) {
		data >> temp;
		*arr++ = temp;
	}
}
*/

void loader_OBJ::addFace(std::string& input,std::vector<INDEX_TYPE>& vindices,std::vector<INDEX_TYPE>& nindices,std::vector<INDEX_TYPE>& tindices) {
	std::stringstream data(input);
	data.ignore(5,' ');
	INDEX_TYPE index[3];
	INDEX_TYPE norm[3];
	INDEX_TYPE tc[3];
	for (size_t i(0);i<3;++i) {
		data >> index[i];
		data.ignore(1);
		//Texture co-ords
		data >> tc[i];
		data.ignore(1);
		//For normal data, but not used
		data >> norm[i];
	}
	// obj counts from 1 not 0
	for (int i(2);i >= 0;--i) {
		vindices.push_back(index[i]-1);
		tindices.push_back(tc[i] -1);
		nindices.push_back(norm[i] -1);
	}
}

/*
void loader_OBJ::mtlib_parse(const std::string& input) {
	std::stringstream data(input);
	data.ignore(10,' ');
	std::string filename;
	data >> filename;
	readMtl(filename);
}

void loader_OBJ::readMtl(const std::string& filename) {

	std::ifstream input(filename.c_str());
	if (!input.good())
		return;
	std::string s;
	while ((getline(input,s)).good()) {
		if (s == "")
			continue;
		switch (s[0]) {
			case 'K':
				switch (s[1]) {
					case 'a':
						//ambient
						LightingInfo(s,3,lighting[AMB]);
						break;


					case 'd':
						//difuse
						LightingInfo(s,3,lighting[DIF]);
						break;


					case 's':
						//specular
						LightingInfo(s,3,lighting[SPEC]);
						break;

				}
				break;

			case 'N':
				if (s[1] != 's')
					continue;
				//specular coef
				LightingInfo(s,1,&specCoef);
				break;
			case 'd':
				// transparency
				// Don't currently use it

				break;


			default:
				break;
		}

	}
	input.close();

}
*/



bool loader_OBJ::loadfile(std::vector<vec3> &verts, std::vector<vec3> &norms,std::vector<vec2> &texCoords, std::vector<INDEX_TYPE> &vindices,std::vector<INDEX_TYPE> &nindices,std::vector<INDEX_TYPE> &tindices) {
	std::ifstream input(m_filename.c_str());
	if (!input.good()) {
		m_status = FAILED;
		return false;
	}
	std::string s;
	while ((getline(input,s)).good()) {
		if (s == "")
			continue;
		switch (s[0]) {
			case 'v':
				switch (s[1]) {
					case ' ':
						addVertex(s,verts);
						break;
					case 'n':
						addVertex(s,norms);
						break;
					case 't':
						addTexCoord(s,texCoords);
						break;
					default:
						break;
				}
				break;

			case 'f':
				addFace(s,vindices,nindices,tindices);
				break;

			case 'o':
				// object name
			case '#':
				// comment
				continue;
			case 'm':
					//mtlib_parse(s);
				break;

			default:
				break;
		}
	}
	input.close();
	return true;

}

struct vnt {
	vec3 vertex;
	vec3 norm;
	vec2 tc;
};
void loader_OBJ::load() {
	std::vector<vec3> verts;
	std::vector<vec3> norms;
	std::vector<vec2> texCoords;
	std::vector<INDEX_TYPE> vindices;
	std::vector<INDEX_TYPE> nindices;
	std::vector<INDEX_TYPE> tindices;
	if (!loadfile(verts,norms,texCoords,vindices,nindices,tindices)) {
		//Error occued
		m_status = FAILED;
		return;
	}

	std::vector<vnt> finalOutput;
	for (size_t i(0);i <vindices.size();++i) {
		vnt temp;
		temp.vertex = verts[vindices[i]];
		temp.norm = norms[nindices[i]];
		temp.tc = texCoords[tindices[i]];
		finalOutput.push_back(temp);
	}
	BUFFER_LAYOUT layout(BUFFER_LAYOUT::POS_NORM_TC);
	if (!m_data.model.loadMesh(finalOutput,vindices,layout) ||
		!m_data.model.loadMaterial("BASIC",NULL,0,
				"../resources/color.ps","ColorPixelShader",
				"../resources/color.vs","ColorVertexShader",layout)) {
		m_status = FAILED;
		return;
	}
	m_status = LOADED;
}