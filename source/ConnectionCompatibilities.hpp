#pragma once
#ifndef _CONNECTION_COMPATIBILITIES_HPP_
#define _CONNECTION_COMPATIBILITIES_HPP_

#include <boost/serialization/unordered_set.hpp>
#include <boost/serialization/unordered_map.hpp>
#include "PseudofragmentDB.hpp"

// Declaration of the version integer of the ConnectionQueryResults class.
extern const unsigned connection_compatibilities_version;

// Definitions of STL containers of Connections. Provided for convenience.
typedef std::vector<Connection> CONNECTIONS_VECTOR;
typedef std::unordered_set<Connection> CONNECTIONS_SET;
typedef std::unordered_map<Connection, CONNECTIONS_SET> COMPATIBILITY_TABLE;

// Class to store which Connections are compatible with each other,
// according to a compatibility definition.
class ConnectionCompatibilities {
  // Associative container to store Connection-Connection compatibility
  // relationships.
  COMPATIBILITY_TABLE compatibility_table;
  // Integer symbolizing the compatibility definition.
  unsigned stringency = 0;

public:
  ConnectionCompatibilities();
  ConnectionCompatibilities(const PseudofragmentDB& database, unsigned stringency = 1);

  CONNECTIONS_SET& operator[](const Connection& connection);
  const CONNECTIONS_SET& at(const Connection& connection) const;

  bool AreCompatible(const Connection& connection1, const Connection& connection2) const;
  bool AreCompatible(const ConnectionsTable& connections_table, const Connection& connection) const;
  Connection GetRandomCompatibleConnection(const ConnectionsTable& connections_table, const Connection& connection, std::mt19937& prng) const;

  unsigned GetStringency() const;
  bool HasConnection(const Connection& connection) const;
  const COMPATIBILITY_TABLE& GetCompatibilityTable() const;
  void Print() const;

private:
  template <class Archive>
  void serialize(Archive& ar, const unsigned version = connection_compatibilities_version) {
    ar & compatibility_table & stringency;
  };

  friend class boost::serialization::access;
  friend class ConnectionsTable;
};

#endif
