// Auto-generated. Do not edit!

// (in-package link_com.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class hexcomRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.chose = null;
      this.pwm = null;
      this.io = null;
    }
    else {
      if (initObj.hasOwnProperty('chose')) {
        this.chose = initObj.chose
      }
      else {
        this.chose = 0;
      }
      if (initObj.hasOwnProperty('pwm')) {
        this.pwm = initObj.pwm
      }
      else {
        this.pwm = 0;
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
    // Serializes a message object of type hexcomRequest
    // Serialize message field [chose]
    bufferOffset = _serializer.uint8(obj.chose, buffer, bufferOffset);
    // Serialize message field [pwm]
    bufferOffset = _serializer.uint8(obj.pwm, buffer, bufferOffset);
    // Check that the constant length array field [io] has the right length
    if (obj.io.length !== 7) {
      throw new Error('Unable to serialize array field io - length must be 7')
    }
    // Serialize message field [io]
    bufferOffset = _arraySerializer.uint8(obj.io, buffer, bufferOffset, 7);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type hexcomRequest
    let len;
    let data = new hexcomRequest(null);
    // Deserialize message field [chose]
    data.chose = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [pwm]
    data.pwm = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [io]
    data.io = _arrayDeserializer.uint8(buffer, bufferOffset, 7)
    return data;
  }

  static getMessageSize(object) {
    return 9;
  }

  static datatype() {
    // Returns string type for a service object
    return 'link_com/hexcomRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'b691a199974dd65355429c066120d3b8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    
    
    uint8 chose
    uint8 pwm
    uint8[7] io
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new hexcomRequest(null);
    if (msg.chose !== undefined) {
      resolved.chose = msg.chose;
    }
    else {
      resolved.chose = 0
    }

    if (msg.pwm !== undefined) {
      resolved.pwm = msg.pwm;
    }
    else {
      resolved.pwm = 0
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

class hexcomResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.back = null;
    }
    else {
      if (initObj.hasOwnProperty('back')) {
        this.back = initObj.back
      }
      else {
        this.back = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type hexcomResponse
    // Serialize message field [back]
    bufferOffset = _serializer.string(obj.back, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type hexcomResponse
    let len;
    let data = new hexcomResponse(null);
    // Deserialize message field [back]
    data.back = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.back.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'link_com/hexcomResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c4a1d3ec3f5c241f65fed707d363d25e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string back
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new hexcomResponse(null);
    if (msg.back !== undefined) {
      resolved.back = msg.back;
    }
    else {
      resolved.back = ''
    }

    return resolved;
    }
};

module.exports = {
  Request: hexcomRequest,
  Response: hexcomResponse,
  md5sum() { return '4c6bf6a56b94d0854641b3cbd40fb9db'; },
  datatype() { return 'link_com/hexcom'; }
};
