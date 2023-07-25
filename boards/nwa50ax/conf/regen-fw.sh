#!/bin/sh

# Replace firmware id to /rw/fwversion
FW_ID=$(/usr/bin/zykit_info -f)
sed -i "s/###/$FW_ID/g" /rw/fwversion

# Replace model id to /rw/fwversion from model_info.h
MODEL_ID=$(/usr/bin/zykit_info -P)
sed -i "s/MODEL_ID=.*/MODEL_ID=${MODEL_ID}/g" /rw/fwversion
