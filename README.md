Lifeline (WORKING TITLE)
=============

Synopsis
-------------
Lifeline will be a 2D game.

**UNDER CONSTRUCTION: The below is currently intended for internal only**

Setup Build Environment
-------------
If this project gets significantly far such that it is justified I should document build setup for each platform in detail here.

Setup Run Environment
-------------
Using VS2013 with `${LE_RUN_WRITE_SETTINGS_FILE}` enabled you can set a few runtime environment options to make life a little easier.
- `${LE_RUN_WORKING_DIR}`: The working directory to run the application from.
- `${LE_RUN_COMMAND_LINE_ARGS}`: Command line arguments to be passed to the program when run from IDE.
- `${LE_RUN_COPY_EXTERNAL_DLLS_TO_WORKING_DIR}` (Windows only): If `ON`, all needed DLLs will be copied to `${LE_RUN_WORKING_DIR}` at configure time.
- Other settings may be enabled in the future. See all variables named `LE_RUN_*` in the CMake cache for a full list of options.

On other IDEs you'll need to manually do two things:
- Set the working directory to the same directory as `${LE_RUN_WORKING_DIR}`. Note that on Windows DLL files will be copied to this directory, so you may not want it to be the root directory.
- Add `--resource-dir="SOURCE_DIR\resources"` where `SOURCE_DIR` is the root directory of the repository (where the sub-module lifeline-resources is located in the folder resources). If you do not specify this the only way the program will run is if the working directory is set to `SOURCE_DIR` (then the default resource dir `"/resources"` will be used).
