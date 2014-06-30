################################################################################################
# Copyright 2014 by Peter Clark. All Rights Reserved.
################################################################################################`

function(setup_external_dependencies_runtime)
  if("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")

    option(LE_RUN_COPY_EXTERNAL_DLLS_TO_WORKING_DIR
      "Copy external dependency DLLs to the working directory upon configuration." 
      ON)

    if(LE_RUN_COPY_EXTERNAL_DLLS_TO_WORKING_DIR)
      message(STATUS "Copying all external DLLs from ${LE_EXTERNAL_DLL_DIR}/ to ${LE_RUN_WORKING_DIR}/...")

      file(GLOB EXTERNAL_DLL_COPY_LIST "${LE_EXTERNAL_DLL_DIR}/*.DLL")
      if(EXTERNAL_DLL_COPY_LIST)
        foreach(DLL_IT ${EXTERNAL_DLL_COPY_LIST})

          message(STATUS "  Copying ${DLL_IT}...")      
        endforeach()

        file(COPY ${EXTERNAL_DLL_COPY_LIST} DESTINATION "${LE_RUN_WORKING_DIR}")    
      else()
        message(STATUS "  Nothing to copy - no external DLLs found...")
      endif()

      unset(EXTERNAL_DLL_COPY_LIST)
    endif()
  endif()
endfunction()