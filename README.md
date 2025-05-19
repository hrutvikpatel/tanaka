![CI](https://github.com/hrutvikpatel/tanaka/actions/workflows/ci.yml/badge.svg)

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
ctest --output-on-failure
```
