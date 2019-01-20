// Auto-generated. Do not edit!

// (in-package link_com.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class heartbag {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.kpa = null;
      this.io = null;
    }
    else {
      if (initObj.hasOwnProperty('kpa')) {
        this.kpa = initObj.kpa
      }
      else {
        this.kpa = 0.0;
      }
      if (initObj.hasOwnProperty('io')) {
        this.io = initObj.io
      }
      else {
        this.io = new Array(7).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type heartbag
    // Serialize message field [kpa]
    bufferOffset = _serializer.float32(obj.kpa, buffer, bufferOffset);
    // Check that the constant length array field [io] has the right length
    if (obj.io.length !== 7) {
      throw new Error('Unable to serialize array field io - length must be 7')
    }
    // Serialize message field [io]
    bufferOffset = _arraySerializer.uint8(obj.io, buffer, bufferOffset, 7);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type heartbag
    let len;
    let data = new heartbag(null);
    // Deserialize message field [kpa]
    data.kpa = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [io]
    data.io = _arrayDeserializer.uint8(buffer, bufferOffset, 7)
    return data;
  }

  static getMessageSize(object) {
    return 11;
  }

  static datatype() {
    // Returns string type for a message object
    return 'link_com/heartbag';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '3975ec5bee3b3f6b04685f86ab5e40e0';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    #kpa 真空度(0 ~ -100kpa)
    #io[x] = 0 代表第x腿吸盘与真空泵连通，吸盘与放气端口之间阻塞; io[x] = 1 代表第x腿吸盘与放气端口连通，吸盘与真空泵之间阻塞
    
    float32 kpa
    uint8[7] io
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new heartbag(null);
    if (msg.kpa !== undefined) {
      resolved.kpa = msg.kpa;
    }
    else {
      resolved.kpa = 0.0
    }

    if (msg.io !== undefined) {
      resolved.io = msg.io;
    }
    else {
      resolved.io = new Array(7).fill(0)
    }

    return resolved;
    }
};

module.exports = heartbag;
