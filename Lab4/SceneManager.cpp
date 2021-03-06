#include "SceneManager.h"
#define DEG_TO_RADIAN 0.017453293

sceneManager::sceneManager(int windowWidth, int windowHeight)
	: windowWidth(windowWidth), windowHeight(windowHeight)
	 {
	window = setupRC(context);
	glewInitilisation();
	loadShader();
	loadModel();	
	//loadSkybox(cubeTexFiles, &skybox);
	draw();
}

sceneManager::sceneManager()
{}

SDL_Window * sceneManager::setupRC(SDL_GLContext & context)
{
	SDL_Window * window;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize video
		cout << "Unable to initialize SDL " << endl;;

	// Request an OpenGL 3.0 context.

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // Turn on x4 multisampling anti-aliasing (MSAA)

	// Create 800x600 window
	window = SDL_CreateWindow("SDL/GLM/OpenGL Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) // Check window was created OK
		cout << "Unable to create window" << endl;

	context = SDL_GL_CreateContext(window); // Create opengl context and attach to window
	SDL_GL_SetSwapInterval(1); // set swap buffers to sync with monitor's vertical refresh rate
	return window;
}

sceneManager::~sceneManager()
{
	/*SDL_GL_DeleteContext(windowContext);
	SDL_DestroyWindow(window);
	SDL_Quit();*/
}

void sceneManager::draw()
{
	glEnable(GL_CULL_FACE);
	glClearColor(0.5f,0.5f,0.5f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN),800.0f/600.0f,1.0f,150.0f);

	glm::mat4 view(1.0);

	ourShader->use();
	ourShader->setMat4("projection", projection);
	ourShader->setMat4("view", view);
	
	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(5.0f, -5.0f, -30.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
	ourShader->setMat4("model", model);
	ourModel->draw(*ourShader);


	SDL_GL_SwapWindow(window);  //Swap buffers
	//draw();		//WILL CAUSE STACKOVER FLOW -- WILL NEED TO BE CHANGED
}

void sceneManager::glewInitilisation()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) { // glewInit failed, something is seriously wrong
		std::cout << "glewInit failed, aborting." << endl;
		exit(1);
	}
	cout << glGetString(GL_VERSION) << endl;
}




void sceneManager::loadModel()
{
	ourModel = make_shared<Model>("../nanosuit.obj");

}

void sceneManager::loadShader()
{
	ourShader = make_shared<Shader>("../shader.vs", "../shader.fs");
	//cubeSkybox = rt3d::initShaders("../cubeSkybox.vert", "../cubeSkybox.frag");
}

void sceneManager::textureInit()
{
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
}




//glEnable(GL_DEPTH_TEST);
//glEnable(GL_BLEND);
//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//GLuint sceneManager::loadSkybox(const char *fname[6], GLuint *texID)
//{
//	glGenTextures(1, texID); // generate texture ID
//	GLenum sides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
//						GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
//						GL_TEXTURE_CUBE_MAP_POSITIVE_X,
//						GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
//						GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
//						GL_TEXTURE_CUBE_MAP_NEGATIVE_Y };
//	SDL_Surface *tmpSurface;
//
//	glBindTexture(GL_TEXTURE_CUBE_MAP, *texID); // bind texture and set parameters
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	GLuint externalFormat;
//	for (int i = 0; i < 6; i++)
//	{
//		// load file - using core SDL library
//		tmpSurface = SDL_LoadBMP(fname[i]);
//		if (!tmpSurface)
//		{
//			std::cout << "Error loading bitmap" << std::endl;
//			return *texID;
//		}
//
//		// skybox textures should not have alpha (assuming this is true!)
//		SDL_PixelFormat *format = tmpSurface->format;
//		externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;
//
//		glTexImage2D(sides[i], 0, GL_RGB, tmpSurface->w, tmpSurface->h, 0,
//			externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
//		// texture loaded, free the temporary buffer
//		SDL_FreeSurface(tmpSurface);
//	}
//	return *texID;
//}
