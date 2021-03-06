# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from hexapodservice/hexapodserviceGoal.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import hexapodservice.msg

class hexapodserviceGoal(genpy.Message):
  _md5sum = "31dfab14f36d4b9186c0a13e789e9115"
  _type = "hexapodservice/hexapodserviceGoal"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
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
"""
  __slots__ = ['MODE','SIMPLEMOTION_MODE','MAXPOINTS','LEG_INDEX','ONELEG','ALLLEGS']
  _slot_types = ['int32','int32','int32','int32','hexapodservice/legjoints','hexapodservice/legs']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       MODE,SIMPLEMOTION_MODE,MAXPOINTS,LEG_INDEX,ONELEG,ALLLEGS

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(hexapodserviceGoal, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.MODE is None:
        self.MODE = 0
      if self.SIMPLEMOTION_MODE is None:
        self.SIMPLEMOTION_MODE = 0
      if self.MAXPOINTS is None:
        self.MAXPOINTS = 0
      if self.LEG_INDEX is None:
        self.LEG_INDEX = 0
      if self.ONELEG is None:
        self.ONELEG = hexapodservice.msg.legjoints()
      if self.ALLLEGS is None:
        self.ALLLEGS = hexapodservice.msg.legs()
    else:
      self.MODE = 0
      self.SIMPLEMOTION_MODE = 0
      self.MAXPOINTS = 0
      self.LEG_INDEX = 0
      self.ONELEG = hexapodservice.msg.legjoints()
      self.ALLLEGS = hexapodservice.msg.legs()

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
      buff.write(_struct_4i.pack(_x.MODE, _x.SIMPLEMOTION_MODE, _x.MAXPOINTS, _x.LEG_INDEX))
      length = len(self.ONELEG.coxa)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(struct.pack(pattern, *self.ONELEG.coxa))
      length = len(self.ONELEG.femur)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(struct.pack(pattern, *self.ONELEG.femur))
      length = len(self.ONELEG.tibia)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(struct.pack(pattern, *self.ONELEG.tibia))
      length = len(self.ONELEG.tarsus)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(struct.pack(pattern, *self.ONELEG.tarsus))
      for val1 in self.ALLLEGS.leg:
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
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.ONELEG is None:
        self.ONELEG = hexapodservice.msg.legjoints()
      if self.ALLLEGS is None:
        self.ALLLEGS = hexapodservice.msg.legs()
      end = 0
      _x = self
      start = end
      end += 16
      (_x.MODE, _x.SIMPLEMOTION_MODE, _x.MAXPOINTS, _x.LEG_INDEX,) = _struct_4i.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.ONELEG.coxa = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.ONELEG.femur = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.ONELEG.tibia = struct.unpack(pattern, str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.ONELEG.tarsus = struct.unpack(pattern, str[start:end])
      self.ALLLEGS.leg = []
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
        self.ALLLEGS.leg.append(val1)
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
      buff.write(_struct_4i.pack(_x.MODE, _x.SIMPLEMOTION_MODE, _x.MAXPOINTS, _x.LEG_INDEX))
      length = len(self.ONELEG.coxa)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(self.ONELEG.coxa.tostring())
      length = len(self.ONELEG.femur)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(self.ONELEG.femur.tostring())
      length = len(self.ONELEG.tibia)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(self.ONELEG.tibia.tostring())
      length = len(self.ONELEG.tarsus)
      buff.write(_struct_I.pack(length))
      pattern = '<%sq'%length
      buff.write(self.ONELEG.tarsus.tostring())
      for val1 in self.ALLLEGS.leg:
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
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.ONELEG is None:
        self.ONELEG = hexapodservice.msg.legjoints()
      if self.ALLLEGS is None:
        self.ALLLEGS = hexapodservice.msg.legs()
      end = 0
      _x = self
      start = end
      end += 16
      (_x.MODE, _x.SIMPLEMOTION_MODE, _x.MAXPOINTS, _x.LEG_INDEX,) = _struct_4i.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.ONELEG.coxa = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.ONELEG.femur = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.ONELEG.tibia = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      pattern = '<%sq'%length
      start = end
      end += struct.calcsize(pattern)
      self.ONELEG.tarsus = numpy.frombuffer(str[start:end], dtype=numpy.int64, count=length)
      self.ALLLEGS.leg = []
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
        self.ALLLEGS.leg.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_4i = struct.Struct("<4i")
