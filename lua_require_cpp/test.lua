--
-- Created by IntelliJ IDEA.
-- User: zhenkai
-- Date: 2020/4/28
-- Time: 15:53
-- To change this template use File | Settings | File Templates.
--

-- /usr/local/openresty/luajit/bin/luajit test.lua

local motanlient = require("motan")

local str = motanlient.client_init();
print(str)

str = motanlient.caller_init();
print(str)

str = motanlient.caller_add();
print(str)

str = motanlient.caller_do();
print(str)

