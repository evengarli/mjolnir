# MJOLNIR 🔨

A simple TCP port scanner written in C++.

## What it does

Mjolnir scans for open ports on a target IP address or hostname. It can scan custom port ranges or quickly check common ports.

## Installation

```bash
git clone https://github.com/evengarli/mjolnir.git
cd mjolnir
chmod +x install.sh
```

## Usage

### Basic Commands

**Scan a port range:**
```bash
./mjolnir -ip 192.168.1.1 -pR 1-1000
```

**Fast scan (common ports only):**
```bash
./mjolnir -ip google.com -f
```

**Save results to a file:**
```bash
./mjolnir -ip 192.168.1.1 -pR 80-443 -o results
```

### Options
- `-ip <address>` - Target IP or hostname
- `-pR <start-end>` - Port range (e.g., 1-1000)
- `-f` - Fast scan mode
- `-o <filename>` - Save to file
- `-h` - Help

## Example Output

```
------------------------------------------------------
Scanning 192.168.1.1 from port 1 to port 1000
------------------------------------------------------
22      OPEN
80      OPEN
443     OPEN
```

## Important

Only use this tool on networks and systems you own or have permission to test. Unauthorized scanning may be illegal.

## License

MIT License
