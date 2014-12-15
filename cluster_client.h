/*
 * Copyright (c) 2008-2014, Chen Huaying <chying.ren@gmail.com>
 * All Rights Reserved.
 *
 * redis cluster client, wrapper of Cluster_Redis
 */

#ifndef CLUSTER_CLIENT_H_
#define CLUSTER_CLIENT_H_

#include <vector>
#include "Cluster_Redis.h"

#define CLUSTER_ERR -1
#define CLUSTER_OK   0

using std::pair;

class ClusterClient {

    public:
        explicit ClusterClient() {};
        ~ClusterClient() {};
        int32_t Init(const char *redis_master_ips);
        int32_t Uninit();
        void show_clients();
        RetInfo *String_Set(const char *key,
                const char *value,
                int32_t expiration);
        RetInfo *String_Get(const char *key, string &value);

    private:
        map<string, ClusterRedis *> clients;
        std::vector<pair<string,int> > cluster_masters;

        // ip_list format: <ip:port>;<ip:port>;...
        // 192.168.0.1:6379;192.168.0.2:6379;...
        void ip_list_unserailize(const char *ip_list);
        // ip_addr format: <ip:port>
        // 192.168.0.1:6379
        int32_t add_new_client(const char *ip_addr);
        ClusterClient(const ClusterClient&);
        ClusterClient& operator=(const ClusterClient&);
};



#endif  /*CLUSTER_CLIENT_H_*/
