#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/client_subscriptions.h>

#include <stdlib.h>
#include <iostream>

void writeInteger(UA_Client *client, char *id);
void readMatrix(UA_Client *client, char *id);
void writePumpData(UA_Client *client, char *id);
void listTreeRecursive(UA_Client *client, UA_NodeId nodeId);

int main(void)
{
    UA_Client *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    UA_StatusCode retVal = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if (retVal != UA_STATUSCODE_GOOD)
    {
        std::cout << "连接服务器失败,请检查网络连接" << std::endl;
        UA_Client_delete(client);
        return (int)retVal;
    }
    char id_integer[] = "the.answer";
    char id_matrix[] = "double.matrix";
    readMatrix(client, id_matrix);
    // for (int i = 0; i < 10; i++)
    // {
    //     writeInteger(client, id_integer);
    //     sleep(1);
    // }
    printf("%-9s %-16s %-16s %-16s\n", "NAMESPACE", "NODEID", "BROWSE NAME", "DISPLAY NAME");
    UA_NodeId pumpTypeId = {1, UA_NODEIDTYPE_NUMERIC, {1001}};
    listTreeRecursive(client, UA_NODEID_STRING(1, "PLC"));

    //UA_Client_run_iterate(client, 10000);
    UA_Client_delete(client);
    return EXIT_SUCCESS;
}

void readMatrix(UA_Client *client, char *id)
{
    UA_Variant value;
    //将value的值置为0；
    UA_Variant_init(&value);
    const UA_NodeId node_id = UA_NODEID_STRING(1, id);
    if (UA_Client_readValueAttribute(client, node_id, &value) == UA_STATUSCODE_GOOD)
    {
        UA_Double *data = (UA_Double *)value.data;
        size_t len = value.arrayLength;
        std::cout << "the matrix data is: \033[32m: ";
        for (size_t i = 0; i < len; i++)
        {
            std::cout << *(data + i) << " ";
        }
        std::cout << std::endl;
    }

    UA_Variant_clear(&value);
}

void writeInteger(UA_Client *client, char *id)
{
    UA_Variant value;
    //将value的值置为0；
    UA_Variant_init(&value);
    UA_NodeId node_id = UA_NODEID_STRING(1, id);
    //读取节点的值
    if (UA_Client_readValueAttribute(client, node_id, &value) == UA_STATUSCODE_GOOD)
    {
        UA_Int32 data = *(UA_Int32 *)value.data;
        std::cout << node_id.identifier.numeric << " the data is: \033[32m" << data << std::endl;
        //向节点写入新数据
        UA_Int32 integer = data + 1;
        UA_Variant new_var;
        UA_Variant_init(&new_var);
        UA_Variant_setScalar(&new_var, &integer, &UA_TYPES[UA_TYPES_INT32]);
        UA_Client_writeValueAttribute(client, node_id, &new_var);
    }
    else
    {
        std::cout << "\033[32m没有读取到数据" << std::endl;
    }
}

void writePumpData(UA_Client *client, char *id)
{

    // UA_RelativePathElement rpe;
    // UA_RelativePathElement_init(&rpe);
    // rpe.referenceTypeId = UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT);
    // rpe.isInverse = false;
    // rpe.includeSubtypes = false;
    // rpe.targetName = UA_QUALIFIEDNAME(1, "Status");

    // UA_BrowsePath bp;
    // UA_BrowsePath_init(&bp);
    // bp.startingNode = *nodeId;
    // bp.relativePath.elementsSize = 1;
    // bp.relativePath.elements = &rpe;

    // UA_TranslateBrowsePathsToNodeIdsResponse response = UA_Client_Service_translateBrowsePathsToNodeIds(client, );
    // UA_BrowsePathResult bpr = response.results;

    // UA_BrowsePathResult bpr = UA_Server_translateBrowsePathToNodeIds(server, &bp);
    // if (bpr.statusCode != UA_STATUSCODE_GOOD || bpr.targetsSize < 1)
    // {
    //     return bpr.statusCode;
    // }

    // /* Set the status value */
    // UA_Boolean status = true;
    // UA_Variant value;
    // UA_Variant_setScalar(&value, &status, &UA_TYPES[UA_TYPES_BOOLEAN]);
    // // UA_Server_writeValue(server, bpr.targets[0].targetId.nodeId, value);
    // UA_Client_writeValueAttribute(client, bpr.targets[0].targetId.nodeId, &value);
    // UA_BrowsePathResult_clear(&bpr);
}

