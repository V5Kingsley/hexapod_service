// Auto-generated. Do not edit!

// (in-package hexapodservice.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let legjoint = require('./legjoint.js');

//-----------------------------------------------------------

class leg {
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
        this.leg = new Array(6).fill(new legjoint());
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type leg
    // Check that the constant length array field [leg] has the right length
    if (obj.leg.length !== 6) {
      throw new Error('Unable to serialize array field leg - length must be 6')
    }
    // Serialize message field [leg]
    obj.leg.forEach((val) => {
      bufferOffset = legjoint.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type leg
    let len;
    let data = new leg(null);
    // Deserialize message field [leg]
    len = 6;
    data.leg = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.leg[i] = legjoint.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    return 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hexapodservice/leg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '77281f1f9c4cd29d21908d690db99185';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    hexapodservice/legjoint[6] leg
    
    ================================================================================
    MSG: hexapodservice/legjoint
    float64 coxa
    float64 femur
    float64 tibia
    float64 tarsus
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new leg(null);
    if (msg.leg !== undefined) {
      resolved.leg = new Array(6)
      for (let i = 0; i < resolved.leg.length; ++i) {
        if (msg.leg.length > i) {
          resolved.leg[i] = legjoint.Resolve(msg.leg[i]);
        }
        else {
          resolved.leg[i] = new legjoint();
        }
      }
    }
    else {
      resolved.leg = new Array(6).fill(new legjoint())
    }

    return resolved;
    }
};

module.exports = leg;
