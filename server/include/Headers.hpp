#pragma once

#include <string>
#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/event.h>
#include <thread>

#include "../../common/Headers.hpp"
#include "../../common/Protocols/FixMessage.hpp"
#include "../../common/Protocols/Logon.hpp"
#include "../../common/Protocols/ExecutionReport.hpp"
#include "../../common/Protocols/OrderCancelRequest.hpp"
#include "../../common/Protocols/OrderCancelReplaceRequest.hpp"
#include "../../common/Protocols/MarketDataIncrementalRefresh.hpp"
#include "../../common/Protocols/MarketDataSnapshotFullRefresh.hpp"
#include "../../common/Protocols/NewOrder.hpp"

#include "FixServer.hpp"
#include "Networks/Socket.hpp"
#include "Networks/UDPSocket.hpp"
#include "Networks/TCPSocket.hpp"
#include "Networks/EventHandler.hpp"
#include "Networks/EventMultiplexer.hpp"
