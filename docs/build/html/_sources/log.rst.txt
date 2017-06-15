.. default-domain:: cpp

.. cpp:namespace:: pessum

=======
Logging
=======

The logging functionality of Pessum, is very simple. It permits logs entries to
be added to a set of global log entries for that occurance of the program. These
log entries can then be handled by provided functions when they are added, or
they can be retreaved later with one of several log retreval functions. The
entire list of log entries can also be saved to an external file for review
after program termination.

Enumerators
===========

LogType
-------

.. enum:: LogType

   Used to define the type/importance of the log call.

   =======  =
   ERROR    0
   WARNING  1
   TRACE    2
   DEBUG    3
   SUCCESS  4
   INFO     5
   DATA     6
   NONE     7
   =======  =

LogOptions
----------

.. enum:: LogOptions
  
   Used to specify a logging option to set using :func:`SetLogOption`.

   ==========  =
   TIME_STAMP  0
   DATE_STAMP  1
   ==========  =

Functions
=========

Log
---

.. function:: void Log(int type, std::string msg, std::string func, ...)

   ========  ===============================================
   ``type``  Type of log entry from :enum:`LogType`
   ``msg``   Format string of log entry
   ``func``  The name of the function creating the log entry
   ``...``   Additional formating args for ``msg``
   ========  ===============================================

   Core function for all logging output, ``msg`` is a format string with
   additional arguments as needed from ``...``. Formated string and log type
   are saved to :var:`global_logs`.

GetLog
------

GetLog
~~~~~~

.. function:: std::string GetLog(int type)

   ========  ==========================================
   ``type``  The type of log entry to find and retrieve
   ========  ==========================================

   Gets last log entry of specified type with formated string.

   **Return:** Formated string of log entry.

FGetLog
~~~~~~~

.. function:: std::pair\<int, std::string> FGetLog(int type)

   ========  ==========================================
   ``type``  The type of log entry to find and retrieve
   ========  ==========================================

   Gets last log entry of specified type with log type and formated string.

   **Return:** Pair of log type and formated string of log entry.

IGetLog
~~~~~~~

.. function:: std::string IGetLog(int index)

   =========  ==================================================
   ``index``  The index of the log entry from :var:`global_logs`
   =========  ==================================================

   Gets log entry of specified index with formated string.

   **Return:** Formated string of log entry.

IFGetLog
~~~~~~~~

.. function:: std::string IFGetLog(int index)

   =========  ==================================================
   ``index``  The index of the log entry from :var:`global_logs`
   =========  ==================================================

   Gets log entry of specified index with log type formated string.

   **Return:** Pair of log type and formated string of log entry.

VGetLog
~~~~~~~

.. function:: std::vector\<std::string> VGetLog(int start, int end)

   =========  =============================================
   ``start``  The first index value from :var:`global_logs`
   ``end``    The last index value from :var:`global_logs`
   =========  =============================================

   Get a set of log entries between (inclusive) specified start and end index
   with formated string.

   **Return:** Vector of strings of log entries.

VFGetLog
~~~~~~~~

.. function:: std::vector\<std::string> VFGetLog(int start, int end)

   =========  =============================================
   ``start``  The first index value from :var:`global_logs`
   ``end``    The last index value from :var:`global_logs`
   =========  =============================================

   Get a set of log entries between (inclusive) specified start and end index
   with log type and formated string.

   **Return:** Vector of pairs of log type and formated stirng of log entry.

Set Log Options
---------------

SetLogHandle[1/2]
~~~~~~~~~~~~~~~~~

.. function:: void SetLogHandle(void(*handle)(std::pair\<int, std::string>))

   ==========  ============================================================================
   ``handle``  Pointer to function with return of void and args of a pair of int and string
   ==========  ============================================================================

   Sets :var:`log_handle_full` to given pointer.

SetLogHandle[2/2]
~~~~~~~~~~~~~~~~~

.. function:: void SetLogHandle(void(*handle)(std::string))

   ==========  ============================================================
   ``handle``  Pointer to function with return of void and args of a string
   ==========  ============================================================

   Sets :var:`log_handle` to given pointer.

SetLogOption
~~~~~~~~~~~~

.. function:: void SetLogOption(int option, int setting)

   ===========  ========================================
   ``option``   Value for option from :enum:`LogOptions`
   ``setting``  Value to set for ``option``
   ===========  ========================================

   Sets ``option`` of :var:`options` to ``setting``.

GetTypeStr
----------

.. function:: std::string GetTypeStr(int type)

   ========  ==============================================
   ``type``  Type from :enum:`LogType` to convert to string
   ========  ==============================================

   Determines that string corisponding to ``type`` value.

   **Return:** String corisponding to ``type`` value.

SaveLog
-------

.. function:: void SaveLog(std::string file)

   ========  ==========================
   ``file``  Path to file save log into
   ========  ==========================

   Saves the log entries from :var:`global_logs` to specified file.

Variables
=========

options
-------

.. var:: extern std::array<int, 2> options

   Array storing values for the different log options set in :func:`SetLogOption`.

global_logs
-----------

.. var:: extern std::vector\<std::pair\<int, std::string>> global_logs

   All log calls are saved to this vector, and can be retrieved later with any
   form of the :func:`GetLog` functions.

log_handle_full
---------------

.. var:: extern void (*log_handle_full)(std::pair\<int,std::string>)

   Pointer to function for handling log calls with full log information.
   This function is called with every log entry added through :func:`Log`.

log_handle
----------

.. var:: extern void (*log_handle)(std::string)

   Pointer to function for handling logs with only formated string
   This funtion is called with every log entry added through :func:`Log`.
