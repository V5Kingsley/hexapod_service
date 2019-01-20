// Auto-generated. Do not edit!

// (in-package hexapodservice.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let legjoints = require('./legjoints.js');

//-----------------------------------------------------------

class legs {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.leg = null;
    }
    else {
      if (initObj.hasOwnProperty('leg')) {
        this.leg = initObj.leg
      }
      else {
        this.leg = new Array(6).fill(new legjoints());
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type legs
    // Check that the constant length array field [leg] has the right length
    if (obj.leg.length !== 6) {
      throw new Error('Unable to serialize array field leg - length must be 6')
    }
    // Serialize message field [leg]
    obj.leg.forEach((val) => {
      bufferOffset = legjoints.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type legs
    let len;
    let data = new legs(null);
    // Deserialize message field [leg]
    len = 6;
    data.leg = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.leg[i] = legjoints.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.leg.forEach((val) => {
      length += legjoints.getMessageSize(val);
    });
    return length;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hexapodservice/legs';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '283042c2b49d709689847698830e74a9';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    hexapodservice/legjoints[6] leg
    
    ================================================================================
    MSG: hexapodservice/legjoints
    int64[] coxa
    int64[] femur
    int64[] tibia
    int64[] tarsus
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new legs(null);
    if (msg.leg !== undefined) {
      resolved.leg = new Array(6)
      for (let i = 0; i < resolved.leg.length; ++i) {
        if (msg.leg.length > i) {
          resolved.leg[i] = legjoints.Resolve(msg.leg[i]);
        }
        else {
          resolved.leg[i] = new legjoints();
        }
      }
    }
    else {
      resolved.leg = new Array(6).fill(new legjoints())
    }

    return resolved;
    }
};

module.exports = legs;
