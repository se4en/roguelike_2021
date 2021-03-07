#include "common.h"
#include "Image.h"
#include "Player.h"
#include "Map.h"
#include "Menu.h"

#define GLFW_DLL
#include <GLFW/glfw3.h>

struct InputState
{
  bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
  GLfloat lastX = 400, lastY = 300; //исходное положение мыши
  bool firstMouse = true;
  bool captureMouse         = true;  // Мышка захвачена нашим приложением или нет?
  bool capturedMouseJustNow = false;
} static Input;


GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;
  case GLFW_KEY_1:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    break;
  case GLFW_KEY_2:
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    break;
	default:
		if (action == GLFW_PRESS)
      Input.keys[key] = true;
		else if (action == GLFW_RELEASE)
      Input.keys[key] = false;
	}
}

void processPlayerMovement(Player &player, Map &map)
{ 
  bool flag = false;
  if (Input.keys[GLFW_KEY_E])
    map.BreakDoor(player.GetCoords());
  if (Input.keys[GLFW_KEY_W]) {
    player.ProcessInput(MovementDir::UP, map);
    if (player.icon==STAY_R)
      player.icon = RUN_R;
    else if (player.icon==STAY_L)
      player.icon = RUN_L;
    flag = true;
  }
  else if (Input.keys[GLFW_KEY_S]) {
    player.ProcessInput(MovementDir::DOWN, map);
    if (player.icon==STAY_R)
      player.icon = RUN_R;
    else if (player.icon==STAY_L)
      player.icon = RUN_L;
    flag = true;
  }
  if (Input.keys[GLFW_KEY_A]) {
    player.ProcessInput(MovementDir::LEFT, map);
    flag = true;
  }
  else if (Input.keys[GLFW_KEY_D]) {
    player.ProcessInput(MovementDir::RIGHT, map);
    flag = true;
  }
  if (!flag) {
    if (player.icon==RUN_R)
      player.icon = STAY_R;
    else if (player.icon==RUN_L)
      player.icon = STAY_L;
  }
}

void processMenuNovigation(Menu &menu)
{ 
  if (Input.keys[GLFW_KEY_ENTER])
    menu.Enter();
  else if (Input.keys[GLFW_KEY_W])
    menu.Up();
  else if (Input.keys[GLFW_KEY_S])
    menu.Down();
}

void OnMouseButtonClicked(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    Input.captureMouse = !Input.captureMouse;

  if (Input.captureMouse)
  {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Input.capturedMouseJustNow = true;
  }
  else
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
  if (Input.firstMouse)
  {
    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
    Input.firstMouse = false;
  }

  GLfloat xoffset = float(xpos) - Input.lastX;
  GLfloat yoffset = Input.lastY - float(ypos);

  Input.lastX = float(xpos);
  Input.lastY = float(ypos);
}


void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
  // ...
}


int initGL()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  std::cout << "Controls: "<< std::endl;
  std::cout << "press right mouse button to capture/release mouse cursor  "<< std::endl;
  std::cout << "W, A, S, D - movement  "<< std::endl;
  std::cout << "press ESC to exit" << std::endl;

	return 0;
}

