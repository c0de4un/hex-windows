# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# CONSTANTS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( HEX_WIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/windows" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# HEADERS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( HEX_WIN_PUBLIC "${HEX_WIN_DIR}/public/hex/windows/" )
set( HEX_WIN_HEADERS
    ""
)

# DEBUG
if ( HEX_DEBUG OR HEX_LOGGING )
    set( HEX_WIN_HEADERS
        # METRICS
        "${HEX_WIN_PUBLIC}metrics/WinConsoleLogger.hpp"
        ${HEX_WIN_HEADERS}
    )
endif ( HEX_DEBUG OR HEX_LOGGING )

# Append to Exportable Headers
set( HEX_EXPORT_HEADERS ${HEX_WIN_HEADERS} ${HEX_EXPORT_HEADERS} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# SOURCES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( HEX_WIN_PRIVATE "${HEX_WIN_DIR}/private/hex/windows/" )
set( HEX_WIN_SOURCES
    ""
)

# DEBUG
if ( HEX_DEBUG OR HEX_LOGGING )
    set( HEX_WIN_SOURCES
        # METRICS
        "${HEX_WIN_PRIVATE}metrics/WinConsoleLogger.cpp"
        ${HEX_WIN_HEADERS}
    )
endif ( HEX_DEBUG OR HEX_LOGGING )

# Append to Exportable Sources
set( HEX_EXPORT_SOURCES ${HEX_WIN_SOURCES} ${HEX_EXPORT_SOURCES} )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
