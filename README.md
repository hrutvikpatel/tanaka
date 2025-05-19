# tanaka
Background daemon to backup your files to a cloud provider


Purpose
config/
Load/save daemon config (S3/Spaces choice, watched paths)
cli/
Code for CLI commands (e.g. add, remove, status)
core/
Main daemon logic (startup, loop, scheduling)
db/
Abstracts interaction with SQLite (sync state, queue)
storage/
Upload code for S3 and Spaces + file compression logic
watcher/
Handles inotify or FSEvents/etc. to watch files
utils/
Generic utilities: logging, hashing (SHA256, etc.)
data/
Stores runtime data: config file, local DB, state files
main.cpp
Initializes and runs the daemon (calls into core)



```mermaid
graph TD
    A[Daemon starts on boot] --> B[Load Config]
    B -->|If config missing| C[Wait for user to run CLI]
    C --> D[User sets config with cloud provider and paths to sync]
    D --> E[Daemon restarts with new config]
    
    B --> F[Connect to SQLite DB]
    F --> G[Check upload queue]
    F --> H[List root paths]
    F --> I[Get sync status]
    F --> J[Add file hash]
    F --> K[Add new root path]

    A --> L[Watch root paths for changes]
    L --> M[File added or changed]
    M --> N[Check file type]
    N -->|If compressible| O[Compress file]
    N -->|If video| P[Skip compression]

    O --> Q[Upload to S3 / Spaces]
    P --> Q

    Q --> R[Update SQLite: mark as synced]

    C -.-> CLI[User CLI Tool]
    D -.-> CLI
```


To Build
```
rm -rf build
cmake -B build -S . -DBUILD_TESTING=OFF
cmake --build build
```

To Test
```
rm -rf build
cmake -B build -S . -DBUILD_TESTING=ON
cmake --build build
ctest --output-on-failure
```
