if(NOT LIBPERSEUS_FOUND)

  pkg_check_modules (LIBPERSEUS_PKG libperseus)
  find_path(LIBPERSEUS_INCLUDE_DIR NAMES perseus-sdr.h
    PATHS
    ${LIBPERSEUS_PKG_INCLUDE_DIRS}
    /usr/include
    /usr/local/include
  )

  find_library(LIBPERSEUS_LIBRARIES NAMES perseus-sdr
    PATHS
    ${LIBPERSEUS_PKG_LIBRARY_DIRS}
    /usr/lib
    /usr/local/lib
  )

  if(LIBPERSEUS_INCLUDE_DIR AND LIBPERSEUS_LIBRARIES)
    set(LIBPERSEUS_FOUND TRUE CACHE INTERNAL "libperseus found")
    message(STATUS "Found libperseus: ${LIBPERSEUS_INCLUDE_DIR}, ${LIBPERSEUS_LIBRARIES}")
  else(LIBPERSEUS_INCLUDE_DIR AND LIBPERSEUS_LIBRARIES)
    set(LIBPERSEUS_FOUND FALSE CACHE INTERNAL "libperseus found")
    message(STATUS "libperseus not found.")
  endif(LIBPERSEUS_INCLUDE_DIR AND LIBPERSEUS_LIBRARIES)

  mark_as_advanced(LIBPERSEUS_INCLUDE_DIR LIBPERSEUS_LIBRARIES)

endif(NOT LIBPERSEUS_FOUND)
