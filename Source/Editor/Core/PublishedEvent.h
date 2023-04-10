#pragma once

#include "EditorEvent.h"
namespace psdf
{

class PublishedEvent
{
  public:
    using SharedPtr = std::shared_ptr<PublishedEvent>;

    virtual std::string getName() = 0;

    virtual ~PublishedEvent() = default;
};

class Editor;

class EditorPublishedEvent : public EditorEvent
{
  public:
    using SharedPtr = std::shared_ptr<EditorPublishedEvent>;

    PublishedEvent::SharedPtr getEvent() const;
    const void *getPublisher() const;

    std::string getName() const override;

  protected:
    static SharedPtr create(PublishedEvent::SharedPtr pPublishedEvent, const void *pPublisher);

    EditorPublishedEvent(PublishedEvent::SharedPtr pPublishedEvent, const void *pPublisher);

  private:
    PublishedEvent::SharedPtr mpPublishedEvent;
    const void *mpPublisher;

    friend Editor;
};

} // namespace psdf
