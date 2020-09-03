#include "MemcachedCluster.hpp"
#include "Retry.hpp"

const memcached_st MemcachedCluster::empty_memc{};

void MemcachedCluster::init() {
  REQUIRE(cluster.start());

  REQUIRE(memcached_create(&memc));
  for (const auto &server : cluster.getServers()) {
    auto target = server.getSocketOrPort();
    if (holds_alternative<string>(target)) {
      REQUIRE(MEMCACHED_SUCCESS == memcached_server_add_unix_socket(&memc, get<string>(target).c_str()));
    } else {
      REQUIRE(MEMCACHED_SUCCESS == memcached_server_add(&memc, "localhost", get<int>(target)));
    }
  }

  Retry cluster_is_listening([this]() {
    return cluster.isListening();
  });
  REQUIRE(cluster_is_listening());
}

MemcachedCluster::~MemcachedCluster() {
  if (memcmp(&memc, &empty_memc, sizeof(memc))) {
    memcached_free(&memc);
  }
}

void MemcachedCluster::flush() {
  REQUIRE(MEMCACHED_SUCCESS == memcached_flush(&memc, 0));
}

MemcachedCluster::MemcachedCluster()
: cluster{Server{
  getenv_else("MEMCACHED_BINARY", "memcached"),
  {random_socket_or_port_arg()}
}}
{
  init();
}

MemcachedCluster::MemcachedCluster(Cluster &&cluster_)
: cluster{forward<Cluster>(cluster_)}
{
  init();
}

MemcachedCluster MemcachedCluster::mixed() {
  return MemcachedCluster{};
}

MemcachedCluster MemcachedCluster::network() {
  return MemcachedCluster{Cluster{Server{
    getenv_else("MEMCACHED_BINARY", "memcached"),
    {"-p", random_socket_or_port_string}
  }}};
}

MemcachedCluster MemcachedCluster::socket() {
  return MemcachedCluster{Cluster{Server{
    getenv_else("MEMCACHED_BINARY", "memcached"),
    {"-s", random_socket_or_port_string}
  }}};
}

void MemcachedCluster::enableBinaryProto(bool enable) {
  REQUIRE(MEMCACHED_SUCCESS == memcached_behavior_set(&memc,
      MEMCACHED_BEHAVIOR_BINARY_PROTOCOL, enable));
}
