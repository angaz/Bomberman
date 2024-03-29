#include "Window.hpp"

cge::Window::Window() :
		_width(0),
		_height(0),
		_lastFrameTime(static_cast<unsigned int>(glfwGetTime() * 1000.0)),
		_glfwWindow(nullptr)
{

}

cge::Window::~Window() {
	if (this->_glfwWindow != nullptr) {
		glfwDestroyWindow(this->_glfwWindow);
	}

	glfwTerminate();
}

void	cge::Window::create(const std::string &windowName, unsigned width, unsigned height, unsigned windowFlags) {
	glfwInit();

	this->_width = width;
	this->_height = height;
	this->_lastFrameTime = static_cast<unsigned int>(glfwGetTime() * 1000.0);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_FOCUSED, GL_TRUE);

	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	this->_glfwWindow = glfwCreateWindow(
		this->_width,
		this->_height,
		windowName.c_str(),
		((windowFlags & Window::Flags::FULLSCREEN) != 0) ? glfwGetPrimaryMonitor() : nullptr,
		nullptr
	);

	glfwMakeContextCurrent(this->_glfwWindow);
	glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (this->_glfwWindow == nullptr) {
		throw SDL_FatalError("Could not create GLFW window");
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

	/// Enable VSYNC?
	glfwSwapInterval(((windowFlags & Window::Flags::VSYNC_ENABLED) != 0) ? 1 : 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwFocusWindow(this->_glfwWindow);
}

void cge::Window::swapBuffers() {
	auto currentTime = static_cast<unsigned int>(glfwGetTime() * 1000.0);
	this->_deltaFrameTime = currentTime - this->_lastFrameTime;
	this->_lastFrameTime = currentTime;
	glfwSwapBuffers(this->_glfwWindow);
}

cge::Window::Window(const Window &window) {
	*this = window;
}

unsigned	cge::Window::getWidth() const {
	return this->_width;
}

unsigned	cge::Window::getHeight() const {
	return this->_height;
}

cge::Window::Window(const std::string &windowName, unsigned width, unsigned height, unsigned windowFlags) {
	this->create(windowName, width, height, windowFlags);
}

unsigned	cge::Window::getFrameTime() const {
	return this->_deltaFrameTime;
}

GLFWwindow	*cge::Window::getGLFWWindow() const {
	return (this->_glfwWindow);
}

void	cge::Window::recreate(unsigned width, unsigned height) {
	cge::Settings::Settings *settings = cge::Settings::Settings::getSingleton();

	GLFWmonitor *monitor = glfwGetWindowMonitor(this->_glfwWindow);
	if (monitor == nullptr) {
		monitor = glfwGetPrimaryMonitor();
	}

	const GLFWvidmode *mode = glfwGetVideoMode(monitor);
	if (settings->getSettings().Fullscreen) {
		glfwSetWindowMonitor(this->_glfwWindow, monitor, 0, 0, width, height, mode->refreshRate);

	} else {
		glfwSetWindowMonitor(this->_glfwWindow, nullptr, (mode->width - width) / 2, (mode->height - height) / 2, width, height, 0);
	}

	glViewport(0, 0, width, height);
}
