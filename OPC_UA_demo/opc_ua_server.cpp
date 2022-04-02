#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>
#include <open62541/client_subscriptions.h>

#include <signal.h>
#include <stdlib.h>

static void stopHandler(int sig);
static void addVariable(UA_Server *server);
static void addMatrixVariable(UA_Server *server);
static void addMonitoredItemToCurrentTimeVariable(UA_Server *server);

static volatile UA_Boolean running = true;

int main(void)
{
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    //创建服务器
    UA_Server *server = UA_Server_new();

    //获取端口4840上的默认配置;
    UA_ServerConfig *config = UA_Server_getConfig(server);
    //在端口4840应用默认配置
    UA_ServerConfig_setDefault(config);

    // config->verifyRequestTimestamp = UA_RULEHANDLING_ACCEPT;
    // //添加变量;
    // addCurrentTimeVariable(server);
    // //添加读写变量时的回调函数
    // addValueCallbackToCurrentTimeVariable(server);
    // addCurrentTimeDataSourceVariable(server);
    // addCurrentTimeExternalDataSource(server);
    addVariable(server);
    addMatrixVariable(server);
    addMonitoredItemToCurrentTimeVariable(server);
    //运行服务器，进行事件循环， 当runing 为false时解除阻塞;
    UA_StatusCode retval = UA_Server_run(server, &running);
    //服务器下线
    UA_Server_delete(server);
    return retval = UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}

static void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "received ctrl-c");
    running = false;
}

/*向服务器添加变量*/
static void addVariable(UA_Server *server)
{
    //声明默认数据结构类型的变量；
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    UA_Int32 myInteger = 49;
    //将attr的值绑定到myInteger
    UA_Variant_setScalar(&attr.value, &myInteger, &UA_TYPES[UA_TYPES_INT32]);
    attr.description = UA_LOCALIZEDTEXT("en-US", "the answer");
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "the answer");
    attr.dataType = UA_TYPES[UA_TYPES_INT32].typeId;
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;

    /* Add the variable node to the information model */
    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "the.answer");
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "the answer");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId,
                              parentReferenceNodeId, myIntegerName,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), attr, NULL, NULL);
}

static void addMatrixVariable(UA_Server *server)
{
    //声明默认数据结构类型的变量；
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT("en-US", "Double Matrix");
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    /* Set the variable value constraints */
    attr.dataType = UA_TYPES[UA_TYPES_DOUBLE].typeId;
    //指定attr的值的排列行数
    attr.valueRank = UA_VALUERANK_TWO_DIMENSIONS;
    UA_UInt32 arrayDims[2] = {2, 2};
    //指定attr为两行两列
    attr.arrayDimensions = arrayDims;
    attr.arrayDimensionsSize = 2;

    /* Set the value. The array dimensions need to be the same for the value. */
    UA_Double zero[4] = {0.1, 0.2, 0.0, 0.0};
    //将attr的值绑定到myzero
    UA_Variant_setArray(&attr.value, zero, 4, &UA_TYPES[UA_TYPES_DOUBLE]);
    attr.value.arrayDimensions = arrayDims;
    attr.value.arrayDimensionsSize = 2;

    UA_NodeId myIntegerNodeId = UA_NODEID_STRING(1, "double.matrix");
    UA_QualifiedName myIntegerName = UA_QUALIFIEDNAME(1, "double matrix");
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_Server_addVariableNode(server, myIntegerNodeId, parentNodeId,
                              parentReferenceNodeId, myIntegerName,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE),
                              attr, NULL, NULL);
}

static void dataChangeNotificationCallback(UA_Server *server, UA_UInt32 monitoredItemId,
                                           void *monitoredItemContext, const UA_NodeId *nodeId,
                                           void *nodeContext, UA_UInt32 attributeId,
                                           const UA_DataValue *value)
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Received Notification");
}

/*添加变量监控，当变量改变时调用回调函数*/
static void addMonitoredItemToCurrentTimeVariable(UA_Server *server)
{
    //UA_NodeId currentTimeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER_SERVERSTATUS_CURRENTTIME);
    UA_NodeId currentTimeNodeId = UA_NODEID_STRING(1, "the.answer");
    UA_MonitoredItemCreateRequest monRequest = UA_MonitoredItemCreateRequest_default(currentTimeNodeId);
    monRequest.requestedParameters.samplingInterval = 1000.0; /* 100 ms interval */
    UA_Server_createDataChangeMonitoredItem(server, UA_TIMESTAMPSTORETURN_SOURCE,
                                            monRequest, NULL, dataChangeNotificationCallback);
}