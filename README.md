# The Shard language library

This is the main library of the Shard language.

[![Contributors](https://img.shields.io/github/contributors/shard-lang/shard.svg?maxAge=3600)](https://github.com/shard-lang/shard/graphs/contributors)

[![license](https://img.shields.io/github/license/shard-lang/shard.svg?maxAge=3600)](https://github.com/shard-lang/shard/blob/master/LICENSE)

[![Build Status](https://travis-ci.org/shard-lang/shard.svg?branch=master)](https://travis-ci.org/shard-lang/shard)

[//]: #[![Downloads](https://img.shields.io/github/downloads/shard-lang/shard/total.svg?maxAge=60)]()

[![Issues](https://img.shields.io/github/issues-raw/shard-lang/shard.svg?maxAge=600)](https://github.com/shard-lang/shard/issues)
[![ClosedIssues](https://img.shields.io/github/issues-closed-raw/shard-lang/shard.svg?maxAge=600)](https://github.com/shard-lang/shard/issues?q=is%3Aissue+is%3Aclosed)


[//]: #[![PullRequests](https://img.shields.io/github/issues-pr-raw/shard-lang/shard.svg?maxAge=600)](https://github.com/shard-lang/shard/pulls)
[//]: #[![ClosedPullRequests](https://img.shields.io/github/issues-pr-closed-raw/shard-lang/shard.svg?maxAge=600)](https://github.com/shard-lang/shard/pulls?q=is%3Apr+is%3Aclosed)


[//]: #[![Release](https://img.shields.io/github/release/shard-lang/shard.svg?maxAge=3600)](https://github.com/shard-lang/shard/releases)
[//]: #[![CommitsSinceRelease](https://img.shields.io/github/commits-since/shard-lang/shard/0.svg?maxAge=600)]()

[//]: #[![Tag](https://img.shields.io/github/tag/shard-lang/shard.svg?maxAge=3600)](https://github.com/shard-lang/shard/tags)
[//]: #[![CommitsSinceTag](https://img.shields.io/github/commits-since/shard-lang/shard/0.svg?maxAge=600)]()

## Building from source

### Requirements

* CMake 3.8
* C++17 compiler

### Build

$ mkdir build && cd build
$ cmake ..
$ cmake --build .

### CMake options

* `SHARD_BUILD_AST` - Build AST part.
* `SHARD_BUILD_INTERPRETER` - Build language interpreter library.
* `SHARD_BUILD_PARSER` - Build parser.
* `SHARD_BUILD_TOKENIZER` - Build tokenizer.
* `SHARD_BUILD_TESTS` - Build unit tests.
* `SHARD_COVERAGE` - Enable code coverage analysis (requires `SHARD_BUILD_TESTS`).
* `SHARD_BUILD_TOOLS` - Build language tools.