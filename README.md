![BUILD](https://github.com/hrutvikpatel/tanaka/actions/workflows/ci.yml/badge.svg)

# Tanaka

**Tanaka** is a C++ daemon/CLI tool for working with cloud storage providers. It supports configurable providers like **DigitalOcean Spaces**, with pluggable configuration and rotating file-based logging.

---

## 📦 Configuration

Before running Tanaka, create a config file:

```bash
mkdir ~/.config/tanaka && touch ~/.config/tanaka/config.toml
```

### Example contents of config.toml

```toml
[provider]
active = "DigitalOcean Spaces"

["DigitalOcean Spaces"]
token = "abc123"
region = "nyc3"
bucket = "my-bucket"
```


To Build (without tests)
```bash
rm -rf build
cmake -B build -S . -DBUILD_TESTING=OFF
cmake --build build
```

To Test
```bash
rm -rf build
cmake -B build -S . -DBUILD_TESTING=ON
cmake --build build
ctest --output-on-failure --test-dir
```

```mermiad
graph TD
  %% CLI and Daemon Interaction
  subgraph CLI/Daemon
    UserInput["User Input / CLI"]
    SyncDaemon["SyncDaemon (background thread)"]
  end

  %% Service Layer
  subgraph Service Layer
    TrackedFolderService["TrackedFolderService"]
    FilesToUploadService["FilesToUploadService"]
    UploadService["UploadService"]
    CompressionService["CompressionService"]
    ConfigLoader["Config (TOML Loader)"]
    DeleteFolderService["DeleteFolderService (Soft Delete + Stop Sync)"]
    CloudDeleteService["CloudDeleteService (Permanent Removal)"]
  end

  %% DAO Layer
  subgraph DAO Layer
    TrackedFolderDao["TrackedFolderDao"]
    FilesToUploadDao["FilesToUploadDao"]
  end

  %% Provider Interface
  subgraph Providers
    ProviderInterface["IProvider (interface)"]
    DigitalOcean["DigitalOceanSpacesProvider"]
    S3["S3Provider (future)"]
  end

  %% Storage
  subgraph Storage
    SQLiteDB["SQLite Database"]
  end

  %% Config Interaction
  UserInput --> ConfigLoader
  ConfigLoader --> ProviderInterface

  %% Folder tracking flow
  UserInput --> TrackedFolderService
  TrackedFolderService --> TrackedFolderDao
  TrackedFolderDao --> SQLiteDB

  %% Files-to-upload flow
  SyncDaemon --> FilesToUploadService
  FilesToUploadService --> FilesToUploadDao
  FilesToUploadDao --> SQLiteDB

  %% Upload flow
  SyncDaemon --> UploadService
  UploadService --> FilesToUploadService
  UploadService --> CompressionService
  UploadService --> ProviderInterface

  %% Delete/Stop Sync Flow
  UserInput --> DeleteFolderService
  DeleteFolderService --> TrackedFolderService
  DeleteFolderService --> CloudDeleteService
  CloudDeleteService --> ProviderInterface

  %% Provider Extensions
  ProviderInterface --> DigitalOcean
  ProviderInterface --> S3
```