int main(int argc, char** argv)
{
	if(!glfwInit())
    return -1;

//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow*  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "task1 base project", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window); 

	glfwSetKeyCallback        (window, OnKeyboardPressed);  
	glfwSetCursorPosCallback  (window, OnMouseMove); 
  glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
	glfwSetScrollCallback     (window, OnMouseScroll);

	if(initGL() != 0) 
		return -1;
	
  //Reset any OpenGL errors which could be present for some reason
	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR)
		gl_error = glGetError();

  // init screen
  Image screenBuffer(WINDOW_WIDTH, WINDOW_HEIGHT, 4);
  std::shared_ptr<Image> shared(&screenBuffer);
  float coef = 0;

  // init map
  std::map<std::string, std::string> tiles {
    {"lava", "./resources/lava.png"},
    // FLOOR
    {"floor_1", "./resources/floor_1.png"},
    {"floor_2", "./resources/floor_2.png"},
    {"floor_3", "./resources/floor_3.png"},
    {"floor_4", "./resources/floor_4.png"},
    // WALLS
    {"wall_A", "./resources/walls/A.png"},
    {"wall_B", "./resources/walls/B.png"},
    {"wall_C", "./resources/walls/C.png"},
    {"wall_D", "./resources/walls/D.png"},
    {"wall_E", "./resources/walls/E.png"},
    {"wall_F", "./resources/walls/F.png"},
    {"wall_G", "./resources/walls/G.png"},
    {"wall_H", "./resources/walls/H.png"},
    // DOOR
    {"door", "./resources/door.jpg"},
    // CASTLE
    {"castle", "./resources/door.jpg"},
    // LETTERS
    {"A", "./resources/font/letter-65.png"}, // 0
    {"E", "./resources/font/letter-69.png"}, // 1
    {"V", "./resources/font/letter-86.png"}, // 2
    {"L", "./resources/font/letter-76.png"}, // 3
    {"1", "./resources/font/letter-49.png"}, // 4 
    {"2", "./resources/font/letter-50.png"}, // 5
    {"Y", "./resources/font/letter-89.png"}, // 6
    {"O", "./resources/font/letter-79.png"}, // 7
    {"U", "./resources/font/letter-85.png"}, // 8
    {"D", "./resources/font/letter-68.png"}, // 9
    {"I", "./resources/font/letter-73.png"}, // 10
    {"!", "./resources/font/letter-33.png"}, // 11
    {"W", "./resources/font/letter-87.png"}, // 11
    {"N", "./resources/font/letter-78.png"}, // 12
    {"T", "./resources/font/letter-84.png"}, // 13
    {"B", "./resources/font/letter-66.png"}, // 14
    {")", "./resources/font/letter-1.png"}  // 15
  };
  std::map<int, std::string> levels {
    {1, "./resources/level_1.txt"},
    {2, "./resources/level_2.txt"}
  };
  Map map(&screenBuffer, tiles, levels);
  map.LoadLevel(1);
  map.Draw(std::pair<Point, Point>({.x=0, .y=0}, {.x=WINDOW_WIDTH-1, .y=WINDOW_HEIGHT-1}));

  // init player
  std::map<std::string, std::string> icons {
    {"stay_r-0", "./resources/player/stay_r-0.png"},
    {"stay_r-1", "./resources/player/stay_r-1.png"},
    {"stay_r-2", "./resources/player/stay_r-2.png"},
    {"stay_r-3", "./resources/player/stay_r-3.png"},
    {"stay_l-0", "./resources/player/stay_l-0.png"},
    {"stay_l-1", "./resources/player/stay_l-1.png"},
    {"stay_l-2", "./resources/player/stay_l-2.png"},
    {"stay_l-3", "./resources/player/stay_l-3.png"},
    {"run_r-0", "./resources/player/run_r-0.png"},
    {"run_r-1", "./resources/player/run_r-1.png"},
    {"run_r-2", "./resources/player/run_r-2.png"},
    {"run_r-3", "./resources/player/run_r-3.png"},
    {"run_r-4", "./resources/player/run_r-4.png"},
    {"run_r-5", "./resources/player/run_r-5.png"},
    {"run_l-0", "./resources/player/run_l-0.png"},
    {"run_l-1", "./resources/player/run_l-1.png"},
    {"run_l-2", "./resources/player/run_l-2.png"},
    {"run_l-3", "./resources/player/run_l-3.png"},
    {"run_l-4", "./resources/player/run_l-4.png"},
    {"run_l-5", "./resources/player/run_l-5.png"}
  };
	Player player(&screenBuffer, map.GetStart(), icons);

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);  GL_CHECK_ERRORS;
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;

  bool flag_1 = false;
  bool flag_2 = false;
  bool flag_3 = false;

  // LEVEL 1
  map.Dark();
  map.LoadLevel(1);
  map.PrintLevel1();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
  glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data()); GL_CHECK_ERRORS;
  glfwSwapBuffers(window);
  for (int f=1; f<50; f++)
    std::this_thread::sleep_for(std::chrono::milliseconds(40));
  map.SetStatus(MP_2LVL);
  for (coef = 0; coef<=1; coef += 0.04) {
    map.Dark2Level(coef);
    map.PrintLevel1();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data()); GL_CHECK_ERRORS;
  	glfwSwapBuffers(window);
  }
  map.SetStatus(MP_INGAME);
  map.Draw(std::pair<Point, Point>({.x=0, .y=0}, {.x=WINDOW_WIDTH-1, .y=WINDOW_HEIGHT-1}));
  player.Restart();

  int level = 1;

  //game loop
	while (!glfwWindowShouldClose(window)) {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
    glfwPollEvents();
    
    //if (map.GetStatus()==)

    if (player.GetStatus()==ST_ON_RUN) {
      processPlayerMovement(player, map);
      map.Draw(player.GetLeftRight());
      player.Draw();
    }


    switch (map.GetStatus()) {

      case MP_INGAME:
        switch (player.GetStatus()) {
          case ST_ON_RUN:
            break;
          case ST_DIED:
            map.Draw(player.GetLeftRight());
            map.SetStatus(MP_2DARK);
            coef = 1;
            break;
          case ST_WON:
            map.Draw(player.GetLeftRight());
            level++;
            //if (level<3) {
            //  map.LoadLevel(2);
            std::cout << level << std::endl;
            map.SetStatus(MP_2DARK);
            coef = 1;
            break;
        }
        break;

      case MP_2DARK:
        if (coef >= 0.5) {
          map.Map2Dark(coef);
          if (player.GetStatus()==ST_DIED)
            map.PrintDie();
          else if (player.GetStatus()==ST_WON && level==1)
            map.PrintNotBad();
          else if (player.GetStatus()==ST_WON && level==2) {
            map.PrintNotBad();
          }
          coef -= 0.01;
        }
        else if (coef >= 0) {
          map.Map2Dark(coef);
          if (level==1)
            map.PrintLevel1();
          else if (level==2)
            map.PrintLevel2();
          else if (level==3)
            break;
          coef -= 0.01;
        }
        else {
          if (level==1) {
            map.PrintLevel1();
            map.LoadLevel(1);
          }
          else {
            map.PrintLevel2();
            map.LoadLevel(2);
          }
          map.SetStatus(MP_2LVL);

          coef = 0;
        }
        break;

      case MP_2LVL:
        if (coef <= 1) {
          map.Dark2Level(coef);
          if (level==1)
            map.PrintLevel1();
          else if (level==2)
            map.PrintLevel2();
          coef += 0.04;
        }
        else {
          map.SetStatus(MP_INGAME);
          player.status = ST_ON_RUN;
          map.Draw(std::pair<Point, Point>({.x=0, .y=0}, {.x=WINDOW_WIDTH-1, .y=WINDOW_HEIGHT-1}));
          player.Restart();
        }
        break;
    }

    // step
    if (flag_1) {
      if (flag_2) {
        if (flag_3) {
          ++player.cntr;
          flag_1 = false;
          flag_2 = false;       
          flag_3 = false;
        }
        else 
          flag_3 = true;
      }
      else flag_2 = true;
    }
    else {
      flag_1 = true;
    }  
    

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.Data()); GL_CHECK_ERRORS;

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
