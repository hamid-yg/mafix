#pragma once

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#include "../../common/Headers.hpp"
#include "../../common/Protocols/FixMessage.hpp"
#include "../../common/Protocols/Logon.hpp"
#include "../../common/Protocols/ExecutionReport.hpp"
#include "../../common/Protocols/OrderCancelRequest.hpp"
#include "../../common/Protocols/OrderCancelReplaceRequest.hpp"
#include "../../common/Protocols/MarketDataIncrementalRefresh.hpp"
#include "../../common/Protocols/MarketDataSnapshotFullRefresh.hpp"
#include "../../common/Protocols/NewOrder.hpp"

#include "TradingClient.hpp"
