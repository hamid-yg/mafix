#pragma once

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <map>
#include <sstream>
#include <numeric>

#include "Order.hpp"
#include "OrderBook.hpp"
#include "Market.hpp"
#include "Protocols/FixMessage.hpp"
#include "Protocols/Logon.hpp"
#include "Protocols/ExecutionReport.hpp"
#include "Protocols/OrderCancelRequest.hpp"
#include "Protocols/OrderCancelReplaceRequest.hpp"
#include "Protocols/MarketDataIncrementalRefresh.hpp"
#include "Protocols/MarketDataSnapshotFullRefresh.hpp"
#include "Protocols/NewOrder.hpp"
