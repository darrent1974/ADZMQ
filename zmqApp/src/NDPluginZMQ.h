#ifndef NDPluginZMQ_H
#define NDPluginZMQ_H

#include "NDPluginDriver.h"

/* ZMQ general parameters */
#define NDPluginZMQTopicIDString               "TOPIC_ID"                /* (asynOctet,   r/w) Bluesky ZMQ Topic ID string */

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 255
#endif

/** Base class for NDArray ZMQ streaming plugins. */
class NDPluginZMQ : public NDPluginDriver {
public:
    NDPluginZMQ(const char *portName, const char *serverHost, int queueSize, int blockingCallbacks,
                 const char *NDArrayPort, int NDArrayAddr,
                 int maxBuffers, size_t maxMemory,
                 int priority, int stackSize);

    ~NDPluginZMQ();

    /* These methods override those in the base class */
    virtual void processCallbacks(NDArray *pArray);

protected:
    /* ZMQ general parameters */
    int NDPluginZMQTopicID;

    std::string getAttributesAsJSON(NDAttributeList *pAttributeList);
    bool sendNDArray(NDArray *pArray);

private:
    void *context;
    void *socket;
    char serverHost[HOST_NAME_MAX];
    int socketType;
};

#define NUM_NDPLUGIN_ZMQ_PARAMS 0

#endif
