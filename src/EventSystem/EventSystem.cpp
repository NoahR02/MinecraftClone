#include "../precompiledheader.h"
#include "EventSystem.h"

int EventSystem::messageSubscribe(const std::string& name, const std::function<void(MessageData& messageData)>& function) {
  auto& collection = messages[name];
  collection.push_back(function);

  // Return the index.
  return function.target_type().hash_code();
}

void EventSystem::messageUnsubscribe(const std::string& name, const size_t functionPointer) {
  auto& collection = messages[name];
}

void EventSystem::messageUnsubscribeAll(const std::string& name) {
  messages.erase(name);
}

void EventSystem::messageEmitNow(const std::string& name, MessageData& messageData) {

  auto& collection = messages[name];

  for(const auto& lambda : collection) {
    lambda(messageData);
  }

  //std::cerr << "Key: " << name << " was not found." << std::endl;
}

void EventSystem::messagePushOnQueue(const std::string& name, MessageData& messageData) {
  messageQueue.push(QueueData{name, messageData});
}

void EventSystem::messageQueueExecuteAll() {

  for(int i = 0; i < messageQueue.size(); ++i) {

    auto& queueData = messageQueue.front();

    auto& collection = messages[queueData.name];
    for(const auto& lambda : collection) {
      lambda(queueData.messageData);
    }

    messageQueue.pop();

  }

}