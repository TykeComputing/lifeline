Lifeline (WORKING TITLE)
=============

Synopsis
-------------
Lifeline will be a 2D game/engine. What exactly the game will be is undecided at this point.

Goals
-------------
1. Gain experience in subjects I haven't gotten to spend much time on in [the other projects I've worked on](http://www.peterclark.net).
2. Practice game development, with an emphasis on rapidly iterating and building only what is needed when it is needed.
3. (Stretch) Create a game that I would want to play and ship it.

Setup Build Environment
-------------
If this project gets significantly far such that it is justified I should document build setup for each platform in detail here.

If working on Windows you can checkout [lifeline-external-dependencies](https://github.com/peter-clark/lifeline-external-dependencies), it has all required 3rd party libraries and headers. CMake will look for this in `${LE_EXTERNAL_DEPEND_DIR}` which by default is `<REPO_ROOT>/external`.

Otherwise you can manually configure in the CMake cache where each library is located. 

Setup Run Environment
-------------
On supported IDEs with `${LE_RUN_WRITE_SETTINGS_FILE}` enabled you can set a few runtime environment options to life a little easier. See `${LE_RUN_WRITE_SETTINGS_FILE}` documentation for supported IDEs.
- `${LE_RUN_WORKING_DIR}`: The working directory to run the application from.
- `${LE_RUN_COMMAND_LINE_ARGS}`: Command line arguments to be passed to the program when run from IDE.
- `${LE_RUN_COPY_EXTERNAL_DLLS_TO_WORKING_DIR}` (Windows only): If `ON`, all needed DLLs will be copied to `${LE_RUN_WORKING_DIR}` at configure time.
- Other settings may be enabled in the future. See all variables named `LE_RUN_*` in the CMake cache for a full list of options.

Related Links
-------------
[Trello Board](https://trello.com/b/INfwr8jl/lifeline)
[lifeline-resources](https://github.com/peter-clark/lifeline-resources)
