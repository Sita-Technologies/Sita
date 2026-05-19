opensource Sita Team Decompiler
===============================

A decompiler for [opentext Gupta Team Developer](https://www.opentext.com/products-and-solutions/products/specialty-technologies/opentext-gupta-development-tools-databases/opentext-gupta-team-developer) applications. Reads compiled `.exe` programs and binary `.app` / `.apl` source files and writes back source-form SAL (`.apt`-shaped text, or reconstructed binary `.app` / `.apl`).

### Repository layout

```
.            Makefile, README.md, this file
src/         C++ sources, headers, COPYING (GPLv3) and generated SAL constant tables
build/       compile artifacts (.o, .d) and the final Sita binary (gitignored)
```

### Dependencies

Linux build:

- a C++ compiler with C++11 support — `g++` is used by default
- GNU `make`
- `iconv` — provided by glibc on Linux; on musl/Alpine install `libiconv-dev`

No third-party libraries beyond the C library. Windows-specific headers
(`windows.h`, `shlwapi.h`, `direct.h`, `malloc.h`) are guarded by
`_WIN32` / `_WIN64` macros and only pulled in when building on Windows.

### Building

From the repository root:

```
make
```

This produces `build/Sita`.

Useful overrides:

```
make CXX=clang++           # use a different compiler
make CXXFLAGS='-O0 -g'     # debug build
make -j                    # parallel build
make clean                 # remove build/
```

Alternatively, create a new Visual Studio C++ project and add the cpp source
and hpp/inc header files from `src/` to that project.

### Installing

```
make install                          # installs to /usr/local/bin (needs sudo)
make install PREFIX=$HOME/.local      # user-local install
make install DESTDIR=/tmp/stage       # stage into a packaging tree
make uninstall
```

### Usage

```
build/Sita [option [option [...]]] <input>
```

`<input>` is either a Team Developer compiled `.exe` or a `.app` / `.apl`
source file (Sita auto-detects by scanning for the `MGDR` magic).
Decompiled SAL source is written to stdout in `.apt`-shaped form: each
outline item carries a `.head <level> -  ` prefix, multi-line continuations
(Application Description body, multi-line SAL strings inside code) appear
as bare lines. The version banner goes to stderr so stdout is a clean text
stream.

Stdout encoding is UTF-8 with LF endings. To produce a TD-IDE-compatible
`.apt` file ready for Team Developer without further processing, use
`-t <file>` (Sita writes UTF-16LE + BOM + CRLF itself). Alternatively,
`iconv -f UTF-8 -t UTF-16LE` plus a leading `0xFF 0xFE` BOM converts the
stdout stream equivalently.

Options (output flags `-a` / `-t` / `-p` / `-P` are mutually exclusive):

| Flag                | What it does                                                                  |
|---------------------|-------------------------------------------------------------------------------|
| `-a <file>`         | Write a single reconstructed binary `.app` file. |
| `-t <file>`         | Write a single text `.apt` file directly in Team-Developer-ready encoding (UTF-16LE + BOM + CRLF). |
| `-p <dir>`          | **Project mode (binary)**: write `<dir>/<name>.app` (binary main with library content inlined alongside the `File Include:` directive) plus one `<dir>/<libname>.apl` per `File Include:` for source-style viewing/editing. Subdirectories named in includes are auto-created; library paths are validated against directory traversal (no `..`, no absolute paths, no drive letters). With no `-r`, embedded resources are also extracted into `<dir>`. |
| `-P <dir>`          | **Project mode (text)**: same split as `-p` but main is `<name>.apt`. All Sita-written `.apt`/`.apl` files are UTF-16LE + BOM + CRLF. |
| `-r <dir>`          | Dump every embedded resource (icons, bitmaps, RTF, …) into `<dir>` as raw files. May be used alongside any output flag, or alone to extract resources without decompilation. With `-p`/`-P` and no `-r`, resources are written into the project dir instead. Resource filenames embedded in the `.exe` are sanitized — unsafe names (`..`, absolute, drive letters) fall back to `resource_SSSSHHHH.bin`. |
| `-d <dir>`          | Debug: dump each tag-OSEG segment as `item_<id>.bin`. Useful for binary-level investigation; not for normal use. |
| `-v`                | Verbose / debug output: prepends item-id, type, and flag information to each line; also dumps full ItemBody contents in-line. The output is no longer a clean `.apt` stream in this mode. |
| `--`                | End of options; the next arg is the input filename even if it starts with `-`. |

Examples:

```
# Decompile a .exe to stdout in .apt-shaped UTF-8 text
build/Sita app.exe > app.apt.txt

# Single-file outputs (no library splitting)
build/Sita -a recompiled.app app.exe              # binary .app
build/Sita -t recompiled.apt app.exe              # text .apt (UTF-16+BOM+CRLF)

# Project mode: split out File Include: libraries into their own files
# (resources also land in the same directory unless -r overrides)
build/Sita -p decompiledProject app.exe           # binary main + .apl libs + resources
build/Sita -P decompiledProject app.exe           # text main + .apl libs + resources
ls decompiledProject/                             # → app.app + lib1.apl + close.bmp + ...

# Decompile a .app source file (Sita reads it natively — same flags work)
build/Sita some.app
build/Sita vtmisc.apl                             # binary .apl files are MGDR too

# Dump embedded resources for inspection (no decompilation)
build/Sita -r /tmp/resources app.exe

# Project + separate resource directory (-r overrides the project-dir default)
build/Sita -p decompiledProject -r decompiledProject/res app.exe

# Verbose mode for debugging which ItemBody types each item carries
build/Sita -v app.exe | less
```

Run `build/Sita` with no arguments to see the full usage hint.

### Project status

Experimental, in active development. Output quality is good enough that the
typical compiled program decompiles to readable, usable SAL source.

**Supported targets:**
- TD 5.1 – 7.5 input binaries (`.exe`) and source files (`.app` / `.apl`,
  binary MGDR or text `.apt` form)
- 32-bit applications are officially supported; 64-bit support is
  tested and largely working, with a few cosmetic differences vs the
  32-bit output still being chased

Larger productive applications still surface long-tail residuals.
