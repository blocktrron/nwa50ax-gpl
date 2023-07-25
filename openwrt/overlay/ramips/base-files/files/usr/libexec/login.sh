#!/bin/sh

[ "$(uci get system.@system[0].ttylogin)" == 1 ] || exec /bin/sh --login

exec /bin/login
