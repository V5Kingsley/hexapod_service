# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from hexapodservice/hexapodserviceAction.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import std_msgs.msg
import genpy
import actionlib_msgs.msg
import hexapodservice.msg

class hexapodserviceAction(genpy.Message):
  _md5sum = "253731c42181dfd32504f6a64aacfded"
  _type = "hexapodservice/hexapodserviceAction"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

hexapodserviceActionGoal action_goal
hexapodserviceActionResult action_result
hexapodserviceActionFeedback action_feedback

================================================================================
MSG: hexapodservice/hexapodserviceActionGoal
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalID goal_id
hexapodserviceGoal goal

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: actionlib_msgs/GoalID
# The stamp should store the time at which this goal was requested.
# It is used by an action server when it tries to preempt all
# goals that were requested before a certain time
time stamp

# The id provides a way to associate feedback and
# result message with specific goal requests. The id
# specified must be unique.
string id


================================================================================
MSG: hexapodservice/hexapodserviceGoal
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
int32 MODE 
int32 SIMPLEMOTION_MODE
int32 MAXPOINTS
int32 LEG_INDEX
hexapodservice/legjoints ONELEG
hexapodservice/legs ALLLEGS

================================================================================
MSG: hexapodservice/legjoints
int64[] coxa
int64[] femur
int64[] tibia
int64[] tarsus

================================================================================
MSG: hexapodservice/legs
hexapodservice/legjoints[6] leg

================================================================================
MSG: hexapodservice/hexapodserviceActionResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
hexapodserviceResult result

================================================================================
MSG: actionlib_msgs/GoalStatus
GoalID goal_id
uint8 status
uint8 PENDING         = 0   # The goal has yet to be processed by the action server
uint8 ACTIVE          = 1   # The goal is currently being processed by the action server
uint8 PREEMPTED       = 2   # The goal received a cancel request after it started executing
                            #   and has since completed its execution (Terminal State)
uint8 SUCCEEDED       = 3   # The goal was achieved successfully by the action server (Terminal State)
uint8 ABORTED         = 4   # The goal was aborted during execution by the action server due
                            #    to some failure (Terminal State)
uint8 REJECTED        = 5   # The goal was rejected by the action server without being processed,
                            #    because the goal was unattainable or invalid (Terminal State)
uint8 PREEMPTING      = 6   # The goal received a cancel request after it started executing
                            #    and has not yet completed execution
uint8 RECALLING       = 7   # The goal received a cancel request before it started executing,
                            #    but the action server has not yet confirmed that the goal is canceled
uint8 RECALLED        = 8   # The goal received a cancel request before it started executing
                            #    and was successfully cancelled (Terminal State)
uint8 LOST            = 9   # An action client can determine that a goal is LOST. This should not be
                            #    sent over the wire by an action server

#Allow for the user to associate a string with GoalStatus for debugging
string text


================================================================================
MSG: hexapodservice/hexapodserviceResult
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
int32 status
int32 freespace
bool motionActive
string result

================================================================================
MSG: hexapodservice/hexapodserviceActionFeedback
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======

Header header
actionlib_msgs/GoalStatus status
hexapodserviceFeedback feedback

================================================================================
MSG: hexapodservice/hexapodserviceFeedback
# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
hexapodservice/leg ALLLEGS_fdbk


================================================================================
MSG: hexapodservice/leg
hexapodservice/legjoint[6] leg

