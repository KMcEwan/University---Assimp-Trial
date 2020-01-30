#pragma once
#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <SDL.h>
#include "../rt3d.h"


using namespace std;


class sceneManager
{
private:
	void loadModel();
	void loadShader();
	int windowWidth;
	int windowHeight;
	void textureInit();
	
public:
	sceneManager(int windowWidth, int windowHeight);
	sceneManager();
	~sceneManager();
	void draw();
	SDL_GLContext context;
	SDL_Window *window;
	void glewInitilisation();
	shared_ptr<Shader> ourShader;
	shared_ptr<Model> ourModel;
	GLuint cubeSkybox;
	SDL_Window * setupRC(SDL_GLContext &context);
	GLuint loadSkybox(const char *fname[6], GLuint *texID);
	GLuint skybox;
	const char *cubeTexFiles[6] = {
			"../resource/Town-skybox/Town_bk.bmp",
			"../resource/Town-skybox/Town_ft.bmp",
			"../resource/Town-skybox/Town_rt.bmp",
			"../resource/Town-skybox/Town_lf.bmp",
			"../resource/Town-skybox/Town_up.bmp",
			"../resource/Town-skybox/Town_dn.bmp"
	};
};