// Auto-generated. Do not edit!

// (in-package hexapodservice.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class legjoints {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.coxa = null;
      this.femur = null;
      this.tibia = null;
      this.tarsus = null;
    }
    else {
      if (initObj.hasOwnProperty('coxa')) {
        this.coxa = initObj.coxa
      }
      else {
        this.coxa = [];
      }
      if (initObj.hasOwnProperty('femur')) {
        this.femur = initObj.femur
      }
      else {
        this.femur = [];
      }
      if (initObj.hasOwnProperty('tibia')) {
        this.tibia = initObj.tibia
      }
      else {
        this.tibia = [];
      }
      if (initObj.hasOwnProperty('tarsus')) {
        this.tarsus = initObj.tarsus
      }
      else {
        this.tarsus = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type legjoints
    // Serialize message field [coxa]
    bufferOffset = _arraySerializer.int64(obj.coxa, buffer, bufferOffset, null);
    // Serialize message field [femur]
    bufferOffset = _arraySerializer.int64(obj.femur, buffer, bufferOffset, null);
    // Serialize message field [tibia]
    bufferOffset = _arraySerializer.int64(obj.tibia, buffer, bufferOffset, null);
    // Serialize message field [tarsus]
    bufferOffset = _arraySerializer.int64(obj.tarsus, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type legjoints
    let len;
    let data = new legjoints(null);
    // Deserialize message field [coxa]
    data.coxa = _arrayDeserializer.int64(buffer, bufferOffset, null)
    // Deserialize message field [femur]
    data.femur = _arrayDeserializer.int64(buffer, bufferOffset, null)
    // Deserialize message field [tibia]
    data.tibia = _arrayDeserializer.int64(buffer, bufferOffset, null)
    // Deserialize message field [tarsus]
    data.tarsus = _arrayDeserializer.int64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.coxa.length;
    length += 8 * object.femur.length;
    length += 8 * object.tibia.length;
    length += 8 * object.tarsus.length;
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'hexapodservice/legjoints';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '30491f146cc62d519f29e03cbd6340f7';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
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
    const resolved = new legjoints(null);
    if (msg.coxa !== undefined) {
      resolved.coxa = msg.coxa;
    }
    else {
      resolved.coxa = []
    }

    if (msg.femur !== undefined) {
      resolved.femur = msg.femur;
    }
    else {
      resolved.femur = []
    }

    if (msg.tibia !== undefined) {
      resolved.tibia = msg.tibia;
    }
    else {
      resolved.tibia = []
    }

    if (msg.tarsus !== undefined) {
      resolved.tarsus = msg.tarsus;
    }
    else {
      resolved.tarsus = []
    }

    return resolved;
    }
};

module.exports = legjoints;