void listTreeRecursive(UA_Client *client, UA_NodeId nodeId)
{
    size_t i, j;

    /* 初始化查询请求 */
    UA_BrowseRequest bReq;
    UA_BrowseRequest_init(&bReq);
    bReq.requestedMaxReferencesPerNode = 0;
    bReq.nodesToBrowse = UA_BrowseDescription_new();    //给查询描述分配内存
    bReq.nodesToBrowseSize = 1;           //查询节点数量

    //保存根结点，并设置查询节点不进行筛选
    UA_NodeId_copy(&nodeId, &bReq.nodesToBrowse[0].nodeId);
    bReq.nodesToBrowse[0].resultMask = UA_BROWSERESULTMASK_ALL; /* return everything */

    //客户端查询请求，并将结果保存到回应bResp中
    UA_BrowseResponse bResp = UA_Client_Service_browse(client, bReq);

    /***********************************************************************/
    //初始化迭代查询请求
    // UA_BrowseNextRequest bNextReq;
    // UA_BrowseNextRequest_init(&bNextReq);
    // // normally is set to 0, to get all the nodes, but we want to test browse next
    // bNextReq.releaseContinuationPoints = UA_FALSE;
    // bNextReq.continuationPoints = &bResp.results[0].continuationPoint;
    // bNextReq.continuationPointsSize = 1;
    // UA_BrowseNextResponse bNextResp = UA_Client_Service_browseNext(client, bNextReq);

    std::cout << "size: " << bResp.resultsSize << std::endl;
    //遍历每个节点
    for (i = 0; i < bResp.resultsSize; i++)
    {
        //遍历每个节点中的引用
        for (j = 0; j < bResp.results[i].referencesSize; j++)
        {
            UA_ReferenceDescription *ref = &(bResp.results[i].references[j]);
            if ((ref->nodeClass == UA_NODECLASS_OBJECT || ref->nodeClass == UA_NODECLASS_VARIABLE || ref->nodeClass == UA_NODECLASS_METHOD))
            {

                if (ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_NUMERIC)
                {
                    printf("%-9d %-16d %-16.*s %-16.*s\n", ref->nodeId.nodeId.namespaceIndex,
                           ref->nodeId.nodeId.identifier.numeric, (int)ref->browseName.name.length,
                           ref->browseName.name.data, (int)ref->displayName.text.length,
                           ref->displayName.text.data);

                    listTreeRecursive(client, UA_NODEID_NUMERIC(ref->nodeId.nodeId.namespaceIndex,
                                                                ref->nodeId.nodeId.identifier.numeric));
                }
                else if (ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_STRING)
                {
                    printf("%-9d %-16.*s %-16.*s %-16.*s\n", ref->nodeId.nodeId.namespaceIndex,
                           (int)ref->nodeId.nodeId.identifier.string.length,
                           ref->nodeId.nodeId.identifier.string.data,
                           (int)ref->browseName.name.length, ref->browseName.name.data,
                           (int)ref->displayName.text.length, ref->displayName.text.data);

                    listTreeRecursive(client, UA_NODEID_STRING(ref->nodeId.nodeId.namespaceIndex,
                                                               (char *)ref->nodeId.nodeId.identifier.string.data));
                }
            }
            /* TODO: distinguish further types */
        }
    }

    // for (i = 0; i < bNextResp.resultsSize; i++)
    // {
    //     for (j = 0; j < bNextResp.results[i].referencesSize; j++)
    //     {
    //         UA_ReferenceDescription *ref = &(bNextResp.results[i].references[j]);
    //         if ((ref->nodeClass == UA_NODECLASS_OBJECT || ref->nodeClass == UA_NODECLASS_VARIABLE || ref->nodeClass == UA_NODECLASS_METHOD))
    //         {

    //             if (ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_NUMERIC)
    //             {
    //                 printf("%-9d %-16d %-16.*s %-16.*s\n", ref->nodeId.nodeId.namespaceIndex,
    //                        ref->nodeId.nodeId.identifier.numeric, (int)ref->browseName.name.length,
    //                        ref->browseName.name.data, (int)ref->displayName.text.length,
    //                        ref->displayName.text.data);

    //                 listTreeRecursive(client, UA_NODEID_NUMERIC(ref->nodeId.nodeId.namespaceIndex,
    //                                                             ref->nodeId.nodeId.identifier.numeric));
    //             }
    //             else if (ref->nodeId.nodeId.identifierType == UA_NODEIDTYPE_STRING)
    //             {
    //                 printf("%-9d %-16.*s %-16.*s %-16.*s\n", ref->nodeId.nodeId.namespaceIndex,
    //                        (int)ref->nodeId.nodeId.identifier.string.length,
    //                        ref->nodeId.nodeId.identifier.string.data,
    //                        (int)ref->browseName.name.length, ref->browseName.name.data,
    //                        (int)ref->displayName.text.length, ref->displayName.text.data);

    //                 listTreeRecursive(client, UA_NODEID_STRING(ref->nodeId.nodeId.namespaceIndex,
    //                                                            (char *)ref->nodeId.nodeId.identifier.string.data));
    //             }
    //         }
    //         /* TODO: distinguish further types */
    //     }
    // }
    UA_BrowseRequest_deleteMembers(&bReq);
   // UA_BrowseResponse_deleteMembers(&bResp);
}