.. default-domain:: cpp

.. cpp:namespace:: pessum

====
Data
====

The data handling aspect of Pessum is primarily used to save data that is
changed must be maintained external to the program, and when the program ends,
the data can be saved to a different file.

Functions
=========

Load
----

.. function:: std::vector\<DataPoint> Load(std::string file)

   ========  ==============================
   ``file``  Path to file to read data from
   ========  ==============================

   Reads data from a specified file, and returns a vector of the data in
   :class:`DataPoint`. The data will be converted into any basic types that it
   can be converted to (``int``, ``double``, ``bool``, ``std::string``).

   **Return:** Vector of :class:`DataPoint` containing information read
   from ``file``.

Save
----

.. function:: void Save(std::string file, std::vector\<DataPoint> data)

   ========  ============================
   ``file``  Path to file to save data to
   ``data``  Data to save to file
   ========  ============================

   Saves information from ``data`` to ``file``.
