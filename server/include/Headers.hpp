#pragma once

#include <string>
#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/event.h>
#include <thread>

#include "../../common/Headers.hpp"
#include "FixServer.hpp"

#include "Protocols/FixMessage.hpp"
#include "Protocols/Logon.hpp"
#include "Protocols/ExecutionReport.hpp"
#include "Protocols/OrderCancelRequest.hpp"
#include "Protocols/OrderCancelReplaceRequest.hpp"
#include "Protocols/MarketDataIncrementalRefresh.hpp"
#include "Protocols/MarketDataSnapshotFullRefresh.hpp"
#include "Protocols/NewOrder.hpp"

#include "Networks/Socket.hpp"
#include "Networks/UDPSocket.hpp"
#include "Networks/TCPSocket.hpp"
#include "Networks/EventHandler.hpp"
#include "Networks/EventMultiplexer.hpp"
