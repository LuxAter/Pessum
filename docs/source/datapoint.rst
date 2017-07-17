.. default-domain:: cpp

.. cpp:namespace:: pessum

==========
Data Point
==========

The DataPoint class is a simple class that can contain a value for ``int``,
``double``, ``std::string``, or ``bool``. This is used for when the type of
the value is not known to the program. The type can then be determined through
the use of :member:`type`.

Enumerators
===========

PessumDataType
--------------

.. enum:: PessumDataType

   Used to define the type of a :class:`DataPoint`.

   =============  =
   PESSUM_NONE    0
   PESSUM_INT     1
   PESSUM_DOUBLE  2
   PESSUM_STR     3
   PESSUM_BOOL    4
   =============  =

Classes
=======

DataPoint
---------

.. class:: DataPoint

   Class structure to contain data of one of several different base types. The
   data in a :class:`DataPoint` class can be ``int``, ``double``,
   ``std::string``, or ``bool``.

   .. code-block:: c++

    class DataPoint{
     public:
      explicit DataPoint();
      explicit DataPoint(int value);
      explicit DataPoint(double value);
      explicit DataPoint(std::string value);
      explicit DataPoint(const char* value);
      explicit DataPoint(bool value);

      void operator=(int value);
      void operator=(double value);
      void operator=(std::string value);
      void operator=(const char* value);
      void operator=(bool value);

      operator int();
      operator double();
      operator std::string();
      operator bool();

      int int_value, type;
      double double_value;
      std::string string_value;
      bool bool_value;
    };

Constructors
~~~~~~~~~~~~

DataPoint(void)
+++++++++++++++

.. function:: DataPoint::DataPoint()

   Default constructor, sets all values to default, and :member:`type` to
   ``PESSUM_NONE``.

DataPoint(int)
++++++++++++++

.. function:: DataPoint::DataPoint(int value)

   =========  =================================
   ``value``  Integer value to use as set value
   =========  =================================

   Constructor that sets the :member:`type` to ``PESSUM_INT``, and sets
   :member:`int_value` to ``value``.

DataPoint(double)
+++++++++++++++++

.. function:: DataPoint::DataPoint(double value)

   =========  ================================
   ``value``  Double value to use as set value
   =========  ================================

   Constructor that sets the :member:`type` to ``PESSUM_DOUBLE``, and sets
   :member:`double_value` to ``value``.

DataPoint(std::string)
++++++++++++++++++++++

.. function:: DataPoint::DataPoint(std::string value)

   =========  ================================
   ``value``  String value to use as set value
   =========  ================================

   Constructor that sets the :member:`type` to ``PESSUM_STR``, and sets
   :member:`string_value` to ``value``.

DataPoint(const char*)
++++++++++++++++++++++

.. function:: DataPoint::DataPoint(const char* value)

   =========  ================================
   ``value``  String value to use as set value
   =========  ================================

   Constructor that sets the :member:`type` to ``PESSUM_STR``, and sets
   :member:`string_value` to ``value``.

DataPoint(bool)
+++++++++++++++

.. function:: DataPoint::DataPoint(bool value)

   =========  =================================
   ``value``  Boolian value to use as set value
   =========  =================================

   Constructor that sets the :member:`type` to ``PESSUM_BOOL``, and sets
   :member:`bool_value` to ``value``.

Operators
~~~~~~~~~

operator=(int)
++++++++++++++

.. function:: DataPoint::operator=(int value)

   =========  ===============================
   ``value``  Double vlue to use as set value
   =========  ===============================

   Operator that sets the :member:`type` to ``PESSUM_INT``, and sets
   :member:`int_value` to ``value``.

operator=(double)
+++++++++++++++++

.. function:: DataPoint::operator=(double value)

   =========  ===============================
   ``value``  Double vlue to use as set value
   =========  ===============================

   Operator that sets the :member:`type` to ``PESSUM_DOUBLE``, and sets
   :member:`double_value` to ``value``.

operator=(std::string)
++++++++++++++++++++++

.. function:: DataPoint::operator=(std::string value)

   =========  ===============================
   ``value``  Double vlue to use as set value
   =========  ===============================

   Operator that sets the :member:`type` to ``PESSUM_STR``, and sets
   :member:`string_value` to ``value``.

operator=(const char*)
++++++++++++++++++++++

.. function:: DataPoint::operator=(const char* value)

   =========  ===============================
   ``value``  Double vlue to use as set value
   =========  ===============================

   Operator that sets the :member:`type` to ``PESSUM_STR``, and sets
   :member:`string_value` to ``value``.

operator=(bool)
+++++++++++++++

.. function:: DataPoint::operator=(bool value)

   =========  ===============================
   ``value``  Double vlue to use as set value
   =========  ===============================

   Operator that sets the :member:`type` to ``PESSUM_BOOL``, and sets
   :member:`bool_value` to ``value``.

operator int()
+++++++++++++++++++++++++

.. function:: DataPoint::operator int()

   **Return:** :member:`int_value`

operator double()
++++++++++++++++++++++++++++

.. function:: DataPoint::operator double()

   **Return:** :member:`double_value`

operator std::string()
+++++++++++++++++++++++++++++++++

.. function:: DataPoint::operator std::string()

   **Return:** :member:`string_value`

operator bool()
++++++++++++++++++++++++++

.. function:: DataPoint::operator bool()

   **Return:** :member:`bool_value`

Functions
=========

Make_DataPoint
--------------

.. function:: DataPoint Make_DataPoint(std::string str)

   =======  =======================================
   ``str``  String to convert to :class:`DataPoint`
   =======  =======================================

   This function takes a string, and reads it. If the string can be converted
   into some other type (``int``, ``double``, or ``bool``), it is converted.
   Then everything is saved into a :class:`DataPoint`.

   **Return:** :class:`DataPoint` containing the reducd type of the string data.
