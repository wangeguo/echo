#include <echo/echo.h>
#include <echo/engine/engine.h>
#include <stdexcept>

const std::string echo::Echo::UNABLE_TO_START = "Unable to start the Echo";

echo::Echo::Echo()
{
	// call Echo with NULL context
}

echo::Echo::Echo(echo::Context context)
{
	this->context = context;
	this->started = false;
	name = NULL;
	description = NULL;
	author = NULL;
	owner = NULL;

	if(echo::engine::Engine::getInstance() == NULL) {
		echo::Context::getCurrentLogger()::severe("Unable to fully initialize the Echo. No Echo engine available.");
		throw std::runtime_error(
			"Unable to fully initialize the Echo. No Echo Engine available.");
	}
	// echo.component.ChildContext.fireContextChanged(this,context);
}


echo::Application echo::Echo::getApplication() {
	return echo::Application::getCurrent();
}

std::string echo::Echo::getAuthor() {
	return author;
}

echo::Context echo::Echo::getContext(){
	return context;
}

std::string echo::Echo::getDescription()
{
	return description;
}

echo::util::logging::Logger echo::Echo::getLogger()
{
	echo::util::logging::Logger result;
	echo::Context context = getContext();

	if(context == NULL){
		context = echo::Context::getCurrent();
	}

	if(context != NULL){
		result = context.getLogger();
	}

	if(result == NULL){
		result = Engine.getLogger(this, "echo");
	}

	return result;
}

std::string echo::Echo::getName()
{
	return name;
}

std::string echo::Echo::getOwner()
{
	return owner;
}

void echo::Echo::handle(echo::Request request,
						echo::Response response) 
{
	// Associate the response to the current thread
	echo::Response::setCurrent(response);

	// Associate the context to the current thread
	if(getContext() != NULL){
		echo::Context::setCurrent(getContext());
	}

	// Check if the Echo was started
	if(isStopped()){
		try {
			start();
		}
		catch(std::exception e){
			// Occurred while starting the Echo
			getContext().getLogger().log(Level.WARNING, UNABLE_TO_START,e);
			response.setStatus(Status.SERVER_ERROR_INTERNAL);
		}

		if(!isStarted()){
			// No exception raised but the Echo somehow couldn't by started
			getContext().getLogger().log(echo::util::logging::Level.WARNING,
										 UNABLE_TO_START);
			response.setStatus(Status.SERVER_ERROR_INTERNAL);
		}
	}
}

bool echo::Echo::isStarted()
{
	return started;
}

bool echo::Echo::isStopped()
{
	return !started;
}

void echo::Echo::setAuthor(std::string author)
{
	this->author = author;
}

void echo::Echo::setContext(echo::Context context)
{
	this->context = context;
	// echo.engine.component.ChildContext.fireContextChanged(this, context);
}

void echo::Echo::setDescription(std::string description)
{
	this->description = description;
}

void echo::Echo::setName(std::string name)
{
	this->name = name;
}

void echo::Echo::setOwner(std::string owner)
{
	this->owner = owner;
}

void echo::Echo::start() 
{
	started = true;
}

void echo::Echo::stop()
{
	started = false;
}
