#include "loader_OBJ.h"
#include <fstream>
#include <sstream>
#include "..\math.h"


//http://en.wikipedia.org/wiki/Wavefront_.obj_file
void loader_OBJ::addVertex(std::string& input,std::vector<vec3>& vec) {
	std::stringstream data(input);
	data.ignore(5,' ');
	vec3 temp;
	data >> temp.x;
	data >> temp.y;
	data >> temp.z;
	vec.push_back(temp);
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

void loader_OBJ::addFace(std::string& input,std::vector<unsigned int>& indices) {
	std::stringstream data(input);
	data.ignore(5,' ');
	unsigned int index[3];
	unsigned int norm;
	unsigned int tc;
	for (size_t i(0);i<3;++i) {
		data >> index[i];
		data.ignore(1);
		//Texture co-ords
		data >> tc;
		data.ignore(1);
		//For normal data, but not used
		data >> norm;
	}
	// obj counts from 1 not 0
	indices.push_back(index[2]-1);
	indices.push_back(index[1]-1);
	indices.push_back(index[0]-1);
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



bool loader_OBJ::loadfile(std::vector<vec3> &verts, std::vector<vec3> &norms, std::vector<unsigned int> &indices) {
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
					default:
						// nooo idea
						break;
				}
				break;

			case 'f':
				addFace(s,indices);
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

void loader_OBJ::load() {
	std::vector<vec3> verts;
	std::vector<vec3> norms;
	std::vector<vec3> vertsDX;
	std::vector<unsigned int> indices;
	if (!loadfile(verts,norms,indices)) {
		//Error occued
		m_status = FAILED;
		return;
	}
	for (int i(0);i< indices.size();i++) {
		vertsDX.push_back(verts[indices[i]]);
	}
	
	if (!m_data.model.loadMesh(vertsDX,indices) ||
		!m_data.model.loadMaterial("BASIC",NULL,0,
				"../resources/color.ps","ColorPixelShader",
				"../resources/color.vs","ColorVertexShader")) {
		m_status = FAILED;
		return;
	}
	m_status = LOADED;
}