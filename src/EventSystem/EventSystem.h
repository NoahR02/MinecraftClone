#ifndef MINECRAFTCLONE_EVENTSYSTEM_H
#define MINECRAFTCLONE_EVENTSYSTEM_H

#include <unordered_map>
#include <functional>
#include <string>
#include <queue>

struct EventSystem {

  union MessageData {

    int64_t i64[2];
    char c128[128];
    int8_t i128[128];
    double d64[2];

    int32_t i32[4];
    float f32[4];

    int16_t i16[8];

    bool b1[128];

  };

  std::unordered_map<std::string, std::vector<std::function<void(MessageData&)>>> messages;

  struct QueueData {
    std::string name;
    MessageData messageData;
  };

  std::queue<QueueData> messageQueue;

  int messageSubscribe(const std::string& name, const std::function<void(MessageData& messageData)>& function);

  void messageUnsubscribe(const std::string& name, const size_t functionPointer);
  void messageUnsubscribeAll(const std::string& name);

  void messageEmitNow(const std::string& name, MessageData& messageData);

  void messagePushOnQueue(const std::string& name, MessageData& messageData);
  void messageQueueExecuteAll();

};


#endif
