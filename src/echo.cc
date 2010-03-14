#include <stdexcept>

#include <echo/echo.h>
#include <echo/engine/engine.h>

namespace echo {

const std::string Echo::UNABLE_TO_START("Unable to start the Echo");

Echo::Echo()
{
  // call Echo with NULL context
}

Echo::Echo(echo::Context context)
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


echo::Application Echo::getApplication() {
  return echo::Application::getCurrent();
}

std::string Echo::getAuthor() {
  return author;
}

echo::Context Echo::getContext(){
  return context;
}

std::string Echo::getDescription()
{
  return description;
}

echo::util::logging::Logger Echo::getLogger()
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

std::string Echo::getName()
{
  return name;
}

std::string Echo::getOwner()
{
  return owner;
}

void Echo::handle(echo::Request request,
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

bool Echo::isStarted()
{
  return started;
}

bool Echo::isStopped()
{
  return !started;
}

void Echo::setAuthor(std::string author)
{
  this->author = author;
}

void Echo::setContext(echo::Context context)
{
  this->context = context;
  // echo.engine.component.ChildContext.fireContextChanged(this, context);
}

void Echo::setDescription(std::string description)
{
  this->description = description;
}

void Echo::setName(std::string name)
{
  this->name = name;
}

void Echo::setOwner(std::string owner)
{
  this->owner = owner;
}

void Echo::start() 
{
  started = true;
}

void Echo::stop()
{
  started = false;
}

} // namespace echo
