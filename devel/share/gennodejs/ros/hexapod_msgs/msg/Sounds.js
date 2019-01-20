// Auto-generated. Do not edit!

// (in-package hexapod_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Sounds {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.torque = null;
      this.battery = null;
      this.auto_level = null;
      this.stand = null;
      this.waiting = null;
      this.shut_down = null;
    }
    else {
      if (initObj.hasOwnProperty('torque')) {
        this.torque = initObj.torque
      }
      else {
        this.torque = false;
      }
      if (initObj.hasOwnProperty('battery')) {
        this.battery = initObj.battery
      }
      else {
        this.battery = false;
      }
      if (initObj.hasOwnProperty('auto_level')) {
        this.auto_level = initObj.auto_level
      }
      else {
        this.auto_level = false;
      }
      if (initObj.hasOwnProperty('stand')) {
        this.stand = initObj.stand
      }
      else {
        this.stand = false;
      }
      if (initObj.hasOwnProperty('waiting')) {
        this.waiting = initObj.waiting
      }
      else {
        this.waiting = false;
      }
      if (initObj.hasOwnProperty('shut_down')) {
        this.shut_down = initObj.shut_down
      }
      else {
        this.shut_down = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Sounds
    // Serialize message field [torque]
    bufferOffset = _serializer.bool(obj.torque, buffer, bufferOffset);
    // Serialize message field [battery]
    bufferOffset = _serializer.bool(obj.battery, buffer, bufferOffset);
    // Serialize message field [auto_level]
    bufferOffset = _serializer.bool(obj.auto_level, buffer, bufferOffset);
    // Serialize message field [stand]
    bufferOffset = _serializer.bool(obj.stand, buffer, bufferOffset);
    // Serialize message field [waiting]
    bufferOffset = _serializer.bool(obj.waiting, buffer, bufferOffset);
    // Serialize message field [shut_down]
    bufferOffset = _serializer.bool(obj.shut_down, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Sounds
    let len;
    let data = new Sounds(null);
    // Deserialize message field [torque]
    data.torque = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [battery]
    data.battery = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [auto_level]
    data.auto_level = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [stand]
    data.stand = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [waiting]
    data.waiting = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [shut_down]
    data.shut_down = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 6;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hexapod_msgs/Sounds';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9e277e5433232e212c4281205788a826';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool torque
    bool battery
    bool auto_level
    bool stand
    bool waiting
    bool shut_down
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Sounds(null);
    if (msg.torque !== undefined) {
      resolved.torque = msg.torque;
    }
    else {
      resolved.torque = false
    }

    if (msg.battery !== undefined) {
      resolved.battery = msg.battery;
    }
    else {
      resolved.battery = false
    }

    if (msg.auto_level !== undefined) {
      resolved.auto_level = msg.auto_level;
    }
    else {
      resolved.auto_level = false
    }

    if (msg.stand !== undefined) {
      resolved.stand = msg.stand;
    }
    else {
      resolved.stand = false
    }

    if (msg.waiting !== undefined) {
      resolved.waiting = msg.waiting;
    }
    else {
      resolved.waiting = false
    }

    if (msg.shut_down !== undefined) {
      resolved.shut_down = msg.shut_down;
    }
    else {
      resolved.shut_down = false
    }

    return resolved;
    }
};

module.exports = Sounds;