================================================================================
MSG: hexapodservice/legjoint
float64 coxa
float64 femur
float64 tibia
float64 tarsus
"""
  __slots__ = ['action_goal','action_result','action_feedback']
  _slot_types = ['hexapodservice/hexapodserviceActionGoal','hexapodservice/hexapodserviceActionResult','hexapodservice/hexapodserviceActionFeedback']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       action_goal,action_result,action_feedback

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(hexapodserviceAction, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.action_goal is None:
        self.action_goal = hexapodservice.msg.hexapodserviceActionGoal()
      if self.action_result is None:
        self.action_result = hexapodservice.msg.hexapodserviceActionResult()
      if self.action_feedback is None:
        self.action_feedback = hexapodservice.msg.hexapodserviceActionFeedback()
    else:
      self.action_goal = hexapodservice.msg.hexapodserviceActionGoal()
      self.action_result = hexapodservice.msg.hexapodserviceActionResult()
      self.action_feedback = hexapodservice.msg.hexapodserviceActionFeedback()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs))
      _x = self.action_goal.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs))
      _x = self.action_goal.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_4i().pack(_x.action_goal.goal.MODE, _x.action_goal.goal.SIMPLEMOTION_MODE, _x.action_goal.goal.MAXPOINTS, _x.action_goal.goal.LEG_INDEX))
      length = len(self.action_goal.goal.ONELEG.coxa)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(struct.pack(pattern, *self.action_goal.goal.ONELEG.coxa))
      length = len(self.action_goal.goal.ONELEG.femur)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(struct.pack(pattern, *self.action_goal.goal.ONELEG.femur))
      length = len(self.action_goal.goal.ONELEG.tibia)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(struct.pack(pattern, *self.action_goal.goal.ONELEG.tibia))
      length = len(self.action_goal.goal.ONELEG.tarsus)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(struct.pack(pattern, *self.action_goal.goal.ONELEG.tarsus))
      for val1 in self.action_goal.goal.ALLLEGS.leg:
        length = len(val1.coxa)
        buff.write(_struct_I.pack(length))
        pattern = '<%sq'%length
        buff.write(struct.pack(pattern, *val1.coxa))
        length = len(val1.femur)
        buff.write(_struct_I.pack(length))
        pattern = '<%sq'%length
        buff.write(struct.pack(pattern, *val1.femur))
        length = len(val1.tibia)
        buff.write(_struct_I.pack(length))
        pattern = '<%sq'%length
        buff.write(struct.pack(pattern, *val1.tibia))
        length = len(val1.tarsus)
        buff.write(_struct_I.pack(length))
        pattern = '<%sq'%length
        buff.write(struct.pack(pattern, *val1.tarsus))
      _x = self
      buff.write(_get_struct_3I().pack(_x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs))
      _x = self.action_result.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs))
      _x = self.action_result.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_get_struct_B().pack(self.action_result.status.status))
      _x = self.action_result.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2iB().pack(_x.action_result.result.status, _x.action_result.result.freespace, _x.action_result.result.motionActive))
      _x = self.action_result.result.result
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_3I().pack(_x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs))
      _x = self.action_feedback.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs))
      _x = self.action_feedback.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_get_struct_B().pack(self.action_feedback.status.status))
      _x = self.action_feedback.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      for val1 in self.action_feedback.feedback.ALLLEGS_fdbk.leg:
        _x = val1
        buff.write(_get_struct_4d().pack(_x.coxa, _x.femur, _x.tibia, _x.tarsus))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.action_goal is None:
        self.action_goal = hexapodservice.msg.hexapodserviceActionGoal()
      if self.action_result is None:
        self.action_result = hexapodservice.msg.hexapodserviceActionResult()
      if self.action_feedback is None:
        self.action_feedback = hexapodservice.msg.hexapodserviceActionFeedback()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_goal.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_goal.goal_id.id = str[start:end]
      _x = self
      start = end
      end += 16
      (_x.action_goal.goal.MODE, _x.action_goal.goal.SIMPLEMOTION_MODE, _x.action_goal.goal.MAXPOINTS, _x.action_goal.goal.LEG_INDEX,) = _get_struct_4i().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.action_goal.goal.ONELEG.coxa = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.action_goal.goal.ONELEG.femur = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.action_goal.goal.ONELEG.tibia = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.action_goal.goal.ONELEG.tarsus = struct.unpack(pattern, str[start:end])
      self.action_goal.goal.ALLLEGS.leg = []
      for i in range(0, 6):
        val1 = hexapodservice.msg.legjoints()
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        pattern = '<%sq'%length
        start = end
        end += struct.calcsize(pattern)
        val1.coxa = struct.unpack(pattern, str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        pattern = '<%sq'%length
        start = end
        end += struct.calcsize(pattern)
        val1.femur = struct.unpack(pattern, str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        pattern = '<%sq'%length
        start = end
        end += struct.calcsize(pattern)
        val1.tibia = struct.unpack(pattern, str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        pattern = '<%sq'%length
        start = end
        end += struct.calcsize(pattern)
        val1.tarsus = struct.unpack(pattern, str[start:end])
        self.action_goal.goal.ALLLEGS.leg.append(val1)
      _x = self
      start = end
      end += 12
      (_x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_result.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_result.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_result.status.status,) = _get_struct_B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.text = str[start:end].decode('utf-8')
      else:
        self.action_result.status.text = str[start:end]
      _x = self
      start = end
      end += 9
      (_x.action_result.result.status, _x.action_result.result.freespace, _x.action_result.result.motionActive,) = _get_struct_2iB().unpack(str[start:end])
      self.action_result.result.motionActive = bool(self.action_result.result.motionActive)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.result.result = str[start:end].decode('utf-8')
      else:
        self.action_result.result.result = str[start:end]
      _x = self
      start = end
      end += 12
      (_x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_feedback.status.status,) = _get_struct_B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.text = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.text = str[start:end]
      self.action_feedback.feedback.ALLLEGS_fdbk.leg = []
      for i in range(0, 6):
        val1 = hexapodservice.msg.legjoint()
        _x = val1
        start = end
        end += 32
        (_x.coxa, _x.femur, _x.tibia, _x.tarsus,) = _get_struct_4d().unpack(str[start:end])
        self.action_feedback.feedback.ALLLEGS_fdbk.leg.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_3I().pack(_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs))
      _x = self.action_goal.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs))
      _x = self.action_goal.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_4i().pack(_x.action_goal.goal.MODE, _x.action_goal.goal.SIMPLEMOTION_MODE, _x.action_goal.goal.MAXPOINTS, _x.action_goal.goal.LEG_INDEX))
      length = len(self.action_goal.goal.ONELEG.coxa)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(self.action_goal.goal.ONELEG.coxa.tostring())
      length = len(self.action_goal.goal.ONELEG.femur)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(self.action_goal.goal.ONELEG.femur.tostring())
      length = len(self.action_goal.goal.ONELEG.tibia)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(self.action_goal.goal.ONELEG.tibia.tostring())
      length = len(self.action_goal.goal.ONELEG.tarsus)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(self.action_goal.goal.ONELEG.tarsus.tostring())
      for val1 in self.action_goal.goal.ALLLEGS.leg:
        length = len(val1.coxa)
        buff.write(_struct_I.pack(length))
        pattern = '<%sq'%length
        buff.write(val1.coxa.tostring())
        length = len(val1.femur)
        buff.write(_struct_I.pack(length))
        pattern = '<%sq'%length
        buff.write(val1.femur.tostring())
        length = len(val1.tibia)
        buff.write(_struct_I.pack(length))
        pattern = '<%sq'%length
        buff.write(val1.tibia.tostring())
        length = len(val1.tarsus)
        buff.write(_struct_I.pack(length))
        pattern = '<%sq'%length
        buff.write(val1.tarsus.tostring())
      _x = self
      buff.write(_get_struct_3I().pack(_x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs))
      _x = self.action_result.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs))
      _x = self.action_result.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_get_struct_B().pack(self.action_result.status.status))
      _x = self.action_result.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2iB().pack(_x.action_result.result.status, _x.action_result.result.freespace, _x.action_result.result.motionActive))
      _x = self.action_result.result.result
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_3I().pack(_x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs))
      _x = self.action_feedback.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_get_struct_2I().pack(_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs))
      _x = self.action_feedback.status.goal_id.id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_get_struct_B().pack(self.action_feedback.status.status))
      _x = self.action_feedback.status.text
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      for val1 in self.action_feedback.feedback.ALLLEGS_fdbk.leg:
        _x = val1
        buff.write(_get_struct_4d().pack(_x.coxa, _x.femur, _x.tibia, _x.tarsus))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.action_goal is None:
        self.action_goal = hexapodservice.msg.hexapodserviceActionGoal()
      if self.action_result is None:
        self.action_result = hexapodservice.msg.hexapodserviceActionResult()
      if self.action_feedback is None:
        self.action_feedback = hexapodservice.msg.hexapodserviceActionFeedback()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.action_goal.header.seq, _x.action_goal.header.stamp.secs, _x.action_goal.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_goal.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_goal.goal_id.stamp.secs, _x.action_goal.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_goal.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_goal.goal_id.id = str[start:end]
      _x = self
      start = end
      end += 16
      (_x.action_goal.goal.MODE, _x.action_goal.goal.SIMPLEMOTION_MODE, _x.action_goal.goal.MAXPOINTS, _x.action_goal.goal.LEG_INDEX,) = _get_struct_4i().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.action_goal.goal.ONELEG.coxa = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.action_goal.goal.ONELEG.femur = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.action_goal.goal.ONELEG.tibia = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.action_goal.goal.ONELEG.tarsus = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
      self.action_goal.goal.ALLLEGS.leg = []
      for i in range(0, 6):
        val1 = hexapodservice.msg.legjoints()
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        pattern = '<%sq'%length
        start = end
        end += struct.calcsize(pattern)
        val1.coxa = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        pattern = '<%sq'%length
        start = end
        end += struct.calcsize(pattern)
        val1.femur = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        pattern = '<%sq'%length
        start = end
        end += struct.calcsize(pattern)
        val1.tibia = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        pattern = '<%sq'%length
        start = end
        end += struct.calcsize(pattern)
        val1.tarsus = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
        self.action_goal.goal.ALLLEGS.leg.append(val1)
      _x = self
      start = end
      end += 12
      (_x.action_result.header.seq, _x.action_result.header.stamp.secs, _x.action_result.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_result.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_result.status.goal_id.stamp.secs, _x.action_result.status.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_result.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_result.status.status,) = _get_struct_B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.status.text = str[start:end].decode('utf-8')
      else:
        self.action_result.status.text = str[start:end]
      _x = self
      start = end
      end += 9
      (_x.action_result.result.status, _x.action_result.result.freespace, _x.action_result.result.motionActive,) = _get_struct_2iB().unpack(str[start:end])
      self.action_result.result.motionActive = bool(self.action_result.result.motionActive)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_result.result.result = str[start:end].decode('utf-8')
      else:
        self.action_result.result.result = str[start:end]
      _x = self
      start = end
      end += 12
      (_x.action_feedback.header.seq, _x.action_feedback.header.stamp.secs, _x.action_feedback.header.stamp.nsecs,) = _get_struct_3I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.action_feedback.status.goal_id.stamp.secs, _x.action_feedback.status.goal_id.stamp.nsecs,) = _get_struct_2I().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.goal_id.id = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.goal_id.id = str[start:end]
      start = end
      end += 1
      (self.action_feedback.status.status,) = _get_struct_B().unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.action_feedback.status.text = str[start:end].decode('utf-8')
      else:
        self.action_feedback.status.text = str[start:end]
      self.action_feedback.feedback.ALLLEGS_fdbk.leg = []
      for i in range(0, 6):
        val1 = hexapodservice.msg.legjoint()
        _x = val1
        start = end
        end += 32
        (_x.coxa, _x.femur, _x.tibia, _x.tarsus,) = _get_struct_4d().unpack(str[start:end])
        self.action_feedback.feedback.ALLLEGS_fdbk.leg.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_B = None
def _get_struct_B():
    global _struct_B
    if _struct_B is None:
        _struct_B = struct.Struct("<B")
    return _struct_B
_struct_3I = None
def _get_struct_3I():
    global _struct_3I
    if _struct_3I is None:
        _struct_3I = struct.Struct("<3I")
    return _struct_3I
_struct_4i = None
def _get_struct_4i():
    global _struct_4i
    if _struct_4i is None:
        _struct_4i = struct.Struct("<4i")
    return _struct_4i
_struct_4d = None
def _get_struct_4d():
    global _struct_4d
    if _struct_4d is None:
        _struct_4d = struct.Struct("<4d")
    return _struct_4d
_struct_2iB = None
def _get_struct_2iB():
    global _struct_2iB
    if _struct_2iB is None:
        _struct_2iB = struct.Struct("<2iB")
    return _struct_2iB
_struct_2I = None
def _get_struct_2I():
    global _struct_2I
    if _struct_2I is None:
        _struct_2I = struct.Struct("<2I")
    return _struct_2I
